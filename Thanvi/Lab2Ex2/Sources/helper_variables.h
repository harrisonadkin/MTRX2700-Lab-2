// Header file "helper_variables.h" to be included in only the main.c file
// Stores all the global changable variables that can be modified.



#ifndef helper_variables
#define helper_variables

// Variables to get array element
volatile extern int r;
volatile extern int w;
volatile extern int read_complete;

// Create global arrays for input and output
#define array_size 1000


// End of string character
#define end_of_string 0

// Serial parameters structure
extern struct serial_config {
  unsigned char *data_address;
  int serial_num;
  unsigned char input_array[array_size];
    struct {
      unsigned char baud_rate;
      unsigned char read;
      unsigned char wrote;
    } status;
}serial;



#endif