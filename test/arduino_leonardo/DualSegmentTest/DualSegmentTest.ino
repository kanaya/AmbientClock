#include "Tlc5940.h" 

/// #define NUM_TLCS 4

//              01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16
int zer[16] = {  1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1 };
int one[16] = {  0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0 };
int two[16] = {  0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0 };
int thr[16] = {  1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0 };
int fou[16] = {  1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 };
int fiv[16] = {  0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1 };
int six[16] = {  1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1 };
int sev[16] = {  1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 };
int eig[16] = {  1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1 };
int nin[16] = {  1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1 };

int *nums[10] = { zer, one, two, thr, fou, fiv, six, sev, eig, nin };

#define N_CH (16 * NUM_TLCS)
#define MAX_BRIGHTNESS 4095 // 0-4095 
#define POWAN_SPEED 100     // microsecond 

char curCh = 0;  // current channel 
int curBr = 0;   // current brightness 

void setup() { 
  TLC_CHANNEL_TYPE ch = curCh; 
  Tlc.init(); 
  Tlc.clear(); 
  for(ch = 0; ch < N_CH; ++ch) { 
    Tlc.set(ch, 0); 
  } 
  Tlc.update(); 
}


void turn_seg_on(int ch) {
  int i;
  for (i = 0; i < MAX_BRIGHTNESS; ++i) {
    Tlc.set(ch, i);
    Tlc.update();
    delayMicroseconds(100);
  }
}

void turn_seg_off(int ch) {
  int i;
  for (i = MAX_BRIGHTNESS - 1; i >= 0; --i) {
    Tlc.set(ch, i);
    Tlc.update();
    delayMicroseconds(100);
  }
}

void loop() {
  int c;
  for (c = 0; c < 64; ++c) {
    int d = (c + 1) % 64;
    turn_seg_on(d);
    turn_seg_off(c);
  }
}
