#include "term_control.h"
#include "heap_allocations.h"
#include "register_access.h"
#include "uart.h"
#include <stdint.h>

char *buffer = 0;
uint32_t buffer_len = 0;
uint32_t buffer_use = 0;

void term_init(char *buff, uint32_t len) {
  // initialize uart
  uart_init();

  // save addr and len of buffer
  buffer = buff;
  buffer_len = len;
}

void printc(char c) {
  // simply pass char to uart
  uart_writeByte(c);
}

void print(char s[], uint32_t len) {
  // iterate over s, print each char individually
  for (int i = 0; i < len; i++) {
    printc(s[i]);
  }
}

void clear_screen() {
  // clears the screen via ansi-voodoo
  print("\e[2J", 4);
}

void stdin_clear() {
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

char stdin_read() {
  // try to read a char via uart
  char c = uart_readByte();
  if (c != 0 && c != 0xD) {
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

uint32_t stdin_len() { return buffer_use; }