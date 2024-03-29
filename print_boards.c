#include "print_boards.h"
#include "term_control.h"
#include <stdint.h>

#pragma region helper_functions

void print_columns() {
  const char columns[] = "0123456789";
  for (int i = 0; i < 10; i++) {
    term_print("   ");
    term_printc(columns[i]);
  }
}

void print_header() {
  char player_header[] = "Your Board:";
  char bot_header[] = "Opponent Board:";

  // print both headers
  term_print(player_header);
  term_set_cursor_pos(1, 49);
  term_println(bot_header);

  // print column-numbers
  term_print("\n ");
  print_columns();
  term_set_cursor_pos(3, 50);
  print_columns();
}

void print_legend() {
  // trust me, this is fine
  term_set_cursor_pos(1, 100);
  term_print("\e[1mLegend:\e[0m");
  term_set_cursor_pos(2, 103);
  term_print("\u25A0  = Ship");
  term_set_cursor_pos(3, 103);
  term_print("\e[1;31mX\e[0m  = Hit");
  term_set_cursor_pos(4, 103);
  term_print("\e[1;34mO\e[0m  = Miss");
  term_set_cursor_pos(5, 102);
  term_print("\e[1;32m< >\e[0m = Cursor");
  term_set_cursor_pos(7, 100);
  term_print("\e[1mControls:\e[0m");
  term_set_cursor_pos(8, 102);
  term_print("\e[1mWASD\e[0m => Move the Cursor");
  term_set_cursor_pos(9, 105);
  term_print("\e[1m\u21b5\e[0m => Shoot");
}

void print_row_delimiter(int row) {
  if (row != 9) {
    term_print(" ─┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤");
    term_print("      ");
    term_println("─┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤");
  } else {
    term_print(" ─┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘");
    term_print("      ");
    term_println("─┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘");
  }
}

void print_field(int y, int x, enum boardstates board[], int cursor_x, int cursor_y, int print_ships) {
  char ship_str[] = "\u25A0";
  char hit_str[] = "\e[1;31mX\e[0m";
  char miss_str[] = "\e[1;34mO\e[0m";

  if (y == cursor_y && x == cursor_x) {
    term_print("\e[1;32m<\e[0m");
  } else {
    term_printc(' ');
  }

  // print all the fancy ships and hits, etc.
  switch (board[y * 10 + x]) {
  case 's':
    if (print_ships) {
      term_print(ship_str);
    } else {
      term_printc(' ');
    }
    break;

  case 'X':
    term_print(hit_str);
    break;

  case 'O':
    term_print(miss_str);
    break;

  case ' ':
    term_printc(' ');
    break;

  default:
    term_printc(-1);
    break;
  }

  // continue printing fancy formatting/cursor
  if (y == cursor_y && x == cursor_x) {
    term_print("\e[1;32m>\e[0m");
  } else {
    term_printc(' ');
  }
}

void print_row(int row, enum boardstates board[], int cursor_x, int cursor_y, int print_ships) {
  const char rows[] = "ABCDEFGHIJ";

  // print all the fancy formatting/cursor
  term_printc(rows[row]);
  term_print(" │");
  for (int x = 0; x < 10; x++) {
    print_field(row, x, board, cursor_x, cursor_y, print_ships);
    term_print("│");
  }
}

#pragma endregion

void print_boards(struct board *player, struct board *bot, struct cursor_position *cursor_position) {
  // reset cursor-position
  term_set_cursor_pos(1, 1);

  // print lines that are seperatefrom the dynamically changing board
  print_header();

  // print all the boards
  term_set_cursor_pos(4, 1);
  print_row_delimiter(0);
  for (int y = 0; y < 10; y++) {
    print_row(y, player->data, -1, -1, 1);
    term_print("     ");
    print_row(y, bot->data, cursor_position->cursor_x, cursor_position->cursor_y, 0);
    term_printc('\n');
    print_row_delimiter(y);
  }

  // print a nice legend using ansi instead of newlines
  // to move the cursor to avoid drawing over the boards
  print_legend();

  // move the cursor somewhere nice so it look good when quemu is terminated
  term_set_cursor_pos(25, 1);
}

void update_boards(struct board *player, struct board *bot, struct cursor_position *cursor_position) {

  for (int i = 0; i < 10; i++) {
    term_set_cursor_pos(5 + 2 * i, 4);
    for (int j = 0; j < 10; j++) {
      print_field(i, j, player->data, -1, -1, 1);
      term_print("\e[C");
    }
    term_set_cursor_pos(5 + 2 * i, 52);
    for (int j = 0; j < 10; j++) {
      print_field(i, j, bot->data, cursor_position->cursor_x, cursor_position->cursor_y, 0);
      term_print("\e[C");
    }
  }

  // move the cursor somewhere nice so it look good when quemu is terminated
  term_set_cursor_pos(25, 1);
}