#include "IMAGE.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include "CImg.h"


using namespace cimg_library;
using namespace std;

const int HistogramSize = 256;

// NA RAZIE TYLKO CZERWONY TRZEBA SIE ZASTANOWIC JAK ROZPOZNAC CZARNO BIALY I KOLOROWY
void histogram(CImg<float> & image)
{
	int histogram[HistogramSize] = {};
	int histogramred[HistogramSize] = {};
	int histogramblue[HistogramSize] = {};
	int histogramgreen[HistogramSize] = {};
	for (int x = 0; x < image.width(); x++)
	{
		for (int y = 0; y < image.height(); y++)
		{
			histogramred[(int)image(x, y, 0, 0)]++;
		}
	}
	int histogramheight = 0;
	for (int i = 0; i < HistogramSize; i++)
	{
		if (histogramred[i] > histogramheight)
			histogramheight = histogramred[i];
	}
	CImg<float> histogramredpicture(HistogramSize, histogramheight/10, 1, 3);
	for (int x = 0; x < HistogramSize; x+=2)
	{
		for (int y = 0; y < histogramred[x]/10; y++)
		{
			histogramredpicture(x, y, 0, 0) = 255;
			histogramredpicture(x+1, y, 0, 0) = 255;
		}
	}
	verticalFlip(histogramredpicture);;
	histogramredpicture.save("test.bmp");
}