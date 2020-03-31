/*
  Control Mosfet avec peak de puissance cadencé

  The circuit:
  - Mosfet attached from digital pin 3.

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Fading
*/

int sortie = 3;
int value = 0;
int omega = 0; //en RPM
long T = 0;
int incomingByte = 0; // for incoming serial data
int i = 0;
long T_lecture = 0;
long t_avant = 0;
long t_actuel = 0;
int v_corr = 0;
float M_actuel = 0; // couple 
float M[] = {0, 0.07, 0.35, 0.92, 1.37, 0.82,1.01, 2.26, 1.58, 0.57, 0.11, 0.01};

void setup() {
  Serial.begin(9600);
  // nothing happens in setup
}

void loop() {
  // fade in from min to max in increments of 5 points:
  value = analogRead(A0);
  value = map(value,0,1024,0,255);
  omega = map(value,0,255,0,40);
  T = 60000/omega; //en millis
  T = constrain(T,0,60000);
  T_lecture = (long) T / sizeof(M)/sizeof(M[0]);
  
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();
    incomingByte = map(incomingByte,0,100,0,50);
    i = i + incomingByte;
  }
  
  //lecture du tableau selon la période T
  t_actuel = millis();
  if(t_actuel - t_avant >= T_lecture){
    if(i < sizeof(M)/sizeof(M[0])){
      i++;
    }
    else{
      i = 0;
    }
    t_avant = t_actuel;
  }
//  v_corr = (int) (omega + 3.48*M[i])*(24/58);
  v_corr = (int) (omega + 3.48*M[i])*0.413;
  value = map(v_corr,0,24,0,255);
  value = constrain(value,0,255); 
  analogWrite(sortie,value);
//  Serial.println(value);
  delay(10);
}
