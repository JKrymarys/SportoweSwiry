#include "stdafx.h"
#include <iostream>
#include <string>
#include "CImg.h"

using namespace cimg_library;
using namespace std;

const int ArrSize = 255;

//declarations


#pragma region Funkcje




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

float negativelut(float value, float level = 0)
{
	if (value < 127) return value + 127;
	else return value - 127;
}


// ARRAY OF POINTERS TO FUNCTIONS
float(*operations[3])(float, float) = { brightlut, contrastlut, negativelut };



// PRZECHODZI PRZEZ WSZYSTKIE PIXELE WCZESNIEJ TWORZAC LUT ODPOWIEDNIE DO OPERACJI
void basicoperations(float level, CImg <float> & image, float(*operation)(float, float)) {

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
	delete [] lut;
}


//FLIPY

void verticalFlip(CImg<float> & image) {

	for (int x = 0; x < image.width(); x++)
	{
		for (int y = 0; y < image.height() / 2; y++)
		{
			for (int c = 0; c < 3; c++) {
				swap(image(x, y, 0, c), image(x, image.height() - y - 1, 0, c));
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
				swap(image(x, y, 0, c), image(image.width() - x - 1, y, 0, c));
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
				swap(image(x, y, 0, c), image(image.width() - 1 - x, image.height() - 1 - y, 0, c));
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
			arr[temp] = image(x+i, y+j, 0, c);
			temp++;
		}
	}
	sort(arr, arr + 9);
	///*cout << endl;
	//cout << endl;
	//for (int i = 0; i < 9; i++)
	//{
	//	*/cout << arr[i] << "\t";
	//}
	int mediana = (arr[4] + arr[5]) / 2;
	delete [] arr;
	return mediana;
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



void SaveImage(CImg<float> & image) {
	string name;
	cout << "Give name of output file" << endl;
	cin >> name;
	name += ".bmp";
	image.save(name.c_str());
}


#pragma endregion

int main(int argc, char * argv[]) {

	cout << "Hello in our program \n <if you need help, plese use --help >" << endl;
	string operation_to_do;
	string path_to_file;
	float modificator;
	CImg <float> image;




	//CHECK THE ARGUMENTS
	if (argc == 2 && (string)argv[1] == "--help")
	{
		cout << "Help......." << endl;
		return 0;
	}
	else if (argc == 3)
	{
		//load image 
		image.load(argv[1]);


		//operation
		operation_to_do = argv[2];
	}
	else
	{
		cout << "Invalid arguments" << endl;
		return 0;
	}


	// CHOISE OF THE OPERATION

	//OPERATIONS PERFORMED ON THE ORIGINAL IMAGE
	if ((string)argv[2] == "--brightness")
	{
		cout << "Give level of brighting " << endl;
		cin >> modificator;
		basicoperations(modificator, image, operations[0]);
		SaveImage(image);

	}
	else if ((string)argv[2] == "--contrast")
	{
		cout << "Give level of contrast " << endl;
		cin >> modificator;
		basicoperations(modificator, image, operations[1]);
		SaveImage(image);
	}
	else if ((string)argv[2] == "--negative")
	{
		basicoperations(0, image, operations[2]);
		SaveImage(image);
	}
	else if ((string)argv[2] == "--vflip") {

		verticalFlip(image);
		SaveImage(image);
	}
	else if ((string)argv[2] == "--hflip")
	{
		horizontalFlip(image);
		SaveImage(image);
	}
	else if ((string)argv[2] == "--dflip") {
		diagonalFlip(image);
		SaveImage(image);
	}

	//OPERATIONS PERFORMED ON THE COPY 
	else if ((string)argv[2] == "--shrink")
	{

		shrink(image);
	}
	else if ((string)argv[2] == "--enlarge")
	{
		SaveImage(enlarge(image));
	}
	else if ((string)argv[2] == "--median")
	{
		SaveImage(medianfilter(image));
	}


	//IN CASE OF INPROPIATE PARAMETER
	else
	{
		cout << "Invalid operation\n If you need help, run program with --help parameter" << endl;
	}




	return 0;
}