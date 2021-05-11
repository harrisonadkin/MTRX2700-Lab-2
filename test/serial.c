#include <hidef.h>
#include "serial.h"
#include "derivative.h"


/* VARIABLE DEFINITIONS */

unsigned char string[255];
unsigned char *send_str;
unsigned int status_register;                              

int ind = 0;                                         
int run;                                              

SERIAL current_sci;                                   


/* CONTROL REGISTER 2 CONFIGURATION FUNCTION */

void CR2_config(void){                                
  if (current_sci.function == 0){                     // testing whether to configure for transmitting or receiving 
    switch(current_sci.interface){                    // whether to configure for SCI0 or SCI1
      
      case 0:
        SCI0CR2 = SCI0CR2 | SCI0CR2_RIE_MASK;         // set receiver full interrupt enable bit      
        SCI0CR2 = SCI0CR2 | SCI0CR2_RE_MASK;          // set receiver enable bit                      
        break;
        
      case 1:;
        SCI1CR2 = SCI1CR2 | SCI1CR2_RIE_MASK;         // set receiver full interrupt enable bit      
        SCI1CR2 = SCI1CR2 | SCI1CR2_RE_MASK;          // set receiver enable bit
        break;
    }
  
  } else if (current_sci.function == 1){               
  
  switch(current_sci.interface){
    
    case 0:
      SCI0CR2 = SCI0CR2 | SCI0CR2_SCTIE_MASK;         // set receiver full interrupt enable bit      
      SCI0CR2 = SCI0CR2 | SCI0CR2_TE_MASK;            // set receiver enable bit
      break;
    
    case 1:
      SCI1CR2 = SCI1CR2 | SCI1CR2_SCTIE_MASK;         // set receiver full interrupt enable bit      
      SCI1CR2 = SCI1CR2 | SCI1CR2_TE_MASK;            // set receiver enable bit
      break;
    }
  }   
}


/* CLEAR CONTROL REGISTER 2 FUNCTION */

void clear_CR2(void){                                 // clears sci0 and sci1 control register data
  SCI0CR2 = 0;
  SCI1CR2 = 0;
}


/* SET BAUD RATE FUNCTION */
void set_baud(void){

  unsigned char *bdl;                                 // pointer to baud rate register
  
  switch(current_sci.interface){                      // pointing bdl variable to correct interface BDL address 
    case 0:
      bdl = &SCI0BDL; 
      break;
      
    case 1:
      bdl = &SCI1BDL;
      break;
  }
  
  *bdl = current_sci.baud_rate;                       // assign inputted baud rate to baud rate register
}


/* SERIAL INTERFACING FUNCTION */

void sci(int bd, int intf, int fn, char **data_loc){
  
  if (ind == 0){                                      // checking index value as a way to ensure data isn't overwritten during operation 
    run = 1;                                          // assigning inputted values to serial object
    current_sci.baud_rate = bd;
    current_sci.interface = intf;
    current_sci.function = fn;
  
    switch(current_sci.function){
      case 0:
        *data_loc = &string[0];                       // set inputted pointer to location of received string buffer
        break;
      case 1:
        send_str = *data_loc;                         // sets inputted string to transmit                                            
        break;
    }

    set_baud();                                       // set baud rate
    CR2_config();                                     // configure control register
  }
  
  while(run == 1){                                    // run while receiving/transmitting data
    //_FEED_COP();
  }
  
}


/* RESET FUNCTION */
                                                      
void reset(void){                                     // resets necessary registers/variables for new serial interfacing
  ind = 0;
  clear_CR2();
  run = 0;  
}


/* TRANSMIT DATA FUNCTION */

void transmit(void){

  switch(current_sci.interface){                      // determines which interface to use
    case 0:
      status_register = SCI0SR1;                      // read status register
      SCI0DRL = *(send_str + ind);                    // assign next character to data register
      break;
      
    case 1:
      status_register = SCI1SR1;                      // read status register
      SCI1DRL = *(send_str + ind);                    // assign next character to data register
      break;
  }

  if (send_str[ind] == 0){                            // testing for null character at end of string
    reset();                                          // reset parameters
  } else{
    ind++;                                            // if not, increment string index
  } 
}


/* READ DATA FUNCTION */

void read(void){
  switch(current_sci.interface){                      // determines correct interface to use
    case 0:
      status_register = SCI0SR1;                      // read status register
      string[ind] = SCI0DRL;                          // assign data register character to local variable
      break;
    case 1:
      status_register = SCI1SR1;                      // read status register
      string[ind] = SCI1DRL;                          // assign data register character to local variable
      break;
  }
  if (string[ind] == 13){                             // checks for carriage return (enter) character
    string[++ind] = '\n';                             // adds newline and null character to end of string
    string[++ind] = '\0';
    
    reset();                                          // reset parameters
  }
  else{
    ind++;                                            // otherwise, increment index
  } 
   
}

#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void SCI1_ISR(void){
  
  switch(current_sci.function){                       // determine whether to read or write from function variable in struct
    case 0:
      read();
      break;
    case 1:
      transmit();
      break;
  }
}

__interrupt void SCI0_ISR(void){
  
  switch(current_sci.function){                       // determine whether to read or write from function variable in struct
    case 0:
      read();
      break;
    case 1:
      transmit();
      break;
  }
}
