#include "stdafx.h"
#include <iostream>
#include <string>
#include "IMAGE.h"

using namespace cimg_library;
using namespace std;

const int ArrSize = 255;



int main(int argc, char * argv[]) {

	float(*operations[3])(float, float) = { brightlut, contrastlut, negativelut };

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
	else if((string)argv[2] == "--gmean")
	{
		SaveImage(geometricfilter(image));
	}

	//IN CASE OF INPROPIATE PARAMETER
	else
	{
		cout << "Invalid operation\n If you need help, run program with --help parameter" << endl;
	}




	return 0;
}