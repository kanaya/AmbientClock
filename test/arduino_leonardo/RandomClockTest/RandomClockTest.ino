#include "Tlc5940.h" 

/// Do not turn on more than 33 segments

/// #define NUM_TLCS 4

int led_mapper[16] = { 4, 1, 6, 8, 2, 3, 5, 10, 7, 12, 14, 15, 9, 11, 16, 13 };

//             01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16
int n0[16] = {  1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1 };
int n1[16] = {  0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0 };
int n2[16] = {  0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0 };
int n3[16] = {  1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0 };
int n4[16] = {  1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 };
int n5[16] = {  1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1 };
int n6[16] = {  1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1 };
int n7[16] = {  1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 };
int n8[16] = {  1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1 };
int n9[16] = {  1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1 };
int aa[16] = {  1, 2, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0 };
int ab[16] = {  0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 1, 1 };
int ac[16] = {  0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 };
int ad[16] = {  0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 };
int ae[16] = {  0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 };
int af[16] = {  0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 };
int ag[16] = {  0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 };
int ah[16] = {  0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 };
int ai[16] = {  0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 };
int aj[16] = {  0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 };
int ak[16] = {  0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 };
int al[16] = {  0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 };
int am[16] = {  0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 };
int an[16] = {  0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 };
int ao[16] = {  0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 };
int ap[16] = {  0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 };
int aq[16] = {  0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 };
int ar[16] = {  0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 };
int as[16] = {  0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 };
int at[16] = {  0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 };
int au[16] = {  0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 };
int av[16] = {  0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 };
int aw[16] = {  0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 };
int ax[16] = {  0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 };
int ay[16] = {  0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 };
int az[16] = {  0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 };

int *alphanums[36] = { n0, n1, n2, n3, n4, n5, n6, n7, n8, n9,
  aa, ab, ac, ad, ae, af, ag, ah, ai, aj, ak, al, am,
  an, ao, ap, aq, ar, as, at, au, av, aw, ax, ay, az };

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
  int h = random(12) + 1;
  int m = random(60);
  int d1 = h / 10;
  int d2 = h % 10;
  int d3 = m / 10;
  int d4 = m % 10;
  turn_segs_on_and_off(alphanums[d1], alphanums[d2], alphanums[d3], alphanums[d4]);
  delay(DELAY);
}
