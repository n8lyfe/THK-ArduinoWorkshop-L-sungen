/*

*/

// include the library code:
#include <LiquidCrystal.h>
#include <Encoder.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 10, 9);
Encoder encoder (2, 3);

int led = 7;
int btn = 8;

int encTmp = 0;

int deBouPeriod = 20;
long tmpTimeNow = 0;
long timeNow = 0;


int subMenu = 0;


void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.print("Press Button");
  lcd.setCursor(0, 1);
  lcd.print("to Set Timer");
  pinMode(led, OUTPUT);
  pinMode(btn, INPUT_PULLUP);
}

void loop() {

  if (digitalRead(btn) == LOW && subMenu == 0) {
    lcd.clear();
    subMenu = 1;

  }
  else if (subMenu == 1) {
    setTimer();
  }

  else if (subMenu == 2) {
    timeNow = millis();
    subMenu = 3;
  }

  else if (subMenu == 3) {
    startTimer(encChange() / 4, timeNow);
  }


}

