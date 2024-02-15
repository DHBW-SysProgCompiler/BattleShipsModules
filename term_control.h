/**
 * @file
 * @copyright
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * @author Eric Erath
 *
 * @brief Functions to control in and output from terminal
 **/

#ifndef TERMCONTROL_H
#define TERMCONTROL_H

#include <stdint.h>

#pragma region init

/**
 * @brief Initialize the Terminal-Controller
 *
 * @param buff poiter to a buffer where user input will be stored
 * @param len length of the buffer
 */
void term_init(char *buff, uint32_t len);

#pragma endregion

#pragma region output

/**
 * @brief clear the console-screen
 */
void term_clear_screen();

/**
 * @brief Print a singe char
 *
 * @param c char to be printed
 */
void term_printc(char c);

/**
 * @brief Prints an entire String (char-array)
 *
 * @param s the char-array to be printed
 */
void term_print(char s[]);

/**
 * @brief Prints an entire String (char-array) and appends a newline
 *
 * @param s the char-array to be printed
 */
void term_println(char s[]);

#pragma endregion

#pragma region input

/**
 * @brief tries to read a char from stdin and append it to the buffer
 *
 * @return read char
 */
char term_stdin_read();

/**
 * @brief returns the length of the buffered string from stdin
 *
 * @return length of filled part in the buffer
 *
 * @note will not append /n to buffer
 * @note they are to dangerous when printing string read from stdin
 * @note will still return 0xD to detect presses of the enter-key
 * @note will also discard ALL escapes (but still return)
 */
uint32_t term_stdin_len();

/**
 * @brief clears the buffer from stdin
 */
void term_stdin_clear();

#pragma endregion

#pragma region cursor

/**
 * @brief saves the current cursor-position, so that it can be restored with
 * term_restore_cursor_pos()
 */
void term_save_cursor_pos();

/**
 * @brief restores the saved position of the terminal-cursor
 *
 * @note restoring when not having saved first will lead to undefined behaviour
 */
void term_restore_cursor_pos();

/**
 * @brief sets the cursor-position
 *
 * @param pos new position for cursor in format "y;x"
 *
 * @note origin is 1;1 in top-left of terminal
 */
void term_set_cursor_pos(char pos[]);

#pragma endregion

#endif