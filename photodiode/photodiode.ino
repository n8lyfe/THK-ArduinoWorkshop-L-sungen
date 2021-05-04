

void setup(void) {
  
  pinMode(3, OUTPUT);
  Serial.begin(9600);
  Serial.println();
    
}

void loop(void) {
  
  
  if (analogRead(A0) <50){
    analogWrite(3,0);
  }
  else{
    analogWrite(3, map(analogRead(A0),50,100,0,255));
  }
  Serial.println(analogRead(A0));


  delay(50);
}
