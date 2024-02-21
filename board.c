#include "board.h"
#include "math.h"
#include <stdint.h>

void board_init(board *board) {
  for (int i = 0; i < 100; i++) {
    board->data[i] = EMPTY;
  }
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

void board_shoot(board *board, cursor_position *coordinates) {}