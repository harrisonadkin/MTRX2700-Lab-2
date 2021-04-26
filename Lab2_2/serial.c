// serial.c

#include <stdio.h>
#include <stdlib.h>
#include "helper_variables.h"
#include "serial.h"


// include the register/pin definitions
#include "derivative.h"      /* derivative-specific definitions */




#pragma CODE_SEG __NEAR_SEG NON_BANKED // Place this bit of code in non banked memory location
// Configuring SCI0 port
void configure_SCI(int serial_num){

  if (serial_num == 0){
      
    SCI0BDH = 0;          
    SCI0BDL = 156;        // Setting baud rate to 156
    SCI0CR1 = 0b01000100; // Setting data format, wake up condition and parity
    SCI0CR2 = 0b00101100; // Interrupts for TDRE and RDRF flags are enabled and Tranmitter and Receiver Enabled
     
  
  }else if (serial_num == 1){
    SCI1BDH = 0;
    SCI1BDL = 156;        // Setting baud rate to 156
    SCI1CR1 = 0b01000100; // Setting data format, wake up condition and parity
    SCI1CR2 = 0b00101100; // Interrupts for TDRE and RDRF flags are enabled and Tranmitter and Receiver Enabled
    
  }
}                 



// Function that gives the parameters of the chosen struct at that moment in time
struct serial_config serial_status(struct serial_config *serial, int serial_num){

  if (serial_num == 0){
    serial->data_address = (unsigned char*)((0xCF));
    serial->serial_num = 0;
    serial->status.baud_rate = 156;
    serial->status.read = SCI0SR1_RDRF;
    serial->status.wrote = SCI0SR1_TDRE;
    
  } else if (serial_num == 1){
    serial->data_address = (unsigned char*)(0xD7);
    serial->serial_num = 1;
    serial->status.baud_rate = 156;
    serial->status.read = SCI1SR1_RDRF;
    serial->status.wrote = SCI1SR1_TDRE;
    
  }
  
  return *serial;
  
}


__interrupt void SCI0_ISR(void){
  

  // If RDRF triggered the interrupt, the data register can be read
  if (SCI0SR1_RDRF == 1){
    // read sci0 and store into array until we reach the end_of_string;
    if (SCI0DRL != end_of_string){
      serial.input_array[r] = SCI0DRL;
      r = r+ 1;  
    }
    serial.input_array[r] = end_of_string; // Manually add an end_of_string char
    
  // If TDRE triggered the interrupt, the program is ready to write
  } else if (SCI0SR1_TDRE == 1){
    // write the data register to the value in the input array
    // until we reach end_of_string
    if (serial.input_array[w] != end_of_string){
      SCI0DRL = serial.input_array[w];
      w = w + 1;
    }
    SCI0DRL = end_of_string; // Manually send the end of string char
    
  }
}


__interrupt void SCI1_ISR(void){
  
  // If RDRF triggered the interrupt, the data register can be read
  if (SCI1SR1_RDRF == 1){
    // read sci0 and store into array until we reach the end_of_string;
    if (SCI1DRL != end_of_string){
      serial.input_array[r] = SCI1DRL;
      r = r+ 1;  
    }
    serial.input_array[r] = end_of_string; // Manually add an end_of_string char
    
  // If TDRE triggered the interrupt, the program is ready to write
  } else if (SCI1SR1_TDRE == 1){
    // write the data register to the value in the input array
    // until we reach end_of_string
    if (serial.input_array[w] != end_of_string){
      SCI1DRL = serial.input_array[w];
      w = w + 1;
    }
    SCI1DRL = end_of_string; // Manually send the end of string char
    
  }
  
}
