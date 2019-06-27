#ifndef HEADER_H_
#define HEADER_H_

#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C"
{
#endif

#if defined(__clang__) || defined(__GNUC__)
#define LIKELY(x) __builtin_expect(!!(x), 1)
#define UNLIKELY(x) __builtin_expect(!!(x), 0)
#else
#define LIKELY(x) (x)
#define UNLIKELY(x) (x)
#endif

    union Entry
    {
        int missing;
        float fvalue;
        int qvalue;
    };

    size_t get_num_output_group(void);
    size_t get_num_feature(void);
    float predict(union Entry * data, int pred_margin);
    float predict_margin_unit0(union Entry * data);
    float predict_margin_unit1(union Entry * data);
    float predict_margin_unit2(union Entry * data);
    float predict_margin_unit3(union Entry * data);
    float predict_margin_unit4(union Entry * data);
    float predict_margin_unit5(union Entry * data);
    float predict_margin_unit6(union Entry * data);
    float predict_margin_unit7(union Entry * data);

#ifdef __cplusplus
}
#endif

#endif
