#include "Menu.hpp"

bool Menu::_enableMouse = 0;

//constructors/destructors---------------------------------

Menu::Menu(void) {}

Menu::~Menu(void) {}

//Member functions-----------------------------------------

bool Menu::getEnableMouse(void)
{
	return _enableMouse;
}

void Menu::setEnableMouse(bool n)
{
	_enableMouse = n;
}