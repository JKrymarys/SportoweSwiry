

#ifndef IMAGE_H_
#define IMAGE_H_


#include "CImg.h"

using namespace cimg_library;

const int num_of_layers = 3;
const int MAX_PIXEL_VALUE = 255;

// FUNCTION CREATING LOOKUPTABLE
int * lookuptable(float level, float(*operation)(float, float));
// FUNCTIONS FOR LOOKUPTABLE
float brightlut(float value, float level);
float contrastlut(float value, float level);
float negativelut(float value, float level = 0);
// FUNCTION USING LOOKUPTABLE
void basicoperations(float level, CImg<float> & image, float(*operation)(float, float));
void Comparisions();
// FLIPS
void verticalFlip(CImg<float> & image);
void horizontalFlip(CImg<float> & image);
void diagonalFlip(CImg<float>& image);
// SHRINK AND ENLARGE
CImg<float> shrink(CImg<float> & image);
CImg<float> enlarge(CImg<float> & image);
// MEDIANFILTER AND MEDIANA
CImg<float> * medianfilter(CImg<float> & image);
float mediana(CImg<float> & image, int x, int y, int c);
//GEOMETRICMEAN FILTER AND GEOMETRICMEAN
float geometricmean(CImg<float> & image, int x, int y, int c);
CImg<float> * geometricfilter(CImg<float> & image);
// SAVING IMAGE FUNCTION
void SaveImage(CImg<float> & image);
// ERRORS CALCULATIONS
void Mean_square_error(CImg<float> & image_without_noise, CImg<float> & image_with_noise);
void Peak_mean_square_error(CImg<float> & image_without_noise, CImg<float> & image_with_noise);
void Signal_to_noise_error(CImg<float> & image_without_noise, CImg<float> & image_with_noise);
void Peak_signal_to_noise_error(CImg<float> & image_without_noise, CImg<float> & image_with_noise);
void Maximum_difference(CImg<float> & image_without_noise,CImg<float> & image_with_noise);

double Find_maximum_value(CImg<float> & image_without_noise);

void Show_error_data(double clean_picture_data, double median_filter_data, double gmean_filter_data);



// TASK 2 FUNCTIONS

void histogram(CImg<float> & image);



#endif // !IMAGE_H_

