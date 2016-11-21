#include "IMAGE.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include "CImg.h"
#include <sstream>


using namespace cimg_library;
using namespace std;

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
			tab[i] = 255;
		}
	}
	if (n == 1)
	{
		for (int i = 0; i < 9; i++)
		{
			tab[i] = 0;
		}
		tab[4] = 255;
		tab[5] = 255;
	}
	if (n == 4)
	{
		for (int i = 0; i < 9; i++)
		{
			tab[i] = 0;
		}
		tab[1] = 255;
		tab[3] = 255;
		tab[4] = 255;
		tab[5] = 255;
		tab[7] = 255;
	}
}



CImg<float> * Dilation(CImg<float> & image, int mask) {
	CImg <float> * filtredimage = new CImg<float>(image);

	StructuralElement Element(mask);
	
	for (int x = 1; x < image.width()-1; x++)			//in such case we avoid the border pixels
	{
		for (int y = 1; y < image.height()-1; y++)
		{
			if (image(x, y, 0, 0) == 255)
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
			if (Element(_x, _y) == 255)
			{
				(*image)(x - 1 + _x, y - 1 + _y) = 255;
			}
		}
	}
	// If the element in the middle is white (VI, VIII)
	if (Element(1, 1) == 0)
	{
		(*image)(x, y) = 0;
	}
}

CImg<float> * Erosion(CImg<float> & image, int mask) {
	CImg <float> * filtredimage = new CImg<float>(image);

	StructuralElement Element(mask);

	for (int x = 1; x < image.width() - 1; x++)			//in such case we avoid the border pixels
	{
		for (int y = 1; y < image.height() - 1; y++)
		{
			if (image(x, y, 0, 0) == 255)
			{
				if (!erosecheck(filtredimage, x, y, Element))
					(*filtredimage)(x, y, 0, 0) = 0;
			}
		}
	}
	return filtredimage;
}


bool erosecheck(CImg<float> * image, int x, int y, StructuralElement & Element)
{
	for (int _x = 0; _x < 3; _x++)
	{
		for (int _y = 0; _y < 3; _y++)
		{
			if (Element(_x, _y) == 255)
			{
				if (!((*image)(x - 1 + _x, y - 1 + _y) == 255))
				{
					return false;
				}
			}
		}
	}
	return true;
}