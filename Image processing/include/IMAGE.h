

#ifndef IMAGE_H_
#define IMAGE_H_


#include "CImg.h"

using namespace cimg_library;

// FUNCTION CREATING LOOKUPTABLE
int * lookuptable(float level, float(*operation)(float, float));
// FUNCTIONS FOR LOOKUPTABLE
float brightlut(float value, float level);
float contrastlut(float value, float level);
float negativelut(float value, float level = 0);
// FUNCTION USING LOOKUPTABLE
void basicoperations(float level, CImg<float> & image, float(*operation)(float, float));
// FLIPS
void verticalFlip(CImg<float> & image);
void horizontalFlip(CImg<float> & image);
void diagonalFlip(CImg<float>& image);
// SHRINK AND ENLARGE
void shrink(CImg<float> & image);
CImg<float> enlarge(CImg<float> & image);
// MEDIANFILTER AND MEDIANA
CImg<float> medianfilter(CImg<float> & image);
float mediana(CImg<float> & image, int x, int y, int c);
//GEOMETRICMEAN FILTER AND GEOMETRICMEAN
float geometricmean(CImg<float> & image, int x, int y, int c);
CImg<float> medianfilter(CImg<float> & image);
// SAVING IMAGE FUNCTION
void SaveImage(CImg<float> & image);

#endif // !IMAGE_H_

