#pragma once
#include "stdafx.h"
#include "Button.h"
#include "Game.h"

class HighscoreScreen
{
public:
	//Initialises Highscore screen
	HighscoreScreen();
	//Draws highscore screen to window
	void Draw();
	//Checks for button presses
	void Update(sf::Vector2i vc, sf::Event e);
private:
	//Main menu button
	Button MainB;
	//Text(with font) and sprite(with texture) to be displayed
	sf::Text text;
	sf::Text stext;
	sf::Font font;
	sf::Texture background;
	sf::Sprite back;
};