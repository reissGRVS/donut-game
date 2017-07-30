#pragma once
#include "VisibleGameObject.h"
class Door :
	public VisibleGameObject
{
public:
	//Initialises the door object
	Door(int x, int y, std::string name);
	~Door();
	//Draws the door sprite to window
	void Draw(sf::RenderWindow& rw);
	//Checks if player is trying to use door and if they can use door
	void Update(float f);
	//Sets active state of door to define whether the player can use door
	void Activate(bool a);
private:
	//The name of the level the door links to
	std::string levelname;
	//Text object that is displayed on the door
	sf::Text name;
	//Whether the door can be used or not
	bool active;

};

