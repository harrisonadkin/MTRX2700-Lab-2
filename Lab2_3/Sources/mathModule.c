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

// Buffer arrays to store results in 
float buffer1[bufferSize];
float buffer2[bufferSize];
float buffer3[bufferSize];
float buffer4[bufferSize];


// Main function that calls individual functions - This updates thebuffer values
void mathTimer(float * output1, float * output2, float * output3, float * output4){

  // Initialise variables of different data types to work with
  volatile int a = 3;
  volatile long b = 1234567891;
  volatile float c = 1.2345;
  volatile double d = 3.00000000001234;
  
  // Call the calculation functions for the respective data type
  // Each function calculates the time taken for all of the math operations for given datatype  
  EnableInterrupts;
  intCalcs(a);
  longCalcs(b);
  floatCalcs(c);
  doubleCalcs(d);
  
  //convertString(output);
  // Storing the output of the functions into output arrays which can be accessed later
  memcpy(output1, buffer1, 6*sizeof(float));
  memcpy(output2, buffer2, 6*sizeof(float));
  memcpy(output3, buffer3, 6*sizeof(float));
  memcpy(output4, buffer4, 6*sizeof(float));

}



// Time calculations for integers
void intCalcs(volatile int a){
  volatile int ans;
  unsigned int time;
     
      // Addition
      time = TCNT;                          // Store the counter value before starting the operation
      ans = a+a;                            // Call the operation
      buffer1[0] = calcTime(time)*(2/24.0); // Calculate the time taken (in micro s) and store in a global array 
      
      // Multiplication
      time = TCNT;
      ans = a*a;
      buffer1[1] = calcTime(time)*(2/24.0);
    
      // Division
      time = TCNT;
      ans = a/a;
      buffer1[2] = calcTime(time)*(2/24.0);

      // Sqrt
      time = TCNT;
      ans = sqrt(a);
      buffer1[3] = calcTime(time)*(2/24.0);
      
      // sin
      time = TCNT;
      ans = sin(a);
      buffer1[4] = calcTime(time)*(2/24.0);
      
      // cos
      time = TCNT;
      ans = cos(a);
      buffer1[5] = calcTime(time)*(2/24.0); 

}

// Time calculations for longs
void longCalcs(volatile long b){
  volatile long ans;
  unsigned int time;
  
      // Addition
      time = TCNT;
      ans = b+b;
      buffer2[0] = calcTime(time)*(2/24.0);

      // Multiplication
      time = TCNT;
      ans = b*b;
      buffer2[1] = calcTime(time)*(2/24.0);
    
      // Division
      time = TCNT;
      ans = b/b;
      buffer2[2] = calcTime(time)*(2/24.0);

      // Sqrt
      time = TCNT;
      ans = sqrt(b);
      buffer2[3] = calcTime(time)*(2/24.0);
      
      // Sin
      time = TCNT;
      ans = sin(b);
      buffer2[4] = calcTime(time)*(2/24.0);

      // Cos
      time = TCNT;
      ans = cos(b);
      buffer2[5] = calcTime(time)*(2/24.0);
   
}

// Time calculations for floats
void floatCalcs(volatile float c){
  volatile float ans;
  unsigned int time;
  
      // Addition
      time = TCNT;
      ans = c+c;
      buffer3[0] = calcTime(time)*(2/24.0);

      // Multiplication
      time = TCNT;
      ans = c*c;
      buffer3[1] = calcTime(time)*(2/24.0);
                          
      // Division             
      time = TCNT;
      ans = c/c;
      buffer3[2] = calcTime(time)*(2/24.0);

      // Sqrt
      time = TCNT;
      ans = sqrt(c);
      buffer3[3] = calcTime(time)*(2/24.0);
      
      // sin
      time = TCNT;
      ans = sin(c);
      buffer3[4] = calcTime(time)*(2/24.0);
      
      // Cos
      time = TCNT;
      ans = cos(c);
      buffer3[5] = calcTime(time)*(2/24.0);
   
}

// Time calculations for doubles
void doubleCalcs(volatile double d){
  volatile double ans;
  unsigned int time;
  
      // Addition
      time = TCNT;
      ans = d+d;
      buffer4[0] = calcTime(time)*(2/24.0);

      // Multiplication
      time = TCNT;
      ans = d*d;
      buffer4[1] = calcTime(time)*(2/24.0);
    
      // Division
      time = TCNT;
      ans = d/d;
      buffer4[2] = calcTime(time)*(2/24.0);

      // Sqrt
      time = TCNT;
      ans = sqrt(d);
      buffer4[3] = calcTime(time)*(2/24.0);
      
      // Sin
      time = TCNT;
      ans = sin(d);
      buffer4[4] = calcTime(time)*(2/24.0);
      
      // Cos
      time = TCNT;
      ans = cos(d);
      buffer4[5] = calcTime(time)*(2/24.0);
   
}




