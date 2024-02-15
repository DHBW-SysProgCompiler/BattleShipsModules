#ifndef TIMER_H
#define TIMER_H

#include <stdbool.h>
#include <stdint.h>

// Definitions ----------------------------------------------------------------

// Base Address (Instance)
#define TIMER0_BASE_ADDRESS 0x40008000
#define TIMER1_BASE_ADDRESS 0x40009000
#define TIMER2_BASE_ADDRESS 0x4000A000

// Register Offsets (from Table 141, page 100)
// Tasks:
#define TIMER_START 0x000    // Start Timer
#define TIMER_STOP 0x004     // Stop Timer
#define TIMER_COUNT 0x008    // Increment Timer (Counter mode only)
#define TIMER_CLEAR 0x00C    // Clear time
#define TIMER_SHUTDOWN 0x010 // Shut down timer

#define TIMER_CAPTURE_0 0x040 // Capture Timer value to CC[0] register
#define TIMER_CAPTURE_1 0x044 // Capture Timer value to CC[1] register
#define TIMER_CAPTURE_2 0x048 // Capture Timer value to CC[2] register
#define TIMER_CAPTURE_3 0x04C // Capture Timer value to CC[3] register

// Events:
#define TIMER_COMPARE_0 0x140 // Compare event on CC[0] match
#define TIMER_COMPARE_1 0x144 // Compare event on CC[1] match
#define TIMER_COMPARE_2 0x148 // Compare event on CC[2] match
#define TIMER_COMPARE_3 0x14C // Compare event on CC[3] match

// Registers:
#define TIMER_SHORTS 0x200    // Shortcut register
#define TIMER_INTENSET 0x304  // Enable interrupt
#define TIMER_INTENCLR 0x308  // Disable interrupt
#define TIMER_MODE 0x504      // Timer mode selection
#define TIMER_BITMODE 0x508   // Configure the number of bits used by the TIMER
#define TIMER_PRESCALER 0x510 // Timer prescaler register
#define TIMER_CC_0 0x540      // Capture/Compare register 0
#define TIMER_CC_1 0x544      // Capture/Compare register 1
#define TIMER_CC_2 0x548      // Capture/Compare register 2
#define TIMER_CC_3 0x54C      // Capture/Compare register 3

// Other:
#define TIMER_TASK_START 1    // Value for starting a Task
#define TIMER_EVENT_TRIGGER 1 // Value for setting/starting an Event
#define TIMER_EVENT_CLEAR 0   // Value for clearing/stopping an Event

#define SHORTS_COMPARE0_CLEAR_ENABLE (1 << 0)  // Shortcut between COMPARE[0] event and CLEAR task
#define SHORTS_COMPARE0_CLEAR_DISABLE (0 << 0) // Shortcut between COMPARE[0] event and CLEAR task
#define SHORTS_COMPARE1_CLEAR_ENABLE (1 << 1)  // Shortcut between COMPARE[1] event and CLEAR task
#define SHORTS_COMPARE1_CLEAR_DISABLE (0 << 1) // Shortcut between COMPARE[1] event and CLEAR task

#define SHORTS_COMPARE0_STOP_ENABLE (1 << 8)  // Shortcut between COMPARE[0] event and STOP task
#define SHORTS_COMPARE0_STOP_DISABLE (0 << 8) // Shortcut between COMPARE[0] event and STOP task
#define SHORTS_COMPARE1_STOP_ENABLE (1 << 9)  // Shortcut between COMPARE[1] event and STOP task
#define SHORTS_COMPARE1_STOP_DISABLE (0 << 9) // Shortcut between COMPARE[1] event and STOP task

#define INT_COMPARE0 (1 << 16) // Enable/Disable Interrupt on COMPARE[0] event
#define INT_COMPARE1 (1 << 17) // Enable/Disable Interrupt on COMPARE[1] event
#define INT_COMPARE2 (1 << 18) // Enable/Disable Interrupt on COMPARE[2] event
#define INT_COMPARE3 (1 << 19) // Enable/Disable Interrupt on COMPARE[3] event

// Custom

/**
 * @brief Enum of all available timers.
 * Timer0, Timer1, Timer2
 */
enum Timer {
  TIMER0 = TIMER0_BASE_ADDRESS,
  TIMER1 = TIMER1_BASE_ADDRESS,
  TIMER2 = TIMER2_BASE_ADDRESS,
};

enum Capture {
  CC0 = TIMER_COMPARE_0,
  CC1 = TIMER_COMPARE_1,
  CC2 = TIMER_COMPARE_2,
  CC3 = TIMER_COMPARE_3,
};

//  Define function pointer types
typedef void (*FunctionPointer)(void);

// C Function Definitions -----------------------------------------------------

/**
 * @brief Initialize a new timer with one capture target. Does NOT start the
 * timer. timer_init(TIMER0, 15, 3, 1953); initializes Timer0 to tick on cc0
 * every ~4sec.
 * @param timer Timer to use. Timer0..2
 * @param prescaler Prescaler to reduce percision. min (1 = 0b00000001), max (15
 * = 0b00001111)
 * @param bitmode Timer bitmode. 0=16b, 1=8b, 2=24b, 3=32b
 * @param cc0 Capture Target 0. Value to compare timer against.
 * @param run_on_match Function to run once the cc0 target is reached
 */
void timer_init(enum Timer timer, uint32_t prescaler, uint32_t bitmode, uint32_t cc0, FunctionPointer run_on_match);

/**
 * @brief Changes the timer prescaler.
 *
 * @param timer Selected timer
 * @param prescaler Prescaler to reduce percision. min (1 = 0b00000001), max (15
 * = 0b00001111)
 */
void timer_prescaler(enum Timer timer, uint32_t prescaler);

/**
 * @brief Change timer bitmode
 *
 * @param timer Selected timer
 * @param bitmode Timer bitmode. 0=16b, 1=8b, 2=24b, 3=32b
 */
void timer_bitmode(enum Timer timer, uint32_t bitmode);

/**
 * @brief Add timer capture target
 *
 * @param timer Selected timer
 * @param cc Selected capture group
 * @param compareValue Value to compare timer against
 * @param clear_on_match Clears/Restarts the timer once target is reached
 * @param stop_on_match Stops the timer once the target is reached
 * @param run_on_match Function to run once the target is reached
 */
void timer_add_capture(enum Timer timer, enum Capture cc, uint32_t compareValue, bool clear_on_match, bool stop_on_match, FunctionPointer run_on_match);

/**
 * @brief Remove timer capture target
 *
 * @param timer Selected timer
 * @param cc Selected capture group
 */
void timer_remove_capture(enum Timer timer, enum Capture cc);

/**
 * @brief Start timer
 *
 * @param timer Selected timer
 */
void timer_start(enum Timer timer);

/**
 * @brief Remove timer
 *
 * @param timer Selected timer
 */
void timer_stop(enum Timer timer);

/**
 * @brief Clearst the timer, to start from the beginning
 *
 * @param timer Selected timer
 */
void timer_clear(enum Timer timer);

/**
 * @brief Clears the Compare Event
 *
 * @param timer Selected timer
 * @param cc Selected capture group
 */
void timer_event_clear(enum Timer timer, enum Capture cc);

/**
 * @brief Check if timer event has triggered
 *
 * @param timer Selected timer
 * @param cc Selected capture group
 * @return uint32_t
 */
uint32_t timer_check(enum Timer timer, enum Capture cc);

#endif