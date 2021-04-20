#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */


#define hiFreq  1250
#define lowFreq 5000
char flag;

void main(void) {
  /* put your own code here */
  
  TSCR1 = 0b10010000;
  TSCR2 = 0b00000011; // prescalar 8
  TIOS  = 0b00100000; // do channel 7 instead 
  TFLG2 = 0b00000000;
  //TCTL1 = 0b00000100; 
  TCTL1 = 0b00001100;
  TRLG2 = 0b11111111;

	EnableInterrupts;


  while(1){
    
  
  }
}


/* interrupts */

interrupt 