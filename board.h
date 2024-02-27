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

#include "board.h"
#include "math.h"
#include "random.h"
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
 * @brief places the ships on the board
 *
 * @param board pointer to the board to be initialized
 */
void board_place_ships(board *board);

/**
 * @brief shoots to given coordinates
 *
 * @param board pointer to the board to be shot at
 * @param coordinates position to shoot at
 *
 * @return 2 on MISS, 4 on HIT, else 0
 */
uint8_t board_shoot(board *board, cursor_position *coordinates);

/**
 * @brief shoots to given coordinates
 *
 * @param board pointer to the board to be shot at
 * @param field_index array-index to shoot at
 *
 * @return 2 on MISS, 4 on HIT, else 0
 */
uint8_t board_shoot_index(board *board, int field_index);

/**
 * @brief shoots to given coordinates
 *
 * @param board pointer to the player_board to be shot at by the bot
 *
 * @return 2 on MISS, 4 on HIT, else 0
 */
uint8_t board_bot_shoot(board *board);

/**
 * @brief parses a char from user and interprets as wasd-controls, alters position accordingly
 *
 * @param cursor_position pointer to the cursor_position to be updated
 * @param wasd char to be parsed
 *
 * @return 1 if position was updated, else 0
 */
uint8_t cursor_parse_wasd(cursor_position *cursor_position, char wasd);

/**
 * @brief parses a char from user and interprets as wasd-controls, alters position accordingly, shoots on enter
 *
 * @param bot_board pointer to the bot-board to be updated
 * @param cursor_position pointer to the cursor_position to be updated
 * @param wasd char to be parsed
 *
 * @return default 0, else board has to be reprinted
 */
uint8_t cursor_parse_input(board *bot_board, cursor_position *cursor_position, char wasd);

/**
 * @brief counts how many fields of the board are in the given state
 *
 * @param board board to be counted on
 * @param stat what kind of state should be counted
 *
 * @return number of fields in the given state
 */
uint8_t board_stats(board *board, boardstates stat);

#endif