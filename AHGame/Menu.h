#pragma once
#include "stdafx.h"
#include "Button.h"
#include "Game.h"

class Menu
{
public:
	//Initialises main menu
	Menu();
	//Draws main menu screen to window
	void Draw();
	//Checks for button presses
	void Update(sf::Vector2i vc, sf::Event ewwww);
private:
	//Play, Highscore and Exit buttons
	Button PlayB;
	Button HighB;
	Button ExitB;
	
	//Sprite(with texture) to be displayed
	sf::Texture background;
	sf::Sprite sprite;

};