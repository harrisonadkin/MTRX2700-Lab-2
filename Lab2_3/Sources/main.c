#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */
#include "timers.h"
#include "math.h"
#include "functions.h"
#include "globals.h"

// example score: Jupiter theme [THE PLANETS] in b flat 
// current notes only across scales 3,4,5. No flats or sharps.
// duration is value multiplied by 10ms. 100 = 1s of note. 
unsigned int score[] = {
  A3,C4,D4,ZZ,D4,F4,E4,C4,F4,G4,F4,E4,D4,E4,D4,C4,A3,
  ZZ,A3,C4,D4,ZZ,D4,F4,E4,C4,F4,G4,A4,ZZ,A4,ZZ,A4,G4,F4,G4,F4,
  C5,A4,G4,ZZ,G4,F4,A4,G4,C4,C5,A4,G4,ZZ,G4,A4,C5,D5,
  ZZ,D5,E5,F5,E5,D5,C5,E5,A4,G4,F4,G4,A4,C5,0};
unsigned int duration[] = { 
  100,100,100,3,50,50,75,25,50,50,100,100,50,50,100,100,200,
  3,50,50,100,3,50,50,75,25,50,50,100,3,100,3,50,50,100,100,200,
  50,50,100,3,100,50,50,100,100,50,50,100,3,100,50,50,200,
  3,50,50,100,100,100,100,100,100,50,50,100,100,200};

void main(void) {
  /* put your own code here */
 
  Init_TC5();                 // initialise registers for buzzer
	EnableInterrupts;
  playnote(score, duration);  // pass score and duration pointers into play function

  while(1);                   // BJORK the swedish dog
    
}