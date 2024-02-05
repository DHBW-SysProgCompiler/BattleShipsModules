#ifndef TERMCONTROL_H
#define TERMCONTROL_H

#include <stdint.h>

/**
 * @brief Initialize the Terminal-Controller
 */
void term_init();

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

/**
 * @brief tries to read a char from stdin and append it to the buffer
 * 
 * @return returns the read char
 */
char stdin_read();

/**
 * @brief returns the buffered string from stdin
 * 
 * @return String from User-Input
 */
char* stdin_get();

/**
 * @brief clears the buffer fron stdin
 */
void stdin_clear();

#endif