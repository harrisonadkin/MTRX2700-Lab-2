#include "timers.h"

// include the register/pin definitions
#include "derivative.h"      /* derivative-specific definitions */
#include "globals.h"

void Init_TC5 (void) {
  // set up the timers for channel 5 to use the interrupt
  
  TSCR1 = 0b11110000;   // timer enable, timer stop in wait and freeze, 
  TSCR2 = 0b00000011;   // no overflow, prescalar 8
  TIOS |= 0b00100000;   // channel 5 to output compare, rest for input capture 
  TCTL1 = 0b00000100;   // channel 5 to toggle OCx output line
  TIE  |= 0b00100000;   // channel 5 timer interrupt enable 
  TC0   = TCNT + delay; // ready channel 0 for output compare
  
}

// initialising channel 5 interrupt
#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void TC5_ISR(void) { 

  TC5 += delay; // add delay time to output compare. plays note at correct frequency. 
}


/*#pragma CODE_SEG __NEAR_SEG NON_BANKED 
__interrupt void TOF_ISR(void) { 
  
  // timer overflow code
 
}          */