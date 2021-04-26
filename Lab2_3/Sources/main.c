#include <hidef.h>      /* common defines and macros */
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "derivative.h" /* derivative-specific definitions */
#include "timers.h"
#include "musicModule.h"
#include "mathModule.h"
#include "serialModule.h"
#include "tableModule.h"
#include "globals.h"



 
    

unsigned char * example;
unsigned char * transmit_string = "BYORK\r\n\0";
 

void main(void) {
  /* put your own code here */
 
  //serialInitialise(156,SCI1,READ,&example);
  //serialInitialise(156,SCI1,WRITE,&example);
  //serialInitialise(156,SCI1,WRITE,&transmit_string);
  
   createTable();
  
  
  //Init_TC5();                 // initialise registers for buzzer	
  //scoreFunc(); 
   

  while(1){                   // BJORK the swedish dog
  
   // flag is set to 1 on completion, use this to print to serial
   // time and notes remaining are shifting during play, print this to serial too.

  }
}

