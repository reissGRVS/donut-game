#include "stdafx.h"
#include "Door.h"
#include "Level.h"


Door::Door(int x, int y, std::string iname)
{
	//Initalises door
	//Sets the levelname to passed string
	levelname = iname;
	//Loads texture and sets up sprite
	Load("portalu.png");
	GetSprite().setScale(2, 2);
	GetSprite().setPosition(x, y);

	//Sets up the name text object to display
	name.setString(levelname);
	name.setFont(Level::GetFont());
	name.setCharacterSize(12);
	name.setColor(sf::Color::Black);
	name.setPosition(sf::Vector2f(x+16, y+20));
	
}


Door::~Door()
{
}

void Door::Draw(sf::RenderWindow & rw)
{
	//Draws the door sprite and the name text to the window
	VisibleGameObject::Draw(rw);
	rw.draw(name);
}

void Door::Update(float f)
{
	//Checks to see if the window is active and if the player sprite is intersecting with the door sprite
	if (active && GetBoundingRect().intersects(Game::GetObjectManager().Get(PLAYER)->GetBoundingRect()))
	{
		//Loads the level set in door levelname string
		Level::Load(levelname);
		//Resets the level class
		Level::Reset();
	}
}

void Door::Activate(bool a)
{
	//Sets if the door is active or not and loads a different sprite depending on active
	active = a;
	if (active) Load("portal.png");
	else Load("portalu.png");
}
