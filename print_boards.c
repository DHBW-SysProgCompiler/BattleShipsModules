#include "print_boards.h"
#include "math.h"
#include "term_control.h"
#include <stdint.h>

#pragma region helper_functions

void print_columns() {
  char columns[] = "0123456789";
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
  term_set_cursor_pos("1;49");
  term_println(bot_header);

  // print column-numbers
  term_print("\n ");
  print_columns();
  term_set_cursor_pos("3;50");
  print_columns();
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

void print_row(int row, char board[], int cursor_x, int cursor_y) {
  char rows[] = "ABCDEFGHIJ";
  term_printc(rows[row]);
  term_print(" │");
  for (int x = 0; x < 10; x++) {
    if (row == cursor_y && x == cursor_x) {
      term_printc('<');
    } else {
      term_printc(' ');
    }
    term_printc(board[row * 10 + x]);
    if (row == cursor_y && x == cursor_x) {
      term_printc('>');
    } else {
      term_printc(' ');
    }
    term_print("│");
  }
}

#pragma endregion

void print_boards(char player_board[], char bot_board[], int cursor_x,
                  int cursor_y) {
  print_header();

  // print all the boards
  term_set_cursor_pos("4;1");
  print_row_delimiter(0);
  for (int y = 0; y < 10; y++) {
    print_row(y, player_board, cursor_x, cursor_y);
    term_print("     ");
    print_row(y, bot_board, -1, -1);
    term_printc('\n');
    print_row_delimiter(y);
  }
}