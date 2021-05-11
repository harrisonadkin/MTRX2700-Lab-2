#ifndef SERIAL_HEADER
#define SERIAL_HEADER


void sci(int bd, int intf, int fn, char **data_loc);      // function to interface with serial input/output 


typedef struct {                                          // struct to store basic parameters for serial communication
  int baud_rate;
  int interface;
  int function;
  

} SERIAL;


#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void SCI1_ISR(void);                          // SCI1 interrupt service routine
__interrupt void SCI0_ISR(void);                          // SCI0 interrupt service routine

#endif