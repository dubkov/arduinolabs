void setup(){
  for (int i=2; i<10; i++){
    pinMode(i,OUTPUT);
  }
  Serial.begin(9600);
}

void loop(){
  if (Serial.available()>0){
    byte lol = Serial.read()-'0';
    digitalWrite(lol,!digitalRead(lol));
  }
}
