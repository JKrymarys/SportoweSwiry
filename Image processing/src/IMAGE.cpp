#include "stdafx.h"
#include "IMAGE.h"
#include <iostream>
#include <string>
#include<cstdlib>
#include<cmath>

using namespace cimg_library;


const int ArrSize = 255;

// FUNCKJA TWORZACA LUT W ZALEZNOSCI OD PRZEKAZANEJ OPERACJI
int * lookuptable(float level, float(*operation)(float, float))
{
	int * lut = new int[ArrSize];
	{
		for (int i = 0; i < ArrSize; i++)
		{
			lut[i] = operation(i, level);
		}


	}
	return lut;
}

// MOZLIWE OPERACJE ZWIAZANE Z LUTEM

float brightlut(float value, float level)
{
	if (value + level < 0) { return 0; }
	else if (value + level > 255) { return 255; }
	else return value + level;
}

float contrastlut(float value, float level)
{
	if (value < 127)
	{
		return value - level < 0 ? 0 : value - level;
	}
	if (value >= 127)
	{
		return value + level > 255 ? 255 : value + level;
	}

	//if (value < 127) {
	//	return value*level < 0 ? 0 : value*level;
	//}
	//if (value > 127) {
	//	return value*level > 255 ? 255 : value*level;
	//}
}

float negativelut(float value, float level )
{
	if (value < 127) return value + 127;
	else return value - 127;
}


// ARRAY OF POINTERS TO FUNCTIONS




// PRZECHODZI PRZEZ WSZYSTKIE PIXELE WCZESNIEJ TWORZAC LUT ODPOWIEDNIE DO OPERACJI
void basicoperations(float level, CImg<float> & image, float(*operation)(float, float)) {

	int * lut = lookuptable(level, operation);

	for (int x = 0; x < image.width(); x++)
	{
		for (int y = 0; y < image.height(); y++)
		{
			for (int c = 0; c < 3; c++)
			{
				image(x, y, 0, c) = lut[(int)image(x, y, 0, c)];
			}
		}
	}
	delete[] lut;
}


//FLIPY

void verticalFlip(CImg<float> & image) {

	for (int x = 0; x < image.width(); x++)
	{
		for (int y = 0; y < image.height() / 2; y++)
		{
			for (int c = 0; c < 3; c++) {
				std::swap(image(x, y, 0, c), image(x, image.height() - y - 1, 0, c));
			}
		}
	}

}

void horizontalFlip(CImg<float> & image) {

	for (int y = 0; y < image.height(); y++)
	{
		for (int x = 0; x < image.width() / 2; x++)
		{
			for (int c = 0; c < 3; c++) {
				std::swap(image(x, y, 0, c), image(image.width() - x - 1, y, 0, c));
			}
		}
	}

}

void diagonalFlip(CImg<float>& image) {

	for (int x = 0; x < image.width(); x++)
	{
		for (int y = 0; y < image.height() / 2; y++)
		{
			for (int c = 0; c < 3; c++)
			{
				std::swap(image(x, y, 0, c), image(image.width() - 1 - x, image.height() - 1 - y, 0, c));
			}
		}
	}
}

void shrink(CImg<float> & image) {

	CImg<float> shrinked_image((image.width() / 2), (image.height() / 2), 1, 3);

	for (int x = 0; x < shrinked_image.width(); x++)  //zeby nie wjsc za tablice
	{
		for (int y = 0; y < shrinked_image.height(); y++)
		{
			for (int c = 0; c < 3; c++)
			{

				shrinked_image(x, y, 0, c) = image(2 * x, 2 * y, 0, c); //co drugi pixel (0,0)(2,2)(4,4) itp

			}
		}
	}

	shrinked_image.save("shrinked.bmp");
}

CImg<float> enlarge(CImg<float> & image) {

	CImg<float> enlarged_image((image.width() * 2), (image.height() * 2), 1, 3);

	for (int x = 0; x < enlarged_image.width() - 1; x += 2)
	{
		for (int y = 0; y < enlarged_image.height() - 1; y += 2)
		{
			for (int c = 0; c < 3; c++)
			{

				enlarged_image(x, y, 0, c) = image(x / 2, y / 2, 0, c);
				enlarged_image(x + 1, y + 1, 0, c) = image(x / 2, y / 2, 0, c);

			}
		}
	}
	return enlarged_image;
}




float mediana(CImg<float> & image, int x, int y, int c)
{
	int * arr = new int[9];
	int temp = 0;
	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			arr[temp] = image(x + i, y + j, 0, c);
			temp++;
		}
	}
	std::sort(arr, arr + 9);
	int mediana = (arr[4] + arr[5]) / 2;
	delete[] arr;
	return mediana;
}


float geometricmean(CImg<float> & image, int x, int y, int c)
{
	int sum = 0;
	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			sum+=image(x + i, y + j, 0, c);
		}
	}
	return (int)std::power(sum, 1/9);
}

CImg<float> medianfilter(CImg<float> & image) {
	CImg<float> filterimage = image;
	for (int x = 1; x < image.width() - 1; x++)
	{
		for (int y = 1; y < image.height() - 1; y++)
		{
			for (int c = 0; c < 3; c++)
			{
				filterimage(x, y, 0, c) = mediana(image, x, y, c);
			}
		}
	}
	return filterimage;
}

CImg<float> geometricfilter(CImg<float> & image) {
	CImg<float> filterimage = image;
	for (int x = 1; x < image.width() - 1; x++)
	{
		for (int y = 1; y < image.height() - 1; y++)
		{
			for (int c = 0; c < 3; c++)
			{
				filterimage(x, y, 0, c) = geometricmean(image, x, y, c);
			}
		}
	}
	return filterimage;
}

	



void SaveImage(CImg<float> & image) {
	std::string name;
	std::cout << "Give name of output file" << std::endl;
	std::cin >> name;
	name += ".bmp";
	image.save(name.c_str());
}
