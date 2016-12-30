#include "Fourier.h"
#include <cmath>
#include <iostream>

using namespace std;

const complex<double> i(0.0, 1.0);
const double pi = 3.1415;


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
			
		}
	}


	
	for (int i = 0; i < image.width(); i++)
	{
		for (int x = 0; x < image.height(); x++)
		{
			Arr2[x][i] = Second_Transform(Arr, i, x, image.height(), false);
			cout << "At coordinates " << x << i << " Real Value - " << Arr2[i][x].real() << " Imaginary - " << Arr2[i][x].imag() << endl;
		}
	}

	
	return Arr2;

	

}


CImg<float> * IDFT(complex<double> ** Arr, int M, int N)
{

	complex<double> ** Arr1 = new complex<double>*[N];
	for (int i = 0; i < N; ++i)
	{
		Arr1[i] = new complex<double>[M];
	}

	complex<double> ** Arr2 = new complex<double>*[N];
	for (int i = 0; i < N; ++i)
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

	CImg<float> * toreturn = new CImg<float>(M, N);

	for (int x = 0; x < toreturn->width(); x++)
	{
		for (int y = 0; y < toreturn->height(); y++)
		{
			//newvalue = sqrt(Arr2[y][x].real()*Arr2[y][x].real() + Arr2[y][x].imag()*Arr2[y][x].imag());
			(*toreturn)(x, y) = abs(Arr2[y][x]);
			//if (image(x, y) > 1000)
			//cout << image(x, y) << endl;
			//cout << "At coordinates " << x << y << " Real Value - " << Arr2[y][x].real() << " Imaginary - " << Arr2[y][x].imag() << endl;
		}
	}
	return toreturn;
	
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
	if (inverse)
		sum = sum / N;
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
	if(inverse)
		sum = sum / N;
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

void savefourier(complex<double> ** Arr, int width, int height)
{
	CImg<float> * tosave = new CImg<float>(width, height);
	

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			(*tosave)(x, y) = abs(Arr[y][x]);
		}
	}
	imageswap((*tosave));
	tosave->save("test.bmp");
}


complex<double> ** FFT(CImg<float> & image)
{
	complex<double> ** Arr = new complex<double>*[image.height()];
	for (int i = 0; i < image.height(); ++i)
	{
		Arr[i] = new complex<double>[image.width()];
	}


	for (int i = 0; i < image.height(); i++)
	{

		for (int x = 0; x < image.width(); x++)
		{
			Arr[i][x] = image(x, i);
		}
	}

	//Transform each row

	for (int i = 0; i < image.height(); i++)
	{
		FFT_ROW(Arr[i], image.width());
	}


	//Transform each colum
	
	for (int i = 0; i < image.width(); i++)
	{
		FFT_COLUMN(Arr, image.height(), i);
	}

	/*
	cout << "FFT EFFECTS" << endl << endl;

	for (int i = 0; i < image.height(); i++)
	{

		for (int x = 0; x < image.width(); x++)
		{
			cout << "At coordinates " << x << i << " Real Value - " << Arr[i][x].real() << " Imaginary - " << Arr[i][x].imag() << endl;
			//cout << x << " " << i << " " << Arr[i][x] << endl;
		}
	}
	*/
	return Arr;
}

void FFT_ROW(complex<double> Arr[], int length)
{
	if (length <= 1)
		return;

	complex<double> * ArrOdd = new complex<double>[length / 2];
	complex<double> * ArrEven = new complex<double>[length / 2];
	for (int i = 0, x = 0; i < length / 2; x = x + 2, i++)
	{
		ArrEven[i] = Arr[x];
		ArrOdd[i] = Arr[x + 1];
	}


	FFT_ROW(ArrEven, length / 2);
	FFT_ROW(ArrOdd, length / 2);

	
	complex<double> alfa;
	complex<double> t;
	for (int k = 0; k < length / 2; ++k)
	{
		alfa = ((2 * pi * k) / length);
		t = (cos(alfa) - i*sin(alfa)) * ArrOdd[k];
		Arr[k] = ArrEven[k] + t;
		Arr[k + length / 2] = ArrEven[k] - t;
	}
}

/*
void FFT_COLUMN(complex<double> ** Arr, int length, int column)
{

	complex<double> * ArrOdd = new complex<double>[length / 2];
	complex<double> * ArrEven = new complex<double>[length / 2];
	for (int i = 0, x = 0; i < length / 2; x = x + 2, i++)
	{
		ArrEven[i] = Arr[column][x];
		ArrOdd[i] = Arr[column][x + 1];
	}


	FFT_ROW(ArrEven, length / 2);
	FFT_ROW(ArrOdd, length / 2);


	complex<double> alfa;
	complex<double> t;
	for (int k = 0; k < length / 2; ++k)
	{
		alfa = ((2 * pi * k) / length);
		t = (cos(alfa) - i*sin(alfa)) * ArrOdd[k];
		Arr[column][k] = ArrEven[k] + t;
		Arr[column][k + length / 2] = ArrEven[k] - t;
	}
}
*/

void FFT_COLUMN(complex<double> ** Arr, int length, int column)
{

	complex<double> * Array = new complex<double>[length];
	for (int i = 0; i < length; i++)
	{
		Array[i] = Arr[i][column];
	}


	FFT_ROW(Array, length);

	for (int i = 0; i < length; i++)
	{
		 Arr[i][column] = Array[i];
	}
	delete[] Array;
}