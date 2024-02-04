#include <stdint.h>

#include "nvic.h"
#include "timer.h"

#include "register_access.h"

void timer_init(enum Timer timer, uint32_t prescaler, uint32_t bitmode, uint32_t cc0) {
  // Add prescaler
  timer_prescaler(timer, prescaler);
  // Add bitmode
  timer_bitmode(timer, bitmode);
  // Add capture target
  timer_add_capture(timer, CC0, cc0);
}

void timer_prescaler(enum Timer timer, uint32_t prescaler) {
  /* Prescaler --------------------------------------------------------------
  Set the Prescaler to min (1 = 0b00000001)
  register_write((TIMER0_BASE_ADDRESS + TIMER_PRESCALER), 1);

  Set the Prescaler to max (15 = 0b00001111)
  register_write((TIMER0_BASE_ADDRESS + TIMER_PRESCALER), 15);

  Set the Prescaler to custom value from arguments
  */
  register_write((timer + TIMER_PRESCALER), prescaler);
}

void timer_bitmode(enum Timer timer, uint32_t bitmode) {
  /* BitMode ----------------------------------------------------------------
  set BitMode Register = use 8bit
  register_write((TIMER0_BASE_ADDRESS + TIMER_BITMODE), 0);

  set BitMode Register = use 32bit
  register_write((TIMER0_BASE_ADDRESS + TIMER_BITMODE), 3);

  set BitMode Register to custom value from arguments 
  */
  register_write((timer + TIMER_BITMODE), bitmode);
}

void timer_add_capture(enum Timer timer, enum Capture cc, uint32_t compareValue) {
  uint32_t timer_cc;
  uint32_t int_compare;
  uint32_t clear;
  switch (cc) {
    case CC0:
      timer_cc = TIMER_CC_0;
      int_compare = INT_COMPARE0; // Interrupt on Compare[0]
      clear = 0x01; //  A=1 -- CLEAR on CC[0]
      break;
    case CC1:
      timer_cc = TIMER_CC_1;
      int_compare = INT_COMPARE1;
      clear = 0x02; //  B=1 -- CLEAR on CC[1]
      break;
    case CC2:
      timer_cc = TIMER_CC_2;
      int_compare = INT_COMPARE2;
      clear = 0x04; //  C=1 -- CLEAR on CC[2]
      break;
    case CC3:
      timer_cc = TIMER_CC_3;
      int_compare = INT_COMPARE3;
      clear = 0x08; //  D=1 -- CLEAR on CC[3]
      break;
    default:
      timer_cc = TIMER_CC_0;
      int_compare = INT_COMPARE0;
      clear = 0x01; //  A=1 -- CLEAR on CC[0]
      break;
  }

  /* Compare Value ----------------------------------------------------------
   Compare Value to 255
   register_write((TIMER0_BASE_ADDRESS + TIMER_CC_0), 255); // fast as hell!

   Compare/Count to ~4sek
   register_write((TIMER0_BASE_ADDRESS + TIMER_CC_0), 1953); // ~4 sek

   Compare/Count to custom value from arguments
  */
  register_write((timer + timer_cc), compareValue);

  // Enable Shortcuts ----------------------------------------------------
  // - Enable Shortcut between CC[0] and STOP + CLEAR
  // register_write((timer + TIMER_SHORTS), 0x101); // G=1 + A=1
  // - Enable Shortcut between CC[0] and CLEAR
  uint32_t shorts = register_read((timer + TIMER_SHORTS));
  register_write((timer + TIMER_SHORTS), clear | shorts); // Merge with previous

  // Enable Interrupt
  uint32_t ints = register_read((timer + TIMER_INTENSET));
  register_write((timer + TIMER_INTENSET), int_compare | ints); // Merge with previous
}

void timer_remove_capture(enum Timer timer, enum Capture cc) {
  uint32_t timer_cc;
  uint32_t int_compare;
  uint32_t clear;
  switch (cc) {
    case CC0:
      timer_cc = TIMER_CC_0;
      int_compare = INT_COMPARE0; // Interrupt on Compare[0]
      clear = 0x01; //  A=1 -- CLEAR on CC[0]
      break;
    case CC1:
      timer_cc = TIMER_CC_1;
      int_compare = INT_COMPARE1;
      clear = 0x02; //  B=1 -- CLEAR on CC[1]
      break;
    case CC2:
      timer_cc = TIMER_CC_2;
      int_compare = INT_COMPARE2;
      clear = 0x04; //  C=1 -- CLEAR on CC[2]
      break;
    case CC3:
      timer_cc = TIMER_CC_3;
      int_compare = INT_COMPARE3;
      clear = 0x08; //  D=1 -- CLEAR on CC[3]
      break;
    default:
      timer_cc = TIMER_CC_0;
      int_compare = INT_COMPARE0;
      clear = 0x01; //  A=1 -- CLEAR on CC[0]
      break;
  }

  // Disable Shortcuts ----------------------------------------------------
  // - Disable Shortcut between CC[0] and STOP + CLEAR
  // register_write((timer + TIMER_SHORTS), 0x101); // G=1 + A=1
  // - Disable Shortcut between CC[0] and CLEAR
  uint32_t shorts = register_read((timer + TIMER_SHORTS));
  register_write((timer + TIMER_SHORTS), (~clear) & shorts); // Overwrite previous

  // Disable Interrupt
  uint32_t ints = register_read((timer + TIMER_INTENSET));
  register_write((timer + TIMER_INTENSET), (~int_compare) & ints); // Overwrite previous
}

void timer_start(enum Timer timer) {
  uint32_t iid;
  switch (timer)
  {
  case TIMER0:
    iid = Interrupt_ID8;
    break;
  case TIMER1:
    iid = Interrupt_ID9;
    break;
  case TIMER2:
    iid = Interrupt_ID10;
    break;
  default:
    iid = Interrupt_ID8;
    break;
  }

  // Start the Module -------------------------------------------------------
  // Start Timer
  register_write((timer + TIMER_START), TIMER_TASK_START);

  // Enable User-Interrupt from Cortex-M0
  // ID8 ist der Timer0
  uint32_t ints = register_read(Interrupt_Set_Enable);
  register_write(Interrupt_Set_Enable, iid | ints); // Merge with existing
}

void timer_stop(enum Timer timer) {
  uint32_t iid;
  switch (timer)
  {
  case TIMER0:
    iid = Interrupt_ID8;
    break;
  case TIMER1:
    iid = Interrupt_ID9;
    break;
  case TIMER2:
    iid = Interrupt_ID10;
    break;
  default:
    iid = Interrupt_ID8;
    break;
  }

  // Start the Module -------------------------------------------------------
  // Start Timer
  register_write((timer + TIMER_STOP), TIMER_TASK_START);

  // Enable User-Interrupt from Cortex-M0
  // ID8 ist der Timer0
  uint32_t ints = register_read(Interrupt_Set_Enable);
  register_write(Interrupt_Set_Enable, (~iid) & ints); // Overwrite existing
}

void timer_clear(enum Timer timer, enum Capture cc) {
  // Write a `0` to the compare 0 Register.
  register_write((timer + cc), TIMER_EVENT_CLEAR);
}

uint32_t timer_check(enum Timer timer, enum Capture cc) {
  return register_read((timer + cc));
}
