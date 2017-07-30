#pragma once
#include "stdafx.h"
class Window
{
public:
	//Returns a pointer the the _mainWindow
	static sf::RenderWindow& GetWindow();
private:
	//The window that the whole program uses to display to
	static sf::RenderWindow _mainWindow;
};