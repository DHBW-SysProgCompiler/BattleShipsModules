#include "timer.h"

void Interrupt8_Handler(void) {
  uint32_t cc0 = timer_check(TIMER0, CC0);
  uint32_t cc1 = timer_check(TIMER0, CC1);
  uint32_t cc2 = timer_check(TIMER0, CC2);
  uint32_t cc3 = timer_check(TIMER0, CC3);

  timer_event_clear(TIMER0, CC0);
  cc0 = timer_check(TIMER0, CC0);

  timer_event_clear(TIMER0, CC1);
  cc1 = timer_check(TIMER0, CC1);

  timer_event_clear(TIMER0, CC2);
  cc2 = timer_check(TIMER0, CC2);

  timer_event_clear(TIMER0, CC3);
  cc3 = timer_check(TIMER0, CC3);

  uart_writeByte(0x2B);
}

int main(void) {
  uart_init();
  uart_writeByte(0x2F);
  timer_init(TIMER0, 15, 3, 1953);
  timer_start(TIMER0);

  for (;;) {
    /* code */
  }

  return 0;
}