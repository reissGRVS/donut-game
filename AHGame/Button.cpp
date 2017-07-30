#include "stdafx.h"
#include "Button.h"


Button::Button(GameState a, sf::Vector2f p, std::string t)
{
	//Loads a texture and applies it to the button sprite
	Load(t);
	//Sets a button action - what gamestate to change to when pressed
	action = a;
	//Sets origin and position of button sprite
	GetSprite().setOrigin(144, 36);
	SetPosition(p.x+144, p.y+36);
}

//Same as above but defaults to a play button if parameters arent passed
Button::Button()
{
	Load("playbutton.png");
	action = Playing;
	GetSprite().setOrigin(144, 36);
	SetPosition(0, 0);
}
//Changes position of the button sprite
void Button::ChangePos(sf::Vector2f p)
{
	SetPosition(p.x+144, p.y+36);
}

//Changes the texture of the button sprite
void Button::ChangeTexture(std::string t)
{
	Load(t);
}

//Changes the action of the button
void Button::ChangeAction(GameState a)
{
	action = a;
}


GameState Button::Update( sf::Vector2i vc, sf::Event e)
{
	//Checks if the position passed is contained within the button
	if (GetBoundingRect().contains(vc.x, vc.y))
	{
		//Scales up the button slightly
		GetSprite().setScale(1.1, 1.1);
		//Checks if event passed is a mouse button press - if true returns the buttons action
		if(e.type == sf::Event::MouseButtonPressed) return (action);
	}
	else
	{
		//Scales the button to its standard scale
		GetSprite().setScale(1, 1);
	}

	//Returns nothing
	return Uninitialized;
}

void Button::Draw(sf::RenderWindow & rw)
{
	//Draws the button sprite to screen
	VisibleGameObject::Draw(rw);
}
