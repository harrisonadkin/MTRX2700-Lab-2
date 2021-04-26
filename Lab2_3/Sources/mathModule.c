#include "mathModule.h"
#include <math.h>
#include <hidef.h>
#include "derivative.h"
#include "globals.h"

/******************************************************************************
*                                                                             *
*                                                                             *
*                          Math Module Functions                              *
*                                                                             *
*                                                                             *
******************************************************************************/


float buffer[bufferSize];

void mathTimer(float * output){
  volatile int a = 3;
  volatile long b = 1234567891;
  volatile float c = 1.2345;
  volatile double d = 3.00000000001234;
  
  EnableInterrupts;
  intCalcs(a);
  longCalcs(b);
  floatCalcs(c);
  doubleCalcs(d);
  //convertString(output);
  memcpy(output, buffer, 24*sizeof(float));

}


void intCalcs(volatile int a){
  volatile int ans;
  unsigned int time;
    
      time = TCNT;
      ans = a+a;
      buffer[0] = calcTime(time)*(2/24.0);
      
      time = TCNT;
      ans = a*a;
      buffer[1] = calcTime(time)*(2/24.0);
    
      time = TCNT;
      ans = a/a;
      buffer[2] = calcTime(time)*(2/24.0);

      time = TCNT;
      ans = sqrt(a);
      buffer[3] = calcTime(time)*(2/24.0);
      
      time = TCNT;
      ans = sin(a);
      buffer[4] = calcTime(time)*(2/24.0);
      
      time = TCNT;
      ans = cos(a);
      buffer[5] = calcTime(time)*(2/24.0); 

}

void longCalcs(volatile long b){
  volatile long ans;
  unsigned int time;
  
      time = TCNT;
      ans = b+b;
      buffer[6] = calcTime(time)*(2/24.0);

      time = TCNT;
      ans = b*b;
      buffer[7] = calcTime(time)*(2/24.0);
    
      time = TCNT;
      ans = b/b;
      buffer[8] = calcTime(time)*(2/24.0);

      time = TCNT;
      ans = sqrt(b);
      buffer[9] = calcTime(time)*(2/24.0);
      
      time = TCNT;
      ans = sin(b);
      buffer[10] = calcTime(time)*(2/24.0);

      time = TCNT;
      ans = cos(b);
      buffer[11] = calcTime(time)*(2/24.0);
   
}

void floatCalcs(volatile float c){
  volatile float ans;
  unsigned int time;
  
      time = TCNT;
      ans = c+c;
      buffer[12] = calcTime(time)*(2/24.0);

      time = TCNT;
      ans = c*c;
      buffer[13] = calcTime(time)*(2/24.0);
                                       
      time = TCNT;
      ans = c/c;
      buffer[14] = calcTime(time)*(2/24.0);

      time = TCNT;
      ans = sqrt(c);
      buffer[15] = calcTime(time)*(2/24.0);
      
      time = TCNT;
      ans = sin(c);
      buffer[16] = calcTime(time)*(2/24.0);
      
      time = TCNT;
      ans = cos(c);
      buffer[17] = calcTime(time)*(2/24.0);
   
}

void doubleCalcs(volatile double d){
  volatile double ans;
  unsigned int time;
  
      time = TCNT;
      ans = d+d;
      buffer[18] = calcTime(time)*(2/24.0);

      time = TCNT;
      ans = d*d;
      buffer[19] = calcTime(time)*(2/24.0);
    
      time = TCNT;
      ans = d/d;
      buffer[20] = calcTime(time)*(2/24.0);

      time = TCNT;
      ans = sqrt(d);
      buffer[21] = calcTime(time)*(2/24.0);
      
      time = TCNT;
      ans = sin(d);
      buffer[22] = calcTime(time)*(2/24.0);
      
      time = TCNT;
      ans = cos(d);
      buffer[23] = calcTime(time)*(2/24.0);
   
}

void convertString(float * output){
  //using sprintf to convert string of floats to chars to print in printing module
  
}


