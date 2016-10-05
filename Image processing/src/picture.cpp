#include"Picture.h"

Picture::Picture(CImg & image)
{
	height = image.height();
	width = image.width();
	pct = new double*[height];
	for (int i = 0; i < height; i++)
	{
		pct[i] = new int[width];
	}
	for (x = 0; x < height; x++)
	{
		for (y = 0; y < width; y++)
		{
			pct[x][y] = image._atXY(x, y);
		}
	}
}
Picture::~Picture()
{
	for (int i = 0; i < height; i++)
	{
		delete [] pct[i];
	}
	delete [] pct;
}