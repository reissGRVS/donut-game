#pragma once
#include "stdafx.h"
#include "ObjectManager.h"
#include "VisibleGameObject.h"
#include "Player.h"
#include "Tile.h"
#include "Game.h"
#include "LevelCreator.h"
#include "stdafx.h"
#include "ScoreHandler.h"

class Level
{
public:
	//Initialise the level class
	static void Init();
	//Loads a level data file and sets as current level
	static void Load(std::string filen);
	//Handles the completion of a level
	static void Finish(int score);
	//Draws all the levels tiles to the window
	static void Draw();
	//Resets the level to its starting state
	static void Reset();
	//Returns whether the current level is the hub level
	static bool IsHub();
	//Returns a pointer to tilemap texture
	static sf::Texture& GetTexture();
	//Returns pointer to font used by doors
	static sf::Font& GetFont();
	//Returns pointer to the object manager that stores all of a levels tiles
	const static ObjectManager& GetObjectManager();
	
private:
	//Texture used by all tiles
	static sf::Texture tileMap;
	//Font used by all doors
	static sf::Font bit;
	//Level background image
	static sf::Sprite backgrounds;
	static sf::Texture background;
	//Object manager that stores all of the current levels tiles
	static ObjectManager _mapManager;
	//The filename of the current loaded level
	static std::string filename;
};