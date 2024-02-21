#include "random.h"
#include <stdint.h>

// also need access for basic register read and write
#include "register_access.h"

/**
 * @brief Enables the generation of random numbers
 *
 * This is done by writing a `1` to the `START_TASK` of the RNG peripheral.
 */
void rng_init() {

  // Write a '1' to the Start Task, to start the generation of random numbers
  register_write((RNG_BASE_ADDRESS + RNG_START), RNG_TASK_START);
}

/**
 * @brief Get the Random Value from the generator immediately.
 *
 * The function is **NOT** waiting until the next value is generated!
 *
 * @return uint8_t random byte
 */
uint8_t rng_getRandomValue_immediately() {

  // Read 32-Bit Register containing the RNG Value
  uint32_t randomValue = register_read((RNG_BASE_ADDRESS + RNG_VALUE));

  // its actual just 8-Bit, so cast it.
  return (uint8_t)randomValue;
}

/**
 * @brief Get the next Random Value from the generator.
 *
 * The function waits until the next value is generated!
 *
 * @return uint8_t random byte
 */
uint8_t rng_getRandomValue_waiting() {
  while (!register_read(RNG_BASE_ADDRESS + RNG_VALRDY)) {
  }
  register_write(RNG_BASE_ADDRESS + RNG_VALRDY, 0);
  return register_read(RNG_BASE_ADDRESS + RNG_VALUE);
}
