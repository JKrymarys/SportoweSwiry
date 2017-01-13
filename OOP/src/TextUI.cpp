#include "TEXTUI.H"

using namespace std;


TextUI::TextUI() {}

void TextUI::printGrid(Grid * grid)
{
	cout << "\n" << endl;
	cout << "    1 2 3 4 5 6 7 8 9 10 " << endl;
	cout << "________________________" << endl;
	for (int y = 0; y < 10; ++y)
	{
		cout << (((y+1)!=10)? (y+1) : 0)<<"| ";

		for (int x = 0; x < 10; ++x)
		{

			if (!grid->isAvaliable(coords(x, y)) && !grid->wasShot(coords(x, y)))
				cout << " i";
			else if (!grid->isAvaliable(coords(x, y)) && grid->wasShot(coords(x, y)))
				cout << " X";
			else if (grid->isAvaliable(coords(x, y)) && grid->wasShot(coords(x, y)))
				cout << " *";
			else
				cout << " O";
		}
		cout <<endl;
	}
	cout << "\n" << endl;
}
void TextUI::PrintText(string string)
{
	cout << string << endl;
}

int TextUI::SelectShip()
{
	int ship_id;
	do
	{
		cout << "Choose ship:" << endl;
		
		if (cin >> ship_id)
			break;
		else
		{
			cout << "Please enter a valid ship id" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

	} while (ship_id > 3 || ship_id < 0);

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
		
		if (cin >> x >> y)
			break;
		else
		{
			cout << "Please enter a valid coords" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}


	}

	return coords(x - 1, y - 1);

}

coords TextUI::getCoords() {
	coords toreturn;

	cout << "Type coordinates x, y " << endl;
	cin >> toreturn.first >> toreturn.second;
	while (toreturn.first >  10 || toreturn.second > 10 || toreturn.first < 1 || toreturn.second< 1 ) // should be grid->height, grid ->length
	{
		cout << "Coordinates out of range, retype" << endl;
		
		if (cin >> toreturn.first >> toreturn.second)
			break;
		else
		{
			cout << "Please enter a valid coords" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

	}
	return coords(toreturn.first-1, toreturn.second-1);

}

bool TextUI::getBool()
{
	char input = NULL;
	do	{
		cout << "Please enter an anser (y/n)" << endl;
		if (cin >> input && (input == 'y' || input == 'n'))
			break;
		else
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

		}

	} while (!(input == 'y' || input == 'n'));

	//ej to jest piekne
	return (input == 'y') ? true : false;
}

void TextUI::AskToSave()
{
	cout << "Would you like to save the state of game and end it ? " << endl;
}