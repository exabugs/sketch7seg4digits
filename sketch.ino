#include "Ticker.h"

Ticker ticker;
Ticker ticker2;

#define SCK 14                // CLK       クロック信号出力ピン
#define RCK 12                // LOAD      ラッチ動作出力ピン
#define SI  13                // MOSI - DI データ信号出力ピン
#define CLR 15                // クリア

const int segments[] = {
//  HGFEDCBA
  0b00111111, // 0
  0b00000110, // 1
  0b01011011, // 2
  0b01001111, // 3
  0b01100110, // 4
  0b01101101, // 5
  0b01111101, // 6
  0b00100111, // 7
  0b01111111, // 8
  0b01101111, // 9
};

const int digits[] = {
//  HGFEDCBA
  0b00000001, // 0
  0b00000010, // 1
  0b00000100, // 2
  0b00001000, // 3
};

void out1(int x, int d) {
  digitalWrite(CLR, LOW) ; // Clear
  digitalWrite(CLR, HIGH) ;

  digitalWrite(RCK, LOW) ;
  shiftOut(SI, SCK, MSBFIRST, digits[d]);
  shiftOut(SI, SCK, MSBFIRST, segments[x]);
  digitalWrite(RCK, HIGH) ;        // ラッチ信号を出す
}

void out4(int val) {
  static int p = 0;
  p = ++p % 4;
  int x[4];
  for (int i = 0; i < 4; i++) {
    x[i] = val % 10;
    val = val / 10;
  }
  out1(x[p], p);
}

void setup() {
  Serial.begin(115200);
  Serial.print("\n");

  pinMode(SCK, OUTPUT) ;
  pinMode(RCK, OUTPUT) ;
  pinMode(SI,  OUTPUT) ;
  pinMode(CLR, OUTPUT) ;

  delay(3000) ;            // 3S後開始

  Serial.print("Start\n");

  ticker.attach_ms(1000, timer);
  ticker2.attach_ms(4, loop2);
}

int cnt = 1000000;

void loop() {
}

void loop2() {
  out4(cnt);
}

void timer() {
  cnt--;
  Serial.print(cnt);
  Serial.print("\n");
}

