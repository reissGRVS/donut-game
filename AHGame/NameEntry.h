#pragma once
#include "stdafx.h"
#include "LevelCreator.h"
#include <Windows.h>
class NameEntry
{
public:
	//Initialises the NameEntry class
	static void Init();
	//Draws the NameEntry screen to the window
	static void Draw(sf::RenderWindow & rw);
	//Checks for keyboard input
	static void Update(sf::RenderWindow & rw);
	//Returns the string str
	static std::string GetName();
private:
	//Holds the current players name(also used whilst it is being typed)
	static std::string str;
	//Sprite(with texture) and text(with font) to be displayed
	static sf::Text text;
	static sf::Font font;
	static sf::Texture background;
	static sf::Sprite back;
};