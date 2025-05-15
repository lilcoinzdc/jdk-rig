#ifndef ARGON2_AVX512F_H
#define ARGON2_AVX512F_H

#include "core.h"

void jdkrig_ar2_fill_segment_avx512f(const argon2_instance_t *instance, argon2_position_t position);
int jdkrig_ar2_check_avx512f(void);

#endif // ARGON2_AVX512F_H
