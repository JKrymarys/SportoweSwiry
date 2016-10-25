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
// we set starting display point because of hh:mm:ss:ssss format of display and because evey character cell in video memory consits of two bites.
const int SecondsDisplayStartPoint = 6*2;
const int MinutesDisplayStartPoint = 3*2;
const int MilisecondsDisplayStartPoint = 9*2;
void interrupt (* OldHandler08H)(...);
void interrupt (* OldHandler09H)(...);

//---------------------------------------------------------------------

void interrupt NewHandler08H(...)
{
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
	char h[3]; // char array to hold hours
	char m[3]; // char array to hold minutes
	char s[3]; // char array to hold seconds
	char ms[5]; // char array to hold miniseconds
	
	itoa(hours, h, 10);
	itoa(minutes, m, 10);
	itoa(seconds, s, 10);
	itoa(miliseconds, ms, 10);
	
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
		pokeb(0xB800, 0x0000 + 2*2, ':');
		pokeb(0xB800, 0x0000 + 5*2, ':');
		pokeb(0xB800, 0x0000 + 8*2, ' ');
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
		pokeb(0xB800, 0x0000 + 2*2, ':');
		pokeb(0xB800, 0x0000 + 5*2, ':');
		pokeb(0xB800, 0x0000 + 8*2, ':');
	}
	OldHandler08H();
}


void interrupt NewHandler09H(...)
{
	if(inport(0x60) == F12)
	{	
		if(timeformat == 1)
			timeformat = 0;
		else if (timeformat == 0)
			timeformat = 1;
	}
	outp(0x20,0x20);
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
 while (inportb(0x60) != ESCAPE);
 setvect(0x08, OldHandler08H);
 setvect(0x09, OldHandler09H);
 _setcursortype(_NORMALCURSOR);
 clrscr();
}