#include "IMAGE.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include "CImg.h"


using namespace cimg_library;
using namespace std;

const int HistogramSize = 256;

int * createhistogramtable(CImg<float> & image, int channel)
{
	int * histogram = new int[HistogramSize]();
	for (int x = 0; x < image.width(); x++)
	{
		for (int y = 0; y < image.height(); y++)
		{
			histogram[(int)image(x, y)]++;
		}
	}
	for (int i = 0; i < HistogramSize; i++) {
		cout << histogram[i] << "\t";
	}
	cout << endl << endl;
	return histogram;
}


void createhistogramimage(CImg<float> & image, int channel)
{
	int * histogram = createhistogramtable(image, channel);
	int histogramheight = 0;
	for (int i = 0; i < HistogramSize; i++)
	{
		if (histogram[i] > histogramheight)
			histogramheight = histogram[i];
	}
	CImg<float> histogrampicture(HistogramSize, histogramheight/10 + 1, 1, 3);
	for (int x = 0; x < HistogramSize; x+=2)
	{
		for (float y = (histogramheight)/10 ; y > histogramheight/10-histogram[x]/10 ; y--)
		{
			histogrampicture(x, y) = 127;
			histogrampicture(x+1, y) = 127;
		}
	}
	SaveImage2(histogrampicture);
	delete[] histogram;
}


void UniformFinalProbabilityDensityFunction(CImg<float> & image, int channel)
{
	double numofpixels;
	int gmax, gmin, sum;
	gmax = 255;
	gmin = 0;
	numofpixels = image.width()*image.height();
	int * histogram = createhistogramtable(image, channel);
	float * lut = new float[HistogramSize];
	for (int i = 0; i < HistogramSize; i++)
	{
		sum = 0;
		for (int m = 0; m <= i; m++)
		{
			sum += histogram[m];
		}
		lut[i] = gmin + (gmax - gmin) * (1.0 / numofpixels) * sum;
	}
	cout << "LOOOOOOK UP TABLE" << endl;
	for (int i = 0; i < HistogramSize; i++) {
		cout << lut[i] << "\t";
	}
	cout << endl << endl << endl;
	for (int x = 0; x < image.width(); x++)
	{
		for (int y = 0; y < image.height(); y++)
		{

				image(x, y) = lut[(int)image(x, y)];
		}
	}
	image.save("dupa.bmp");
	createhistogramimage(image, channel);
	delete[] lut;
	delete[] histogram;
}