#include <SPI.h>
// TODO: in Release Candidate redefine vaska as if(0)
#define vaska if(1)

unsigned char fight = 0;

void setup() {
  Serial.begin(19200);

  // start the SPI library:
  SPI.begin();
  
  // corresponds to leds:
  //         654321
  DDRC = 0b00111111;
  //             87
  DDRB = 0b00000011;
//  SPSR |=1;
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,INPUT);
  pinMode(13,OUTPUT);
  vaska Serial.println("Sending end!");
  
}

unsigned char i=1;
void loop() {
  if (Serial.available()){
    fight = Serial.read();
    digitalWrite(10,LOW);
    SPI.transfer(fight);
    digitalWrite(10,HIGH);
    lightUp(fight);
  }
  
}

void lightUp(unsigned char bight)
{
  vaska Serial.println((int) bight);
  PORTC = bight;
  PORTB = bight >> 6;
}
