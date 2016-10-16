#include "ComplexNumber.h"
#include <cmath>

ComplexNumber::ComplexNumber(double x_, double y_){
	x = x_;
	y = y_;
}
double ComplexNumber::abs(){
	return sqrt(x*x+y*y);
}