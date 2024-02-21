#include "board.h"
#include "math.h"
#include "random.h"
#include <stdint.h>

void board_init(board *board) {
  for (int i = 0; i < 100; i++) {
    board->data[i] = EMPTY;
  }
}

uint8_t board_shoot(board *board, cursor_position *coordinates) {
  int i = coordinates->cursor_y * 10 + coordinates->cursor_x;
  switch (board->data[i]) {
  case SHIP:
    board->data[i] = HIT;
    return 4;
  case EMPTY:
    board->data[i] = MISS;
    return 2;
  }
  return 0;
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