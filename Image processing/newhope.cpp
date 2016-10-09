#include "stdafx.h"
#include <iostream>
#include <string>
#include "CImg.h"

using namespace cimg_library;
using namespace std;

const int ArrSize = 255;

//declarations



// FUNCKJA TWORZACA LUT W ZALEZNOSCI OD PRZEKAZANEJ OPERACJI
int * lookuptable(float level, float(*operation)(float, float))
{
	int * lut = new int[ArrSize];
	{
		for (int i = 0; i < ArrSize; i++)
		{
			lut[i] = operation(i, level);
		}

		//cout << endl << "LOOKUPTABLE TEST" << endl;

		//for (int i = 0; i < ArrSize; i++)
		//{
		//	cout << lut[i] << endl;
		//}

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
				image(x, y, 0, c) = lut[ (int)image(x, y, 0, c) ];
			}
		}
	}
}


//FLIPY

void verticalFlip(CImg<float> & image) {

	for (int x = 0; x < image.width(); x++)
	{
		for (int y = 0; y < image.height()/2; y++)
		{
			for (int c = 0; c < 3; c++) {
				swap(image(x, y, 0, c),image(x,image.height() - y - 1,0,c));
			}
		}
	}

}

void horizontalFlip(CImg<float> & image) {

	for (int y = 0; y < image.height(); y++)
	{
		for (int x = 0; x < image.width()/2; x++)
		{
			for (int c = 0; c < 3; c++) {
				swap(image(x, y, 0, c), image(image.width()-x-1 , y , 0, c));
			}
		}
	}

}

void diagonalFlip(CImg<float>& image) {
	
	for (int x = 0; x < image.width(); x++)
	{
		for (int y = 0; y < image.height()/2; y++)
		{
			for (int c = 0; c < 3; c++)
			{
				swap(image(x, y, 0, c), image(image.width()-1-x,image.height()-1-y,0,c));
			}
		}
	}
}

void shrink(CImg<float> & image, CImg<float> & shrinked_image) {
	
	for (int x = 0; x < shrinked_image.width(); x++)
	{
		for (int y = 0; y < shrinked_image.height(); y++)
		{
			for (int c = 0; c < 3; c++)
			{

				shrinked_image(x, y, 0, c) = image(2*x,2*y,0,c);

			}
		}
	}

	shrinked_image.save("shrinked.bmp");
}





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

	if ((string)argv[2] == "--brightness")
	{
		cout << "Give level of brighting " << endl;
		cin >> modificator;
		basicoperations(modificator, image, operations[0]);
		
		
	}
	else if ((string)argv[2] == "--contrast")
	{
		cout << "Give level of contrast " << endl;
		cin >> modificator;
		basicoperations(modificator, image, operations[1]);
		
	}
	else if ((string)argv[2] == "--negative")
	{
		basicoperations(0, image, operations[2]);
		
	}
	else if ((string)argv[2] == "--vflip") {
		
		verticalFlip(image);
		
		
	}
	else if ((string)argv[2] == "--hflip")
	{
		horizontalFlip(image);
	}
	else if ((string)argv[2] == "--dflip") {
		diagonalFlip(image);
	}

	//nie działa xd
	else if ((string)argv[2] == "--shrink")
	{
		CImg<float> shrinked_image(image.width() / 2, image.height() / 2, 0, 3);
		shrink(image,shrinked_image);
	}
	else
	{
		cout << "Invalid operation\n If you need help, run program with --help parameter" << endl;
	}

	//TODO funkcja z podaniem nazwy pliku(?) 
	
	image.save("output.bmp");



	return 0;
}