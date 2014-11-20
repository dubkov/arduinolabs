#ifndef fourSeven_h
#define fourSeven_h

class fourSeven
{
private:
	// segments of 7-segment digit
	unsigned char _p[7];
	// pictures of digits (you can extend it to cover hex if you want)
	unsigned char _pic[10];
	// global colon
	unsigned char _pinColon;
	// digits of 4x7-segment
	unsigned char _pin1st, _pin2nd, _pin3rd, _pin4th;

public:
    fourSeven(unsigned char pinA, unsigned char pinB, unsigned char pinC, unsigned char pinD, 
			  unsigned char pinE, unsigned char pinF, unsigned char pinG, unsigned char pinH, 
			  unsigned char pin1, unsigned char pin2, unsigned char pin3, unsigned char pin4 );

	void drawDigit(unsigned char pos, unsigned char digit);
	void show(unsigned int value);
	
	// amount of time given to each digit, in milliseconds
	unsigned char ms;
};


#endif
