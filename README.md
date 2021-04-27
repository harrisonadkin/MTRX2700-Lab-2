# MTRX2700-Lab-2
Lab 2 Repository

## Ex1

### timer
E-clock = 24mHz

### TSCR1
	-Enable timer & counter
	-stop when MCU is in wait/freeze
	-no fast flag clear
### TSCR2
	-Prescaler set to 2 (frequency of the timer prescaler clock derived from the Bus Clock)
		Interrupt every 2^16*(2/24000)=5.46ms
	-Enable time overflow interrupt
### TFLG2
	-set flag when an interrupt condition occurred (when 16bit timer overflows from FFFF->0000)

## Needs Count & Clear overflow

### Initialize time overflow interrupt
	-TOF count increment of 1
	-Needs to reset the flag each time (TFLG2)

### Calc time taken
	-use overflow counter to calculate CLK cycles
	-Overflow counted in TOF and each time time taken is calculated, we need to clear counter
	-time taken = time count register – number of overflows*2^16
				(can make interrupt every 2^16 counts)
## Different Calculations
	-for example int addition
		-time taken calculated by func above, using TCNT as input 
		- f= e-clk/presclaer
	-do the same thing for other operations and datatypes
	-the use of memcpy: sending stuffs in buffer array to mian.c
