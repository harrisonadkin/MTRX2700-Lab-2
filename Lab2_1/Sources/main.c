#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "math.h"




int counter;              // count to increment

void main(void) {
  
  /*Setting Variables: */
  
  
  int flag = 1;             // flag to decipher which mathematical function
  long initialTime = 0;
  long timeTaken1 = 0;
  long timeTaken2 = 0;
  long timeTaken3 = 0;
  

  volatile int int1 = 3, int2 = 4, answer;           // initialise two integers
  //volatile long long1, long2;        // initialise two longs
  //volatile float float1, float2;     // initialise two floats
  //double double1, double2;  // initialise two doubles
  
  TSCR1 = 0b11100000;       // turn on timer (important !!)    (stop while in wait) 
  TIOS = 0b11111100;        // set last field bit so that channel 1/2 is input capture (other 6 channels don't matter yet)
  TSCR2 = 0b10000001;       // first bit to enable interrupts, last 3 bits to determine prescalar (110 is 64)
  TFLG2 = 0b00000000;       // set timer overflow flag to 0
  counter = 0;              // set counter to 0


	EnableInterrupts;

  /* Logic begins: */    
  







  while(1) {
   
   
   
    initialTime = TCNT;
    answer = int1 + int2; 
    timeTaken1 = TCNT - initialTime;
    

    initialTime = TCNT;
    answer = int1 * int2;
    timeTaken2 = TCNT - initialTime;
          
   
    initialTime = TCNT;
    answer = int1 - int2;
    timeTaken3 = TCNT - initialTime;

    
    
    
  while(1){ 
  }
  
  }
}