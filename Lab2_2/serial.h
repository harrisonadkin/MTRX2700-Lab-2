// serial.h
// Header file for serial 

#ifndef SERIAL_HEADER
#define SERIAL_HEADER

                    
// Functions
#pragma CODE_SEG __NEAR_SEG NON_BANKED
                                     
                        

void configure_SCI(int serial_num);
//void configure_SCI1(void);

struct serial_config serial_status(struct serial_config *serial, int serial_num);

__interrupt void SCI0_ISR(void);
__interrupt void SCI1_ISR(void);



#endif