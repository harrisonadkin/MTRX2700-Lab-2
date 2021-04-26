#include <stdio.h>
#include <stdlib.h>

#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "helper_variables.h"
#include "serial.h"

          
                                     
void main(void) {
  // Defining an empty array to store input from user
  //input_array = calloc(array_size, sizeof(char)); //creating a predefined memory of 0's. 
  
               
  // Call functions to initialise both serial ports
  configure_SCI(0);
  configure_SCI(1);
  r = 0;
	w = 0;
 
  // enable the interrupts (same as 'CLI' in asm)
	EnableInterrupts;


 
  for(;;) {
  
  /*
  // Automatically write to sci if we reach the end of string when reading
  if (input_array[r] == end_of_string){
    if (serial.serial_num == 0){
      SCI0SR1_RDRF = 0;
      SCI0SR1_TDRE = 1; // Should trigger the sci_isr
    }else if (serial.serial_num ==1){
      SCI1SR1_RDRF = 0;
      SCI1SR1_TDRE = 1; // Should trigger the sci_isr
    
    }   // But we can't write to the status registers
   
  }*/
    _FEED_COP(); /* feeds the dog */
    
    
  } /* loop forever */
  /* please make sure that you never leave main */
 
}

