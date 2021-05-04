/*
   RGB Led Fader
   Fades an RGB LED by using the analogWrite() function
   Created at TH Köln
   by Maurice Thomé, 13.04.2016
*/

//PWM Output Pins:
int blue = 2;
int green = 3;
int red = 4;

//fade speed:
int speed = 10;


void setup() {

  //Set all used Pins as output Pins
  pinMode (blue, OUTPUT);
  pinMode (green, OUTPUT);
  pinMode (red, OUTPUT);

}

void loop() {

  //check https://www.arduino.cc/en/Reference/AnalogWrite for more information

  int k = 255;

  for (int i = 0; i <= 255; i++) {
    analogWrite (blue, k);
    analogWrite (green, i);
    k--;
    delay (speed);
  }

  k = 255;
  for (int i = 0; i <= 255; i++) {
    analogWrite (green, k);
    analogWrite (red, i);
    k--;
    delay (speed);
  }

  k = 255;
  for (int i = 0; i <= 255; i++) {
    analogWrite (red, k);
    analogWrite (blue, i);
    k--;
    delay (speed);
  }
}
