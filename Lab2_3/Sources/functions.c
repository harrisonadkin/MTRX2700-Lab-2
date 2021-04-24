#include "functions.h"
#include <hidef.h>      
#include "derivative.h"
#include "globals.h"

// delay function given integer duration (multiplies by 10ms)
// ANNOTATE!!!
void delay10ms(int duration){
  int counter;
  TIOS |= 0b01000000;
  TC6   = TCNT + 30000;
  
  for(counter = 0; counter < duration; counter++){
    while(!(TFLG1 & 0b01000000));
    TC6 += 30000;
  }
  
  TIOS &= 0b10111111; 
}

// Takes pointer to score and duration arrays and plays each note for that duration
void playnote(unsigned int * score, unsigned int * duration){
  int j = 0;
  while(score[j]){
    
    delay = score[j];
    delay10ms(duration[j]);
    j++;
    
  }
  // turn off output compares for use later
  TIOS &= 0xDF;  
}




//struct musicNote generateNote(int frequency, int duration){
  //struct musicNote newNote;
  
  //newNote.frequency = frequency;
  //newNote.duration  = duration;
  //newNote.played    = false;

//  return newNote;
//}

//int initialiseNote(struct musicNote *_musicNote, int frequency, int duration){
 // _musicNote->frequency = frequency;
  //_musicNote->duration = duration;
  
  //return true;  
//}