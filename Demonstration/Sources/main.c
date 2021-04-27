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


  

float intTimes[bufferSize];
float longTimes[bufferSize];
float floatTimes[bufferSize];
float doubleTimes[bufferSize];

 

void main(void) {
  /* put your own code here */
  unsigned char *readString = 0;
  char *writeString2 = "Playing Jupiter\r\n\0";
  char *writeString1 = "Reading Math\r\n\0";
 
 
  EnableInterrupts;
  serialInitialise(156,SCI1,READ,&readString);
  serialInitialise(156,SCI1,WRITE,&readString);
  serialInitialise(156,SCI1,WRITE,&writeString1);
  
  Init_Math();
  mathTimer(intTimes, longTimes, floatTimes, doubleTimes);
  
  
  serialInitialise(156,SCI1,READ,&readString);
  serialInitialise(156,SCI1,WRITE,&readString);
  serialInitialise(156,SCI1,WRITE,&writeString2);
  
  Init_TC5();                 // initialise registers for buzzer	
  scoreFunc(); 
   

  while(1){                   // BJORK the swedish dog
  
   // flag is set to 1 on completion, use this to print to serial
   // time and notes remaining are shifting during play, print this to serial too.

  }
}

