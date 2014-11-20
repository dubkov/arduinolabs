/* fourSeven.cpp
Four-Seven is an Arduino library for 4-digit 7-segment led-display.  
Created by Powerless Duo, November 15, 2014
*/

#include <Arduino.h>
#include <inttypes.h>
#include "stdlib.h"
#include "fourSeven.h"

#define dW digitalWrite

fourSeven::fourSeven(unsigned char pinA, unsigned char pinB, unsigned char pinC, unsigned char pinD, 
					 unsigned char pinE, unsigned char pinF, unsigned char pinG, unsigned char pinH, 
					 unsigned char pin1, unsigned char pin2, unsigned char pin3, unsigned char pin4 )
{
    _p[0] = pinA, _p[1] = pinB, _p[2] = pinC, _p[3] = pinD, 
	_p[4] = pinE, _p[5] = pinF, _p[6] = pinG, _pinColon = pinH;
	_pin1st = pin1, _pin2nd = pin2, _pin3rd = pin3, _pin4th = pin4;
	
	_pic[0] = 0b1111110, _pic[1] = 0b0110000, _pic[2] = 0b1101101, 
	_pic[3] = 0b1111001, _pic[4] = 0b0110011, _pic[5] = 0b1011011, 
	_pic[6] = 0b1011111, _pic[7] = 0b1110000, _pic[8] = 0b1111111, 
	_pic[9] = 0b1111011; // you can extend it here
	
	for (int i=0; i<7; i++)
		pinMode(_p[i],OUTPUT);
	pinMode(_pinColon, OUTPUT);
	pinMode(_pin1st, OUTPUT);
	pinMode(_pin2nd, OUTPUT);
	pinMode(_pin3rd, OUTPUT);
	pinMode(_pin4th, OUTPUT);
}

void fourSeven::drawDigit(unsigned char pos, unsigned char digit)
{
	switch(pos)
	{			// dW is defined as digitalWrite
	case 1:		dW(_pin1st, 0);	dW(_pin2nd, 1);	dW(_pin3rd, 1);	dW(_pin4th, 1);	break;
	case 2:		dW(_pin1st, 1);	dW(_pin2nd, 0);	dW(_pin3rd, 1);	dW(_pin4th, 1);	break;
	case 3:		dW(_pin1st, 1);	dW(_pin2nd, 1);	dW(_pin3rd, 0);	dW(_pin4th, 1);	break;
	case 4:		dW(_pin1st, 1);	dW(_pin2nd, 1);	dW(_pin3rd, 1);	dW(_pin4th, 0);	break;
	default:	dW(_pin1st, 1);	dW(_pin2nd, 1);	dW(_pin3rd, 1);	dW(_pin4th, 1);	break;
	}
	
	if(digit < 10)
		for (int i=0; i<7;i++)
			digitalWrite(_p[i],(_pic[digit]&(64>>i)) ? 1 : 0);
	else
		/* handle this in any way necessary */;
}

void fourSeven::show(unsigned int value)
{
	if(value > 9999) /* handle this in any way necessary */;
	else
	{
		drawDigit(4, value%10);		delay(ms);
		drawDigit(3, value/10%10);	delay(ms);
		drawDigit(2, value/100%10); delay(ms);
		drawDigit(1, value/1000);	delay(ms);
		drawDigit(0,0);
	}
}
