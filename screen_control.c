#include <stdint.h>
#include "uart.h"
#include "screen_control.h"

void init() { uart_init(); }
void printc(char c) { uart_writeByte(c); }
void print(char s[], uint32_t len) {
  for (int i = 0; i < len; i++) {
    printc(s[i]);
  }
}
void clear_screen() { print("\e[2J", 4); }