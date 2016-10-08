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

		cout << endl << "LOOKUPTABLE TEST" << endl;

		for (int i = 0; i < ArrSize; i++)
		{
			cout << lut[i] << endl;
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
		image.save("output.bmp");
	}

	if ((string)argv[2] == "--contrast")
	{
		cout << "Give level of contrast " << endl;
		cin >> modificator;
		basicoperations(modificator, image, operations[1]);
		image.save("output.bmp");
	}

	if ((string)argv[2] == "--negative")
	{
		basicoperations(0, image, operations[2]);
		image.save("output.bmp");
	}


	return 0;
}