#ifndef TIMERS_HEADER
#define TIMERS_HEADER


// function to initialise the timer
void Init_TC5 (void);

// Timer interrupt definition
__interrupt void TC5_ISR(void);
//__interrupt void TOF_ISR(void);  //add this one when integrating lmao


#endif