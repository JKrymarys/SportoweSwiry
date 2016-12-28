#define _USE_MATH_DEFINES
#include "Fourier.h"
#include <cmath>
#include <iostream>

using namespace std;

const complex<double> i(0.0, 1.0);
double pi = M_PI;


complex<double> ** DFT(CImg<float> & image)
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
			Arr2[i][x] = image(x, i);
		}
	}


	for (int i = 0; i < image.height(); i++)
	{

		for (int x = 0; x < image.width(); x++)
		{
			Arr[i][x] = First_Transform(Arr2, x, i, image.width(), false);
			//cout << "At coordinates " << x << i << " Real Value - " << Arr[i][x].real() << " Imaginary - " << Arr[i][x].imag() << endl;
			//cout << x << " " << i << " " << Arr[i][x] << endl;
		}
	}

	cout << "FIRST PART DONE";


	for (int i = 0; i < image.width(); i++)
	{
		for (int x = 0; x < image.height(); x++)
		{
			Arr2[x][i] = Second_Transform(Arr, i, x, image.height(), false);
			//cout << Arr2[x][i] << endl;
		}
	}
	image.channel(0);
	double newvalue;

	for (int i = 0; i < (image.width() / 2) ; ++i)
	{
		for (int j = 0; j < (image.height() / 2); ++j)
		{
			std::swap(Arr2[j][i], Arr2[j + image.height()/2 ][i + image.width()/2 ]);
		}
	}
	for (int i = image.width() / 2; i < image.width(); ++i)
	{
		for (int j = 0; j < (image.height() / 2); ++j)
		{
			std::swap(Arr2[j][i], Arr2[j + image.height() / 2][i - image.width() / 2]);
		}
	}


	for (int x = 0; x < image.width(); x++)
	{
		for (int y = 0; y < image.height(); y++)
		{
			newvalue = abs(Arr2[y][x]);
			//newvalue = sqrt(Arr2[y][x].real()*Arr2[y][x].real() + Arr2[y][x].imag()*Arr2[y][x].imag());
			image(x, y) = newvalue;
			//if (image(x, y) > 1000)
			//cout << image(x, y) << endl;
			//cout << "At coordinates " << x << y << " Real Value - " << Arr2[y][x].real() << " Imaginary - " << Arr2[y][x].imag() << endl;
		}
	}

	imageswap(image);
	image.save("test.bmp");

	return Arr2;


}


complex<double> ** IDFT(complex<double> ** Arr, int M, int N)
{

	complex<double> ** Arr1 = new complex<double>*[N];
	for (int i = 0; i < N; i++)
	{
		Arr1[i] = new complex<double>[M];
	}

	complex<double> ** Arr2 = new complex<double>*[N];
	for (int i = 0; i < N; i++)
	{
		Arr2[i] = new complex<double>[M];
	}

	for (int i = 0; i < M; i++)
	{
		for (int x = 0; x < N; x++)
		{
	
			Arr1[i][x] = First_Transform(Arr, x, i, M, true);
			//cout << Arr2[x][i] << endl;
		}
	}


	for (int i = 0; i < N; i++)
	{

		for (int x = 0; x < M; x++)
		{
			Arr2[x][i] = Second_Transform(Arr1,i, x, N, true);
			//cout << "At coordinates " << x << i << " Real Value - " << Arr[i][x].real() << " Imaginary - " << Arr[i][x].imag() << endl;
			//cout << x << " " << i << " " << Arr[i][x] << endl;
		}
	}

	return Arr2;
}


complex<double> First_Transform(complex<double> ** Arr, int column, int row, double N, bool inverse)
{
	complex<double> sum(0.0, 0.0);
	double k;
	if (inverse)
		k = -1;
	else
		k = 1;
	double alfa;
	for (int x = 0; x < N; ++x)
	{
		alfa = ((2 * pi* column * x) / N);
		sum += Arr[row][x] * (cos(alfa) - k*i*sin(alfa));
	}
		sum = sum / sqrt(N);
	return sum;
}

complex<double> Second_Transform(complex<double> ** Arr, int column, int row, double N, bool inverse)
{
	complex<double> sum(0.0, 0.0);
	double alfa;
	double k;
	if (inverse)
		k = -1;
	else
		k = 1;
	for (int x = 0; x < N; ++x)
	{
		alfa = ((2 * pi* row * x) / N);
		sum += Arr[x][column] * (cos(alfa) - k*i*sin(alfa));
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


complex<double>** LowPassFilter(CImg<float> &image,int radius) {

	//little idiotproof solution :P
	if (radius > image.width() / 2 || radius > image.height() / 2)
	{
		cout << "You have chosen too big radius" << endl;
		return 0;
	}

	complex<double>  **mask = DFT(image);
	

	//just 4 debbuging
	CImg<float> mask_image(image.width(), image.height());
		mask_image = *PrintMask(mask,image.width(),image.height());
		mask_image.save("mask.bmp");

		for (int x = 0; x < image.width(); ++x)
		{
			for (int y = 0; y < image.height(); ++y)
			{
				if (!checkRadius(x, y, image.width() / 2, image.height() / 2, radius))
					mask[y][x] = 0;
			}
		}

		mask_image = *PrintMask(mask, image.width(), image.height());
		mask_image.save("mask2.bmp");

		return mask;
}

CImg<float>* PrintMask(complex<double>**Arr, int N, int M)
{
	CImg<float> * toreturn = new CImg<float>(M, N);

	for (int x = 0; x < toreturn->width(); x++)
	{
		for (int y = 0; y < toreturn->height(); y++)
		{
			//newvalue = sqrt(Arr2[y][x].real()*Arr2[y][x].real() + Arr2[y][x].imag()*Arr2[y][x].imag());
			(*toreturn)(x, y) = abs(Arr[y][x]);
			//if (image(x, y) > 1000)
			//cout << image(x, y) << endl;
			//cout << "At coordinates " << x << y << " Real Value - " << Arr2[y][x].real() << " Imaginary - " << Arr2[y][x].imag() << endl;
		}
	}
	return toreturn;
}

bool checkRadius(int x, int y, int x_0, int y_0, int radius)
{
	if (pow(x - x_0, 2) + pow(y - y_0, 2) <= radius*radius)
		return true;
	else
		return false;
}


complex<double>** HighPassFilter(CImg<float> &image, int radius) {

	//little idiotproof solution :P
	if (radius > image.width() / 2 || radius > image.height() / 2)
	{
		cout << "You have chosen too big radius" << endl;
		return 0;
	}

	complex<double>  **mask = DFT(image);


	//just 4 debbuging
	CImg<float> mask_image(image.width(), image.height());
	mask_image = *PrintMask(mask, image.width(), image.height());
	mask_image.save("mask.bmp");

	for (int x = 0; x < image.width(); ++x)
	{
		for (int y = 0; y < image.height(); ++y)
		{
			if (checkRadius(x, y, image.width() / 2, image.height() / 2, radius))
				mask[y][x] = 0;
		}
	}

	mask_image = *PrintMask(mask, image.width(), image.height());
	mask_image.save("mask2.bmp");

	return mask;
}


complex<double>** BandPassFilter(CImg<float> &image, int radius_start, int radius_end) {

	//little idiotproof solution :P
	if (radius_end > image.width() / 2 || radius_end > image.height() / 2)
	{
		cout << "You have chosen too big radius" << endl;
		return 0;
	}

	complex<double>  **mask = DFT(image);


	//just 4 debbuging
	CImg<float> mask_image(image.width(), image.height());
	mask_image = *PrintMask(mask, image.width(), image.height());
	mask_image.save("mask.bmp");

	for (int x = 0; x < image.width(); ++x)
	{
		for (int y = 0; y < image.height(); ++y)
		{
			if (!checkRadiusRegion(x, y, image.width() / 2, image.height() / 2, radius_start,radius_end))
				mask[y][x] = 0;
		}
	}

	mask_image = *PrintMask(mask, image.width(), image.height());
	mask_image.save("mask2.bmp");

	return mask;
}

complex<double>** BandCutFilter(CImg<float> &image, int radius_start, int radius_end) {

	//little idiotproof solution :P
	if (radius_end > image.width() / 2 || radius_end > image.height() / 2)
	{
		cout << "You have chosen too big radius" << endl;
		return 0;
	}

	complex<double>  **mask = DFT(image);


	//just 4 debbuging
	CImg<float> mask_image(image.width(), image.height());
	mask_image = *PrintMask(mask, image.width(), image.height());
	mask_image.save("mask.bmp");

	for (int x = 0; x < image.width(); ++x)
	{
		for (int y = 0; y < image.height(); ++y)
		{
			if (checkRadiusRegion(x, y, image.width() / 2, image.height() / 2, radius_start, radius_end))
				mask[y][x] = 0;
		}
	}

	mask_image = *PrintMask(mask, image.width(), image.height());
	mask_image.save("mask2.bmp");

	return mask;
}
bool checkRadiusRegion(int x, int y, int x_0, int y_0, int radius_start, int radius_end)
{
	if (pow(radius_start,2) <= pow(x - x_0, 2) + pow(y - y_0, 2) && pow(x - x_0, 2) + pow(y - y_0, 2) <= pow(radius_end,2))
		return true;
	else
		return false;
}

complex<double>** MaskFilter(int variant, CImg<float>& image)
{
	//TO DO:
	// flip mask for proper variant
	CImg<float> mask_img;
	if (variant < 3)
		 mask_img = Load_Image("F5mask1.bmp");
	else
		mask_img = Load_Image("F5mask2.bmp");

	switch (variant)
	{
	
	case 2:

		break;
	case 3:
		break;
	}

	complex<double>  **mask = DFT(image);

	//just 4 debbuging
	CImg<float> mask_image(image.width(), image.height());
	mask_image = *PrintMask(mask, image.width(), image.height());
	mask_image.save("mask.bmp");

	for (int x = 0; x < image.width(); ++x)
	{
		for (int y = 0; y < image.height(); ++y)
		{
			if (mask_img(x,y) == 0)
				mask[y][x] = 0;
		}
	}

	mask_image = *PrintMask(mask, image.width(), image.height());
	mask_image.save("mask2.bmp");

	return mask;

}