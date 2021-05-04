/*
   Example Menu
   Example Code to showcase an example menu.
   Includes the LiquidCrystal library by Adafruit & the Encoder library by Paul Stoffregen.
   Created at TH Köln
   v_0.2
   by Maurice Thomé, 07.06.2016
*/



// include the library code:
#include <LiquidCrystal.h>
#include <Encoder.h>

//Dispaly & Encoder:
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
Encoder enc(10, 9);

//LEDs, use your PWM Ouputs!
int ledRed = 6;
int ledGreen = 7;
int ledBlue = 8;

//RGB Werte:
int redValue = -1;
int blueValue = -1;
int greenValue = -1;

//Button Digitalpin
int btn = 13;


//Hier wird die Menüvariable initalisiert. Für den Beispiel Code ist sie auf 0 gesetzt. Kann aber auch einen Anderen Wert einnehmen.
int menuState = 0;
int tmpMenuState = 1000;

//Button debounce Variablen
boolean btnstate = false;
const int debouncePeriod = 30;
long lastKeyPressTime = 0;
long oldPosition = 100;



void setup() {
  lcd.begin(16, 2);
  pinMode(btn, INPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledBlue, OUTPUT);
}

void loop() {
  long timeNow = millis();

  //Anfangs Menü (menuState = 0) Hier wird das erste mal auf das Menü zugegriffen.
  if (menuState == 0 && tmpMenuState != menuState) {

    //Setzt eine temporäre Variable, damit das Menü nicht ständig neu läd und somit das Display nicht flackert.
    tmpMenuState = menuState;

    //1. Menü Punkt wird geschrieben
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.write("Menu");
    lcd.setCursor(0, 0);
    lcd.blink();
  }

  //Button abfrage.
  if (digitalRead(btn) == HIGH && btnstate == false) {
    //debounce:
    btnstate = true;
    lastKeyPressTime = timeNow;

    //Löscht jedes mal den Inhalt des Displays
    lcd.clear();
    lcd.setCursor(1, 0);

    //Button wurde das 1. mal gedrückt und jetzt wird der Menüstatus auf 2 geändert.
    if (menuState == 0) {
      lcd.write("set red");
      menuState = 2;
    }

    //Button wurde gedrückt. Menüstatus ändert sich auf 4, gibt aber vorher auf dem LCD noch "set Blue" aus
    else if (menuState == 3) {
      lcd.setCursor(1, 0);
      lcd.write("set blue");
      lcd.setCursor(0, 0);
      lcd.blink();
      menuState = 4;
    }

    //Button wurde gedrückt. Menüstatus ändert sich auf 6, gibt aber vorher auf dem LCD noch "set Green" aus
    else if (menuState == 5) {
      lcd.setCursor(1, 0);
      lcd.write("set green");
      lcd.setCursor(0, 0);
      lcd.blink();
      menuState = 6;
    }

    //redValue != -1 damit diese if-Abfrage übersprungen wird beim 1. Durchlauf, da rot, grün oder blau nur einen Wert von 0...255 annehmen können.
    if (menuState == 2 && redValue != -1) {
      lcd.write("set blue");
      menuState = 3;
    }
    else if (menuState == 4 && blueValue != -1) {
      lcd.write("set green");
      menuState = 5;
    }
    //Letzter Menüstatus setzt das Menü wieder auf Status 0. Setzt gleichzeitig die RBG Werte wieder auf -1.
    else if (menuState == 6 && greenValue != -1) {
      redValue = -1;
      blueValue = -1;
      greenValue = -1;
      menuState = 0;
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.write("Menu");
      lcd.setCursor(0, 0);
      lcd.blink();
    }
  }

  //gibt den button wieder frei nachdem die debounce Periode abgelaufe  ist
  else if (digitalRead(btn) == LOW && timeNow > lastKeyPressTime + debouncePeriod) {
    btnstate = false;
  }

  //Hier wird der RGB-Led Ihre Werte zugewiesen wenn der Menüstatus 2,4 oder 6 ist. Das sind die Statuse in denen die Werte verändert werden können.
  if (menuState == 2 || menuState == 4 || menuState == 6) {

    //Die Encoderposition wird ausgelesen. Passiert in der Bibliothek
    long newPosition = enc.read();

    //Wenn sich der Encoderwert ändert ( if (newPosition != oldPosition)) gibt er diesen Wert mit lcd.print aus
    if (newPosition != oldPosition) {
      //Übergibt den neuen Wert dem alten Wert
      oldPosition = newPosition;

      //Wenn der Wert des Encoders kleiner als 0 gedreht wird, wird der Wert auf 0 limitiert
      if (newPosition / 4 < 0) {
        newPosition = 0;
        enc.write(newPosition);
      }
      //Wenn der Wert des Encoders größer als 255 gedreht wird, wird der Wert auf 255 limitiert
      if (newPosition / 4 >= 255) {
        newPosition = 255;
        enc.write(newPosition);
      }

      //Je nach Menüstatus (menuState) wird hier rot, grün oder der blue Wert zugewiesen und über digital Write an die Led übergeben.
      if (menuState == 2) {
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.write("set red");
        lcd.setCursor(1, 1);

        //Displayausgabe der aktuellen Encoder Position. Die Library zählt alle 4 Positionen des Encoders hoch. Eine Rasterdrehung entspricht 4 Postionen
        lcd.print(newPosition / 4);
        //Schreibt über digitalWrite die Werte auf die LEDs
        redValue = newPosition / 4;
        digitalWrite(ledRed, redValue);
      }
      //Menüstatus um den Wert der blauen LED zu ändern
      else if (menuState == 4) {
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.write("set blue");
        lcd.setCursor(1, 1);
        lcd.print(newPosition / 4);
        blueValue = newPosition / 4;
        digitalWrite(ledBlue, blueValue);
      }
      //Menüstatus um den Wert der grünen LED zu ändern
      else if (menuState == 6) {
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.write("set green");
        lcd.setCursor(1, 1);
        lcd.print(newPosition / 4);
        greenValue = newPosition / 4;
        digitalWrite(ledGreen, greenValue);
      }
    }
  }

}





