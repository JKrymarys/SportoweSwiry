#ifndef FOURIER_H_
#define FOURIER_H_

#include <complex>
#include "CImg.h"

using namespace cimg_library;
using namespace std;


complex<double> ** DFT(CImg<float> & image);
CImg<float> * IDFT(complex<double> ** Arr, int M, int N);
complex<double> First_Transform(complex<double> ** Arr, int column, int row, double N, bool inverse);
complex<double> Second_Transform(complex<double> ** Arr, int column, int row, double N, bool inverse);
void savefourier(complex<double> ** Arr, int M, int N);
void imageswap(CImg<float> & image);
complex<double> ** FFT(CImg<float> & image);
void FFT_ROW(complex<double> Arr[], int length);
void FFT_COLUMN(complex<double> ** Arr, int length, int column);


#endif // !FOURIER_H_
