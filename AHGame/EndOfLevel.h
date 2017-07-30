#pragma once
#include "stdafx.h"
#include "Button.h"
#include "Game.h"

class EndOfLvl
{
public:
	//Initialises the end of level screen - screenshot of level is passed to it
	EndOfLvl(sf::Image image);
	//Draws the endoflevel screen
	void Draw();
	//Updates the tally up score text
	void UpdateText( float elapsedTime);
	//Checks for button clicks
	void Update(sf::Vector2i vc, sf::Event e);
	//Sets the score to be displayed
	void SetScore(int scor);
private:
	//Retry button
	Button RetryB;
	//Hub Button
	Button HubB;
	//Sprites(with textures) and text(with font) that will be displayed
	sf::Text text;
	sf::Font font;
	sf::Texture background;
	sf::Sprite menu;
	sf::Texture lvl;
	sf::Sprite back;
	std::string textdisplay;
	//The score that will be counted up to
	int score;
	//The counter that counts up to score
	int counter;
	//Time needed to wait before counter changes from 0
	float wait;
	//Timer to make sure counter doesnt update too quickly
	float timepassed;
};