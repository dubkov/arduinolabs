void setup(){
  randomSeed (0);
}

void loop(){
  analogWrite(10,random(0,155));
  analogWrite(9,random(0,155));
  analogWrite(3,random(0,155));
  if (millis()%1000==0){
    digitalWrite (10,HIGH);
    digitalWrite (9,HIGH);
    digitalWrite (3,HIGH);
    delay(500);
  }
}
