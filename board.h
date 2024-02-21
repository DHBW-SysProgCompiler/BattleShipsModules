/**
 * @file
 * @copyright
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * @author Eric Erath
 *
 * @brief Structs, Enums and relevant Functions for the boards of the game
 **/

#ifndef BOARD_H
#define BOARD_H

#include <stdint.h>

/**
 * @brief enumerates all possible states of a single field on the gameboard
 * @note '⎵' = empty space
 * @note 's' = part of a ship
 * @note 'X' = HIT => part of a ship, that has already been shot
 * @note 'O' = MISS => empty space, that has already been shot
 */
typedef enum boardstates { EMPTY = ' ', SHIP = 's', HIT = 'X', MISS = 'O' } boardstates;

/** @brief a struct to store all relevant information about the gamestate */
typedef struct board {
  /** @brief represents the board of the classic Batleship-Game */
  boardstates data[100];
} board;

/** @brief a struct to store the position of the players cursor */
typedef struct cursor_position {
  /** @brief x-coordinate of the cursor */
  int cursor_x;
  /** @brief y-coordinate of the cursor */
  int cursor_y;
} cursor_position;

/**
 * @brief initializes the board to all empty spaces
 *
 * @param board pointer to the board to be initialized
 */
void board_init(board *board);

/**
 * @brief shoots to given coordinates
 *
 * @param board pointer to the board to be initialized
 * @param coordinates position to shoot at
 */
void board_shoot(board *board, cursor_position *coordinates);

/**
 * @brief parses a char from user and interprets as wasd-controls, alters position accordingly
 *
 * @param cursor_position pointer to the cursor_position to be updated
 * @param wasd char to be parsed
 *
 * @return 1 if position was updated, else 0
 */
uint8_t cursor_parse_wasd(cursor_position *cursor_position, char wasd);

#endif