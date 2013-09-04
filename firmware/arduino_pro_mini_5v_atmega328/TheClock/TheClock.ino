//
//
//
//
//
//
//
//
//
//


#include <Tlc5940.h>

#include <Wire.h>
#include <RTClib.h>
#include <Time.h>

#define POWAN 500
#define DELAY 500

#define OFF       0
#define ON        1
#define AFTERGLOW 2

#define SLEEP     0
#define AWAKE     1

#define N_SEGS (16 * NUM_TLCS)
#define MAX_BRIGHTNESS (4096 / 2)
#define AFTERGLOW_BRIGHTNESS 100

#define TH 120

#define SW1 2
#define SW2 4
#define SW3 5

/// Do not turn on more than 33 segments

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

/*
int aa[16] = {  1, 2, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0 };
int ab[16] = {  0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 1, 1 };
int ac[16] = {  0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1 };
int ad[16] = {  1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0 };
int ae[16] = {  0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1 };
int af[16] = {  0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1 };
int ag[16] = {  1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1 };
int ah[16] = {  1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1 };
int ai[16] = {  0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0 };
int aj[16] = {  1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0 };
int ak[16] = {  0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1 };
int al[16] = {  0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1 };
int am[16] = {  1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1 };
int an[16] = {  1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1 };
int ao[16] = {  1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1 };
int ap[16] = {  0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1 };
int aq[16] = {  1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1 };
int ar[16] = {  0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1 };
int as[16] = {  0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1 };
int at[16] = {  0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0 };
int au[16] = {  1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1 };
int av[16] = {  1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 };
int aw[16] = {  1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1 };
int ax[16] = {  0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0 };
int ay[16] = {  0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0 };
int az[16] = {  0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0 };
*/

const int *alphanums[] = {
  n0, n1, n2, n3, n4, n5, n6, n7, n8, n9, 
  /* aa, ab, ac, ad, ae, af, ag, ah, ai, aj, ak, al, am, an, ao, ap, aq, ar, as, at, au, av, aw, ax, ay, az,
  ssp, sex, sdq, ssh, sdl, spc, sam, sap, sop, scp, sas, spl, scm, smn, spr, ssl, scl, ssc, slt, seq, sgt, 
  sit, sat, sob, sbs, scb, sca, sub */ };

static RTC_DS1307 rtc;
static int segs[64];
static int st = SLEEP;

void setup() {
  Serial.begin(57600);

  Wire.begin();
  rtc.begin();
  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(__DATE__, __TIME__));
  }
  
  Tlc.init(); 
  Tlc.clear(); 
  for(int s = 0; s < N_SEGS; ++s) { 
    Tlc.set(s, 0);
    segs[s] = OFF;
  } 
  Tlc.update();
  
  pinMode(SW1, INPUT);
  pinMode(SW2, INPUT);
  pinMode(SW3, INPUT);
  digitalWrite(SW1, HIGH);
  digitalWrite(SW2, HIGH);
  digitalWrite(SW3, HIGH);
}

void powan(int brightnesses[]) {
  for (int i = 0; i < N_SEGS; ++i) {
    Tlc.set(i, brightnesses[i]);
  }
  Tlc.update();
}

void powan_update(int segments[]) {
  int brightnesses[N_SEGS];
  
  if (st == AWAKE) {
    for (int b = MAX_BRIGHTNESS - 1; b >= 0; --b) {
      for (int i = 0; i < N_SEGS; ++i) {
        if (segs[i] == ON && segments[i] == OFF) {
          brightnesses[i] = b;
        }
        else {
          brightnesses[i] = (segs[i] == ON) ? MAX_BRIGHTNESS : 0;
        }
      }
      powan(brightnesses);
      delayMicroseconds(POWAN);
    }
  }
  else {
    st = AWAKE;
  }
  
  for (int b = 0; b < MAX_BRIGHTNESS; ++b) {
    for (int i = 0; i < N_SEGS; ++i) {
      if (segs[i] == OFF && segments[i] == ON) {
        brightnesses[i] = b;
      }
      else {
        brightnesses[i] = (segs[i] == ON) && (segments[i] == ON) ? MAX_BRIGHTNESS : 0;
      }
    }
    powan(brightnesses);
    delayMicroseconds(POWAN);
  }
  
  for (int i = 0; i < N_SEGS; ++i) {
    segs[i] = segments[i];
  }
}

void loop() {
  DateTime now = rtc.now();
  int sensor = analogRead(0);
  
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(' ');
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
  Serial.print("Sensor value = ");
  Serial.print(sensor, DEC);
  Serial.println();
  
  if (sensor > TH) {
    int h = now.hour();
    int m = now.minute();
    int a[4];
    a[0] = h / 10;
    a[1] = h % 10;
    a[2] = m / 10;
    a[3] = m % 10;
    int segments[N_SEGS];
    for (int i = 0; i < NUM_TLCS; ++i) {
      for (int j = 0; j < 16; ++j) {
        segments[i * 16 + j] = alphanums[a[i]][j];
      }
    }
    powan_update(segments);
  }
  else {
    int segments[N_SEGS];
    for (int i = 0; i < N_SEGS; ++i) {
      segments[i] = OFF;
    }
    powan_update(segments);
    st = SLEEP;
  }
  delay(DELAY);
}
