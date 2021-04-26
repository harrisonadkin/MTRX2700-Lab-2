#ifndef FUNCTIONS_HEADER
#define FUNCTIONS_HEADER

// Music Module Functions
void delay10ms(int duration);
void playnote(unsigned int * score, unsigned int * duration);

// Math Module Functions
void mathTimer(float * output);
void intCalcs(volatile int a);
void longCalcs(volatile long b);
void floatCalcs(volatile float c);
void doubleCalcs(volatile double d);
void convertString(float * output);


#endif