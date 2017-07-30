#include "stdafx.h"
#include "Level.h"

void Level::Init()
{
	//Loads the tile images
	tileMap.loadFromFile("tileMap.png");
	//Loads a font 
	bit.loadFromFile("8-bitp.ttf");
	backgrounds.setPosition(0, 0);
	//Adds 12288 tile objects to its objectmanager 
	for (int i = 0; i < 12288; ++i) 
	{
		auto *newTile = new Tile(); //Making a new tile using the constructor and is created dynamically using pointers
		_mapManager.Add(_mapManager.GetObjectCount() + 1, newTile); //Adds the tile to the Level classes object manager
		newTile->SetPosition(((i % 128) * 8), ((i / 128) * 8));  //Setting the position of the tile - "->" because its now a pointer due to dynamic creation
	}

}

void Level::Load(std::string filn)
{
	//Sets the filename to the string passed
	filename = filn;
	//Loads background image and sets to sprite
	background.loadFromFile(filn + ".png");
	backgrounds.setTexture(background);
	//Instantiate a memoryblock and input file stream for the filename
	char * rmemblock;
	std::ifstream ifile(filn+".bin", std::ios::binary);
	//Checks file is fine to read from (e.g. not end of file)
	if (ifile.is_open())
	{
		//Sets the memory block to be 12288 bytes(chars)
		rmemblock = new char[12288];
		//Goes to beginning of file and copies the first 12288 characters to the memory block
		ifile.seekg(0, std::ios::beg);
		ifile.read(rmemblock, 12288);
		//Outputs message to console
		std::cout << "Level loaded" << std::endl;
		//Loops through each position in the memory block
		for (int i = 0; i != 12288; i++)
		{
			//Casts the character (from current position in memoryblock) to an integer
			int tileid = (int)rmemblock[i];
			//Checks tileid is positive and makes positive if not 
			if (tileid < 0)
					tileid = -tileid;
			//Changes the i+1th tiles ID to the ID just read in and updates tile appropriately
			_mapManager.Get(i+1)->Change(tileid);
		}
		//Delets the memory block
		delete[] rmemblock;
	}
	//Outputs message to console
	else std::cout << "Unable to open file";
	
}

void Level::Finish(int score)
{
	//Passes level name as int and score to ScoreHandler to update
	ScoreHandler::Update(std::atoi(filename.c_str()), score);
	//Changes gamestate to end of level
	Game::ChangeGameState(EndOfLevel);
	//Sets score in Game class - so it can be displayed by the end of level screen
	Game::setScore(score);
}
void Level::Draw()
{
	//Draws background and level to window
	Window::GetWindow().draw(backgrounds);
	Level::_mapManager.DrawAll(Window::GetWindow());
}


void Level::Reset()
{
	//Reloads the current level
	Load(filename);
	//Resets the player
	dynamic_cast<Player*>(Game::GetObjectManager().Get(PLAYER))->Reset();
}

bool Level::IsHub()
{
	//Returns true if current level is hub
	return (filename == "hub");
}

sf::Texture& Level::GetTexture()
{
	//Returns pointer to the tile map image
	return tileMap;
}

sf::Font & Level::GetFont()
{
	//Returns pointer to Level font
	return bit;
}

const ObjectManager& Level::GetObjectManager()
{
	//Returns pointer to map manager(Levels object manager)
	return Level::_mapManager;
}

ObjectManager Level::_mapManager;
sf::Texture Level::tileMap;
sf::Font Level::bit;
sf::Texture Level::background;
sf::Sprite Level::backgrounds;
std::string Level::filename;