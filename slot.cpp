#include "slot.h"

slot::slot()
{
	letter = ' ';
	display = SYMBOL;
}

slot::slot(char newLetter, displayState newDisplay)
{
	letter = newLetter;
	display = newDisplay;
}

char slot::getLetter() const { return letter; }
displayState slot::getDisplay() const { return display; }


/*slot slot::changeSlot(displayState newDisplay)
{
cout << "level 4.1" << endl;
slot newSlot = slot(letter, newDisplay);
return newSlot;
}
*/
void slot::changeSlot(displayState newDisplay)
{
	cout << "level 4.1" << endl;
	display = newDisplay;
}
