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

#include "board.h"
#include "term_control.h"
#include <stdint.h>

/**
 * @brief print both player- and bot-boards side by side
 *
 * @param player board of the player
 * @param bot board of the bot
 * @param cursor_position position of the player-cursor
 */
void print_boards(struct board *player, struct board *bot, struct cursor_position *cursor_position);

#endif