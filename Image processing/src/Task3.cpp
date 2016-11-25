#include "IMAGE.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include "CImg.h"
#include <sstream>


using namespace cimg_library;
using namespace std;

const int FOREGROUND = 255;
const int BACKGROUND = 0;
const int INACTIVE = 50;


class StructuralElement {
private:
	unsigned char tab[9];
public:
	StructuralElement(int n);
	int operator()(int x, int y) { return tab[y * 3 + x]; }
};

StructuralElement::StructuralElement(int n)
{
	if (n == 3)
	{
		for (int i = 0; i < 9; i++)
		{
			tab[i] = FOREGROUND;
		}
	}
	if (n == 1)
	{
		for (int i = 0; i < 9; i++)
		{
			tab[i] = BACKGROUND;
		}
		tab[4] = FOREGROUND;
		tab[5] = FOREGROUND;
	}
	if (n == 4)
	{
		for (int i = 0; i < 9; i++)
		{
			tab[i] = BACKGROUND;
		}
		tab[1] = FOREGROUND;
		tab[3] = FOREGROUND;
		tab[4] = FOREGROUND;
		tab[5] = FOREGROUND;
		tab[7] = FOREGROUND;
	}
	if (n == 121)
	{
		tab[0] = BACKGROUND;
		tab[1] = BACKGROUND;
		tab[2] = BACKGROUND;
		tab[3] = INACTIVE;
		tab[4] = FOREGROUND;
		tab[5] = INACTIVE;
		tab[6] = FOREGROUND;
		tab[7] = FOREGROUND;
		tab[8] = FOREGROUND;
	}
	if (n == 122)
	{
		tab[0] = BACKGROUND;
		tab[1] = BACKGROUND;
		tab[2] = BACKGROUND;
		tab[3] = FOREGROUND;
		tab[4] = FOREGROUND;
		tab[5] = FOREGROUND;
		tab[6] = BACKGROUND;
		tab[7] = BACKGROUND;
		tab[8] = BACKGROUND;
	}
}



CImg<float> * Dilation(CImg<float> & image, int mask) {
	CImg <float> * filtredimage = new CImg<float>(image);

	StructuralElement Element(mask);
	
	for (int x = 1; x < image.width()-1; x++)			//in such case we avoid the border pixels
	{
		for (int y = 1; y < image.height()-1; y++)
		{
			if (image(x, y, 0, 0) == FOREGROUND)
			{
				dilate(filtredimage, x, y, Element);
			}
		}
	}
	return filtredimage;
}


void dilate(CImg<float> * image, int x, int y, StructuralElement & Element)
{
	for (int _x = 0; _x < 3; _x++)
	{
		for (int _y = 0; _y < 3; _y++)
		{
			if (Element(_x, _y) == FOREGROUND)
			{
				(*image)(x - 1 + _x, y - 1 + _y) = FOREGROUND;
			}
		}
	}
	// If the element in the middle is BACKGROUND (VI, VIII)
	if (Element(1, 1) == BACKGROUND)
	{
		(*image)(x, y) = BACKGROUND;
	}
}

CImg<float> * Erosion(CImg<float> & image, int mask) {
	CImg <float> * filtredimage = new CImg<float>(image);

	StructuralElement Element(mask);

	for (int x = 1; x < image.width() - 1; x++)			//in such case we avoid the border pixels
	{
		for (int y = 1; y < image.height() - 1; y++)
		{
			if (image(x, y, 0, 0) == FOREGROUND)
			{
				if (!erosecheck(image, x, y, Element))
					(*filtredimage)(x, y, 0, 0) = BACKGROUND;
			}
		}
	}
	return filtredimage;
}


bool erosecheck(CImg<float> & image, int x, int y, StructuralElement & Element)
{
	for (int _x = 0; _x < 3; _x++)
	{
		for (int _y = 0; _y < 3; _y++)
		{
			if (Element(_x, _y) == FOREGROUND)
			{
				if (!(image(x - 1 + _x, y - 1 + _y) == FOREGROUND))
				{
					return false;
				}
			}
		}
	}
	return true;
}


CImg<float> * HMT(CImg<float> & image, int n)
{
	StructuralElement StEl(n);
	CImg<float> * filtredimage = new CImg<float>(image);
	for (int x = 1; x < image.width()-1; x++)
	{
		for (int y = 1; y < image.height()-1; y++)
		{
			HMTcheck(image, x, y, StEl) ? (*filtredimage)(x, y) = FOREGROUND : (*filtredimage)(x, y) = BACKGROUND;
		}
	}
	return filtredimage;
}


bool HMTcheck(CImg<float> & image, int x, int y, StructuralElement & StEl)
{
	for (int _x = 0; _x < 3; _x++)
	{
		for (int _y = 0; _y < 3; _y++)
		{
			if (!(StEl(_x, _y) == INACTIVE))
			{
				if (!(StEl(_x, _y) == image(x - 1 + _x, y - 1 + _y)))
					return false;
			}
		}
	}
	return true;
}