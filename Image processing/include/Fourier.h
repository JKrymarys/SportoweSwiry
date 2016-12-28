#ifndef FOURIER_H_
#define FOURIER_H_

#include <complex>
#include "CImg.h"
#include "Image.h"

using namespace cimg_library;
using namespace std;


complex<double> ** DFT(CImg<float> & image);
complex<double> ** IDFT(complex<double> ** Arr, int M, int N);
complex<double> First_Transform(complex<double> ** Arr, int column, int row, double N, bool inverse);
complex<double> Second_Transform(complex<double> ** Arr, int column, int row, double N, bool inverse);
void imageswap(CImg<float> & image);
complex<double>** LowPassFilter(CImg<float> &image, int radius);
complex<double>** HighPassFilter(CImg<float> &image, int radius);
complex<double>** BandPassFilter(CImg<float> &image, int radius_start, int radius_end);
complex<double>** BandCutFilter(CImg<float> &image, int radius_start, int radius_end);
complex<double>** MaskFilter(int variant, CImg<float>& image);
CImg<float>* PrintMask(complex<double>**Arr, int M, int N);

bool checkRadius(int x, int y, int x_0, int y_0, int radius);
bool checkRadiusRegion(int x, int y, int x_0, int y_0, int radius_start, int radius_end);
#endif // !FOURIER_H_
