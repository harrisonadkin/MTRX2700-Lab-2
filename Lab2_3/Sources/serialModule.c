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

Serial newSerial;
int i = 0;
int runCondition;
unsigned char inputString[255];
unsigned char *outputString;
unsigned char statusRegister;


void serialInitialise(int baudRate, int interface, int function, unsigned char ** dataLocation, int ** stringLen){
    EnableInterrupts;
    if (i == 0) {
      runCondition = 1;
      newSerial.function = function;
      newSerial.interface = interface;
      newSerial.baudRate = baudRate;
      
      if(newSerial.function == 0){
        *dataLocation = &inputString[0];
        *stringLen = &i;

      } else if(newSerial.function == 1){
        outputString = *dataLocation;
      
      }
      
      setBaud();
      setControl();

      }else{
        while(runCondition == 1){
        _FEED_COP(); // BYJORK
        }
      }                
      

}

void setBaud(void){
    unsigned char * baudRate1;
    
    if(newSerial.interface == 0){
        //baudRate1 = &SCI0BDL;
        
     } else if(newSerial.interface == 1){
        baudRate1 = &SCI1BDL;
     }
     
   * baudRate1 = newSerial.baudRate; 
}

void setControl(void){
   if(newSerial.function == 0){
      if(newSerial.interface == 0){
          //SCI0CR2 |= SCI0CR2_RIE_MASK;
          //SCI0CR2 |= SCI0CR2_RE_MASK;
      
      } else if(newSerial.interface == 1){
          SCI1CR2 |= SCI1CR2_RIE_MASK;
          SCI1CR2 |= SCI1CR2_RE_MASK;
      
      }
        
   } else if(newSerial.function == 1){
      if(newSerial.interface == 0){
          //SCI0CR2 |= SCI0CR2_SCTIE_MASK;
          //SCI0CR2 |= SCI0CR2_TE_MASK;
      
      } else if(newSerial.interface == 1){
          SCI1CR2 |= SCI1CR2_SCTIE_MASK;
          SCI1CR2 |= SCI1CR2_TE_MASK;
      
      }
   } 

}

void writeSerial(void){
    
    if(newSerial.interface == 0){
          //statusRegister = SCI0SR1;
          //SCI0DRL = *(outputString + i);
      
    } else if(newSerial.interface == 1){
          statusRegister = SCI1SR1;
          SCI1DRL = *(outputString + i);
      
    }

    if(outputString[i] == 0){
          resetSerial();
    
    } else{
          i++;
    
    }
}

void readSerial(void){

   if(newSerial.interface == 0){
          //statusRegister = SCI0SR1;
          //inputString[i] = SCI0DRL;
      
   } else if(newSerial.interface == 1){
          statusRegister = SCI1SR1;
          inputString[i] = SCI1DRL;
      
   } 

   if(inputString[i] == 13){
          i++;
          inputString[i] = '\n';
          i++;
          inputString[i] = '\0';
          
          resetSerial();
    
   } else{
          i++;
    
   }
}

void resetSerial(void){
    
    i = 0;
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
}*/ 

// initialising SCI1 interrupt
#pragma CODE_SEG __NEAR_SEG NON_BANKED 
__interrupt void SCI1_ISR(void) { 
    
    if(newSerial.function == 0){
          readSerial();
      
    } else if(newSerial.function == 1){
          writeSerial();
  
    }
} 


