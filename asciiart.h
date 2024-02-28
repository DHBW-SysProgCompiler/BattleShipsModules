/**
 * @file
 * @copyright
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * @author Eric Erath
 *
 * @brief Functions to print ascii-art to the terminal
 **/

#ifndef ASCII_H
#define ASCII_H

/**
 * @brief print ascii-art for the main-screen
 */
void art_print_main();
/**
 * @brief print ascii-art for the victory-screen
 */
void art_print_victory();

/**
 * @brief print ascii-art for the loss-screen
 */
void art_print_loss();

/**
 * @brief print a bar graph for better visual display of statistics
 *
 * @param hits number of hits
 * @param misses number of misses
 */
void art_print_bargraph(int hits, int misses);

#endif