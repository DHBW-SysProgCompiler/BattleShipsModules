#ifndef MATH_H
#define MATH_H

#include <stdint.h>

/**
 * @brief divide two integers, alwais round down
 *
 * @param dividend interger to be divided
 * @param divisor integer to be divided by
 *
 * @return the result of the integer-division
 *
 * @note division by zero returns int32_t.max_value (0x7FFF_FFFF)
 */
int32_t math_div(int32_t dividend, int32_t divisor);

/**
 * @brief modulate two integers
 *
 * @param dividend interger to be divided
 * @param divisor integer to be divided by
 *
 * @return the result of the integer-modulation
 *
 * @note modulation by zero returns uint32_t.max_value (0xFFFF_FFFF)
 */
uint32_t math_mod(uint32_t dividend, uint32_t divisor);

#endif