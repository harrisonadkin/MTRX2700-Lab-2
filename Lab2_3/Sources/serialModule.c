#include <hidef.h>      /* common defines and macros */
#include <stdio.h>
#include <string.h>
#include "timers.h"
#include "serialModule.h"
#include "derivative.h"



/******************************************************************************
*                                                                             *
*                                                                             *
*                           Serial Printing Module                            *
*                                                                             *
*                                                                             *
******************************************************************************/


// Initialising a new struct definition
Serial newSerial;
int index = 0;
int runCondition;
unsigned char inputString[255];
unsigned char *outputString;
unsigned char statusRegister;


// Function to initialise all the serial struct parameters
void serialInitialise(int baudRate, int interface, int function, unsigned char ** dataLocation){
    if (index == 0) {
    
      // Storing the serial parameters
      runCondition = 1;
      newSerial.function = function;
      newSerial.interface = interface;
      newSerial.baudRate = baudRate;
      
      
      if(newSerial.function == 0){        // If the function is asked to read
        *dataLocation = &inputString[0];  // the dataLocation is pointing to the input string location

      } else if(newSerial.function == 1){ // If the function is asked to write
        outputString = *dataLocation;     // output string variable is set to the dataLocation
      }

      setControl();                       // Setting the control registers
    }
  
  
    // Stay in the loop and wait for the interrupts
    while(runCondition){
        _FEED_COP(); // BYJORK
    }                        
}


// Setting the control registers
void setControl(void){

   // Setting baud rate to 156
   if(newSerial.interface == 0){
      //SCI0BDL = newSerial.baudRate;
   }else if (newSerial.interface == 1){
      SCI1BDL = newSerial.baudRate;
   }
   
   // If the function is asking to read, enable the recieve enable and enable reciever full interrupt
   if(newSerial.function == 0){
      if(newSerial.interface == 0){
         // SCI0CR2 |= SCI0CR2_RIE_MASK;
         // SCI0CR2 |= SCI0CR2_RE_MASK;
      } else if(newSerial.interface == 1){
          SCI1CR2 |= SCI1CR2_RIE_MASK;
          SCI1CR2 |= SCI1CR2_RE_MASK;
      }
        
        
   // If the function is asking to write, set transmission enable and transmitter interrupt enable
   } else if(newSerial.function == 1){
      if(newSerial.interface == 0){
         // SCI0CR2 |= SCI0CR2_SCTIE_MASK;
         // SCI0CR2 |= SCI0CR2_TE_MASK;
      } else if(newSerial.interface == 1){
          SCI1CR2 |= SCI1CR2_SCTIE_MASK;
          SCI1CR2 |= SCI1CR2_TE_MASK;
      }
   } 
}


// Function to write to the serial port
void writeSerial(void){

    // SCI0 write
    if(newSerial.interface == 0){
        //  statusRegister = SCI0SR1;
        //  SCI0DRL = outputString[index];
      
    // SCI1 write
    } else if(newSerial.interface == 1){
          statusRegister = SCI1SR1;           // Read the status register to reset the flag - allows it to leave the interrupt sequence
          SCI1DRL = *(outputString + index);  // Store the value in the data register from outputString.
    }

    // Check if we have reached the end of string
    if(outputString[index] == 0){             // If the current char in the outputString is null
          resetSerial();                      // End transmission and reset the Serial
    
    } else{
          index++;                            // If current char is not null, keep writing
    }
}



// Function to write to the serial port
void readSerial(void){

   // SCI0 read
   if(newSerial.interface == 0){
        //  statusRegister = SCI0SR1;
        //  inputString[index] = SCI0DRL;
   // SCI1 read
   } else if(newSerial.interface == 1){
          statusRegister = SCI1SR1;          // Read the status register to reset the flag - allows it to leave the interrupt sequence
          inputString[index] = SCI1DRL;      // Store the value from data register into the inputString
   } 

   
   // Check if we have reached the end of string
   if(inputString[index] == 13){             // If the current char in the carraige return
          index++;                           // manually append new line char and null char
          inputString[index] = '\n';
          index++;
          inputString[index] = '\0';
          
          resetSerial();                     // Reset serial
    
   } else{                                   // If the current char is not carraige return, keep writing
          index++;
    
   }
}


// Resets serials to not create interrupts
void resetSerial(void){
    
    index = 0;
    //SCI0CR2 = 0;
    SCI1CR2 = 0;
    runCondition = 0;
    
}

// initialising SCI0 interrupt
/*#pragma CODE_SEG __NEAR_SEG NON_BANKED 
__interrupt void SCI0_ISR(void) { 
    
    if(newSerial.function == 0){
          readSerial();
      
    } else if(newSerial.function == 1){
          writeSerial();
  
    }
} */

// initialising SCI1 interrupt
#pragma CODE_SEG __NEAR_SEG NON_BANKED 
__interrupt void SCI1_ISR(void) { 
    
    // If main function wants to read, call the read function, else the write function
    if(newSerial.function == 0){
          readSerial();
      
    } else if(newSerial.function == 1){
          writeSerial();
  
    }
} 


