#include "Tlc5940.h" 

/// Do not turn on more than 33 segments

/// #define NUM_TLCS 4

int led_mapper[16] = { 4, 1, 6, 8, 2, 3, 5, 10, 7, 12, 14, 15, 9, 11, 16, 13 };

//              01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16
int zer[16] = {  1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1 };
int one[16] = {  0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0 };
int two[16] = {  0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0 };
int thr[16] = {  1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0 };
int fou[16] = {  1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 };
int fiv[16] = {  1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1 };
int six[16] = {  1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1 };
int sev[16] = {  1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 };
int eig[16] = {  1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1 };
int nin[16] = {  1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1 };

int *nums[10] = { zer, one, two, thr, fou, fiv, six, sev, eig, nin };

int segs[64];

#define POWAN 100
#define DELAY 1000

#define OFF       0
#define AFTERGLOW 5
#define ON        10

#define N_SEGS (16 * NUM_TLCS)
#define MAX_BRIGHTNESS (4096 / 2)

void setup() { 
  Tlc.init(); 
  Tlc.clear(); 
  for(int s = 0; s < N_SEGS; ++s) { 
    Tlc.set(s, 0);
    segs[s] = OFF;
  } 
  Tlc.update(); 
}


void turn_segs_on_and_off(int *pattern1, int *pattern2, int *pattern3, int *pattern4) {
  int *patterns[4];
  patterns[0] = pattern1;
  patterns[1] = pattern2;
  patterns[2] = pattern3;
  patterns[3] = pattern4;
  
  // AFTERGLOW --> OFF
  for (int j = 0; j < 4 /* 4 */; ++j) {
    for (int k = 0; k < 16; ++k) {
      int l = j * 16 + k;
      if (segs[l] == AFTERGLOW && patterns[j][k] == 0) {
        Tlc.set(l, 0);
      }
    }
  }
  Tlc.update();
  delayMicroseconds(POWAN);
  
  // ON --> AFTERGLOW
  for (int i = MAX_BRIGHTNESS - 1; i > 0; --i) {
    for (int j = 0; j < 4 /* 4 */; ++j) {
      for (int k = 0; k < 16; ++k) {
        int l = j * 16 + k;
        if (segs[l] == ON && patterns[j][k] == 0) {
          Tlc.set(l, i);
        }
      }
    }
    Tlc.update();
    delayMicroseconds(POWAN);
  }
  
  // _ --> ON
  for (int i = 0; i < MAX_BRIGHTNESS; ++i) {
    for (int j = 0; j < 4 /* 4 */; ++j) {
      for (int k = 0; k < 16; ++k) {
        int l = j * 16 + k;
        if (patterns[j][k] == 1) {
          Tlc.set(l, i);
        }
      }
    }
    Tlc.update();
    delayMicroseconds(POWAN);
  }
  
  
  
  for (int j = 0; j < 4; ++j) {
    for (int k = 0; k < 16; ++k) {
      // ON
      if (patterns[j][k] == 1) {
        segs[j * 16 + k] = ON;
      }
      // ON --> OFF
      else if (segs[j * 16 + k] == ON && patterns[j][k] == 0) {
        segs[j * 16 + k] = AFTERGLOW;
      }
      else {
        segs[j * 16 + k] = OFF;
      }
    }
  }
}

void loop() {
  int x = random(10);
  int y = random(10);
  int z = random(10);
  turn_segs_on_and_off(nums[x], nums[y], nums[z], one);
  delay(DELAY);
}
