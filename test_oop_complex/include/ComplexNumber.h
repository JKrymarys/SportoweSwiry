#ifndef COMPLEXNUMBER_H_
#define COMPLEXNUMBER_H_


class ComplexNumber{
	private:
	double x;
	double y;
	public:
	ComplexNumber(double x_ = 0, double y_ = 0);
	~ComplexNumber() {}
	double abs();	
};

#endif