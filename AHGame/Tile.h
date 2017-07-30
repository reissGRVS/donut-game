#pragma once
#include "VisibleGameObject.h"
class Tile:
	public VisibleGameObject
{
public:
	//Initialises tile
	Tile();
	~Tile();

	//Changes the id and texture of a tile
	void Change(int ida);
	//Draws tile to window
	void Draw(sf::RenderWindow& rw);
	//Returns a tiles id
	int GetID();

private:
	//The id of a tile defines its type and texture
	int id;
};