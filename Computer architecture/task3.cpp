#include <conio.h>
#include <dos.h>
#include <string.h>
#include <stdlib.h>
#include <iostream.h>

//----------------------------------------------------------------------------

const int SCREENHEIGHT = 25;
const int SCREENWIDTH = 80; 
const int ESCAPE = 1;
const int F12 = 88;
const int DISPLAYSTARTPOINT = 0*SCREENHEIGHT+15*2;
const int CLOCKSIZE = 8; // hh:mm:ss
const unsigned char SECONDDECIMALEXTRACTMASK = 15; // 00001111 in binary


int displayflag = 0; 
unsigned char hours;
unsigned char minutes;
unsigned char seconds;
unsigned char previous[CLOCKSIZE*2]; // char array to hold previous data on place of clock
unsigned char clock[CLOCKSIZE];


void interrupt (* OldHandler08H)(...);
void interrupt (* OldHandler09H)(...);




//---------------------------------------------------------------------

void interrupt NewHandler08H(...)
{
	asm sti
	if(displayflag == 1)
	{
		
		outportb(0x70, 4); hours   = inportb(0x71);
		outportb(0x70, 2); minutes = inportb(0x71);
		outportb(0x70, 0); seconds = inportb(0x71);
		
		// Using bitwise operators to extract proper values
		
		clock[0] = (hours >> 4) + '0';
		clock[1] = (hours & SECONDDECIMALEXTRACTMASK) + '0';
		clock[3] = (minutes >> 4) + '0';
		clock[4] = (minutes & SECONDDECIMALEXTRACTMASK) + '0';
		clock[6] = (seconds >> 4) + '0';
		clock[7] = (seconds & SECONDDECIMALEXTRACTMASK) + '0';
		
		// Loop to display current time
		
		for(int i=0; i < CLOCKSIZE; i++)
		{
			pokeb(0xB800, 0x0000 + DISPLAYSTARTPOINT +i*2, clock[i]);
		}
	}
	OldHandler08H();
}


void interrupt NewHandler09H(...)
{
	asm sti
	if(inportb(0x60) == F12)
	{	
		if(displayflag == 0)
		{	
			for(int i = 0; i < CLOCKSIZE*2; i++)
			{
				previous[i] = peekb(0xB800, 0x0000 + DISPLAYSTARTPOINT + i);
			}
			displayflag = 1;
		}
		else
		{
			for(int i = 0; i < CLOCKSIZE*2; i++)
			{
				pokeb(0xB800, 0x0000 + DISPLAYSTARTPOINT + i, previous[i]);
			}
			displayflag = 0;
		}
	}
	OldHandler09H();
}



void main()
{
	clock[2] = ':';
	clock[5] = ':'; // setting colons
	OldHandler08H = getvect(0x08);
	OldHandler09H = getvect(0x09);
	setvect(0x08, NewHandler08H);
	setvect(0x09, NewHandler09H);
	keep(0, (_SS + ((_SP)/16) - _psp));
}