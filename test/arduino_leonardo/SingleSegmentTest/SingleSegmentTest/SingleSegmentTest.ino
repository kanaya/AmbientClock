#include "Tlc5940.h" 

/// #define NUM_TLCS 4

#define N_CH (16 * NUM_TLCS)
#define MAX_BRIGHTNESS 4095 // 0-4095 
#define POWAN_SPEED 100     // microsecond 

char curCh = 0;  // current channel 
int curBr = 0;   // current brightness 

void setup() { 
  TLC_CHANNEL_TYPE ch = curCh; 
  Tlc.init(); 
  Tlc.clear(); 
  for(ch = 0; ch < N_CH; ch++) { 
    Tlc.set(ch, 0); 
  } 
  Tlc.update(); 
}

void loop() { 
  TLC_CHANNEL_TYPE ch = curCh; 
  for (curBr = 0; curBr < MAX_BRIGHTNESS; ++curBr) { 
    Tlc.set(ch, curBr); 
    Tlc.update(); 
    delayMicroseconds(POWAN_SPEED); 
  } 
  for (curBr = MAX_BRIGHTNESS; curBr >= 0; --curBr) { 
    Tlc.set(ch, curBr); 
    Tlc.update(); 
    delayMicroseconds(POWAN_SPEED); 
  } 
  ++curCh; 
  if(curCh >= N_CH) {
    curCh = 0;
  } 
}
