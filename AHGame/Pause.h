#pragma once
#include "stdafx.h"
#include "Button.h"
#include "Game.h"

class CPause
{
public:
	//Initialises the pause menu - screenshot of level is passed
	CPause(sf::Image image);
	//Draws the pause menu to the screen
	void Draw();
	//Checks for button presses
	void Update(sf::Vector2i vc, sf::Event e);
private:
	//Play and Hub buttons
	Button PlayB;
	Button HubB;
	//Sprites(with textures) to be displayed
	sf::Texture texture;
	sf::Sprite pausemenu;
	sf::Sprite back;
	sf::Texture background;
};