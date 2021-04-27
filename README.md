# Lab 2 Project ReadMe File

The following program can take a user input string that defines the notes of a given tune. The program results in the tune being played on the speaker on the HCS12 microcontroller. The implementation of this program has been broken down into smaller tasks, each containing submodules that have been separately written and tested before integrating together into one major project. A list of all the submodules is given below.

Software Submodules:
1. Math module
2. Timers module
3. Serial Module
4. Interrupts module
5. Music module

The given tasks use multiple modules from above to achieve their core functionality and all of the modules have been integrated together to create the final program that can interface with the user and play any given tune.
The breakdown of tasks are discussed below.


## Exercise 1 - Benchmarking the performance of arithmetic functions
The purpose of this task was to calculate and compare the time taken to perform different mathematical operations using the HCS12 microcontroller.
To achieve this, the program was built using three main modules, the math, timers and the table module.
The math calculations and time measurement was achieved through the Math module using 5 different functions. The mathTimer function initialises the variables used in the operation and calls on the other functions. The four other functions operate the same way but each of them operate on a different data type.
For example, the intCalcs function takes an integer input and calculates the time taken. The counter value before math operation is stored, a math function is used on the variable and the duration of the function is calculated by calling a calcTime function. This function takes the difference between the two counter values before and after the math operation, adds the counter overflow and returns the number of clock cycles taken. This value is then converted into microseconds in the intCalcs function. The function operates the same way for all the math operations for integers and similarly, the other functions have the same approach with different data types.
Here, the number of times the timer overflowed is counted by enabling the counter to trigger an interrupt subroutine where the TOFcount variable is incremented, note that it is necessary to reset FLAG while initializing time overflow interrupt.

### Discussion points
#### Lengths of the various data types
Int - 4				int a = 3;
Long - 4			long b = 1234567891;
Float (32bit) - 4		float c = 1.2345;
Float (64bit) double - 8	double d = 3.00000000001234;
The size and data type being used actually depends on the way we initialise the variable.

#### Timing overheads from other operations
Time overflow count would be reseted each time after the time taken is calculated. For overheads, although the calcTime function does take extra time other than math operations, as we used the same function throughout the whole thing, it won’t really matter since the time taken is constant. What we’ve got is the relative difference between times.

#### Influence of the compiler/optimiser
The compiler helps convert C to machine readable language, and it allows functions/operations being accessed instead of directly using assembly languages.

### Testing Procedure:
#### The math function is best tested through an initial compile and run, and a comparison of values to logic. The output range for integer addition, for example, should be in the range of ~1ms. 
#### Testing of this module should utilise stepping, to check through each individual math function and ensure the correct parsing of arrays. Note that a buffer array is initialised in the scope of the math function and copied to the inputted solution array from main. For this to correctly work, we must ensure the correct parsing of the pointer to the solution array from main (utilise heading file to type check), as well as the correct use of the memcpy function. 
#### Finally, ensure that the time calculation function is working as intended by stepping through it accurately.
 

## Exercise 2 Serial with interrupts
The main functionality of this task is to set up the serial input and output operations using interrupts. The serial module is set up such that the serialInitialise function can be called from main with an input baud rate, Serial port number and read or write function (1 or 0) along with a string location. This function sets up the string variables and serial port register values through the setCountrol() function and enters waiting mode to be interrupted by a user input.
When the serial interrupt subroutine is triggered, based on the defined functionality - read or write, the relevant functions are called.
readSerial() - every time the RDRF flag is set, the interrupt subroutine calls this function. This reads the value of the SCI0 or SCI1 data register and stores it in the current element of the inputString. Every time, the input value is checked for the carraige return character and when that is found, an end of string and null character are manually appended before the serial is reset.
writeSerial() - Every time the TDRE flag is set, the interrupt subroutine calls this function. It loops through the string and sends each character to the serial data registers until the null character is reached. The serial is reset once again.
Resetting the serial to make the control register 2 be 0 so it does not take interrupts anymore.
### Discussion points
#### How to buffer the data (for receive and transmit)
There are two seperate strings, one to store the input read from the serial and one to store the data that needs to be written out. We can manipulate the input string and change it before using it as the output string.
#### How long (roughly) does the interrupt handler take to service the input?
Interrupt handler is pretty fast - the output is shown almost immediately after entering the input
The actual time of the function can be calculated using the timer modules

### Testing Procedure:
-  Common serial interfacing errors will involve the use of the SCI0 port in hardware. Ensure that when in hardware, ALL SCI0 related lines are commented out. This includes the interrupt sequence initialisation within the interrupt vector table interrupts.c and every line involving SCI0 in the serial.c file.
-  Another common error will be misdefinitions within the serial sequence, so ensure that the required type inputs outlined in the function headers are parsed.
-  To test if the module is working as expected, test cases were written and the module was tested in steps
	-  Example test case for just the write function: “this is a string. ”
	-  Example test case for read function: type into the serial “this is a string.” and click enter
	-  Both of these need to be tested by looking at the relevant memory locations of the string and stepping through the code to see if the array values are changing as expected.
-  When working with interrupts, some of the common problems encountered were due to not resetting the flags correctly. We need to ensure that the status registers are read after using the data registers to reset the flag and exit the interrupt sequence.

## Exercise 3 Module for the major project - Option 3
The main task for this section is to play a tune on the hardware speaker given a string of notes to play and a string of durations for each note.
This task integrates the music module and a few functions from the timer module to create the required delay.
The playnote function takes 2 integer arrays as input - the scores and durations - and iterates through them. It uses the related frequencies of the notes in the score (as stored in the global variables header) to create a PWM output from the buzzer at that frequency, thus playing the note. Note that the frequencies depend heavily on the clock cycles and must be recalculated for new prescalar values, using 1/FrequencyNote * Clockspeed/(2*prescalar). The frequencies are then played by using channel 5 as an output compare, and the TCTL1 register to toggle the channel 5 output line. The output compare variable is changed in the interrupt sequence to the frequency of the note, updating the toggling speed of the buzzer to the correct note frequency. The function then takes the duration and runs it through a delay function delay10ms that delays the sequence by 10ms, a <duration> amount of times. This will hold the same buzzer frequency for this period of time, effectively playing the note for that duration. This is done using a while loop that enables another channel, channel 6 for output compare, and completes nothing until the timer reaches this channel’s compare. This amount was calculated to be 30000 clock cycle iterations, using the formula time = clockspeed/(cycle iterations * cycles from function * 2 * prescalar). 
Note that as extension, the remaining notes and duration were calculated at each cycle, and a flag was set upon completion of the score. These were set to be integrated to the serial module, however this was incomplete. 

### Testing Procedure:
-  The most common errors would arise in initialisation, so ensure the initialisation header is included in main, and that the registers are set correctly as follows:
TSCR1 = 11110000, TSCR2 = 00000011, TIOS |= 00100000, TCTL1 = 0b00000100, TIE = 00100000. Important bits can be found in HCS12 reference manual.
-  Following this, ensure that the initialisation of the score and duration arrays are within scope of the calling functions, and done correctly. Be sure to include terminating characters (‘0’) at the end of the string and duration. 
-  Then ensure that the play module is running as intended; ensure that the while loop is reached, and correctly iterates through the score. 
-  Following this, ensure the delay module is delayed as intended. This can be tested independently, by feeding the function 100, and ensuring it delays exactly 1s. 
-  Finally, ensure that the finish flag is set upon completion, and utilise steps to ensure that the notes and duration remaining is correct.
-  It is highly recommended that testing is done on a short, well known score (i.e: hot cross buns), to allow note and duration alignment in testing. 

