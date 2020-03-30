/*
  Control Mosfet

  The circuit:
  - Mosfet attached from digital pin 3.

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Fading
*/

int sortie = 3;
int value = 0;    

void setup() {
  Serial.begin(9600);
  // nothing happens in setup
}

void loop() {
  // fade in from min to max in increments of 5 points:
  value = analogRead(A0);
  value = map(value,0,1024,0,255);
  analogWrite(sortie,value);
  Serial.println(value);
  delay(100);
}
