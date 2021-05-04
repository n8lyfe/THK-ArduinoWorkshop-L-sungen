/*
   RotEncoder Library example Code
   Prints out left turns as -1 and right turns as 1
   Created by Maurice Thomé, 06.04.2016
*/

#include <RotEncoder.h>

/*Pin Connections:
  Clock Pin = clkPin
  Data Pin = dtPin
*/

int clkPin = 9;
int dtPin = 10;

int tmp = 0;

RotEncoder enc(clkPin, dtPin);


void setup() {
  Serial.begin(9600);

}

void loop() {
  Serial.println(enc.getTurn());

}
