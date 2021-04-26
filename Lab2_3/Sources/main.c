#include <hidef.h>      /* common defines and macros */
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "derivative.h" /* derivative-specific definitions */
#include "timers.h"
#include "musicModule.h"
#include "mathModule.h"
#include "serialModule.h"
#include "globals.h"



 
    
float output[bufferSize];
char * example[100];
int * example_size;
 

void main(void) {
  /* put your own code here */
 
  serialInitialise(156,0,0,example,example_size);
  
  //Init_Math();                  // initialise registers for timer
  //mathTimer(output);
  
  
  //Init_TC5();                 // initialise registers for buzzer	
  //scoreFunc(); 
   

  while(1){                   // BJORK the swedish dog
  
   // flag is set to 1 on completion, use this to print to serial
   // time and notes remaining are shifting during play, print this to serial too.

  }
}

