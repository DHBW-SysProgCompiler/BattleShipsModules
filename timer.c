#include "timer.h"
#include "nvic.h"
#include "uart.h"
#include <stdbool.h>
#include <stdint.h>

#include "register_access.h"

// Timer clear values
uint32_t timer0_clear_val = ~0;
uint32_t timer1_clear_val = ~0;
uint32_t timer2_clear_val = ~0;
// Timer trigger actions
static void empty_trigger() {}
FunctionPointer timer0_cc0_trigger = empty_trigger;
FunctionPointer timer0_cc1_trigger = empty_trigger;
FunctionPointer timer0_cc2_trigger = empty_trigger;
FunctionPointer timer0_cc3_trigger = empty_trigger;
FunctionPointer timer1_cc0_trigger = empty_trigger;
FunctionPointer timer1_cc1_trigger = empty_trigger;
FunctionPointer timer1_cc2_trigger = empty_trigger;
FunctionPointer timer1_cc3_trigger = empty_trigger;
FunctionPointer timer2_cc0_trigger = empty_trigger;
FunctionPointer timer2_cc1_trigger = empty_trigger;
FunctionPointer timer2_cc2_trigger = empty_trigger;
FunctionPointer timer2_cc3_trigger = empty_trigger;

void timer_init(enum Timer timer, uint32_t prescaler, uint32_t bitmode, uint32_t cc0, FunctionPointer run_on_match) {
  // Add prescaler
  timer_prescaler(timer, prescaler);
  // Add bitmode
  timer_bitmode(timer, bitmode);
  // Add capture target
  timer_add_capture(timer, CC0, cc0, true, false, run_on_match);
  timer_remove_capture(timer, CC1);
  timer_remove_capture(timer, CC2);
  timer_remove_capture(timer, CC3);
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

void timer_add_capture(enum Timer timer, enum Capture cc, uint32_t compareValue, bool clear_on_match, bool stop_on_match, FunctionPointer run_on_match) {
  uint32_t timer_cc;
  uint32_t int_compare;
  uint32_t clear;
  uint32_t stop;
  switch (cc) {
  case CC0:
    timer_cc = TIMER_CC_0;
    int_compare = INT_COMPARE0; // Interrupt on Compare[0]
    clear = 1 << 0;             //  A=1 -- CLEAR on CC[0]
    stop = 1 << 8;              //  G=1 -- STOP on CC[0]
    switch (timer) {
    case TIMER0:
      timer0_cc0_trigger = run_on_match;
      break;
    case TIMER1:
      timer1_cc0_trigger = run_on_match;
      break;
    case TIMER2:
      timer2_cc0_trigger = run_on_match;
      break;
    default:
      timer0_cc0_trigger = run_on_match;
      break;
    }
    break;
  case CC1:
    timer_cc = TIMER_CC_1;
    int_compare = INT_COMPARE1;
    clear = 1 << 1; //  B=1 -- CLEAR on CC[1]
    stop = 1 << 9;  //  H=1 -- STOP on CC[1]
    switch (timer) {
    case TIMER0:
      timer0_cc1_trigger = run_on_match;
      break;
    case TIMER1:
      timer1_cc1_trigger = run_on_match;
      break;
    case TIMER2:
      timer2_cc1_trigger = run_on_match;
      break;
    default:
      timer0_cc1_trigger = run_on_match;
      break;
    }
    break;
  case CC2:
    timer_cc = TIMER_CC_2;
    int_compare = INT_COMPARE2;
    clear = 1 << 2; //  C=1 -- CLEAR on CC[2]
    stop = 1 << 10; //  I=1 -- STOP on CC[2]
    switch (timer) {
    case TIMER0:
      timer0_cc2_trigger = run_on_match;
      break;
    case TIMER1:
      timer1_cc2_trigger = run_on_match;
      break;
    case TIMER2:
      timer2_cc2_trigger = run_on_match;
      break;
    default:
      timer0_cc2_trigger = run_on_match;
      break;
    }
    break;
  case CC3:
    timer_cc = TIMER_CC_3;
    int_compare = INT_COMPARE3;
    clear = 1 << 3; //  D=1 -- CLEAR on CC[3]
    stop = 1 << 11; //  J=1 -- STOP on CC[3]
    switch (timer) {
    case TIMER0:
      timer0_cc3_trigger = run_on_match;
      break;
    case TIMER1:
      timer1_cc3_trigger = run_on_match;
      break;
    case TIMER2:
      timer2_cc3_trigger = run_on_match;
      break;
    default:
      timer0_cc3_trigger = run_on_match;
      break;
    }
    break;
  default:
    timer_cc = TIMER_CC_0;
    int_compare = INT_COMPARE0;
    clear = 1 << 0; //  A=1 -- CLEAR on CC[0]
    stop = 1 << 8;  //  G=1 -- STOP on CC[0]
    switch (timer) {
    case TIMER0:
      timer0_cc0_trigger = run_on_match;
      break;
    case TIMER1:
      timer1_cc0_trigger = run_on_match;
      break;
    case TIMER2:
      timer2_cc0_trigger = run_on_match;
      break;
    default:
      timer0_cc0_trigger = run_on_match;
      break;
    }
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
  if (clear_on_match) {
    uint32_t shorts = register_read((timer + TIMER_SHORTS));
    register_write((timer + TIMER_SHORTS),
                   clear | shorts); // Merge with previous
  } else {
    uint32_t shorts = register_read((timer + TIMER_SHORTS));
    register_write((timer + TIMER_SHORTS),
                   ~clear & shorts); // Overwrite previous
  }
  if (stop_on_match) {
    uint32_t shorts = register_read((timer + TIMER_SHORTS));
    register_write((timer + TIMER_SHORTS),
                   stop | shorts); // Merge with previous
  } else {
    uint32_t shorts = register_read((timer + TIMER_SHORTS));
    register_write((timer + TIMER_SHORTS),
                   ~stop & shorts); // Overwrite previous
  }

  // Enable Interrupt
  uint32_t ints = register_read((timer + TIMER_INTENSET));
  register_write((timer + TIMER_INTENSET),
                 int_compare | ints); // Merge with previous
}

void timer_remove_capture(enum Timer timer, enum Capture cc) {
  uint32_t timer_cc;
  uint32_t int_compare;
  uint32_t clear;
  uint32_t stop;
  switch (cc) {
  case CC0:
    timer_cc = TIMER_CC_0;
    int_compare = INT_COMPARE0; // Interrupt on Compare[0]
    clear = 1 << 0;             //  A=1 -- CLEAR on CC[0]
    stop = 1 << 8;              //  G=1 -- STOP on CC[0]
    switch (timer) {
    case TIMER0:
      timer0_cc0_trigger = empty_trigger;
      break;
    case TIMER1:
      timer1_cc0_trigger = empty_trigger;
      break;
    case TIMER2:
      timer2_cc0_trigger = empty_trigger;
      break;
    default:
      timer0_cc0_trigger = empty_trigger;
      break;
    }
    break;
  case CC1:
    timer_cc = TIMER_CC_1;
    int_compare = INT_COMPARE1;
    clear = 1 << 1; //  B=1 -- CLEAR on CC[1]
    stop = 1 << 9;  //  H=1 -- STOP on CC[1]
    switch (timer) {
    case TIMER0:
      timer0_cc1_trigger = empty_trigger;
      break;
    case TIMER1:
      timer1_cc1_trigger = empty_trigger;
      break;
    case TIMER2:
      timer2_cc1_trigger = empty_trigger;
      break;
    default:
      timer0_cc1_trigger = empty_trigger;
      break;
    }
    break;
  case CC2:
    timer_cc = TIMER_CC_2;
    int_compare = INT_COMPARE2;
    clear = 1 << 2; //  C=1 -- CLEAR on CC[2]
    stop = 1 << 10; //  I=1 -- STOP on CC[2]
    switch (timer) {
    case TIMER0:
      timer0_cc2_trigger = empty_trigger;
      break;
    case TIMER1:
      timer1_cc2_trigger = empty_trigger;
      break;
    case TIMER2:
      timer2_cc2_trigger = empty_trigger;
      break;
    default:
      timer0_cc2_trigger = empty_trigger;
      break;
    }
    break;
  case CC3:
    timer_cc = TIMER_CC_3;
    int_compare = INT_COMPARE3;
    clear = 1 << 3; //  D=1 -- CLEAR on CC[3]
    stop = 1 << 11; //  J=1 -- STOP on CC[3]
    switch (timer) {
    case TIMER0:
      timer0_cc3_trigger = empty_trigger;
      break;
    case TIMER1:
      timer1_cc3_trigger = empty_trigger;
      break;
    case TIMER2:
      timer2_cc3_trigger = empty_trigger;
      break;
    default:
      timer0_cc3_trigger = empty_trigger;
      break;
    }
    break;
  default:
    timer_cc = TIMER_CC_0;
    int_compare = INT_COMPARE0;
    clear = 1 << 0; //  A=1 -- CLEAR on CC[0]
    stop = 1 << 8;  //  G=1 -- STOP on CC[0]
    switch (timer) {
    case TIMER0:
      timer0_cc0_trigger = empty_trigger;
      break;
    case TIMER1:
      timer1_cc0_trigger = empty_trigger;
      break;
    case TIMER2:
      timer2_cc0_trigger = empty_trigger;
      break;
    default:
      timer0_cc0_trigger = empty_trigger;
      break;
    }
    break;
  }

  // Disable Shortcuts
  uint32_t shorts = register_read((timer + TIMER_SHORTS));
  register_write((timer + TIMER_SHORTS),
                 (~clear) & shorts); // Overwrite previous
  shorts = register_read((timer + TIMER_SHORTS));
  register_write((timer + TIMER_SHORTS),
                 (~stop) & shorts); // Overwrite previous
}

void timer_start(enum Timer timer) {
  uint32_t iid;
  switch (timer) {
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
  switch (timer) {
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

void timer_clear(enum Timer timer) {
  // Clear Timer
  register_write((timer + TIMER_CLEAR), TIMER_TASK_START);
}

void timer_event_clear(enum Timer timer, enum Capture cc) {
  // Write a `0` to the compare 0 Register.
  register_write((timer + cc), TIMER_EVENT_CLEAR);
}

uint32_t timer_check(enum Timer timer, enum Capture cc) { return register_read((timer + cc)); }

// Timer0 Interrupt Handler
void Interrupt8_Handler(void) {
  if (timer_check(TIMER0, CC0)) {
    timer_event_clear(TIMER0, CC0);
    if (timer0_cc0_trigger && timer0_cc0_trigger != empty_trigger) {
      timer0_cc0_trigger();
    }
  }
  if (timer_check(TIMER0, CC1)) {
    timer_event_clear(TIMER0, CC1);
    if (timer0_cc1_trigger && timer0_cc1_trigger != empty_trigger) {
      timer0_cc1_trigger();
    }
  }
  if (timer_check(TIMER0, CC2)) {
    timer_event_clear(TIMER0, CC2);
    if (timer0_cc2_trigger && timer0_cc2_trigger != empty_trigger) {
      timer0_cc2_trigger();
    }
  }
  if (timer_check(TIMER0, CC3)) {
    timer_event_clear(TIMER0, CC3);
    if (timer0_cc3_trigger && timer0_cc3_trigger != empty_trigger) {
      timer0_cc3_trigger();
    }
  }
}
