#include "math.h"
#include <stdint.h>

int32_t math_div(int32_t dividend, int32_t divisor) {

  // catch division by zero
  if (divisor == 0) {
    return 0x7FFFFFFF;
  }

  // make sure dividend and divisor are positive (calculate/save sign of result)
  uint32_t sign = 1;
  if (divisor < 0) {
    divisor *= -1;
    sign *= -1;
  }
  if (dividend < 0) {
    dividend *= -1;
    sign *= -1;
  }

  // calculate result // this is inefficient, i dont like it
  uint32_t result = 0;
  while (dividend >= divisor) {
    dividend -= divisor;
    result++;
  }
  result *= sign;

  return result;
}

uint32_t math_mod(int32_t dividend, uint32_t divisor) {

  // catch modulation by 0
  if (divisor == 0) {
    return 0xFFFFFFFF;
  }

  // calculate result // this is inefficient, i dont like it
  while (dividend < 0) {
    dividend += divisor;
  }
  while (dividend >= divisor) {
    dividend -= divisor;
  }

  return dividend;
}

uint32_t math_pow(int32_t base, uint32_t exponent) {
  uint32_t res = 1;
  for (int i = 0; i < exponent; i++) {
    res *= base;
  }
  return res;
}
