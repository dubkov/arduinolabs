#include <SPI.h>
#define pM pinMode

void setup()
{
  // init standards
  SPCR = (1<<SPE);
  
  // Pin modes for leds:
  //         654321
  DDRC = 0b00111111;
  //             87
  DDRB = 0b00000011;
  // Pin modes for SPI:
  pM(SCK,INPUT);  
  pM(MISO,OUTPUT);  
  pM(MOSI,INPUT);  
  pM(SS,INPUT);
  
  // DOUBLE SPEED!!!
  //SPSR |= 1;
}

unsigned char i=1;
void startupDemo()
{
  for(i=0; i<4; i++)
  {  lightUp(255);  delay(100);
     lightUp( 0 );  delay(100);  }
  for(i=0; i<8; i++)
  {  lightUp(1<<(i%8));  delay(100);  }
  for(i=6; i!=255; i--)
  {  lightUp(1<<i);  delay(100);  }
  lightUp(0);
}


void loop()
{
    lightUp(spi_receive());
    delay(1);
}

void lightUp(unsigned char bight)
{
  PORTC = bight;
  PORTB = bight >> 6;
}

unsigned char spi_receive()
{
  while (!(SPSR & (1<<SPIF)));
  return SPDR;                    
}
