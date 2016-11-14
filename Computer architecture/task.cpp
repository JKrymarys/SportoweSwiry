#include <conio.h>
#include <dos.h>
#include <string.h>
#include <stdlib.h>
#include <iostream.h>

//----------------------------------------------------------------------------

const int ESCAPE = 1;
const int TICKPERSEC = 18;
const int MILISECPERTICK = 1000/TICKPERSEC;
const int F12 = 88;
int timeformat = 1;
unsigned int hours;
unsigned int minutes;
unsigned int seconds;
unsigned int miliseconds;
unsigned int currenttime = 0;
// we set starting display points because of hh:mm:ss:ssss format of display and because evey character cell in video memory consits of two bites.
const int SecondsDisplayStartPoint = 6*2;
const int MinutesDisplayStartPoint = 3*2;
const int MilisecondsDisplayStartPoint = 9*2;
void interrupt (* OldHandler08H)(...);
void interrupt (* OldHandler09H)(...);
char h[3]; // char array to hold hours
char m[3]; // char array to hold minutes
char s[3]; // char array to hold seconds
char ms[5]; // char array to hold miniseconds



//---------------------------------------------------------------------

void interrupt NewHandler08H(...)
{
	asm sti
	miliseconds+=MILISECPERTICK;
	if(miliseconds > 1000)
	{
		miliseconds = miliseconds - 1000;
		seconds++;
	}
	if(seconds >=60)
	{
		seconds = seconds - 60;
		minutes++;
	}
	if(minutes >= 60)
	{
		minutes= minutes -60;
		hours++;
	}
	
	
	itoa(hours, h, 10);
	itoa(minutes, m, 10);
	itoa(seconds, s, 10);
	itoa(miliseconds, ms, 10);
	
	// These if statements checks if a number is one digit number, if it is puts it in second position and sets first position to 0 to keep good formating
	
	if(s[1] == '\0')
	{
		s[1] = s[0];
		s[0] = '0';
	}
	
	if(m[1] == '\0')
	{
		m[1] = m[0];
		m[0] = '0';
	}
	
	if(h[1] == '\0')
	{
		h[1] = h[0];
		h[0] = '0';
	}
	
	if(timeformat == 1)
	{
		for(int i=0; i < 2; i++)
		{
			pokeb(0xB800, 0x0000 +i*2, h[i] );
			pokeb(0xB800, 0x0000 + i*2 + MinutesDisplayStartPoint, m[i]);
			pokeb(0xB800, 0x0000 + i*2 + SecondsDisplayStartPoint, s[i]);
		}
		for(i = 0; i < 4; i++)
		{
			pokeb(0xB800, 0x0000 + MilisecondsDisplayStartPoint + i*2, ' '); 
		}
	}
	else
	{
		for(int i =0; i < 2; i++)
		{
			pokeb(0xB800, 0x0000 + i*2, h[i] );
			pokeb(0xB800, 0x0000 + i*2 + MinutesDisplayStartPoint, m[i]);
			pokeb(0xB800, 0x0000 + i*2 + SecondsDisplayStartPoint, s[i]);
			pokeb(0xB800, 0x0000 + i*2 + MilisecondsDisplayStartPoint, ms[i]);
		}
		pokeb(0xB800, 0x0000 + MilisecondsDisplayStartPoint + 2*2, ms[2]);
		pokeb(0xB800, 0x0000 + MilisecondsDisplayStartPoint + 3*2, ms[3]);

	}
	OldHandler08H();
}


void interrupt NewHandler09H(...)
{
	asm sti
	if(inportb(0x60) == F12)
	{	
		if(timeformat == 1)
		{	
			timeformat = 0;
			for(int i = 0; i < 4; i++)
			{
				pokeb(0xB800, 0x0000 + MilisecondsDisplayStartPoint + i*2, ' '); 
			}
		}
		else if (timeformat == 0)
			timeformat = 1;
	}
	OldHandler09H();
}

void setColon() // setting colons appropiate to dipslaying format
{
		pokeb(0xB800, 0x0000 + 2*2, ':');
		pokeb(0xB800, 0x0000 + 5*2, ':');
		pokeb(0xB800, 0x0000 + 8*2, ':');
}

void main()
{
 struct dostime_t tm;
 _dos_gettime(&tm);
 hours = tm.hour;
 minutes = tm.minute;
 seconds = tm.second;
 _setcursortype(_NOCURSOR);
 clrscr();
 OldHandler08H = getvect(0x08);
 OldHandler09H = getvect(0x09);
 setvect(0x08, NewHandler08H);
 setvect(0x09, NewHandler09H);
 setColon();
 while (inportb(0x60) != ESCAPE);
 setvect(0x08, OldHandler08H);
 setvect(0x09, OldHandler09H);
 _setcursortype(_NORMALCURSOR);
 clrscr();
}