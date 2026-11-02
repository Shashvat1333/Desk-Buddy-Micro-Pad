#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "USB.h"
#include "USBHIDKeyboard.h"

#define SCR_W 128
#define SCR_H 64
#define OLED_ADDR 0x3C

Adafruit_SSD1306 oled(SCR_W, SCR_H, &Wire, -1);
USBHIDKeyboard hid;

const int TCH = 3;      
const int POT = 4;
const int PADS[3] = {5, 6, 9};   

enum Face { BLANK, SMILE, STOPWATCH, MAD, PONG_MODE };
Face face = BLANK;
bool oledOk = false;

bool lastTouch = false;
unsigned long touchDown = 0, lastTapAt = 0;
int tapCount = 0;
const unsigned long TAP_GAP = 400;
const unsigned long LONG_HOLD = 3000;
bool holdHandled = false;

unsigned long touchIgnoreUntil = 0;

unsigned long swStart = 0;
unsigned long madStart = 0;


bool padPrev[3] = {HIGH, HIGH, HIGH};
unsigned long padChanged[3] = {0, 0, 0};
unsigned long padLockUntil = 0;

int padY = 24;
const int PAD_H = 16, PAD_W = 4;
float bx = 64, by = 32;
float vx = 2.5, vy = 1.5;


void setup() {
  Serial.begin(115200);
  hid.begin();
  USB.begin();

  pinMode(TCH, INPUT);
  pinMode(POT, INPUT);
  for (int i = 0; i < 3; i++) pinMode(PADS[i], INPUT_PULLUP);

  touchIgnoreUntil = millis() + 1500;

  Wire.begin(7, 8);

  for (int tries = 0; tries < 3 && !oledOk; tries++) {
    oledOk = oled.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
    if (!oledOk) delay(150);
  }

  if (!oledOk) {
    Serial.println("oled not found, pads only");
    return;
  }
  oled.clearDisplay();
  oled.display();
}


void loop() {
  readPads();

  if (!oledOk) return;

  readTouch();

  switch (face) {
    case BLANK:
      static bool wasBlank = false;
      if (!wasBlank) {
        oled.clearDisplay();
        oled.display();
        wasBlank = true;
      }
      return;
    case SMILE:     drawSmile(); break;
    case STOPWATCH: drawStopwatch(); break;
    case MAD:
      drawMad();
      if (millis() - madStart > 3000) face = BLANK;
      break;
    case PONG_MODE: runPong(); break;
  }
}


void readPads() {
  unsigned long now = millis();

  for (int i = 0; i < 3; i++) {
    bool v = digitalRead(PADS[i]);
    if (v == padPrev[i]) continue;
    if (now - padChanged[i] < 30) continue;   

    padChanged[i] = now;
    padPrev[i] = v;

    if (v == HIGH) continue;       
    if (now < padLockUntil) continue;   

    if (i == 0) padSnip();
    else if (i == 1) padMic();
    else padNotepad();
  }
}


void padSnip() {
  hid.press(KEY_LEFT_GUI);
  hid.press(KEY_LEFT_SHIFT);
  hid.press('s');
  delay(40);
  hid.releaseAll();
  padLockUntil = millis() + 300;
}

void padMic() {
  hid.press(KEY_F9);
  delay(40);
  hid.releaseAll();
  padLockUntil = millis() + 300;
}

void padNotepad() {
  hid.press(KEY_LEFT_GUI);
  hid.press('r');
  delay(40);
  hid.releaseAll();

  delay(450);  

  hid.print("notepad");
  delay(40);
  hid.press(KEY_RETURN);
  delay(40);
  hid.releaseAll();


  padLockUntil = millis() + 1500;
}


void readTouch() {
  unsigned long now = millis();
  bool t = digitalRead(TCH) == HIGH;

  if (now < touchIgnoreUntil) {
    lastTouch = false;
    return;
  }

  if (t && !lastTouch) {
    if (face != BLANK) {
      face = BLANK;
      tapCount = 0;
      holdHandled = true;   
      lastTouch = true;
      return;
    }
    touchDown = now;
    holdHandled = false;
  }

  if (t && !holdHandled && now - touchDown >= LONG_HOLD && face == BLANK) {
    face = PONG_MODE;
    resetBall();
    holdHandled = true;
    tapCount = 0;
  }

  if (!t && lastTouch && !holdHandled && now - touchDown < 1000) {
    tapCount++;
    lastTapAt = now;
  }

  lastTouch = t;

  if (tapCount > 0 && !t && now - lastTapAt > TAP_GAP) {
    if (face == BLANK) {
      if (tapCount == 1) face = SMILE;
      else if (tapCount == 2) {
        swStart = now;
        face = STOPWATCH;
      }
      else {
        madStart = now;
        face = MAD;
      }
    }
    tapCount = 0;
  }
}


void drawSmile() {
  oled.clearDisplay();
  oled.fillRoundRect(24, 20, 24, 24, 6, SSD1306_WHITE);
  oled.fillRoundRect(80, 20, 24, 24, 6, SSD1306_WHITE);

  oled.fillCircle(64, 42, 10, SSD1306_WHITE);
  oled.fillRect(50, 32, 28, 10, SSD1306_BLACK);
  oled.display();
}

void drawMad() {
  oled.clearDisplay();
  oled.fillRoundRect(24, 26, 24, 16, 4, SSD1306_WHITE);
  oled.fillRoundRect(80, 26, 24, 16, 4, SSD1306_WHITE);

  oled.drawLine(20, 18, 50, 28, SSD1306_WHITE);
  oled.drawLine(20, 19, 50, 29, SSD1306_WHITE);
  oled.drawLine(108, 18, 78, 28, SSD1306_WHITE);
  oled.drawLine(108, 19, 78, 29, SSD1306_WHITE);

  oled.fillCircle(64, 54, 8, SSD1306_WHITE);
  oled.fillRect(50, 54, 28, 10, SSD1306_BLACK);
  oled.display();
}

void drawStopwatch() {
  oled.clearDisplay();

  unsigned long sec = (millis() - swStart) / 1000;
  int mm = sec / 60;
  int ss = sec % 60;

  oled.setTextSize(1);
  oled.setTextColor(SSD1306_WHITE);
  oled.setCursor(44, 12);
  oled.print("TIMER");

  oled.setTextSize(2);
  oled.setCursor(34, 32);
  if (mm < 10) oled.print("0");
  oled.print(mm);
  oled.print(":");
  if (ss < 10) oled.print("0");
  oled.print(ss);

  oled.display();
}


void resetBall() {
  bx = 64;
  by = 32;
  vx = 2.5;
  vy = 1.5;
}

int potAvg() {
  long total = 0;
  for (int i = 0; i < 8; i++) total += analogRead(POT);
  return total / 8;
}

void runPong() {
  padY = map(potAvg(), 0, 4095, 0, SCR_H - PAD_H);

  bx += vx;
  by += vy;

  if (by <= 0 || by >= SCR_H - 3) vy = -vy;
  if (bx >= SCR_W - 4) vx = -vx;

  if (bx <= PAD_W + 2) {
    if (by + 3 >= padY && by <= padY + PAD_H) {
      vx = -vx;
      bx = PAD_W + 3;  
    } else if (bx <= 0) {
      resetBall();
    }
  }

  oled.clearDisplay();
  oled.fillRect(2, padY, PAD_W, PAD_H, SSD1306_WHITE);
  oled.fillRect((int)bx, (int)by, 3, 3, SSD1306_WHITE);

  for (int y = 0; y < SCR_H; y += 6) oled.drawFastVLine(64, y, 3, SSD1306_WHITE);

  oled.display();
}
