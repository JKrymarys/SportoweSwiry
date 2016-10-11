#include <dos.h>
#include <conio.h>
#include <string.h>
#include <iostream.h>



//constants

const int ESCAPE = 1;
const int UP = 72;
const int DOWN = 80;
const int LEFT = 75;
const int RIGHT = 77;
const int PLUS = 74;
const int MINUS = 78;
const int DELAY = 100;
const int WIDTH = 80;
const int HEIGHT = 25;

char TEXT[] = "ASSEMBLER IS COMING"; 
const int LENGTH =strlen(TEXT);






//variables
int x=40;
int y=12;
int color = 0x0F;

void main(){
	
	
 _setcursortype(_NOCURSOR);
clrscr();

	
	do{

	switch(inportb(0x60))
	{
		
		case UP:
			y--;
			delay(DELAY);
			clrscr();
			break;
		
		case DOWN:
			y++;
			delay(DELAY);
			clrscr();
			break;
	
	case LEFT:
			x--;
			delay(DELAY);
			clrscr();
			break;
		
	case RIGHT:
			x++;
			delay(DELAY);
			clrscr();
			break;
	
	

	case PLUS:
			
			if (color%16==15)
				color -=15;
			else
				color++;

			delay(DELAY);
			clrscr();
			break;
	
	case MINUS:
			color+=16;
			delay(DELAY);
			clrscr();
			break;
	}
	
	if(x>WIDTH-LENGTH)
	{
		x = WIDTH-LENGTH;
	}else if(x<0)
	{
		x=0;
	}
	
	if(y>HEIGHT-1)
	{
		y = HEIGHT-1;
	}else if(y<0){
		y=0;
	}

	
	int startingPoint =  (y*WIDTH*2) + (x*2);
	
	for(int i=0; i < LENGTH; i++)
	{
		pokeb(0xB800, 0x0000 + i*2 +startingPoint+ 0, TEXT[i] );
	}	

		for (int j=0; j<WIDTH*HEIGHT*2; j+=2)
			{
				pokeb(0xB800, 0x0000 + j + 1, color);

			}
		
			

	}while(inport(0x60)!= ESCAPE );

	clrscr();
	_setcursortype(_NORMALCURSOR);
}