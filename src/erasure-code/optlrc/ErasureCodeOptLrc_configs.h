/*
 * zigzag_configs.hpp
 *
 *  Created on: Aug 19, 2016
 *      Author: ido
 */

#ifndef OPTLRC_CONFIGS_HPP_
#define OPTLRC_CONFIGS_HPP_

#define MAX_DATA_CHUNKS     16
#define MAX_CHUNKS  20 
#define MAX_LOCALITY_CHUNKS   8
#define MAX_MATRIX          256
#define MAX_OPTLRC_CHUNKS   4

typedef struct OptLRC {
    /* Used for Decoding */
    unsigned int optlrc_perms[MAX_OPTLRC_CHUNKS][MAX_MATRIX][MAX_MATRIX];

    /* Used for Encoding */
    //unsigned int optlrc_matrix[MAX_OPTLRC_CHUNKS][MAX_MATRIX][MAX_MATRIX];
    unsigned int optlrc_matrix[MAX_MATRIX][MAX_MATRIX];
    unsigned int optlrc_decode[MAX_OPTLRC_CHUNKS][MAX_MATRIX][MAX_MATRIX];
    unsigned int optlrc_coeff[MAX_OPTLRC_CHUNKS][MAX_MATRIX][MAX_MATRIX];

    /* In case chunk i failed, recover rows parity_rows[i] from the row parity */
    unsigned int parity_rows[MAX_MATRIX][MAX_MATRIX];

    /* In case chunk i failed, recover rows optlrc_rows[i] from the zigzag */
    unsigned int optlrc_rows[MAX_OPTLRC_CHUNKS][MAX_MATRIX][MAX_MATRIX];

} OptLRC, *POptLRC;

OptLRC optlrc_9_4_2 = {
.optlrc_matrix = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {2, 2, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1},
        {0, 0, 1, 2},
        {0, 0, 0, 1},
        {2, 2, 0, 0},
        {0, 0, 1, 2}
}

};

typedef struct OptLRC_Configs
{
    POptLRC configs[MAX_CHUNKS][MAX_DATA_CHUNKS][MAX_LOCALITY_CHUNKS];
    OptLRC_Configs()
    {
        /*
         * Total Chunks
         * Data Chunks
         * Locality
         */
        configs[9][4][2]  =  &optlrc_9_4_2;
    }
} OptLRC_Configs, *POptLRC_Configs;

#endif /* OPTLRC_CONFIGS_HPP_ */


