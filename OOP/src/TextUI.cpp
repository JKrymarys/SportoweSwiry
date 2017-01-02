#include "TEXTUI.H"

using namespace std;

void TextUI::ShowGrid()
{
	for (int y = 0; y < 10; ++y)
	{
		for (int x = 0; x < 10; ++x)
		{
			cout << this->Hplayer.getGridFlag(coords(y,x));
		}
		cout << endl;
	}
}