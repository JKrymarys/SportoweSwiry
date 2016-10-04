#include <iostream>
#include <cstdlib>
#include<string>
using namespace std;

int main( int argc, char * argv[] ){

if (argc < 2 || argc > 3)
{
	cout << "The number of arguments is not correct ";
	return 0;
}
string arg1(argv[1]);
if (argc == 2 && arg1 == "--help")
{
	cout << "There will be help"
		return 0;
}
if (argc == 3)
{
	string arg2(argv[2]);
	//image.open(arg1)
	//switch (arg2)
	//{
	//case "--brightness":
	//	break;
	//case "--constrast":
	//	break;
	//case "--neagtive":
	//	break;
	//}
}
system("pause");
return 0;
}