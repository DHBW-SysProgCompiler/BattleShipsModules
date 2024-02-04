#ifndef SCREENCONTROL_H
#define SCREENCONTROL_H

#include <stdint.h>

/**
 * @brief Initialize the Screen-Controller
 */
void init();

/**
 * @brief clear the console-screen
 */
void clear_screen();

/**
 * @brief Print a singe char
 *
 * @param c char to be printed
 */
void printc(char c);

/**
 * @brief Prints an entire String (char-array)
 *
 * @param s the char-array to be printed
 * @param len length of the array
 */
void print(char s[], uint32_t len);

#endif