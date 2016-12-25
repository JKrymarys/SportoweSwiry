#ifndef FOURIER_H_
#define FOURIER_H_

#include <complex>
#include "CImg.h"

using namespace cimg_library;
using namespace std;


void DFT(CImg<float> & image);
complex<double> First_Transform(CImg<float> & image, int column, int row);
complex<double> Second_Transform(complex<double> ** Arr, int column, int row, double N);
void imageswap(CImg<float> & image);


#endif // !FOURIER_H_
