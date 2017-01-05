// Exceptions.cpp : Defines the entry point for the console application.
//

#include<stdexcept>
#include<iostream>
#include<string>

using namespace std;

class Sales
{
public:
	enum {MONTHS = 12};
	class bad_index : public std::logic_error
	{
	private:
		int bi;
	public:
		explicit bad_index(int ix, const std::string & s = "Index error in Sales object \n");
		int bi_val() const { return bi; }
		virtual ~bad_index() {};
	};
	explicit Sales(int yy);
	Sales(int yy, const double * gr, int n);
	virtual ~Sales() {}
	int Year() const { return year; }
	virtual double operator[](int i) const;
	virtual double & operator[](int i);
private:
	double gross[MONTHS];
	int year;
};


Sales::bad_index::bad_index(int ix, const std::string & s) :std::logic_error(s), bi(ix) {

}

Sales::Sales(int yy) {
	year = yy;
	for (int i = 0; i < MONTHS; i++)
		gross[i] = 0;
}

Sales::Sales(int yy, const double  * gr, int n)
{
	year = yy;
	int lim = (n < MONTHS) ? n : MONTHS;
	int i;
	for (i = 0; i < n; ++i)
		gross[i] = gr[i];
	for( ; i < MONTHS; ++i)
		gross[i] = 0;
}

double Sales::operator[](int i) const{
	if (i<0 || i > MONTHS)
		throw bad_index(i);
	return gross[i];
}

double & Sales::operator[](int i) {
	if (i<0 || i > MONTHS)
		throw bad_index(i);
	return gross[i];
}


class LabeledSales : public Sales {
public:
	class labeled_bad_index : public Sales::bad_index
	{
	private:
		std::string bad_label;
	public:
		labeled_bad_index(const std::string &, int bi, const std::string & s = "Index error in LabeledSales object \n");
		std::string label_value() const { return bad_label; }
		virtual ~labeled_bad_index() {}
	};
	explicit LabeledSales(const std::string & lb = "none", int yy = 0);
	LabeledSales(const std::string & lb, int yy, double * gr, int n);
	virtual ~LabeledSales() {}
	const std::string & Label() const { return label; }
	virtual double operator[](int i) const;
	virtual double & operator[](int i);
private:
	std::string label;
};


LabeledSales::labeled_bad_index::labeled_bad_index(const std::string & lb, int bi, const std:: string & s)
	: bad_index(bi, s), bad_label(lb) {}


LabeledSales::LabeledSales(const std::string & lb, int yy) 
	: Sales(yy), label(lb) {}

LabeledSales::LabeledSales(const std::string & lb, int yy, double * gr, int n)
	: Sales(yy, gr, n), label(lb) {}

double LabeledSales::operator[](int i) const
{
	if (i < 0 || i > MONTHS)
		throw labeled_bad_index(Label(), i);
	return Sales::operator[](i);
}

double & LabeledSales::operator[](int i)
{
	if (i < 0 || i > MONTHS)
		throw labeled_bad_index(Label(), i);
	return Sales::operator[](i);
}



int main()
{
	Sales S2015(2015);
	try
	{
		S2015[13];
	}
	catch (LabeledSales::labeled_bad_index & bad)
	{
		cout << bad.what();
		cout << bad.label_value();
		cout << bad.bi_val();
	}
	catch (Sales::bad_index & bad)
	{
		cout << bad.what();
		cout << bad.bi_val();
	}
	LabeledSales LS2013("Label", 2013);
	try
	{
		LS2013[-1];
	}
	catch (LabeledSales::labeled_bad_index & bad)
	{
		cout << bad.what();
		cout << bad.label_value();
		cout << bad.bi_val();
	}
	catch (Sales::bad_index & bad)
	{
		cout << bad.what();
		cout << bad.bi_val();
	}
	return 0;
}

