#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <iostream.h>

//--------------------------------------------------------------------------//

typedef unsigned char BYTE;
typedef unsigned int  WORD;
typedef unsigned int  UINT;
typedef unsigned long DWORD;
typedef unsigned long LONG;

//--------------------------------------------------------------------------//


const int ESC = 27;
const int UP = 72;
const int DOWN = 80;
const int SPACE = 32;
const int MAX_INTENSITY = 255;
const int MIN_INTENSITY = 0;


//--------------------------------------------------------------------------//

struct BITMAPFILEHEADER
{
 UINT  bfType;
 DWORD bfSize;
 UINT  bfReserved1;
 UINT  bfReserved2;
 DWORD bfOffBits;
};

struct BITMAPINFOHEADER
{
 DWORD biSize;
 LONG  biWidth;
 LONG  biHeight;
 WORD  biPlanes;
 WORD  biBitCount;
 DWORD biCompression;
 DWORD biSizeImage;
 LONG  biXPelsPerMeter;
 LONG  biYPelsPerMeter;
 DWORD biClrUsed;
 DWORD biClrImportant;
};

struct RGBQUAD
{
 BYTE rgbBlue;
 BYTE rgbGreen;
 BYTE rgbRed;
 BYTE rgbReserved;
};

//--------------------------------------------------------------------------//

BITMAPFILEHEADER bmfh;
BITMAPINFOHEADER bmih;
RGBQUAD palette[256];
BYTE *video_memory = (BYTE *)0xA0000000L;
FILE *bitmap_file;

//--------------------------------------------------------------------------//

void set_video_mode(int mode)
{
 REGPACK regs;
 regs.r_ax = mode;
 intr(0x10, &regs);
 // asm mov ax, 13h
 // asm int 10h <- graphics card  interrupt handler
}

//--------------------------------------------------------------------------//

void set_video_palette()
{
 outportb(0x03C8, 0);
 for (int i = 0; i < bmih.biClrUsed; i++)
 {
  outp(0x03C9, palette[i].rgbRed   * 63 / 255);
  outp(0x03C9, palette[i].rgbGreen * 63 / 255);
  outp(0x03C9, palette[i].rgbBlue  * 63 / 255);
 }
}

//--------------------------------------------------------------------------//


void palette_up()
{
 outportb(0x03C8, 0);	
 for (int i = 0; i < bmih.biClrUsed; i++)
 {
	if(!(palette[i].rgbRed == MAX_INTENSITY))
		outp(0x03C9, (palette[i].rgbRed++) * 63/255);
	else
		outp(0x03C9, palette[i].rgbRed * 63/255);
	
	if(!(palette[i].rgbGreen  == MAX_INTENSITY))
		outp(0x03C9, (palette[i].rgbGreen++) * 63/255);
	else
		outp(0x03C9, palette[i].rgbGreen * 63/255);
	
    if(!(palette[i].rgbBlue == MAX_INTENSITY))
		outp(0x03C9, (palette[i].rgbBlue++) * 63/255);
	else
		outp(0x03C9, palette[i].rgbBlue * 63/255);
  
 }
}



//--------------------------------------------------------------------------//

void palette_down()
{
 outportb(0x03C8, 0);	
 for (int i = 0; i < bmih.biClrUsed; i++)
 {
	if(!(palette[i].rgbRed == MIN_INTENSITY))
		outp(0x03C9, (palette[i].rgbRed--) * 63/255);
	else
		outp(0x03C9, palette[i].rgbRed * 63/255);
	
	if(!(palette[i].rgbGreen  == MIN_INTENSITY))
		outp(0x03C9, (palette[i].rgbGreen--) * 63/255);
	else
		outp(0x03C9, palette[i].rgbGreen * 63/255);
	
    if(!(palette[i].rgbBlue == MIN_INTENSITY))
		outp(0x03C9, (palette[i].rgbBlue--) * 63/255);
	else
		outp(0x03C9, palette[i].rgbBlue * 63/255);
  
 }
}

//--------------------------------------------------------------------------//


void palette_negation()
{
 outportb(0x03C8, 0);
 for(int i = 0; i < bmih.biClrUsed; i++)
 {
	palette[i].rgbRed = ~palette[i].rgbRed;
	outp(0x03C9, palette[i].rgbRed * 63/255); 
	
	palette[i].rgbGreen = ~palette[i].rgbGreen;
	outp(0x03C9, palette[i].rgbGreen * 63/255);
	
	palette[i].rgbBlue = ~palette[i].rgbBlue;
	outp(0x03C9, palette[i].rgbBlue * 63/255);
 }
}


//--------------------------------------------------------------------------//


void display_image_data(char *file_name)
{
 bitmap_file = fopen(file_name, "rb");
 fread(&bmfh, sizeof(bmfh), 1, bitmap_file);
 fread(&bmih, sizeof(bmih), 1, bitmap_file);
 fread(&palette[0], bmih.biClrUsed * sizeof(RGBQUAD),  1, bitmap_file);
 set_video_palette();
 for(int i = bmih.biHeight-1; i >=0; i--)
 {
	fread(&video_memory[i*bmih.biWidth], bmih.biWidth, 1, bitmap_file);
 }
 fclose(bitmap_file);
}

//--------------------------------------------------------------------------//

int main(int argc, char *argv[])
{
 if (argc != 2) 
 { 
  cout << "Incorrect number of arguments." << endl;
 
  return 1; 
 }
 set_video_mode(0x13);
 display_image_data(argv[1]);
 int BUTTON = 0;
 BUTTON = getch();
 while(BUTTON != ESC)
 {
	if(BUTTON == UP)
		palette_up();
	if(BUTTON == DOWN)
		palette_down();
	if(BUTTON == SPACE)
		palette_negation();
	BUTTON = getch();
 }
 set_video_mode(0x03);
 return 0;
}

//--------------------------------------------------------------------------//