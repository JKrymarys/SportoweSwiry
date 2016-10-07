

#include "stdafx.h"
#include <iostream>
#include <string>
#include "CImg.h"

using namespace cimg_library;
using namespace std;



//declarations

bool Check_boundary(CImg<float> & image, int & x, int & y, int & c, float & level) {

	if (image(x, y, 0, c) + level < 0) { image(x, y, 0, c) = 0;  return true; }
	else if (image(x, y, 0, c) + level > 255) { image(x, y, 0, c) = 255; return true; }
	else { return false; }

}


void brightness(float level, CImg <float> & image) {


	for (int x = 0; x < image.width(); x++)
	{
		for (int y = 0; y < image.height(); y++)
		{
			for (int c = 0; c < 3; c++)
			{
				if (!Check_boundary(image, x, y, c, level))
				{
					image(x, y, 0, c) += level;
				}

			}


		}
	}

}



int main(int argc, char * argv[]) {

	cout << "Hello in our program \n <if you need help, plese use -help >" << endl;
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

	if ( (string)argv[2] == "--brightness")
	{
		cout << "Give level of brighting " << endl;
		cin >> modificator;
		brightness(modificator, image);
		image.save("output.bmp");
	}




	


	return 0;
}