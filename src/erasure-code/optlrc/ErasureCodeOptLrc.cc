#include <errno.h>
#include <algorithm>

#include "ErasureCodeOptLrc.h"
#include "ErasureCodeOptLrc_configs.h"
#include "include/str_map.h"
#include "common/debug.h"
#include "crush/CrushWrapper.h"
#include "osd/osd_types.h"
#include "include/stringify.h"
#include "erasure-code/ErasureCodePlugin.h"
#include "json_spirit/json_spirit_writer.h"
#include "include/assert.h"

extern "C" {
#include "jerasure.h"
#include "reed_sol.h"
#include "galois.h"
#include "liberation.h"
}

#define dout_subsys ceph_subsys_osd
#undef dout_prefix
#define dout_prefix _prefix(_dout)
#define BASIC_BLOCK_SIZE 67108864

OptLRC_Configs optlrc_configs;
POptLRC pOptLRC_G = optlrc_configs.configs[ErasureCodeOptLrc::n][ErasureCodeOptLrc::k][ErasureCodeOptLrc::r];
inline unsigned int get_alignment()
{
    return BASIC_BLOCK_SIZE;
}

inline unsigned int get_chunk_size(unsigned int object_size)
{
    unsigned int alignment = get_alignment();
    unsigned int data_chunk_count = ErasureCodeOptLrc::k;
    unsigned int chunk_size = (object_size + data_chunk_count - 1) / data_chunk_count;
    unsigned int modulo = chunk_size % alignment;
    if (modulo) {
        chunk_size += alignment - modulo;
    }
    return chunk_size;
}
/*
unsigned int ErasureCodeOptLrc::get_chunk_size(unsigned int object_size) const
{
  unsigned alignment = get_alignment();
  if (per_chunk_alignment) {
    unsigned chunk_size = object_size / k;
    if (object_size % k)
      chunk_size++;
    dout(20) << "get_chunk_size: chunk_size " << chunk_size
	     << " must be modulo " << alignment << dendl; 
    assert(alignment <= chunk_size);
    unsigned modulo = chunk_size % alignment;
    if (modulo) {
      dout(10) << "get_chunk_size: " << chunk_size
	       << " padded to " << chunk_size + alignment - modulo << dendl;
      chunk_size += alignment - modulo;
    }
    return chunk_size;
  } else {
    unsigned tail = object_size % alignment;
    unsigned padded_length = object_size + ( tail ?  ( alignment - tail ) : 0 );
    assert(padded_length % k == 0);
    return padded_length / k;
  }
}*/

  inline unsigned int get_chunk_count() {
    return ErasureCodeOptLrc::n;
  }

  inline unsigned int get_data_chunk_count() {
    return ErasureCodeOptLrc::k;
  }
int ErasureCodeOptLrc::encode_chunks(const set<int> &want_to_encode,
				       map<int, bufferlist> *encoded)
{
  char *chunks[n];
  for (int i = 0; i < n; i++)
    chunks[i] = (*encoded)[i].c_str();
  optlrc_encode(want_to_encode, &chunks[0], &chunks[k], (*encoded->begin()).second.length());
  return 0;
}

void ErasureCodeOptLrc::optlrc_encode(const set<int> &want_to_encode, char **data, char **coding, int blocksize)
{
	// TODO select correct group, local can be done with want_to_encode/r
	unsigned int group = 0;
	set<int> data_chunks;
	
	if (want_to_encode.size() == 1) {
		unsigned int erased = *(want_to_encode.begin());
		for (int i=0; i<k; i++) {
			if (pOptLRC_G->optlrc_matrix[erased][i] != 0)
				data_chunks.insert(i);
		}
	}
	else {
		for (int i=0; i<k; i++)
			data_chunks.insert(i);
	}
	int optlrc_encode_local[k][n];
    //vector<int> init_rows(row_count);
	int i=0;
	for (set<int>::iterator it = data_chunks.begin(); it != data_chunks.end(); ++it)
	{
		for (int j=0; j<k; j++) {
			optlrc_encode_local[i][j] = pOptLRC_G->optlrc_matrix[(r+1)*group+j][*it];
			i++;
			//think how to multiply only partial data bus
		}
	}
	//for (i=0; i<k; i++)
	//TODO: adjust for arbitrary code length
	char *dst = coding[0];	
	for (i=0 ; i<k; i++) { 
		char *src = data[0] + i*blocksize;
		galois_w08_region_multiply(src,
		                optlrc_encode_local[n][i],
		                blocksize,
		                dst,
		                1);
	}		
}
    /*for (unsigned int chunk_index = 0; chunk_index < data_chunk_count; chunk_index++) {
        for (unsigned int row_index = 0; row_index < row_count; row_index++) {
            char *dst = chunks[get_optlrc_chunk_index() + optlrc_chunk] + (row_index * row_of_chunk_size);
            unsigned int optlrc_index = poptlrc_G->optlrc_encode[optlrc_chunk][row_index][chunk_index];
            assert(optlrc_index >= 0 && optlrc_index < row_count);
            char *src = chunks[chunk_index] + (optlrc_index * row_of_chunk_size);
            if (zero_elements[chunk_index][optlrc_index] == true) {
                continue;
            }
            galois_multiply(src,
                            poptlrc_G->optlrc_coeff[optlrc_chunk][row_index][chunk_index],
                            row_of_chunk_size,
                            dst,
                            init_rows[row_index]);
            init_rows[row_index] = 1;*/



						   


int ErasureCodeOptLrc::decode_chunks(const set<int> &want_to_read,
				       const map<int, bufferlist> &chunks,
				       map<int, bufferlist> *decoded)
{
	int blocksize = (*chunks.begin()).second.length();
	//int erasures[n];
	int erasures_count = 0;
	char *data[k];
	char *coding[n-k];
	// TODO select correct group, local can be done with want_to_encode/r
	unsigned int group = 0;
	set<int> decode_chunks;	
	
  for (int i =  0; i < n; i++) {
    if (chunks.find(i) == chunks.end()) {
      //erasures[erasures_count] = i;
      erasures_count++;
    }
	else 
		decode_chunks.insert(i);
  }
	/*
    if (i < k)
      data[i] = (*decoded)[i].c_str();
    else
      coding[i - k] = (*decoded)[i].c_str();
  }	
  erasures[erasures_count] = -1;
  assert(erasures_count > 0);*/
  
 	int i=0;
	unsigned int optlrc_decode_local[k][n];	
	for (set<int>::iterator it = decode_chunks.begin(); it != decode_chunks.end(); ++it)
	{
		for (int j=0; j<k; j++) {
			optlrc_decode_local[i][j] = pOptLRC_G->optlrc_matrix[(r+1)*group+j][*it];
			i++;
			//think how to multiply only partial data bus
		}
	} 
	
	//for (i=0; i<k; i++)
	//TODO: adjust for arbitrary code length
	char *dst = coding[0];	
	for (i=0 ; i<k; i++) { 
		char *src = data[0] + i*blocksize;
		galois_w08_region_multiply(src,
		                optlrc_decode_local[n][i],
		                blocksize,
		                dst,
		                1);
	}		
	return 0;
}	

					
 /* unsigned blocksize = (*chunks.begin()).second.length();
  int erasures[k + m + 1];
  int erasures_count = 0;
  char *data[k];
  char *coding[m];
  for (int i =  0; i < k + m; i++) {
    if (chunks.find(i) == chunks.end()) {
      erasures[erasures_count] = i;
      erasures_count++;
    }
    if (i < k)
      data[i] = (*decoded)[i].c_str();
    else
      coding[i - k] = (*decoded)[i].c_str();
  }
  erasures[erasures_count] = -1;

  assert(erasures_count > 0);
  return jerasure_decode(erasures, data, coding, blocksize);
}*/

