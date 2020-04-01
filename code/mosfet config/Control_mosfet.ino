/*
  Control Mosfet for motor speed.
*/

int sortie = 3;
int value = 0;    

void setup() {
  Serial.begin(9600);
}

void loop() {
  value = analogRead(A0);
  value = map(value,0,1024,0,255);
  analogWrite(sortie,value);
  Serial.println(value);
  delay(100);
}
