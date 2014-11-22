#include <SPI.h>
// TODO: in Release Candidate redefine vaska as if(0)
#define vaska if(1)

void setup()
{
  // init standards
  SPI.begin();
  vaska Serial.begin(19200);
  
  // corresponds to leds:
  //         654321
  DDRC = 0b00111111;
  //             87
  DDRB = 0b00000011;
  
  // DOUBLE SPEED!!!
  SPSR |= 1;
  vaska Serial.println("Receiving end!");
}

unsigned char i=1;
void loop()
{
  lightUp(spi_receive());
  delay(1);
}

void lightUp(unsigned char bight)
{
  vaska Serial.println((int) bight);
  PORTC = bight;
  PORTB = bight >> 6;
}

unsigned char spi_receive()
{
  while (!(SPSR & (1<<SPIF)));  // spif means zaebis in afrikaans
  return SPDR;                    
}
