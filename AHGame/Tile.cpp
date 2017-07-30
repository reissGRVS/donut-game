#include "stdafx.h"
#include "Tile.h"
#include "Level.h"
#include <iomanip>
#include <locale>
#include <sstream>
#include <string>

//Initialises tile
Tile::Tile()
{
	//Sets tile to air
	id = 65;
	//Gets texture for all tiles
	GetSprite().setTexture(Level::GetTexture());
	//Sets the tile sprite to display the correct tile texture
	Change(id);
	//Sets to loaded
	Loaded();
}

Tile::~Tile()
{
}

void Tile::Change(int ida)
{	
	//Changes the tile id to the id passed
	Tile::id = ida;
	//Changes the texture of the tile sprite to the correct one(according to the tile ID)
	GetSprite().setTextureRect(sf::IntRect((id - 1) * 16, 0, 16, 16));
	//Sets the scale of the tile depending on ID
	if ( id < (AIR + 1) || (id > 96 && id < 101) || id == 102 || (id > 104 && id < 111))
		GetSprite().setScale(sf::Vector2f(.5, .5));
	else
		GetSprite().setScale(sf::Vector2f(1, 1));
}

void Tile::Draw(sf::RenderWindow & rw)
{
	//Draws the tile sprite
	VisibleGameObject::Draw(rw);
}

int Tile::GetID()
{
	//Returns the tile ID
	return id;
}
