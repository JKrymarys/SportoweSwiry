
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include "CImg.h"
#include "IMAGE.h"

using namespace cimg_library;
using namespace std;




int main(int argc, char * argv[]) {

	float(*operations[3])(float, float) = { brightlut, contrastlut, negativelut };

	string operation_to_do;
	string path_to_file;
	float modificator;
	CImg <float> image;



	
	//CHECK THE ARGUMENTS
	if (argc == 2)
	{
		if ((string)argv[1] == "--help")
		{
			ifstream help_file;
			help_file.open("help.txt");
			string line;
			while (!help_file.eof())
			{
				getline(help_file, line);
				cout << line << endl;
			}
			help_file.close();
			return 0;
		}
		else
		{

			string name_without_noise;
			string name_with_noise;
			CImg<float> image_with_noise;
			CImg<float> image_without_noise;

			cout << "\n Give picture with and without noise" << endl;
			cin >> name_without_noise;
			cin >> name_with_noise;

			image_without_noise.load(name_without_noise.c_str());
			image_with_noise.load(name_with_noise.c_str());


			if ((string)argv[1] == "--mse")
			{
				Mean_square_error(image_without_noise, image_with_noise);

				return 0;
			}
			else if ((string)argv[1] == "--pmse") {
				Peak_mean_square_error(image_without_noise, image_with_noise);
				return 0;

			}
			else if ((string)argv[1] == "--snr")
			{
				Signal_to_noise_error(image_without_noise, image_with_noise);
					return 0;
			}
			else if((string)argv[1]=="--psnr")
			{
				Peak_signal_to_noise_error(image_without_noise,image_with_noise);
				return 0;
			}
			else if ((string)argv[1] == "--md")
			{
				Maximum_difference(image_without_noise,image_with_noise);
				return 0; 
			}
			else
			{
				cout << "Invalid operation\n If you need help, run program with --help parameter" << endl;
			}
		}
		
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

		SaveImage(shrink(image));
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