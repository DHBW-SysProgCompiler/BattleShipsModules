#include "screen_control.h"
#include "uart.h"
#include <stdint.h>

void init() {
  // initialize uart
  uart_init();
  // nothing else to be done *yet*
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