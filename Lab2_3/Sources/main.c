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
  
  // Initialising an empty string for reading user input
  unsigned char *readString = 0;
  // Examples for output strings
  char *writeString2 = "Playing Jupiter\r\n\0";
  char *writeString1 = "Reading Math\r\n\0";
 
 
  
  EnableInterrupts;
  // Initialise serial parameters - comment out which one we don't need
  /*   SCI 1   */
  serialInitialise(156,SCI1,READ,&readString);    // Setting SCI1 to read into readString
  serialInitialise(156,SCI1,WRITE,&readString);   // Setting up SCI1 to write the input
  serialInitialise(156,SCI1,WRITE,&writeString1); // Setting up SCI1 to write heading for the next operation
  
  Init_Math(); // sets up timer for counting calc time of math functions
  mathTimer(intTimes, longTimes, floatTimes, doubleTimes); // All math functions and calculations done through this function
  
  
  // Initialising serial parameters for SCI0
  serialInitialise(156,SCI0,READ,&readString);
  serialInitialise(156,SCI0,WRITE,&readString);
  serialInitialise(156,SCI0,WRITE,&writeString2);
  
  Init_TC5();                 // initialise registers for buzzer - initialising and using chanel 5 for interrupts	
  scoreFunc();                // Function to play the tune on speaker
   

  while(1){                   // BJORK the swedish dog
  
   // flag is set to 1 on completion, use this to print to serial
   // time and notes remaining are shifting during play, print this to serial too.

  }
}

