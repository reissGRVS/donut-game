#pragma once
#include "stdafx.h"
#include "VisibleGameObject.h"

class Button:
	public VisibleGameObject
{
public:
	//Constructors to initialise
	Button();Button(GameState a, sf::Vector2f p, std::string t);
	//Changes position, texture, action of button
	void ChangePos(sf::Vector2f p);
	void ChangeTexture(std::string t);
	void ChangeAction(GameState a);
	//Checks for button being clicked
	GameState Update(sf::Vector2i vc, sf::Event e);
	//Draws button 
	void Draw(sf::RenderWindow & rw);
private:
	//Stores the gamestate the button causes when clicked
	GameState action;
};