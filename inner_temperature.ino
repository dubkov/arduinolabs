// Internal Temperature Sensor
// Example sketch for ATmega328 types.
// 
// April 2012, Arduino 1.0
int digit;
#define pA 0b1000000
#define pB 0b0100000
#define pC 0b0010000
#define pD 0b0001000
#define pE 0b0000100
#define pF 0b0000010
#define pG 0b0000001
#define pALL 0b1111111
#define p0 (pALL - pG)
#define p1 (pB + pC)
#define p2 (pALL - pF - pC)
#define p3 (pALL - pF - pE)
#define p4 (pALL - pA - pE - pD)
#define p5 (pALL - pE - pB)
#define p6 (pALL - pB)
#define p7 (pA + pB + pC)
#define p8 pALL
#define p9 (pALL - pE)

int pd[10] = {p0, p1, p2, p3, p4, p5, p6, p7, p8, p9};

int i,j;
unsigned char microdelay = 4;

void showint(unsigned int four, unsigned int colon=0)
{
  if(four > 9999) Serial.println("four > 9999");
  else
  {
    // first digit
    digit = four/1000;
    digitalWrite(10, colon);
    showdigit(0,1,1,1,digit);
    delay(microdelay);
    
    // second digit
    digit = four/100%10;
    digitalWrite(10, colon);
    showdigit(1,0,1,1,digit);
    delay(microdelay);
    
    // third digit
    digit = four/10%10;
    digitalWrite(10, colon);
    showdigit(1,1,0,1,digit);
    delay(microdelay);
    
    // fourth digit
    digit = four%10;
    digitalWrite(10, colon);
    showdigit(1,1,1,0,digit);
    delay(microdelay);
  }
}

void showdigit(int d1, int d2, int d3, int d4, int digit)
{  
    digitalWrite(11, d1);
    digitalWrite(12, d2);
    digitalWrite(13, d3);
    digitalWrite( 2, d4);
    for (i=1; i<8; i++)
      if(pd[digit] & (1<<(7-i))) digitalWrite(i+2,1);
        else digitalWrite(i+2,0);
}

void setup()
{
  for(i=2; i<14; i++)
    pinMode(i,OUTPUT);
  Serial.begin(9600);
  Serial.println(F("Internal Temperature Sensor"));
}

double val;
void loop()
{
  // Show the temperature in degrees Celcius.
  val = GetTemp() * 100;
  for(j = 0; j < 25; j++)
    showint(val,1);
  //debug();
}

void debug()
{
  while(!Serial.available());   // wait for input
  Serial.println("");          // \n
  i = 0;
  while(Serial.available())    // read bit string "010010110100",
  {                            // may be shorter or longer
    i++;                       // read next bit
    j = Serial.read();         // input
    if(j == '0') digitalWrite(i, LOW);  // nullate
    if(j == '1') digitalWrite(i, HIGH); // onate
    Serial.print((char) j);    // echo
    delay(10);                 // wate
  }
}

double GetTemp(void)
{
  unsigned int wADC;
  double t;

  // The internal temperature has to be used
  // with the internal reference of 1.1V.
  // Channel 8 can not be selected with
  // the analogRead function yet.

  // Set the internal reference and mux.
  ADMUX = (_BV(REFS1) | _BV(REFS0) | _BV(MUX3));
  ADCSRA |= _BV(ADEN);  // enable the ADC

  delay(20);            // wait for voltages to become stable.

  ADCSRA |= _BV(ADSC);  // Start the ADC

  // Detect end-of-conversion
  while (bit_is_set(ADCSRA,ADSC));

  // Reading register "ADCW" takes care of how to read ADCL and ADCH.
  wADC = ADCW;

  // The offset of 324.31 could be wrong. It is just an indication.
  t = (wADC - 324.31 ) / 1.22;

  // The returned temperature is in degrees Celcius.
  return (t);
}
