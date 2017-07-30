#include "Window.h"
#include "stdafx.h"

//Returns a pointer to the classes window
sf::RenderWindow& Window::GetWindow()
{
	return Window::_mainWindow;
}

sf::RenderWindow Window::_mainWindow;