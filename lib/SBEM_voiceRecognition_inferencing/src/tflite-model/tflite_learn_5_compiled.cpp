/* Generated by Edge Impulse
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
// Generated on: 23.10.2023 19:58:22

#include <stdio.h>
#include <stdlib.h>
#include "edge-impulse-sdk/tensorflow/lite/c/builtin_op_data.h"
#include "edge-impulse-sdk/tensorflow/lite/c/common.h"
#include "edge-impulse-sdk/tensorflow/lite/micro/micro_mutable_op_resolver.h"
#include "edge-impulse-sdk/porting/ei_classifier_porting.h"

#if EI_CLASSIFIER_PRINT_STATE
#if defined(__cplusplus) && EI_C_LINKAGE == 1
extern "C" {
    extern void ei_printf(const char *format, ...);
}
#else
extern void ei_printf(const char *format, ...);
#endif
#endif

#if defined __GNUC__
#define ALIGN(X) __attribute__((aligned(X)))
#elif defined _MSC_VER
#define ALIGN(X) __declspec(align(X))
#elif defined __TASKING__
#define ALIGN(X) __align(X)
#elif defined __ICCARM__
#define ALIGN(x) __attribute__((aligned(x)))
#endif

#ifndef EI_MAX_SCRATCH_BUFFER_COUNT
#ifndef CONFIG_IDF_TARGET_ESP32S3
#define EI_MAX_SCRATCH_BUFFER_COUNT 4
#else
#define EI_MAX_SCRATCH_BUFFER_COUNT 8
#endif // CONFIG_IDF_TARGET_ESP32S3
#endif // EI_MAX_SCRATCH_BUFFER_COUNT

#ifndef EI_MAX_OVERFLOW_BUFFER_COUNT
#define EI_MAX_OVERFLOW_BUFFER_COUNT 10
#endif // EI_MAX_OVERFLOW_BUFFER_COUNT

using namespace tflite;
using namespace tflite::ops;
using namespace tflite::ops::micro;

namespace {

#if defined(EI_CLASSIFIER_ALLOCATION_STATIC_HIMAX) || defined(EI_CLASSIFIER_ALLOCATION_STATIC_HIMAX_GNU)
constexpr int kTensorArenaSize = 3168;
#else
constexpr int kTensorArenaSize = 2144;
#endif

#if defined(EI_CLASSIFIER_ALLOCATION_STATIC)
uint8_t tensor_arena[kTensorArenaSize] ALIGN(16);
#elif defined(EI_CLASSIFIER_ALLOCATION_STATIC_HIMAX)
#pragma Bss(".tensor_arena")
uint8_t tensor_arena[kTensorArenaSize] ALIGN(16);
#pragma Bss()
#elif defined(EI_CLASSIFIER_ALLOCATION_STATIC_HIMAX_GNU)
uint8_t tensor_arena[kTensorArenaSize] ALIGN(16) __attribute__((section(".tensor_arena")));
#else
#define EI_CLASSIFIER_ALLOCATION_HEAP 1
uint8_t* tensor_arena = NULL;
#endif

static uint8_t* tensor_boundary;
static uint8_t* current_location;

template <int SZ, class T> struct TfArray {
  int sz; T elem[SZ];
};
enum used_operators_e {
  OP_RESHAPE, OP_CONV_2D, OP_MAX_POOL_2D, OP_FULLY_CONNECTED, OP_SOFTMAX,  OP_LAST
};
struct TensorInfo_t { // subset of TfLiteTensor used for initialization from constant memory
  TfLiteAllocationType allocation_type;
  TfLiteType type;
  void* data;
  TfLiteIntArray* dims;
  size_t bytes;
  TfLiteQuantization quantization;
};
struct NodeInfo_t { // subset of TfLiteNode used for initialization from constant memory
  struct TfLiteIntArray* inputs;
  struct TfLiteIntArray* outputs;
  void* builtin_data;
  used_operators_e used_op_index;
};

typedef struct {
  TfLiteTensor tensor;
  int16_t index;
} TfLiteTensorWithIndex;

typedef struct {
  TfLiteEvalTensor tensor;
  int16_t index;
} TfLiteEvalTensorWithIndex;

TfLiteContext ctx{};
static const int MAX_TFL_TENSOR_COUNT = 4;
static TfLiteTensorWithIndex tflTensors[MAX_TFL_TENSOR_COUNT];
static const int MAX_TFL_EVAL_COUNT = 4;
static TfLiteEvalTensorWithIndex tflEvalTensors[MAX_TFL_EVAL_COUNT];
TfLiteRegistration registrations[OP_LAST];
TfLiteNode tflNodes[11];

const TfArray<2, int> tensor_dimension0 = { 2, { 1,650 } };
const TfArray<1, float> quant0_scale = { 1, { 0.049388669431209564, } };
const TfArray<1, int> quant0_zero = { 1, { -8 } };
const TfLiteAffineQuantization quant0 = { (TfLiteFloatArray*)&quant0_scale, (TfLiteIntArray*)&quant0_zero, 0 };
const ALIGN(16) int32_t tensor_data1[4] = { 1, 1, 50, 13, };
const TfArray<1, int> tensor_dimension1 = { 1, { 4 } };
const ALIGN(16) int32_t tensor_data2[4] = { 1, 50, 1, 8, };
const TfArray<1, int> tensor_dimension2 = { 1, { 4 } };
const ALIGN(16) int32_t tensor_data3[4] = { 1, 1, 25, 8, };
const TfArray<1, int> tensor_dimension3 = { 1, { 4 } };
const ALIGN(16) int32_t tensor_data4[4] = { 1, 25, 1, 16, };
const TfArray<1, int> tensor_dimension4 = { 1, { 4 } };
const ALIGN(8) int32_t tensor_data5[2] = { -1, 208, };
const TfArray<1, int> tensor_dimension5 = { 1, { 2 } };
const ALIGN(16) int32_t tensor_data6[4] = { 2939, -1039, -659, 1182, };
const TfArray<1, int> tensor_dimension6 = { 1, { 4 } };
const TfArray<1, float> quant6_scale = { 1, { 0.00056864198995754123, } };
const TfArray<1, int> quant6_zero = { 1, { 0 } };
const TfLiteAffineQuantization quant6 = { (TfLiteFloatArray*)&quant6_scale, (TfLiteIntArray*)&quant6_zero, 0 };
const ALIGN(16) int8_t tensor_data7[4*208] = { 
  -10, 22, -28, 6, 8, 5, 18, 5, -11, -30, -3, -23, 10, 8, 12, 21, -34, 13, -21, 13, -29, 5, -7, -21, 3, 6, 7, -18, 9, 3, 1, 1, -18, 24, -28, 1, -45, -26, 9, -42, -45, -15, -8, -5, -3, 20, 14, 7, -31, 19, -39, 25, -87, 12, 16, -69, -12, -28, -16, -2, 10, 24, 8, 3, -49, 11, -49, 16, -91, 16, 15, -88, -32, -58, -4, -37, 15, 14, 13, 11, -35, 5, -31, 23, -48, -5, 21, -34, -28, -37, -6, -13, 6, 8, 10, 8, -59, 10, -7, 7, -103, 0, -1, -52, -15, -48, -6, -29, 10, 2, 21, 8, -13, 5, -52, 18, -78, -51, -7, -80, -2, -55, -25, -8, 32, -2, 8, -9, -21, 15, -31, 12, -66, -9, -7, -49, -19, -32, 13, 3, 0, 2, 8, 14, -28, 14, -21, 10, -61, -2, 12, -54, -10, -5, 7, -4, 0, 5, 16, -3, -27, 10, -30, 10, -48, 9, 9, -11, -17, 0, -33, -38, 35, 5, 3, -4, 6, 14, -40, 22, -31, -9, 6, -27, 5, -2, 27, -8, 28, 17, -4, 8, -17, 17, -2, 9, -48, -40, 13, -15, -28, -4, -12, -48, -2, 19, 5, -9, 
  13, 14, 5, -17, 1, -9, 1, 2, 5, 3, 4, 15, -5, -12, 3, -7, 4, 7, 7, 3, 11, -23, -3, 2, 2, 9, -14, 10, -11, 9, -1, -4, 1, 9, 15, 6, 3, -16, -6, 6, 3, -4, -11, 7, -6, 20, -5, 1, 12, 4, 14, 19, 4, -17, -9, 6, 11, 6, -8, 0, -19, 9, 5, 11, 9, 9, 13, 17, 2, -22, 3, 3, 10, 5, -7, -1, -6, 6, 7, 1, 1, 7, 6, 20, 2, -13, 2, 4, 25, 3, -20, -5, -17, 6, 1, 6, 1, 6, 10, 13, 3, -14, -6, 10, 18, 22, -24, -3, -19, 13, 4, 14, 6, 6, 7, 23, 7, -8, 2, 10, 17, 8, 0, 9, -22, 3, -7, 16, 4, 4, 8, 13, 12, -31, 6, 7, 11, 18, 4, 15, -8, -8, -2, 5, 7, -7, 8, 20, 9, -1, -9, 10, 21, 18, 0, -1, 1, -2, -4, -1, 0, -1, 9, 12, 9, 0, -6, 13, 16, 23, 4, -7, -15, -4, 6, -6, -6, -13, 3, -1, 11, -20, -9, 12, 11, 33, 5, -1, -4, 1, -12, -6, -17, -1, -1, 7, 13, 21, -6, 12, 24, 3, 13, 10, -8, -7, -6, -5, 
  -38, -4, 5, -3, 8, 3, -12, 11, 10, 34, 16, 11, 11, -11, -8, -3, 24, 3, -2, -7, 7, 44, -1, -12, 13, -6, 18, 13, 6, -17, -4, -11, 22, -6, 15, -12, -2, 18, -1, -4, 7, -12, 18, 13, 8, -10, -1, -6, 15, -3, 15, -28, 4, 21, 7, -8, 1, -23, 24, 5, 1, -19, 10, 0, 14, -4, 16, -8, 3, 28, 12, 0, 0, -17, 21, 11, 3, -6, 9, -4, 10, -6, 10, -15, 4, 19, 11, 1, 3, -1, 23, 13, -6, -23, 14, -15, 13, -8, 8, -9, 5, 22, 12, 4, -7, -6, 31, 20, 2, -14, 10, -2, 10, -6, 3, -14, 8, 29, 20, 9, 0, -6, 19, 11, 3, -13, 1, -8, 15, -7, 5, -17, 13, 40, 12, 5, -1, -9, -5, -3, 0, -9, 0, 0, 10, -9, 5, -3, 14, 29, 6, 16, -11, -13, -6, 7, -4, -27, 1, -4, 8, -8, 9, -13, 11, 11, 7, 9, -14, -11, 26, 19, 0, -25, 5, -4, 20, 6, 0, -12, 7, 24, 3, 8, -16, -13, -4, 12, 4, -1, -2, -8, 28, -5, 4, -21, 12, 14, -2, 11, -5, 4, -11, 13, 11, 7, -1, 0, 
  40, -56, -21, 5, -98, -27, 17, -67, -34, -94, -30, -39, -32, 19, 8, 4, 13, -55, -29, 12, 0, -45, 14, 12, -25, -45, -55, -37, -31, 28, -2, 2, -52, -44, -52, -9, 12, -18, -12, 9, -9, 26, -40, 17, -4, -62, -21, -22, -31, -35, -30, -1, 10, -16, -88, 13, -8, 26, -40, -56, 2, 2, -126, -30, -72, -31, -44, -39, 11, -19, -58, 14, -42, 28, -10, -55, -22, -120, -127, -39, -56, -43, -74, -8, -6, -26, -108, 13, -39, 25, 18, -7, 30, -16, -82, -77, -46, -35, -55, -16, 1, -60, -59, -2, -1, 22, 7, -33, 12, -28, -34, -85, -31, -40, -97, -35, 2, -45, -57, -9, -8, 39, 20, -40, 11, 3, 11, -47, -56, -12, -75, -45, -65, -5, -27, -55, -29, 38, 2, -18, 1, 19, 16, -26, -31, -13, -49, -23, -115, -21, 7, -43, -23, 11, 40, 4, -7, 2, 15, 3, -48, -1, -28, -12, -119, -22, 0, -39, -21, -37, -8, -2, -7, 17, 25, 0, -7, 6, -14, -32, -122, 22, 18, -27, -4, -76, -26, -2, 2, 10, 12, -3, -10, 4, -1, -15, -95, -8, -5, -20, -4, -44, -40, -18, -25, -4, 4, 9, 
};
const TfArray<2, int> tensor_dimension7 = { 2, { 4,208 } };
const TfArray<1, float> quant7_scale = { 1, { 0.019452942535281181, } };
const TfArray<1, int> quant7_zero = { 1, { 0 } };
const TfLiteAffineQuantization quant7 = { (TfLiteFloatArray*)&quant7_scale, (TfLiteIntArray*)&quant7_zero, 0 };
const ALIGN(16) int32_t tensor_data8[16] = { -3294, -830, -5862, -741, -796, -2009, -1123, -1669, -1949, 597, -706, -122, -1, -558, -142, -1154, };
const TfArray<1, int> tensor_dimension8 = { 1, { 16 } };
const TfArray<16, float> quant8_scale = { 16, { 0.00033859311952255666, 0.00035813337308354676, 0.00022452196571975946, 0.00048648900701664388, 0.00029726655338890851, 0.00063552218489348888, 0.00045963691081851721, 0.0002389365981798619, 0.00045072071952745318, 0.00072682119207456708, 0.00068951066350564361, 0.00057491404004395008, 0.00046067472430877388, 0.00047113958862610161, 0.00030793686164543033, 0.00035321965697221458, } };
const TfArray<16, int> quant8_zero = { 16, { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 } };
const TfLiteAffineQuantization quant8 = { (TfLiteFloatArray*)&quant8_scale, (TfLiteIntArray*)&quant8_zero, 0 };
const ALIGN(16) int8_t tensor_data9[16*1*3*8] = { 
  /* [0][0][][] */ -13,-83,-13,-127,-118,-13,38,-36, 21,-34,-8,-112,-94,-3,23,-32, 3,-22,84,-73,-45,-20,7,-44, 
  /* [1][0][][] */ -2,47,-25,0,20,-20,-59,-127, -6,-33,-9,-3,-6,-16,-79,99, -26,-16,32,-26,28,1,-24,57, 
  /* [2][0][][] */ -25,12,77,-55,-10,10,64,45, 2,-57,6,-4,127,-16,-21,-2, -25,-31,76,-30,28,-3,38,-33, 
  /* [3][0][][] */ 13,-39,-20,-17,43,-10,-1,-57, 47,-127,-9,-19,-3,-83,-22,-66, -15,-82,3,-37,36,-62,-28,-14, 
  /* [4][0][][] */ -22,-127,-5,-51,54,-19,46,-17, -12,-28,10,-92,4,60,20,-6, -10,-14,29,-53,55,60,25,-26, 
  /* [5][0][][] */ -15,36,-16,24,-27,-38,-127,-38, -35,-32,-50,20,27,2,-41,-77, -10,-64,-69,-70,1,14,26,-35, 
  /* [6][0][][] */ -5,-15,52,41,-10,-3,-2,-13, -10,18,-20,-74,3,-7,-18,-45, -9,27,-8,-37,4,1,-127,-4, 
  /* [7][0][][] */ 21,-34,-22,-56,20,127,-33,11, -38,-43,11,-100,10,-119,-12,6, -22,-49,2,-106,83,115,-9,13, 
  /* [8][0][][] */ 29,-40,-5,-32,-85,3,58,20, -127,-54,-56,17,42,-1,5,2, -68,-66,-46,-2,16,-9,-5,-90, 
  /* [9][0][][] */ -36,-17,-24,-60,2,29,29,-11, -114,-49,-71,-52,14,-5,-21,-37, -127,-14,-73,-16,-3,-24,-43,-49, 
  /* [10][0][][] */ 4,-6,-14,-18,-40,-101,-48,-49, -6,-12,-21,-17,-35,-127,-32,-14, -8,-8,-38,33,24,-17,-31,-12, 
  /* [11][0][][] */ -30,-16,-24,8,-2,-12,-26,-17, -66,-9,-88,19,18,-49,-108,-16, -57,5,-108,8,24,-5,-127,1, 
  /* [12][0][][] */ -76,16,-38,-27,-5,-126,-9,41, -17,-22,-9,-15,-32,-127,-24,-17, 9,37,-8,-21,-15,-72,51,-12, 
  /* [13][0][][] */ -5,2,-32,15,-100,-127,-112,-95, -4,-12,1,5,5,-70,-77,-60, 40,-30,40,1,2,-4,-57,-36, 
  /* [14][0][][] */ -17,51,29,-12,-55,-28,17,23, 12,30,17,-1,-42,-63,-2,34, -7,12,26,35,15,-63,-127,-18, 
  /* [15][0][][] */ 50,43,13,-5,43,10,-5,47, -2,-22,-10,15,-72,-7,10,38, -127,-68,-35,-12,7,-6,11,36, 
};
const TfArray<4, int> tensor_dimension9 = { 4, { 16,1,3,8 } };
const TfArray<16, float> quant9_scale = { 16, { 0.0068667209707200527, 0.0072630005888640881, 0.0045533403754234314, 0.0098660727962851524, 0.0060286121442914009, 0.012888488359749317, 0.0093215079978108406, 0.0048456713557243347, 0.0091406861320137978, 0.014740046113729477, 0.013983382843434811, 0.011659345589578152, 0.0093425549566745758, 0.0095547838136553764, 0.0062450072728097439, 0.0071633495390415192, } };
const TfArray<16, int> quant9_zero = { 16, { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 } };
const TfLiteAffineQuantization quant9 = { (TfLiteFloatArray*)&quant9_scale, (TfLiteIntArray*)&quant9_zero, 0 };
const ALIGN(16) int32_t tensor_data10[8] = { -2890, -2873, -3835, -3843, -7639, -8598, -7135, -3299, };
const TfArray<1, int> tensor_dimension10 = { 1, { 8 } };
const TfArray<8, float> quant10_scale = { 8, { 0.00034040177706629038, 0.00041675905231386423, 0.00031587609555572271, 0.00030600628815591335, 0.00024927590857259929, 0.0002206886128988117, 0.00026403856463730335, 0.00042521476279944181, } };
const TfArray<8, int> quant10_zero = { 8, { 0,0,0,0,0,0,0,0 } };
const TfLiteAffineQuantization quant10 = { (TfLiteFloatArray*)&quant10_scale, (TfLiteIntArray*)&quant10_zero, 0 };
const ALIGN(16) int8_t tensor_data11[8*1*3*13] = { 
  /* [0][0][][] */ 19,0,84,-78,-11,-3,2,33,-5,15,28,67,-19, 45,-74,64,-31,-20,34,23,1,-27,17,-27,37,44, 111,-127,6,9,-82,29,49,-1,-16,53,-20,-1,-8, 
  /* [1][0][][] */ -47,-1,61,-29,-5,-31,18,6,-26,44,-24,9,-4, -106,127,7,-27,-26,8,33,-4,-19,1,-7,28,-3, -7,-118,-36,18,13,6,-16,48,-16,3,-20,14,46, 
  /* [2][0][][] */ 23,38,43,-82,-36,-37,26,26,-63,-11,46,54,18, 2,5,66,2,-84,10,42,-28,-3,34,12,6,8, -5,24,80,-22,-127,-14,53,15,-25,-56,31,54,33, 
  /* [3][0][][] */ -96,-38,24,-56,31,-22,62,43,-18,-14,-37,10,-8, -85,-78,-10,63,7,-13,0,65,-33,-18,5,20,14, 89,-12,-94,3,127,1,-74,10,75,-59,-7,14,8, 
  /* [4][0][][] */ -4,-11,-32,127,-8,-5,-75,20,-8,-5,10,-15,-6, -7,-24,-4,127,-43,-67,-33,11,-36,29,-10,-5,31, 19,63,62,45,-35,-79,-55,-2,4,-48,1,22,35, 
  /* [5][0][][] */ 19,47,19,-17,-80,-50,-9,91,-22,25,-35,-43,13, 57,100,-23,-21,-31,6,7,-10,86,31,-44,-25,-59, 60,127,-67,-33,-13,52,9,-14,36,50,-29,-58,28, 
  /* [6][0][][] */ 50,80,10,-66,-29,127,38,-104,-29,32,37,5,-48, -10,54,-27,-19,-2,40,-28,-53,-40,48,39,5,-58, 77,50,5,-40,3,-14,9,-82,27,65,49,40,-58, 
  /* [7][0][][] */ -57,-55,22,-32,28,-22,16,3,28,-17,-7,27,20, -39,112,-14,-28,-10,23,30,24,-20,-8,-13,7,18, 16,127,-53,4,-33,36,38,24,-47,-36,-3,26,-25, 
};
const TfArray<4, int> tensor_dimension11 = { 4, { 8,1,3,13 } };
const TfArray<8, float> quant11_scale = { 8, { 0.0068923053331673145, 0.0084383534267544746, 0.0063957199454307556, 0.0061958804726600647, 0.0050472286529839039, 0.004468405619263649, 0.0053461366333067417, 0.0086095612496137619, } };
const TfArray<8, int> quant11_zero = { 8, { 0,0,0,0,0,0,0,0 } };
const TfLiteAffineQuantization quant11 = { (TfLiteFloatArray*)&quant11_scale, (TfLiteIntArray*)&quant11_zero, 0 };
const TfArray<4, int> tensor_dimension12 = { 4, { 1,1,50,13 } };
const TfArray<1, float> quant12_scale = { 1, { 0.049388669431209564, } };
const TfArray<1, int> quant12_zero = { 1, { -8 } };
const TfLiteAffineQuantization quant12 = { (TfLiteFloatArray*)&quant12_scale, (TfLiteIntArray*)&quant12_zero, 0 };
const TfArray<4, int> tensor_dimension13 = { 4, { 1,1,50,8 } };
const TfArray<1, float> quant13_scale = { 1, { 0.049309287220239639, } };
const TfArray<1, int> quant13_zero = { 1, { -128 } };
const TfLiteAffineQuantization quant13 = { (TfLiteFloatArray*)&quant13_scale, (TfLiteIntArray*)&quant13_zero, 0 };
const TfArray<4, int> tensor_dimension14 = { 4, { 1,50,1,8 } };
const TfArray<1, float> quant14_scale = { 1, { 0.049309287220239639, } };
const TfArray<1, int> quant14_zero = { 1, { -128 } };
const TfLiteAffineQuantization quant14 = { (TfLiteFloatArray*)&quant14_scale, (TfLiteIntArray*)&quant14_zero, 0 };
const TfArray<4, int> tensor_dimension15 = { 4, { 1,25,1,8 } };
const TfArray<1, float> quant15_scale = { 1, { 0.049309287220239639, } };
const TfArray<1, int> quant15_zero = { 1, { -128 } };
const TfLiteAffineQuantization quant15 = { (TfLiteFloatArray*)&quant15_scale, (TfLiteIntArray*)&quant15_zero, 0 };
const TfArray<4, int> tensor_dimension16 = { 4, { 1,1,25,8 } };
const TfArray<1, float> quant16_scale = { 1, { 0.049309287220239639, } };
const TfArray<1, int> quant16_zero = { 1, { -128 } };
const TfLiteAffineQuantization quant16 = { (TfLiteFloatArray*)&quant16_scale, (TfLiteIntArray*)&quant16_zero, 0 };
const TfArray<4, int> tensor_dimension17 = { 4, { 1,1,25,16 } };
const TfArray<1, float> quant17_scale = { 1, { 0.029231669381260872, } };
const TfArray<1, int> quant17_zero = { 1, { -128 } };
const TfLiteAffineQuantization quant17 = { (TfLiteFloatArray*)&quant17_scale, (TfLiteIntArray*)&quant17_zero, 0 };
const TfArray<4, int> tensor_dimension18 = { 4, { 1,25,1,16 } };
const TfArray<1, float> quant18_scale = { 1, { 0.029231669381260872, } };
const TfArray<1, int> quant18_zero = { 1, { -128 } };
const TfLiteAffineQuantization quant18 = { (TfLiteFloatArray*)&quant18_scale, (TfLiteIntArray*)&quant18_zero, 0 };
const TfArray<4, int> tensor_dimension19 = { 4, { 1,13,1,16 } };
const TfArray<1, float> quant19_scale = { 1, { 0.029231669381260872, } };
const TfArray<1, int> quant19_zero = { 1, { -128 } };
const TfLiteAffineQuantization quant19 = { (TfLiteFloatArray*)&quant19_scale, (TfLiteIntArray*)&quant19_zero, 0 };
const TfArray<2, int> tensor_dimension20 = { 2, { 1,208 } };
const TfArray<1, float> quant20_scale = { 1, { 0.029231669381260872, } };
const TfArray<1, int> quant20_zero = { 1, { -128 } };
const TfLiteAffineQuantization quant20 = { (TfLiteFloatArray*)&quant20_scale, (TfLiteIntArray*)&quant20_zero, 0 };
const TfArray<2, int> tensor_dimension21 = { 2, { 1,4 } };
const TfArray<1, float> quant21_scale = { 1, { 0.23736600577831268, } };
const TfArray<1, int> quant21_zero = { 1, { 80 } };
const TfLiteAffineQuantization quant21 = { (TfLiteFloatArray*)&quant21_scale, (TfLiteIntArray*)&quant21_zero, 0 };
const TfArray<2, int> tensor_dimension22 = { 2, { 1,4 } };
const TfArray<1, float> quant22_scale = { 1, { 0.00390625, } };
const TfArray<1, int> quant22_zero = { 1, { -128 } };
const TfLiteAffineQuantization quant22 = { (TfLiteFloatArray*)&quant22_scale, (TfLiteIntArray*)&quant22_zero, 0 };
const TfLiteReshapeParams opdata0 = { { 0, 0, 0, 0, 0, 0, 0, 0, }, 0 };
const TfArray<2, int> inputs0 = { 2, { 0,1 } };
const TfArray<1, int> outputs0 = { 1, { 12 } };
const TfLiteConvParams opdata1 = { kTfLitePaddingSame, 1,1, kTfLiteActRelu, 1,1 };
const TfArray<3, int> inputs1 = { 3, { 12,11,10 } };
const TfArray<1, int> outputs1 = { 1, { 13 } };
const TfLiteReshapeParams opdata2 = { { 0, 0, 0, 0, 0, 0, 0, 0, }, 0 };
const TfArray<2, int> inputs2 = { 2, { 13,2 } };
const TfArray<1, int> outputs2 = { 1, { 14 } };
const TfLitePoolParams opdata3 = { kTfLitePaddingSame, 1,2, 1,2, kTfLiteActNone, { { 0,0, 0, 0 } } };
const TfArray<1, int> inputs3 = { 1, { 14 } };
const TfArray<1, int> outputs3 = { 1, { 15 } };
const TfLiteReshapeParams opdata4 = { { 0, 0, 0, 0, 0, 0, 0, 0, }, 0 };
const TfArray<2, int> inputs4 = { 2, { 15,3 } };
const TfArray<1, int> outputs4 = { 1, { 16 } };
const TfLiteConvParams opdata5 = { kTfLitePaddingSame, 1,1, kTfLiteActRelu, 1,1 };
const TfArray<3, int> inputs5 = { 3, { 16,9,8 } };
const TfArray<1, int> outputs5 = { 1, { 17 } };
const TfLiteReshapeParams opdata6 = { { 0, 0, 0, 0, 0, 0, 0, 0, }, 0 };
const TfArray<2, int> inputs6 = { 2, { 17,4 } };
const TfArray<1, int> outputs6 = { 1, { 18 } };
const TfLitePoolParams opdata7 = { kTfLitePaddingSame, 1,2, 1,2, kTfLiteActNone, { { 0,0, 0, 0 } } };
const TfArray<1, int> inputs7 = { 1, { 18 } };
const TfArray<1, int> outputs7 = { 1, { 19 } };
const TfLiteReshapeParams opdata8 = { { 0, 0, 0, 0, 0, 0, 0, 0, }, 0 };
const TfArray<2, int> inputs8 = { 2, { 19,5 } };
const TfArray<1, int> outputs8 = { 1, { 20 } };
const TfLiteFullyConnectedParams opdata9 = { kTfLiteActNone, kTfLiteFullyConnectedWeightsFormatDefault, false, false };
const TfArray<3, int> inputs9 = { 3, { 20,7,6 } };
const TfArray<1, int> outputs9 = { 1, { 21 } };
const TfLiteSoftmaxParams opdata10 = { 1 };
const TfArray<1, int> inputs10 = { 1, { 21 } };
const TfArray<1, int> outputs10 = { 1, { 22 } };
const TensorInfo_t tensorData[] = {
  { kTfLiteArenaRw, kTfLiteInt8, tensor_arena + 656, (TfLiteIntArray*)&tensor_dimension0, 650, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant0))}, },
  { kTfLiteMmapRo, kTfLiteInt32, (void*)tensor_data1, (TfLiteIntArray*)&tensor_dimension1, 16, {kTfLiteNoQuantization, nullptr}, },
  { kTfLiteMmapRo, kTfLiteInt32, (void*)tensor_data2, (TfLiteIntArray*)&tensor_dimension2, 16, {kTfLiteNoQuantization, nullptr}, },
  { kTfLiteMmapRo, kTfLiteInt32, (void*)tensor_data3, (TfLiteIntArray*)&tensor_dimension3, 16, {kTfLiteNoQuantization, nullptr}, },
  { kTfLiteMmapRo, kTfLiteInt32, (void*)tensor_data4, (TfLiteIntArray*)&tensor_dimension4, 16, {kTfLiteNoQuantization, nullptr}, },
  { kTfLiteMmapRo, kTfLiteInt32, (void*)tensor_data5, (TfLiteIntArray*)&tensor_dimension5, 8, {kTfLiteNoQuantization, nullptr}, },
  { kTfLiteMmapRo, kTfLiteInt32, (void*)tensor_data6, (TfLiteIntArray*)&tensor_dimension6, 16, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant6))}, },
  { kTfLiteMmapRo, kTfLiteInt8, (void*)tensor_data7, (TfLiteIntArray*)&tensor_dimension7, 832, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant7))}, },
  { kTfLiteMmapRo, kTfLiteInt32, (void*)tensor_data8, (TfLiteIntArray*)&tensor_dimension8, 64, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant8))}, },
  { kTfLiteMmapRo, kTfLiteInt8, (void*)tensor_data9, (TfLiteIntArray*)&tensor_dimension9, 384, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant9))}, },
  { kTfLiteMmapRo, kTfLiteInt32, (void*)tensor_data10, (TfLiteIntArray*)&tensor_dimension10, 32, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant10))}, },
  { kTfLiteMmapRo, kTfLiteInt8, (void*)tensor_data11, (TfLiteIntArray*)&tensor_dimension11, 312, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant11))}, },
  { kTfLiteArenaRw, kTfLiteInt8, tensor_arena + 0, (TfLiteIntArray*)&tensor_dimension12, 650, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant12))}, },
  { kTfLiteArenaRw, kTfLiteInt8, tensor_arena + 656, (TfLiteIntArray*)&tensor_dimension13, 400, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant13))}, },
  { kTfLiteArenaRw, kTfLiteInt8, tensor_arena + 0, (TfLiteIntArray*)&tensor_dimension14, 400, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant14))}, },
  { kTfLiteArenaRw, kTfLiteInt8, tensor_arena + 400, (TfLiteIntArray*)&tensor_dimension15, 200, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant15))}, },
  { kTfLiteArenaRw, kTfLiteInt8, tensor_arena + 0, (TfLiteIntArray*)&tensor_dimension16, 200, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant16))}, },
  { kTfLiteArenaRw, kTfLiteInt8, tensor_arena + 400, (TfLiteIntArray*)&tensor_dimension17, 400, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant17))}, },
  { kTfLiteArenaRw, kTfLiteInt8, tensor_arena + 0, (TfLiteIntArray*)&tensor_dimension18, 400, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant18))}, },
  { kTfLiteArenaRw, kTfLiteInt8, tensor_arena + 400, (TfLiteIntArray*)&tensor_dimension19, 208, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant19))}, },
  { kTfLiteArenaRw, kTfLiteInt8, tensor_arena + 0, (TfLiteIntArray*)&tensor_dimension20, 208, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant20))}, },
  { kTfLiteArenaRw, kTfLiteInt8, tensor_arena + 208, (TfLiteIntArray*)&tensor_dimension21, 4, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant21))}, },
  { kTfLiteArenaRw, kTfLiteInt8, tensor_arena + 0, (TfLiteIntArray*)&tensor_dimension22, 4, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant22))}, },
};const NodeInfo_t nodeData[] = {
  { (TfLiteIntArray*)&inputs0, (TfLiteIntArray*)&outputs0, const_cast<void*>(static_cast<const void*>(&opdata0)), OP_RESHAPE, },
  { (TfLiteIntArray*)&inputs1, (TfLiteIntArray*)&outputs1, const_cast<void*>(static_cast<const void*>(&opdata1)), OP_CONV_2D, },
  { (TfLiteIntArray*)&inputs2, (TfLiteIntArray*)&outputs2, const_cast<void*>(static_cast<const void*>(&opdata2)), OP_RESHAPE, },
  { (TfLiteIntArray*)&inputs3, (TfLiteIntArray*)&outputs3, const_cast<void*>(static_cast<const void*>(&opdata3)), OP_MAX_POOL_2D, },
  { (TfLiteIntArray*)&inputs4, (TfLiteIntArray*)&outputs4, const_cast<void*>(static_cast<const void*>(&opdata4)), OP_RESHAPE, },
  { (TfLiteIntArray*)&inputs5, (TfLiteIntArray*)&outputs5, const_cast<void*>(static_cast<const void*>(&opdata5)), OP_CONV_2D, },
  { (TfLiteIntArray*)&inputs6, (TfLiteIntArray*)&outputs6, const_cast<void*>(static_cast<const void*>(&opdata6)), OP_RESHAPE, },
  { (TfLiteIntArray*)&inputs7, (TfLiteIntArray*)&outputs7, const_cast<void*>(static_cast<const void*>(&opdata7)), OP_MAX_POOL_2D, },
  { (TfLiteIntArray*)&inputs8, (TfLiteIntArray*)&outputs8, const_cast<void*>(static_cast<const void*>(&opdata8)), OP_RESHAPE, },
  { (TfLiteIntArray*)&inputs9, (TfLiteIntArray*)&outputs9, const_cast<void*>(static_cast<const void*>(&opdata9)), OP_FULLY_CONNECTED, },
  { (TfLiteIntArray*)&inputs10, (TfLiteIntArray*)&outputs10, const_cast<void*>(static_cast<const void*>(&opdata10)), OP_SOFTMAX, },
};

static void init_tflite_tensor(size_t i, TfLiteTensor *tensor) {
  tensor->type = tensorData[i].type;
  tensor->is_variable = 0;

#if defined(EI_CLASSIFIER_ALLOCATION_HEAP)
  tensor->allocation_type = tensorData[i].allocation_type;
#else
  tensor->allocation_type = (tensor_arena <= tensorData[i].data && tensorData[i].data < tensor_arena + kTensorArenaSize) ? kTfLiteArenaRw : kTfLiteMmapRo;
#endif
  tensor->bytes = tensorData[i].bytes;
  tensor->dims = tensorData[i].dims;

#if defined(EI_CLASSIFIER_ALLOCATION_HEAP)
  if(tensor->allocation_type == kTfLiteArenaRw){
    uint8_t* start = (uint8_t*) ((uintptr_t)tensorData[i].data + (uintptr_t) tensor_arena);

    tensor->data.data =  start;
  }
  else {
      tensor->data.data = tensorData[i].data;
  }
#else
  tensor->data.data = tensorData[i].data;
#endif // EI_CLASSIFIER_ALLOCATION_HEAP
  tensor->quantization = tensorData[i].quantization;
  if (tensor->quantization.type == kTfLiteAffineQuantization) {
    TfLiteAffineQuantization const* quant = ((TfLiteAffineQuantization const*)(tensorData[i].quantization.params));
    tensor->params.scale = quant->scale->data[0];
    tensor->params.zero_point = quant->zero_point->data[0];
  }

}

static void init_tflite_eval_tensor(int i, TfLiteEvalTensor *tensor) {

  tensor->type = tensorData[i].type;

  tensor->dims = tensorData[i].dims;

#if defined(EI_CLASSIFIER_ALLOCATION_HEAP)
  auto allocation_type = tensorData[i].allocation_type;
  if(allocation_type == kTfLiteArenaRw) {
    uint8_t* start = (uint8_t*) ((uintptr_t)tensorData[i].data + (uintptr_t) tensor_arena);

    tensor->data.data =  start;
  }
  else {
    tensor->data.data = tensorData[i].data;
  }
#else
  tensor->data.data = tensorData[i].data;
#endif // EI_CLASSIFIER_ALLOCATION_HEAP
}

static void* overflow_buffers[EI_MAX_OVERFLOW_BUFFER_COUNT];
static size_t overflow_buffers_ix = 0;
static void * AllocatePersistentBufferImpl(struct TfLiteContext* ctx,
                                       size_t bytes) {
  void *ptr;
  uint32_t align_bytes = (bytes % 16) ? 16 - (bytes % 16) : 0;

  if (current_location - (bytes + align_bytes) < tensor_boundary) {
    if (overflow_buffers_ix > EI_MAX_OVERFLOW_BUFFER_COUNT - 1) {
      ei_printf("ERR: Failed to allocate persistent buffer of size %d, does not fit in tensor arena and reached EI_MAX_OVERFLOW_BUFFER_COUNT\n",
        (int)bytes);
      return NULL;
    }

    // OK, this will look super weird, but.... we have CMSIS-NN buffers which
    // we cannot calculate beforehand easily.
    ptr = ei_calloc(bytes, 1);
    if (ptr == NULL) {
      ei_printf("ERR: Failed to allocate persistent buffer of size %d\n", (int)bytes);
      return NULL;
    }
    overflow_buffers[overflow_buffers_ix++] = ptr;
    return ptr;
  }

  current_location -= bytes;

  // align to the left aligned boundary of 16 bytes
  current_location -= 15; // for alignment
  current_location += 16 - ((uintptr_t)(current_location) & 15);

  ptr = current_location;
  memset(ptr, 0, bytes);

  return ptr;
}
typedef struct {
  size_t bytes;
  void *ptr;
} scratch_buffer_t;
static scratch_buffer_t scratch_buffers[EI_MAX_SCRATCH_BUFFER_COUNT];
static size_t scratch_buffers_ix = 0;

static TfLiteStatus RequestScratchBufferInArenaImpl(struct TfLiteContext* ctx, size_t bytes,
                                                int* buffer_idx) {
  if (scratch_buffers_ix > EI_MAX_SCRATCH_BUFFER_COUNT - 1) {
    ei_printf("ERR: Failed to allocate scratch buffer of size %d, reached EI_MAX_SCRATCH_BUFFER_COUNT\n",
      (int)bytes);
    return kTfLiteError;
  }

  scratch_buffer_t b;
  b.bytes = bytes;

  b.ptr = AllocatePersistentBufferImpl(ctx, b.bytes);
  if (!b.ptr) {
    ei_printf("ERR: Failed to allocate scratch buffer of size %d\n",
      (int)bytes);
    return kTfLiteError;
  }

  scratch_buffers[scratch_buffers_ix] = b;
  *buffer_idx = scratch_buffers_ix;

  scratch_buffers_ix++;

  return kTfLiteOk;
}

static void* GetScratchBufferImpl(struct TfLiteContext* ctx, int buffer_idx) {
  if (buffer_idx > (int)scratch_buffers_ix) {
    return NULL;
  }
  return scratch_buffers[buffer_idx].ptr;
}

static const uint16_t TENSOR_IX_UNUSED = 0x7FFF;

static void ResetTensors() {
  for (size_t ix = 0; ix < MAX_TFL_TENSOR_COUNT; ix++) {
    tflTensors[ix].index = TENSOR_IX_UNUSED;
  }
  for (size_t ix = 0; ix < MAX_TFL_EVAL_COUNT; ix++) {
    tflEvalTensors[ix].index = TENSOR_IX_UNUSED;
  }
}

static TfLiteTensor* GetTensorImpl(const struct TfLiteContext* context,
                               int tensor_idx) {

  for (size_t ix = 0; ix < MAX_TFL_TENSOR_COUNT; ix++) {
    // already used? OK!
    if (tflTensors[ix].index == tensor_idx) {
      return &tflTensors[ix].tensor;
    }
    // passed all the ones we've used, so end of the list?
    if (tflTensors[ix].index == TENSOR_IX_UNUSED) {
      // init the tensor
      init_tflite_tensor(tensor_idx, &tflTensors[ix].tensor);
      tflTensors[ix].index = tensor_idx;
      return &tflTensors[ix].tensor;
    }
  }

  ei_printf("ERR: GetTensor called beyond MAX_TFL_TENSOR_COUNT (%d)\n", MAX_TFL_TENSOR_COUNT);
  return nullptr;
}

static TfLiteEvalTensor* GetEvalTensorImpl(const struct TfLiteContext* context,
                                       int tensor_idx) {

  for (size_t ix = 0; ix < MAX_TFL_EVAL_COUNT; ix++) {
    // already used? OK!
    if (tflEvalTensors[ix].index == tensor_idx) {
      return &tflEvalTensors[ix].tensor;
    }
    // passed all the ones we've used, so end of the list?
    if (tflEvalTensors[ix].index == TENSOR_IX_UNUSED) {
      // init the tensor
      init_tflite_eval_tensor(tensor_idx, &tflEvalTensors[ix].tensor);
      tflEvalTensors[ix].index = tensor_idx;
      return &tflEvalTensors[ix].tensor;
    }
  }

  ei_printf("ERR: GetTensor called beyond MAX_TFL_EVAL_COUNT (%d)\n", (int)MAX_TFL_EVAL_COUNT);
  return nullptr;
}

class EonMicroContext : public MicroContext {
 public:
  EonMicroContext(): MicroContext(nullptr, nullptr, nullptr) { }

  void* AllocatePersistentBuffer(size_t bytes) {
    return AllocatePersistentBufferImpl(nullptr, bytes);
  };
  TfLiteStatus RequestScratchBufferInArena(size_t bytes,
                                           int* buffer_index) {
  return RequestScratchBufferInArenaImpl(nullptr, bytes, buffer_index);
  }
  void* GetScratchBuffer(int buffer_index) {
    return GetScratchBufferImpl(nullptr, buffer_index);
  }

  TfLiteTensor* AllocateTempTfLiteTensor(int tensor_index) {
    return GetTensorImpl(nullptr, tensor_index);
  }
  void DeallocateTempTfLiteTensor(TfLiteTensor* tensor) {
    return;
  }
  bool IsAllTempTfLiteTensorDeallocated() {
    return true;
  }

  TfLiteEvalTensor* GetEvalTensor(int tensor_index) {
    return GetEvalTensorImpl(nullptr, tensor_index);
  }
};

} // namespace

TfLiteStatus tflite_learn_5_init( void*(*alloc_fnc)(size_t,size_t) ) {
#ifdef EI_CLASSIFIER_ALLOCATION_HEAP
  tensor_arena = (uint8_t*) alloc_fnc(16, kTensorArenaSize);
  if (!tensor_arena) {
    ei_printf("ERR: failed to allocate tensor arena\n");
    return kTfLiteError;
  }
#else
  memset(tensor_arena, 0, kTensorArenaSize);
#endif
  tensor_boundary = tensor_arena;
  current_location = tensor_arena + kTensorArenaSize;

  EonMicroContext micro_context_;
  ctx.impl_ = static_cast<void*>(&micro_context_);
  ctx.AllocatePersistentBuffer = &AllocatePersistentBufferImpl;
  ctx.RequestScratchBufferInArena = &RequestScratchBufferInArenaImpl;
  ctx.GetScratchBuffer = &GetScratchBufferImpl;
  ctx.GetTensor = &GetTensorImpl;
  ctx.GetEvalTensor = &GetEvalTensorImpl;
  ctx.tensors_size = 23;
  for (size_t i = 0; i < 23; ++i) {
    TfLiteTensor tensor;
    init_tflite_tensor(i, &tensor);
    if (tensor.allocation_type == kTfLiteArenaRw) {
      auto data_end_ptr = (uint8_t*)tensor.data.data + tensorData[i].bytes;
      if (data_end_ptr > tensor_boundary) {
        tensor_boundary = data_end_ptr;
      }
    }
  }
  if (tensor_boundary > current_location /* end of arena size */) {
    ei_printf("ERR: tensor arena is too small, does not fit model - even without scratch buffers\n");
    return kTfLiteError;
  }
  registrations[OP_RESHAPE] = Register_RESHAPE();
  registrations[OP_CONV_2D] = Register_CONV_2D();
  registrations[OP_MAX_POOL_2D] = Register_MAX_POOL_2D();
  registrations[OP_FULLY_CONNECTED] = Register_FULLY_CONNECTED();
  registrations[OP_SOFTMAX] = Register_SOFTMAX();

  for (size_t i = 0; i < 11; ++i) {
    tflNodes[i].inputs = nodeData[i].inputs;
    tflNodes[i].outputs = nodeData[i].outputs;
    tflNodes[i].builtin_data = nodeData[i].builtin_data;
tflNodes[i].custom_initial_data = nullptr;
      tflNodes[i].custom_initial_data_size = 0;
if (registrations[nodeData[i].used_op_index].init) {
      tflNodes[i].user_data = registrations[nodeData[i].used_op_index].init(&ctx, (const char*)tflNodes[i].builtin_data, 0);
    }
  }
  for (size_t i = 0; i < 11; ++i) {
    if (registrations[nodeData[i].used_op_index].prepare) {
      ResetTensors();

      TfLiteStatus status = registrations[nodeData[i].used_op_index].prepare(&ctx, &tflNodes[i]);
      if (status != kTfLiteOk) {
        return status;
      }
    }
  }
  return kTfLiteOk;
}

static const int inTensorIndices[] = {
  0, 
};
TfLiteStatus tflite_learn_5_input(int index, TfLiteTensor *tensor) {
  init_tflite_tensor(inTensorIndices[index], tensor);
  return kTfLiteOk;
}

static const int outTensorIndices[] = {
  22, 
};
TfLiteStatus tflite_learn_5_output(int index, TfLiteTensor *tensor) {
  init_tflite_tensor(outTensorIndices[index], tensor);
  return kTfLiteOk;
}

TfLiteStatus tflite_learn_5_invoke() {
  for (size_t i = 0; i < 11; ++i) {
    ResetTensors();

    TfLiteStatus status = registrations[nodeData[i].used_op_index].invoke(&ctx, &tflNodes[i]);

#if EI_CLASSIFIER_PRINT_STATE
    ei_printf("layer %lu\n", i);
    ei_printf("    inputs:\n");
    for (size_t ix = 0; ix < tflNodes[i].inputs->size; ix++) {
      auto d = tensorData[tflNodes[i].inputs->data[ix]];

      size_t data_ptr = (size_t)d.data;

      if (d.allocation_type == kTfLiteArenaRw) {
        data_ptr = (size_t)tensor_arena + data_ptr;
      }

      if (d.type == TfLiteType::kTfLiteInt8) {
        int8_t* data = (int8_t*)data_ptr;
        ei_printf("        %lu (%zu bytes, ptr=%p, alloc_type=%d, type=%d): ", ix, d.bytes, data, (int)d.allocation_type, (int)d.type);
        for (size_t jx = 0; jx < d.bytes; jx++) {
          ei_printf("%d ", data[jx]);
        }
      }
      else {
        float* data = (float*)data_ptr;
        ei_printf("        %lu (%zu bytes, ptr=%p, alloc_type=%d, type=%d): ", ix, d.bytes, data, (int)d.allocation_type, (int)d.type);
        for (size_t jx = 0; jx < d.bytes / 4; jx++) {
          ei_printf("%f ", data[jx]);
        }
      }
      ei_printf("\n");
    }
    ei_printf("\n");

    ei_printf("    outputs:\n");
    for (size_t ix = 0; ix < tflNodes[i].outputs->size; ix++) {
      auto d = tensorData[tflNodes[i].outputs->data[ix]];

      size_t data_ptr = (size_t)d.data;

      if (d.allocation_type == kTfLiteArenaRw) {
        data_ptr = (size_t)tensor_arena + data_ptr;
      }

      if (d.type == TfLiteType::kTfLiteInt8) {
        int8_t* data = (int8_t*)data_ptr;
        ei_printf("        %lu (%zu bytes, ptr=%p, alloc_type=%d, type=%d): ", ix, d.bytes, data, (int)d.allocation_type, (int)d.type);
        for (size_t jx = 0; jx < d.bytes; jx++) {
          ei_printf("%d ", data[jx]);
        }
      }
      else {
        float* data = (float*)data_ptr;
        ei_printf("        %lu (%zu bytes, ptr=%p, alloc_type=%d, type=%d): ", ix, d.bytes, data, (int)d.allocation_type, (int)d.type);
        for (size_t jx = 0; jx < d.bytes / 4; jx++) {
          ei_printf("%f ", data[jx]);
        }
      }
      ei_printf("\n");
    }
    ei_printf("\n");
#endif // EI_CLASSIFIER_PRINT_STATE

    if (status != kTfLiteOk) {
      return status;
    }
  }
  return kTfLiteOk;
}

TfLiteStatus tflite_learn_5_reset( void (*free_fnc)(void* ptr) ) {
#ifdef EI_CLASSIFIER_ALLOCATION_HEAP
  free_fnc(tensor_arena);
#endif

  // scratch buffers are allocated within the arena, so just reset the counter so memory can be reused
  scratch_buffers_ix = 0;

  // overflow buffers are on the heap, so free them first
  for (size_t ix = 0; ix < overflow_buffers_ix; ix++) {
    ei_free(overflow_buffers[ix]);
  }
  overflow_buffers_ix = 0;
  return kTfLiteOk;
}