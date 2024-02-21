#include "board.h"
#include "math.h"
#include "random.h"
#include <stdint.h>

#pragma region helper - functions

void board_init(board *board) {
  for (int i = 0; i < 100; i++) {
    board->data[i] = EMPTY;
  }
}

int coord_to_index(int x, int y) { return 10 * y + x; }

void dir_to_offset(int offsets[2], int dir) {
  offsets[0] = 0;
  offsets[1] = 0;
  switch (dir) {
  case 0:
    offsets[1] -= 1;
    break;
  case 1:
    offsets[0] += 1;
    break;
  case 2:
    offsets[1] += 1;
    break;
  case 3:
    offsets[0] -= 1;
    break;
  }
}

uint8_t is_valid_placement(board *board, int ship_x, int ship_y, int dir, int len) {
  // ensure dir is a valid direction
  if (dir != math_mod(dir, 4)) {
    return 0;
  }

  // ensure placement is within bounds of board
  // by checking begin and endpoints
  if (ship_x != math_mod(ship_x, 10) || ship_y != math_mod(ship_y, 10)) {
    return 0;
  }
  int offsets[2];
  dir_to_offset(offsets, dir);
  int end_x = ship_x + offsets[0] * len;
  int end_y = ship_y + offsets[1] * len;
  if (end_x != math_mod(end_x, 10) || end_y != math_mod(end_y, 10)) {
    return 0;
  }

  // for each field of the ship, check if adjacend fields are empty
  for (int i = 0; i < len; i++) {
    int current_x = ship_x + i * offsets[0];
    int current_y = ship_y + i * offsets[1];

    // check allsurrounding fields (this checks some twice/thrice, but i dont care)
    int check_offsets[] = {-1, 0, 1};

    for (int j = 0; j < 3; j++) {
      if (current_x + check_offsets[j] == math_mod(current_x + check_offsets[j], 10)) {
        for (int k = 0; k < 3; k++) {
          if (current_y + check_offsets[k] == math_mod(current_y + check_offsets[k], 10)) {
            if (board->data[coord_to_index(current_x + check_offsets[j], current_y + check_offsets[k])] != EMPTY) {
              return 0;
            }
          }
        }
      }
    }
  }
}

void place_ship(board *board, int ship_x, int ship_y, int dir, int len) {
  int x = ship_x;
  int y = ship_y;
  int offsets[2];
  dir_to_offset(offsets, dir);
  for (int i = 0; i < len; i++) {
    board->data[coord_to_index(x + i * offsets[0], y + i * offsets[1])] = SHIP;
  }
}

#pragma endregion

void board_place_ships(board *board) {
  while (1) {
    // clear the board
    board_init(board);

    // iterate over boards and place them
    int lengths[] = {5, 4, 4, 3, 3, 3, 2, 2, 2, 2};
    for (int ship = 0; ship < 10; ship++) {

      // attempt to place each ship x times
      // on succesess continue to next ship
      // else retry
      int maxtrys = 32;
      int trys;
      for (trys = 0; trys < maxtrys; trys++) {

        // collect random data from rng
        uint16_t rand = ((uint16_t)rng_getRandomValue_waiting()) << 8 | (uint16_t)rng_getRandomValue_waiting();
        int x = math_mod((rand & 0b1111111000000000) >> 9, 10);
        int y = math_mod((rand & 0b0000000111111100) >> 2, 10);
        int dir = rand & 0b0000000000000011;

        // place if placement is valid
        if (is_valid_placement(board, x, y, dir, lengths[ship])) {
          place_ship(board, x, y, dir, lengths[ship]);

          // if that was the last ship, return, else continue to next ship
          if (ship == 9) {
            return;
          } else {
            break;
          }
        }
      }

      // we needed more trys than were allowed, need to restart
      if (trys == maxtrys) {
        break;
      }
    }
  }
}

uint8_t board_shoot(board *board, cursor_position *coordinates) { return board_shoot_index(board, coord_to_index(coordinates->cursor_x, coordinates->cursor_y)); }

uint8_t board_shoot_index(board *board, int field_index) {
  switch (board->data[field_index]) {
  case SHIP:
    board->data[field_index] = HIT;
    return 4;
  case EMPTY:
    board->data[field_index] = MISS;
    return 2;
  }
  return 0;
}

uint8_t board_bot_shoot(board *board) {
  int shots[100];
  int shotcount = 0;

  // fill the array with indexes of actually possible shots
  for (int i = 0; i < 100; i++) {
    if (board->data[i] == EMPTY || board->data[i] == SHIP) {
      shots[shotcount] = i;
      shotcount++;
    }
  }

  // choose a random index from the availible shots
  if (shotcount == 0) {
    return 0;
  }
  int shot = math_mod(rng_getRandomValue_immediately(), shotcount);

  // take the shot
  board_shoot_index(board, shots[shot]);
}

uint8_t cursor_parse_wasd(cursor_position *cursor_position, char wasd) {
  switch (wasd) {
  case 'w':
    cursor_position->cursor_y--;
    break;
  case 'a':
    cursor_position->cursor_x--;
    break;
  case 's':
    cursor_position->cursor_y++;
    break;
  case 'd':
    cursor_position->cursor_x++;
    break;

  default:
    return 0;
  }
  cursor_position->cursor_x = math_mod(cursor_position->cursor_x, 10);
  cursor_position->cursor_y = math_mod(cursor_position->cursor_y, 10);
  return 1;
}

uint8_t cursor_parse_input(board *bot_board, cursor_position *cursor_position, char wasd) {
  uint8_t res = 0;
  res = cursor_parse_wasd(cursor_position, wasd);
  if (wasd == 0xD) {
    res = board_shoot(bot_board, cursor_position);
  }
  return res;
}