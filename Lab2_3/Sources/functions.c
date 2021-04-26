#include "functions.h"
#include <hidef.h>
#include "derivative.h"
#include "globals.h"
#include "math.h"



/******************************************************************************
*                                                                             *
*                                                                             *
*                         Music Module Functions                              *
*                                                                             *
*                                                                             *
******************************************************************************/

// delay function given integer duration (multiplies by 10ms) and delays that amount
void delay10ms(int duration){
  int counter;
  TIOS |= 0b01000000;     // enable channel 6 for output compare
  TC6   = TCNT + 30000;   // set an output compare amount that is 30K cycles after current time

// run through for loop "duration" times that takes 10ms
  for(counter = 0; counter < duration; counter++){
    while(!(TFLG1 & 0b01000000));  // while output compare not reached do nothing
    timeRemaining -= 1;
    TC6 += 30000;                  // when output compare reached add another 30K cycles then repeat
  }                                // note 30K was calced using Clockspeed/(10*Amount*prescalar) = 10ms

  TIOS &= 0b10111111;              // turn 6 back off for later use
}



// Takes pointer to score and duration arrays and plays each note for that duration
void playnote(unsigned int * score, unsigned int * duration){
  int i = 0, j = 0;
  
  //while loop to calculate how many notes and total song duration
  while(duration[i]){
    timeRemaining += duration[i];
    notesRemaining += 1;
    i++;
  }
  
  //while loop that runs through score until termination character 0 and plays each note
  while(score[j]){

    frequency = score[j];
    delay10ms(duration[j]);
    notesRemaining -= 1;
    j++;

  }
  // turn off output compares for use later
  TIOS &= 0x11011111;
  flag = 1; 
}


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
  convertString(output);
 // memcpy(output, buffer, 24*sizeof(float));

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
  int i;
    for(i = 0; i < bufferSize; i++){
       sprintf(&output[0], "%8.2lf", buffer[i]);
    
    }
  
}




/******************************************************************************
*                                                                             *
*                                                                             *
*                         Random Testing Functions                            *
*                                                                             *
*                                                                             *
******************************************************************************/
