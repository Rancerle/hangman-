#pragma once
#include <iostream>
#include <string.h>
#include "displayState.h"
using namespace std;

class slot
{
public:
	slot();
	slot(char newLetter, displayState newDisplay);

	char getLetter() const;
	displayState getDisplay() const;

	void changeSlot(displayState newDisplay);

private:
	char letter;
	displayState display;
};
