#ifndef TERMCONTROL_H
#define TERMCONTROL_H

#include <stdint.h>

/**
 * @brief Initialize the Terminal-Controller
 *
 * @param buff poiter to a buffer where user input will be stored
 * @param len length of the buffer
 */
void term_init(char *buff, uint32_t len);

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
 * @return read char
 */
char stdin_read();

/**
 * @brief returns the length of the buffered string from stdin
 *
 * @return length of filled part in the buffer
 *
 * @note will not append /n to buffer
 * @note they are to dangerous when printing string read from stdin
 * @note will still return 0xD to detect presses of the enter-key
 */
uint32_t stdin_len();

/**
 * @brief clears the buffer fron stdin
 */
void stdin_clear();

#endif