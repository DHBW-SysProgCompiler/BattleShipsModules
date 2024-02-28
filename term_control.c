#include "term_control.h"
#include "math.h"
#include "register_access.h"
#include "uart.h"
#include <stdint.h>

char *buffer = 0;
uint32_t buffer_len = 0;
uint32_t buffer_use = 0;

#pragma region init

void term_init(char *buff, uint32_t len) {
  // initialize uart
  uart_init();

  // save addr and len of buffer
  buffer = buff;
  buffer_len = len;

  // hide cursor
  term_print("\e[?25l");
}

#pragma endregion

#pragma region output

void term_printc(char c) {
  // simply pass char to uart
  uart_writeByte(c);
}

void term_print(char s[]) {
  // iterate over s, print each char individually
  uint32_t i = 0;

  while (s[i] != 0) {
    term_printc(s[i++]);
  }
}

void term_println(char s[]) {
  term_print(s);
  term_printc('\n');
}

void term_printnr(int number) {
  // handle negative numbers
  if (number < 0) {
    term_printc('-');
    number *= -1;
  }

  int len = 1;
  while (number >= math_pow(10, len)) {
    len++;
  }
  for (int i = len - 1; i >= 0; i--) {
    int pow = math_pow(10, i);
    int digit = math_div(number, pow);
    term_printc('0' + digit);
    number -= digit * pow;
  }
}

void term_clear_screen() {
  // clears the screen via ansi-voodoo
  term_print("\e[2J\e[3J\e[H");
}

#pragma endregion

#pragma region input

void term_stdin_clear() {
  // clear builtin buffer from qemu
  while (uart_readByte() != 0) {
    continue;
  }
  // clear buffer passed via innit
  for (uint32_t i = 0; i < buffer_len; i++) {
    buffer[i] = 0;
  }
  // reset buffer_use
  buffer_use = 0;
}

char term_stdin_read() {
  // try to read a char via uart
  char c = uart_readByte();
  if (c != 0 && c != 0xD && c != '\e') {
    // append char to the next open slot in the buffer
    for (int32_t i = 0; i < buffer_len; i++) {
      if (buffer[i] == 0) {
        buffer[i] = c;
        buffer_use++;
        break;
      }
    }
  }
  return c;
}

uint32_t term_stdin_len() { return buffer_use; }

#pragma endregion

#pragma region cursor

// all of this code is powered by ansi-voodoo
// this should suffice as documentation

void term_save_cursor_pos() { term_print("\e 7"); }

void term_restore_cursor_pos() { term_print("\e 8"); }

void term_set_cursor_pos(char pos[]) {
  term_print("\e[");
  term_print(pos);
  term_print("H");
}

#pragma endregion