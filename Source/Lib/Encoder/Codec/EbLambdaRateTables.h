/*
* Copyright(c) 2019 Intel Corporation
*
* This source code is subject to the terms of the BSD 2 Clause License and
* the Alliance for Open Media Patent License 1.0. If the BSD 2 Clause License
* was not distributed with this source code in the LICENSE file, you can
* obtain it at https://www.aomedia.org/license/software-license. If the Alliance for Open
* Media Patent License 1.0 was not distributed with this source code in the
* PATENTS file, you can obtain it at https://www.aomedia.org/license/patent-license.
*/

// EbLambdaRateTables.h file contains all material to estimate the rate of intra, inter and skip modes
#ifndef EbLambdaRateTables_h
#define EbLambdaRateTables_h
#ifdef __cplusplus
extern "C" {
#endif

#define NUMBER_OF_INTRA_MODES_MINUS_TWO 34
#define LUMA_INTRA_MODE_BITS_GRE31 \
    196608 // farctional number of bit required for signaling luma intra mode greater than 31
// *Note - As of Oct 2011, the JCT-VC uses the PSNR forumula
//  PSNR = (LUMA_WEIGHT * PSNRy + PSNRu + PSNRv) / (2+LUMA_WEIGHT)
#define LUMA_WEIGHT 1
#define CHROMA_WEIGHT 1
#define RATE_WEIGHT 1

// Precision macros used in the mode decision
#define BIT_ESTIMATE_PRECISION 15
#define LAMBDA_PRECISION 16
#define COST_PRECISION 8
#define MD_SHIFT (BIT_ESTIMATE_PRECISION + LAMBDA_PRECISION - COST_PRECISION)
#define MD_OFFSET (1 << (MD_SHIFT - 1))

// Precision macros for chroma weight
// *Note - As in JCTVC-G1102,
#define CHROMA_WEIGHT_PRECISION 16
#define CHROMA_WEIGHT_SHIFT (CHROMA_WEIGHT_PRECISION - COST_PRECISION)
#define CHROMA_WEIGHT_OFFSET (1 << (CHROMA_WEIGHT_SHIFT - 1))

// Precision macro used in the motion estimation search
#define ME_SHIFT (BIT_ESTIMATE_PRECISION + LAMBDA_PRECISION)

// Syntax element macro
#define ZERO_COST 0
#define TU_SPLIT_ZERO 0
#define TU_SPLIT_TAB_OFFSET 4 // offset to parse transSubDivFlag tables
#define CBF_TAB_OFFSET 3 // offset to parse Cbf tables
#define SPLIT_FLAG_ZERO 0
#define SPLIT_TAB_OFFSET 3 // offset to parse split flag tables
#define SKIP_FLAG_ZERO 0
#define SKIP_FLAG_ONE 1
#define SKIP_TAB_OFFSET 3 // offset to parse skip flag tables

static const uint32_t intra_luma_mode_mapping[] = {
    // intra luma mode mapping for scaling
    3, 4, 4, 3, 5, 5, 5, 3, 1, 1, 1, 3, 6, 6, 6, 3, 7,
    7, 4, 3, 8, 8, 8, 3, 2, 2, 2, 3, 9, 9, 9, 3, 3, 3, // conversion to 9 modes
    3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3,
    3, 3, 3, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3 // conversion to 3 modes
};
static const uint32_t av1_lambda_mode_decision8_bit_sad[QINDEX_RANGE /*256*/] = {
    86,    173,   173,   194,   216,   238,   259,   259,   281,   303,   324,   346,   368,   389,   411,   411,
    433,   454,   476,   498,   519,   541,   563,   563,   584,   606,   628,   649,   671,   693,   693,   714,
    736,   758,   779,   801,   823,   823,   844,   866,   888,   909,   931,   931,   953,   974,   996,   1018,
    1039,  1039,  1061,  1083,  1104,  1126,  1148,  1148,  1169,  1191,  1213,  1234,  1234,  1256,  1278,  1299,
    1321,  1343,  1343,  1364,  1386,  1408,  1429,  1429,  1451,  1473,  1494,  1516,  1516,  1538,  1559,  1581,
    1603,  1603,  1624,  1646,  1668,  1689,  1689,  1711,  1733,  1754,  1754,  1776,  1798,  1819,  1841,  1841,
    1884,  1906,  1949,  1993,  2014,  2058,  2079,  2123,  2144,  2188,  2209,  2253,  2274,  2318,  2339,  2383,
    2404,  2448,  2469,  2513,  2534,  2556,  2599,  2621,  2664,  2707,  2751,  2794,  2837,  2902,  2946,  2989,
    3032,  3076,  3119,  3162,  3206,  3249,  3292,  3336,  3379,  3422,  3487,  3552,  3596,  3661,  3726,  3769,
    3834,  3899,  3942,  4007,  4051,  4116,  4159,  4224,  4311,  4376,  4441,  4506,  4571,  4636,  4701,  4766,
    4831,  4896,  4982,  5047,  5134,  5199,  5264,  5351,  5416,  5481,  5567,  5654,  5740,  5827,  5892,  5979,
    6065,  6152,  6239,  6325,  6412,  6499,  6585,  6694,  6780,  6867,  6975,  7062,  7149,  7257,  7365,  7452,
    7560,  7669,  7777,  7885,  7994,  8102,  8210,  8319,  8427,  8557,  8665,  8795,  8903,  9033,  9163,  9293,
    9423,  9553,  9683,  9835,  9987,  10117, 10290, 10442, 10593, 10767, 10940, 11113, 11308, 11481, 11676, 11893,
    12110, 12326, 12543, 12781, 13041, 13301, 13561, 13865, 14168, 14471, 14818, 15164, 15533, 15944, 16356, 16789,
    17244, 17742, 18262, 18826, 19411, 20039, 20689, 21404, 22140, 22920, 23787, 24675, 25650, 26690, 27773, 28943};
// Lambda Table for bit-depth 10
static const uint32_t av1lambda_mode_decision10_bit_sad[QINDEX_RANGE /*256*/] = {
    22,    49,    54,    70,    81,    91,    108,   119,   135,   151,   167,   184,   200,   216,   232,   254,
    270,   287,   308,   324,   346,   368,   384,   406,   422,   444,   465,   487,   503,   525,   547,   568,
    590,   611,   628,   649,   671,   693,   714,   736,   758,   774,   796,   817,   839,   861,   882,   899,
    920,   942,   964,   985,   1001,  1023,  1045,  1066,  1083,  1104,  1126,  1148,  1164,  1186,  1207,  1224,
    1245,  1261,  1283,  1305,  1321,  1343,  1359,  1381,  1402,  1419,  1440,  1456,  1478,  1494,  1516,  1532,
    1554,  1570,  1586,  1608,  1624,  1646,  1662,  1678,  1700,  1716,  1738,  1754,  1771,  1792,  1808,  1825,
    1857,  1895,  1928,  1960,  1998,  2031,  2063,  2096,  2133,  2166,  2198,  2231,  2263,  2296,  2328,  2361,
    2393,  2426,  2458,  2491,  2523,  2556,  2588,  2621,  2653,  2702,  2745,  2794,  2843,  2886,  2935,  2978,
    3027,  3070,  3119,  3162,  3206,  3255,  3298,  3341,  3385,  3433,  3487,  3547,  3607,  3661,  3720,  3780,
    3834,  3888,  3948,  4002,  4056,  4110,  4170,  4235,  4305,  4370,  4435,  4500,  4571,  4636,  4701,  4766,
    4825,  4906,  4982,  5053,  5128,  5204,  5280,  5351,  5421,  5497,  5578,  5659,  5746,  5827,  5903,  5984,
    6065,  6158,  6244,  6336,  6423,  6510,  6596,  6694,  6786,  6883,  6975,  7073,  7165,  7268,  7371,  7468,
    7571,  7669,  7777,  7885,  7994,  8102,  8210,  8324,  8443,  8557,  8671,  8795,  8920,  9044,  9163,  9299,
    9429,  9564,  9700,  9840,  9987,  10133, 10290, 10447, 10604, 10777, 10945, 11124, 11308, 11498, 11693, 11899,
    12110, 12326, 12559, 12798, 13052, 13312, 13583, 13870, 14168, 14487, 14823, 15175, 15549, 15944, 16356, 16800,
    17266, 17764, 18279, 18836, 19421, 20050, 20705, 21409, 22146, 22942, 23798, 24691, 25655, 26695, 27784, 28959};
// Lambda Table for bit-depth 12
static const uint32_t av1lambda_mode_decision12_bit_sad[QINDEX_RANGE /*256*/] = {
    11,    16,    25,    33,    45,    55,    67,    81,    94,    108,   123,   139,   155,   171,   189,   207,
    224,   243,   262,   281,   300,   320,   339,   360,   380,   400,   422,   442,   464,   484,   506,   528,
    548,   570,   591,   613,   634,   655,   677,   698,   720,   741,   763,   785,   807,   827,   848,   870,
    892,   912,   934,   955,   976,   997,   1018,  1039,  1060,  1080,  1102,  1122,  1142,  1163,  1183,  1203,
    1224,  1244,  1264,  1284,  1305,  1324,  1344,  1364,  1383,  1404,  1423,  1441,  1462,  1481,  1500,  1519,
    1538,  1558,  1577,  1596,  1613,  1632,  1651,  1670,  1689,  1707,  1726,  1743,  1762,  1780,  1799,  1817,
    1852,  1886,  1921,  1955,  1989,  2022,  2056,  2090,  2124,  2158,  2190,  2224,  2258,  2290,  2324,  2357,
    2389,  2422,  2456,  2488,  2521,  2552,  2584,  2617,  2649,  2697,  2744,  2790,  2838,  2884,  2931,  2977,
    3023,  3069,  3114,  3160,  3204,  3249,  3295,  3340,  3383,  3428,  3486,  3544,  3603,  3661,  3718,  3774,
    3831,  3888,  3944,  3999,  4055,  4110,  4164,  4233,  4301,  4368,  4434,  4500,  4567,  4632,  4697,  4762,
    4827,  4902,  4978,  5054,  5128,  5203,  5276,  5349,  5422,  5494,  5577,  5661,  5742,  5823,  5904,  5984,
    6064,  6155,  6244,  6332,  6420,  6508,  6595,  6691,  6787,  6882,  6977,  7070,  7164,  7266,  7368,  7470,
    7570,  7670,  7778,  7887,  7995,  8102,  8209,  8325,  8440,  8555,  8671,  8794,  8918,  9042,  9165,  9297,
    9432,  9564,  9698,  9842,  9987,  10132, 10289, 10446, 10604, 10775, 10947, 11121, 11308, 11498, 11691, 11899,
    12111, 12326, 12558, 12795, 13051, 13312, 13582, 13871, 14169, 14490, 14820, 15178, 15546, 15944, 16357, 16801,
    17263, 17761, 18280, 18838, 19420, 20048, 20702, 21409, 22146, 22940, 23796, 24693, 25657, 26698, 27785, 28958};

#ifdef __cplusplus
}
#endif
#endif //EbLambdaRateTables_h
