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
#define MAX_GROUPS 10

typedef struct OptLRC {
    int optlrc_encode[MAX_MATRIX][MAX_MATRIX];
    int optlrc_perm[MAX_MATRIX];
    int optlrc_coef[MAX_GROUPS][MAX_LOCALITY_CHUNKS];

} OptLRC, *POptLRC;

//struct OptLRC optlrc_9_4_2 = {
//optlrc_encode : {
//{1, 0, 0, 0},
//{0, 1, 0, 0},
//{0, 0, 1, 0},
//{0, 0, 0, 1},
//{1, 0, 0, 1},
//{3, 2, 176, 102},
//{101, 178, 2, 3},
//{102, 176, 178, 101},
//{0, 1, 1, 0}
//},
//optlrc_perm : {5,7,6,3,4,0,2,1,8},
//optlrc_coef : {
//{1,1,1},
//{1,1,1},
//{1,1,1}
//}
//};

struct OptLRC optlrc_10_6_3 = {
optlrc_encode : {
{1, 0, 0, 0, 0, 0},
{0, 1, 0, 0, 0, 0},
{0, 0, 1, 0, 0, 0},
{0, 0, 0, 1, 0, 0},
{0, 0, 0, 0, 1, 0},
{0, 0, 0, 0, 0, 1},
{168, 143, 106, 76, 142, 38},
{168, 142, 106, 76, 143, 38},
{0, 0, 1, 1, 0, 1},
{1, 0, 0, 0, 0, 0}
},
optlrc_perm : {8,7,3,2,5,1,6,4,0,9}
};

struct OptLRC optlrc_9_4_2 = {
optlrc_encode : {
{1, 0, 0, 0},
{0, 1, 0, 0},
{0, 0, 1, 0},
{0, 0, 0, 1},
{245, 104, 35, 207},
{35, 209, 244, 130},
{245, 104, 34, 207},
{34, 209, 244, 130},
{0, 1, 0, 1}
},
optlrc_perm : {4,6,1,7,0,5,2,3,8}
};

struct OptLRC optlrc_10_6_4 = {
optlrc_encode : {
{1, 0, 0, 0, 0, 0},
{0, 1, 0, 0, 0, 0},
{0, 0, 1, 0, 0, 0},
{0, 0, 0, 1, 0, 0},
{0, 0, 0, 0, 1, 0},
{0, 0, 0, 0, 0, 1},
{113, 108, 68, 90, 79, 147},
{1, 1, 0, 1, 0, 1},
{233, 119, 11, 144, 220, 112},
{152, 27, 78, 202, 146, 227}
},
optlrc_perm : {3,4,7,0,8,1,6,2,5,9}
};

struct OptLRC optlrc_15_8_4 = {
optlrc_encode : {
{1, 0, 0, 0, 0, 0, 0, 0},
{0, 1, 0, 0, 0, 0, 0, 0},
{0, 0, 1, 0, 0, 0, 0, 0},
{0, 0, 0, 1, 0, 0, 0, 0},
{0, 0, 0, 0, 1, 0, 0, 0},
{0, 0, 0, 0, 0, 1, 0, 0},
{0, 0, 0, 0, 0, 0, 1, 0},
{0, 0, 0, 0, 0, 0, 0, 1},
{231, 237, 73, 102, 227, 92, 130, 188},
{151, 6, 36, 232, 83, 7, 165, 71},
{150, 6, 36, 232, 82, 6, 165, 71},
{102, 52, 38, 224, 129, 177, 202, 19},
{158, 2, 94, 228, 43, 6, 243, 143},
{121, 238, 22, 130, 200, 90, 113, 51},
{102, 52, 38, 225, 129, 177, 203, 18}
},
optlrc_perm : {0,6,9,10,1,4,12,13,8,2,3,11,5,7,14}
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
        configs[8][3][2]  =  &optlrc_8_3_2;
        configs[12][6][3]  =  &optlrc_12_6_3;
    }
} OptLRC_Configs, *POptLRC_Configs;

#endif /* OPTLRC_CONFIGS_HPP_ */
