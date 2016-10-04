#include <iostream>
#include <cstdlib>
#include<string>
using namespace std;

int main( int argc, char * argv[] ){

string arg1(argv[1]);
if(arg1 == "-help")
	cout << "Prosze";
if((argc == 2))
{
	cout<<"Pomoc, tepy chuju"<<endl;
}
cout << "dupa" << argv[1] << "dupa";
system("pause");
return 0;
}