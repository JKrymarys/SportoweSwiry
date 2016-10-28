
#include <iostream>
#include <string>
#include <cstdlib>
#include <regex>
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
	regex pattern_comparisionts("(?:--)(mse|pmse|snr|psnr|md)");
	regex pattern_basic_operations("(?:--)(brightness|contrast|negative|vflip|hflip|dflip|shrink|enlarge)");
	regex pattern_histograms("(?:--)(--histogram)");
	CImg <float> image;

//nazwa.exe lena.bmp --contrast 30
//nazwa.exe --md lena.bmp lena_noise.bmp
	
	if (argc < 2 || argc > 5)
	{
		cout << "Invalid number of arguments, if you need help use --help argument";
		return 0;
	}

	//CHECK THE ARGUMENTS

#pragma region HELP
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

		}

#pragma endregion
#pragma region TASK_1

	else if (regex_search(argv[1], pattern_comparisionts)) //inf regex match go into coparisions part of main 
	{

		string name_without_noise;
		string name_with_noise;
		CImg<float> image_with_noise;
		CImg<float> image_without_noise;


		name_with_noise = argv[2];
		name_without_noise = argv[3];

		if ((string)argv[1] == "--mse")
		{

			image_without_noise.load(name_without_noise.c_str());
			image_with_noise.load(name_with_noise.c_str());
			Mean_square_error(image_without_noise, image_with_noise);

			return 0;
		}
		else if ((string)argv[1] == "--pmse") {


			image_without_noise.load(name_without_noise.c_str());
			image_with_noise.load(name_with_noise.c_str());
			Peak_mean_square_error(image_without_noise, image_with_noise);
			return 0;

		}
		else if ((string)argv[1] == "--snr")
		{

			image_without_noise.load(name_without_noise.c_str());
			image_with_noise.load(name_with_noise.c_str());
			Signal_to_noise_error(image_without_noise, image_with_noise);
			return 0;
		}
		else if ((string)argv[1] == "--psnr")
		{

			image_without_noise.load(name_without_noise.c_str());
			image_with_noise.load(name_with_noise.c_str());
			Peak_signal_to_noise_error(image_without_noise, image_with_noise);
			return 0;
		}
		else if ((string)argv[1] == "--md")
		{

			image_without_noise.load(name_without_noise.c_str());
			image_with_noise.load(name_with_noise.c_str());
			Maximum_difference(image_without_noise, image_with_noise);
			return 0;
		}
		else
		{
			cout << "(comparisions)Invalid operation\n If you need help, run program with --help parameter" << endl;
			return 0;
		}


		cout << "(test regex2) " << regex_search(argv[1], pattern_basic_operations) << endl;
	}
	else if (regex_search(argv[1], pattern_basic_operations))
	{

		//load image 
		image.load(argv[2]);
		//operation
		operation_to_do = argv[1];
	
		// CHOISE OF THE OPERATION

		//OPERATIONS PERFORMED ON THE ORIGINAL IMAGE
		if ((string)operation_to_do == "--brightness")
		{
			modificator = stod(argv[3]);
			basicoperations(modificator, image, operations[0]);
			SaveImage(image);

		}
		else if ((string)operation_to_do == "--contrast")
		{
			modificator = stof(argv[3]);
			basicoperations(modificator, image, operations[1]);
			SaveImage(image);
		}
		else if ((string)operation_to_do == "--negative")
		{
			modificator = stod(argv[3]);
			basicoperations(0, image, operations[2]);
			SaveImage(image);
		}
		else if ((string)operation_to_do == "--vflip") {

			verticalFlip(image);
			SaveImage(image);
		}
		else if ((string)operation_to_do == "--hflip")
		{
			horizontalFlip(image);
			SaveImage(image);
		}
		else if ((string)operation_to_do == "--dflip") {
			diagonalFlip(image);
			SaveImage(image);
		}

		//OPERATIONS PERFORMED ON THE COPY 
		else if ((string)operation_to_do == "--shrink")
		{
			SaveImage(shrink(image));
		}
		else if ((string)operation_to_do == "--enlarge")
		{
			SaveImage(enlarge(image));
		}
		else if ((string)operation_to_do == "--median")
		{
			CImg<float> * filterimage = medianfilter(image);
			SaveImage(*filterimage);
			delete filterimage;
		}
		else if ((string)operation_to_do == "--gmean")
		{
			CImg<float> * filterimage = geometricfilter(image);
			SaveImage(*filterimage);
			delete filterimage;
		}

		else if (regex_search(argv[1],pattern_histograms)) {
			
	/*		CImg<float> image;
			image.load(argv[2]);

			if ((string)argv[1] == "--histogram")
			{
				
				histogram(image);


				return 0;
			}
*/
	}
	}

	else { cout << "Error" << endl;  return 0; }
	

#pragma endregion

	return 0;
}