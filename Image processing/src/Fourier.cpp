#include "Fourier.h"
#include <cmath>
#include <iostream>

using namespace std;

const complex<double> i(0.0, 1.0);
const double pi = 3.1415;

void DFT(CImg<float> & image)
{
	complex<double> ** Arr = new complex<double>*[image.height()];
	for (int i = 0; i < image.height(); ++i)
	{
		Arr[i] = new complex<double>[image.width()];
	}

	complex<double> ** Arr2 = new complex<double>*[image.height()];
	for (int i = 0; i < image.height(); ++i)
	{
		Arr2[i] = new complex<double>[image.width()];
	}

	for (int i = 0; i < image.height(); i++)			
	{
		
		for (int x = 0; x < image.width(); x++)
		{
			Arr[i][x] = First_Transform(image, x, i);
			//cout << "At coordinates " << x << i << " Real Value - " << Arr[i][x].real() << " Imaginary - " << Arr[i][x].imag() << endl;
			//cout << x << " " << i << " " << Arr[i][x] << endl;
		}
	}

	cout << "FIRST PART DONE";

	double N = image.height();

	for (int i = 0; i < image.width(); i++)
	{
		for (int x = 0; x < image.height(); x++)
		{
			Arr2[x][i] = Second_Transform(Arr, i, x, N);
		}
	}


	
	image.channel(0);
	
	double newvalue;

	for (int x = 0; x < image.width(); x++)			
	{
		for (int y = 0; y < image.height(); y++)
		{
			newvalue = abs(Arr2[y][x]);
			//newvalue = sqrt(Arr2[y][x].real()*Arr2[y][x].real() + Arr2[y][x].imag()*Arr2[y][x].imag());
			image(x, y) = newvalue;
			if (image(x, y) > 1000)
			cout << image(x, y) << endl;
			//cout << "At coordinates " << x << y << " Real Value - " << Arr2[y][x].real() << " Imaginary - " << Arr2[y][x].imag() << endl;
		}
	}
	imageswap(image);
	image.save("test.bmp");

	cout << "SECOND PART DONE";
}


complex<double> First_Transform(CImg<float> & image, int column, int row)
{
	complex<double> sum(0.0, 0.0);
	double N = image.width();
	double alfa;
	for (int x = 0; x < N; ++x)
	{
		alfa = ((2 * pi* column * x) / N);
		sum += double(image(x, row)) * (cos(alfa) - i*sin(alfa));
	}
	sum = sum / sqrt(N);
	return sum;
}

complex<double> Second_Transform(complex<double> ** Arr, int column, int row, double N)
{
	complex<double> sum(0.0, 0.0);
	double alfa;
	for (int x = 0; x < N; ++x)
	{
		alfa = ((2 * pi* row * x) / N);
		sum += Arr[x][column] * (cos(alfa) + i*sin(alfa));
	}
	sum = sum / sqrt(N);
	return sum;

}

void imageswap(CImg<float> & image)
{
	for (int i = 0; i < image.width() / 2; i++)
	{
		for (int j = 0; j < image.height() / 2; j++)
		{
			std::swap(image(i, j), image(i + image.width() / 2, j + image.height() / 2));
		}
	}
	for (int i = image.width() / 2; i < image.width(); i++)
	{
		for (int j =0; j < image.height()/2; j++)
		{
			std::swap(image(i, j), image(i - image.width() / 2, j + image.height() / 2));
		}
	}
}