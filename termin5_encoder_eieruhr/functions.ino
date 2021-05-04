int encChange() {
  int value;
  value = encoder.read();
  if (value <= 0) {
    value = 0;
    encoder.write(0);
  }
  return (value);
}


void setTimer() {
  ledTurnOff();
  lcd.setCursor(0, 0);
  lcd.print("Time in Seconds:");
  lcd.setCursor(0, 1);
  int encVal = encChange() / 4;

  if (encVal != encTmp) {
    lcd.clear();
    lcd.print("Time in Seconds:");
    lcd.setCursor(0, 1);
    encTmp = encVal;
    lcd.print(encVal);
  }

  if (digitalRead(btn) == LOW && encVal > 0) {
    subMenu = 2;
  }
}



void startTimer(int seconds, long timeNow) {
  if ((millis() - timeNow) % 100 == 0) {
    lcd.clear();
    lcd.print((seconds * 1000 - (millis() - timeNow))/100);
  }
  if (millis() >= timeNow + seconds * 1000) {
    ledTurnOn();
  }
}



void ledTurnOn() {
  digitalWrite(led, HIGH);
  lcd.clear();
  lcd.print("Press Button");
  lcd.setCursor(0, 1);
  lcd.print("to Set Timer");
  subMenu = 0;
  encoder.write(0);
}



void ledTurnOff() {
  digitalWrite(led, LOW);
}

