#include "Tlc5940.h" 

/// Do not turn on more than 33 segments

/// #define NUM_TLCS 4

int led_mapper[16] = { 4, 1, 6, 8, 2, 3, 5, 10, 7, 12, 14, 15, 9, 11, 16, 13 };

//              01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16
int zer[16] = {  1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1 };
int one[16] = {  0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 };
int two[16] = {  0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0 };
int thr[16] = {  0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0 };
int fou[16] = {  1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1 };
int fiv[16] = {  1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0 };
int six[16] = {  0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0 };
int sev[16] = {  0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0 };
int eig[16] = {  1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 };
int nin[16] = {  1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0 };

int *nums[10] = { zer, one, two, thr, fou, fiv, six, sev, eig, nin };

int segs[64];

#define N_SEGS (16 * NUM_TLCS)
#define MAX_BRIGHTNESS 4096

void setup() { 
  Tlc.init(); 
  Tlc.clear(); 
  for(int s = 0; s < N_SEGS; ++s) { 
    Tlc.set(s, 0);
    segs[s] = 0; 
  } 
  Tlc.update(); 
}

void turn_seg_on(int seg) {
  if (segs[seg] == 0) {
    for (int i = 0; i < MAX_BRIGHTNESS; ++i) {
      Tlc.set(seg, i);
      Tlc.update();
      delayMicroseconds(100);
    }
  }
  segs[seg] = 1;
}

void turn_segs_on_and_off(int digit, int *pattern) {
  // ON --> OFF
  for (int i = MAX_BRIGHTNESS - 1; i >= 0; --i) {
    for (int j = 0; j < 16; ++j) {
      if (segs[j] == 1 && pattern[j] == 0) {
        Tlc.set(j, i);
      }
    }
    Tlc.update();
    delayMicroseconds(100);
  }
  // OFF --> ON
  for (int i = 0; i < MAX_BRIGHTNESS; ++i) {
    for (int j = 0; j < 16; ++j) {
      if (segs[j] == 0 && pattern[j] == 1) {
        Tlc.set(j, i);
      }
    }
    Tlc.update();
    delayMicroseconds(100);
  } 
  for (int j = 0; j < 16; ++j) {
    // _ --> ON
    if (pattern[j] == 1) {
      segs[j] = 1;
    }
    // _ --> OFF
    else {
      segs[j] = 0;
    }
  }
}

void turn_seg_off(int seg) {
  if (segs[seg] == 1) {
    for (int i = MAX_BRIGHTNESS - 1; i >= 0; --i) {
      Tlc.set(seg, i);
      Tlc.update();
      delayMicroseconds(100);
    }
  }
  segs[seg] = 0;
}

void show_digit(int digit, int num) {
  int *num_pattern = nums[num];
  turn_segs_on_and_off(digit, num_pattern);
}

void loop() {
  int c;
  for (c = 0; c < 10; ++c) {
    show_digit(0, c);
    delay(1000);
  }
}
