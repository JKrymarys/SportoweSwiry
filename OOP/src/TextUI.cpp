#include "TEXTUI.H"
#
using namespace std;


TextUI::TextUI()
{

}

void TextUI::printGrid(Grid * grid)
{
	for (int y = 0; y < 10; ++y)
	{
		for (int x = 0; x < 10; ++x)
		{
			cout << grid->isAvaliable(coords(x,y));
		}
		cout << endl;
	}
}
void TextUI::PrintText(string string)
{
	cout << string << endl;
}

int TextUI::SelectShip()
{
	int ship_id = 1;
	cout << "Choose ship:" << endl;
	
	/*while (ship_id != 1 || ship_id != 2 || ship_id != 3)
	{
		cin >> ship_id;
	}*/

	cout << "You have chosen ship: " << ship_id << endl;
	return ship_id;
}

coords TextUI::getTargetLocation() {

	int x, y;
	cout << "Target Location: " << endl;
	cout << "Type coordinates x,y" << endl;
	cin >> x >> y;
	while (x > 10 || y > 10 || x < 1 || y < 1) // should be grid->height, grid ->length
	{
		cout << "Coordinates out of range, retype" << endl;
		cin >> x >> y;
	}

	return coords(x, y);

}

coords TextUI::getCoords() {
	coords toreturn;

	cout << "Type coordinates x, y " << endl;
	cin >> toreturn.first >> toreturn.second;
	while (toreturn.first >  10 || toreturn.second > 10 || toreturn.first < 1 || toreturn.second< 1 ) // should be grid->height, grid ->length
	{
		cout << "Coordinates out of range, retype" << endl;
		cin >> toreturn.first >> toreturn.second;
	}
	return coords(toreturn.first-1, toreturn.second-1);

}