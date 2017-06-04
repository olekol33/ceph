#ifndef CEPH_ERASURE_CODE_OPTLRC_H
#define CEPH_ERASURE_CODE_OPTLRC_H
#include "ErasureCodeOptLrc_configs.h"

class ErasureCodeOptLrc : public ErasureCode {
public:
  int n;
  std::string DEFAULT_N;
  int k;
  std::string DEFAULT_K;
  int r;
  std::string DEFAULT_R;
  POptLRC pOptLRC_G = optlrc_configs.configs[n][k][r];
  /*const char *technique;
  string ruleset_root;
  string ruleset_failure_domain;
  bool per_chunk_alignment;*/

  explicit ErasureCodeOptLrc(const char *_technique) :
    n(0),
    DEFAULT_N("4"),
    k(0),
    DEFAULT_K("2"),
    r(0),
    DEFAULT_R("2"),
    /*technique(_technique),
    ruleset_root(DEFAULT_RULESET_ROOT),
    ruleset_failure_domain(DEFAULT_RULESET_FAILURE_DOMAIN),
    per_chunk_alignment(false)*/
  {}

  virtual ~ErasureCodeOptLrc() {}
  
/*  virtual int create_ruleset(const string &name,
			     CrushWrapper &crush,
			     ostream *ss) const;*/

  virtual unsigned int get_chunk_count() const {
    return n;
  }

  virtual unsigned int get_data_chunk_count() const {
    return k;
  }

  virtual unsigned int get_chunk_size(unsigned int object_size) const;

  virtual int encode_chunks(const set<int> &want_to_encode,
			    map<int, bufferlist> *encoded);

  virtual int decode_chunks(const set<int> &want_to_read,
			    const map<int, bufferlist> &chunks,
			    map<int, bufferlist> *decoded);

//  virtual int init(ErasureCodeProfile &profile, ostream *ss);

virtual void optlrc_encode(const set<int> &want_to_encode, 
							char **data, char **coding, 
							int blocksize)
						   
  virtual int jerasure_decode(int *erasures,
                               char **data,
                               char **coding) = 0;							   
/*							   
  virtual unsigned get_alignment() const = 0;
  virtual void prepare() = 0;
  static bool is_prime(int value);
protected:
  virtual int parse(ErasureCodeProfile &profile, ostream *ss);*/
};

#endif
