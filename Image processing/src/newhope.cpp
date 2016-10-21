
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


	if (argc < 2 || argc > 3)
	{
		cout << "Invalid number of arguments, if you need help use --help argument";
		return 0;
	}

	//CHECK THE ARGUMENTS
	if (argc == 2)
	{
		if ((string)argv[1] == "--help")
		{
			ifstream help_file;
			help_file.open("help.txt");
			if (help_file.is_open())
			{

				string line;
				while (!help_file.eof())
				{
					getline(help_file, line);
					cout << line << endl;
				}
				help_file.close();
			}
			else
				cout << "Couldnt find help file";
			return 0;
		}
		else
		{

			string name_without_noise;
			string name_with_noise;
			CImg<float> image_with_noise;
			CImg<float> image_without_noise;

	


			if ((string)argv[1] == "--mse")
			{
				cout << "\n Give picture with and without noise" << endl;
				cin >> name_without_noise;
				cin >> name_with_noise;

				image_without_noise.load(name_without_noise.c_str());
				image_with_noise.load(name_with_noise.c_str());
				Mean_square_error(image_without_noise, image_with_noise);

				return 0;
			}
			else if ((string)argv[1] == "--pmse") {
				cout << "\n Give picture with and without noise" << endl;
				cin >> name_without_noise;
				cin >> name_with_noise;

				image_without_noise.load(name_without_noise.c_str());
				image_with_noise.load(name_with_noise.c_str());
				Peak_mean_square_error(image_without_noise, image_with_noise);
				return 0;

			}
			else if ((string)argv[1] == "--snr")
			{
				cout << "\n Give picture with and without noise" << endl;
				cin >> name_without_noise;
				cin >> name_with_noise;

				image_without_noise.load(name_without_noise.c_str());
				image_with_noise.load(name_with_noise.c_str());
				Signal_to_noise_error(image_without_noise, image_with_noise);
					return 0;
			}
			else if((string)argv[1]=="--psnr")
			{
				cout << "\n Give picture with and without noise" << endl;
				cin >> name_without_noise;
				cin >> name_with_noise;

				image_without_noise.load(name_without_noise.c_str());
				image_with_noise.load(name_with_noise.c_str());
				Peak_signal_to_noise_error(image_without_noise,image_with_noise);
				return 0;
			}
			else if ((string)argv[1] == "--md")
			{
				cout << "\n Give picture with and without noise" << endl;
				cin >> name_without_noise;
				cin >> name_with_noise;

				image_without_noise.load(name_without_noise.c_str());
				image_with_noise.load(name_with_noise.c_str());
				Maximum_difference(image_without_noise,image_with_noise);
				return 0; 
			}
			else
			{
				cout << "Invalid operation\n If you need help, run program with --help parameter" << endl;
				return 0;
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
		CImg<float> * filterimage = medianfilter(image);
		SaveImage(*filterimage);
		delete filterimage;
	}
	else if((string)argv[2] == "--gmean")
	{
		CImg<float> * filterimage = geometricfilter(image);
		SaveImage(*filterimage);
		delete filterimage;
	}


	//IN CASE OF INPROPIATE PARAMETER
	else
	{
		cout << "Invalid operation\n If you need help, run program with --help parameter" << endl;
	}




	return 0;
}