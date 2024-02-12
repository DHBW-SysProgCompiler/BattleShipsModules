/**
 * @file
 * @copyright
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * @author Eric Erath
 *
 * @brief Functions to print entire Battleships-Boards to the terminal
 **/

#ifndef BOARDPRINT_H
#define BOARDPRINT_H

#include "term_control.h"
#include <stdint.h>

/**
 * @brief print both player- and bot-boards side by side
 *
 * @param player_board board of the player
 * @param bot_board board of the bot
 * @param cursor_x x-position of the player-cursor (origin is A0/top-left)
 * @param cursor_y y-position of the player-cursor (set -1 to hide cursor)
 *
 * @note boards do not have to be 0-terminated
 * @note however they have to be length 100 (101 if 0-terminated)
 * @note any other lengths will lead to unwanted behaviour
 */
void print_boards(char player_board[], char bot_board[], int cursor_x,
                  int cursor_y);

#endif