#include "stdafx.h"
#include "LevelCreator.h"

void LevelCreator::Start()
{
	//Checks that the game hasnt already been initialised, if it has then returns to caller
	if (_state != Uninitialized)
		return;
	//Creates the window
	Window::GetWindow().create(sf::VideoMode(1280, SCREEN_HEIGHT, 32), "MMM FOOD!!! - LEVEL CREATION");
	//Initiliases the level
	Level::Init();
	//Draws the level to screen
	Level::Draw();
	//Sets state to Editing
	_state = Editing;
	//Starts the creation loop
	CreationLoop();

	//Closes the window when finished
	Window::GetWindow().close();
}

void LevelCreator::CreationLoop()
{
	//Setting up various text and image objects
	sf::Event currentEvent;
	int curTileID = 1;
	sf::Font font;
	font.loadFromFile("coolvetica.ttf");
	sf::Text tileInfo;
	sf::Text brushInfo;
	tileInfo.setPosition(sf::Vector2f(1050, 200));
	tileInfo.setString(" ");
	tileInfo.setFont(font);
	tileInfo.setColor(sf::Color::Black);
	brushInfo.setPosition(sf::Vector2f(1050, 400));
	brushInfo.setString("Brush Size: ");
	brushInfo.setFont(font);
	brushInfo.setColor(sf::Color::Black);
	sf::Sprite previewTile;
	previewTile.setPosition(sf::Vector2f(1050, 50));
	previewTile.setTexture(Level::GetTexture());
	previewTile.setTextureRect(sf::IntRect(0, 0, 8, 8));
	previewTile.setScale(sf::Vector2f(8, 8));
	sf::RectangleShape rectangle;
	rectangle.setFillColor(sf::Color(120, 120, 120, 200));
	rectangle.setSize(sf::Vector2f(256, SCREEN_HEIGHT));
	rectangle.setPosition(sf::Vector2f(1024, 0));
	

	//Loops until gamestate is exiting
	while (_state != Exiting)
	{
		//Handles running the correct code for the current state
		switch (_state)
		{
			case LevelCreator::Editing:
			{
				//Loops until state changes
				while (_state == Editing)
				{
					//Validates current tile id - changes if invalid
					if (curTileID < 1) { curTileID = 1; }
					//Validates brush size - changes if invalid
					if (brush < 1) { brush = 1; }
					//Polls window for event
					Window::GetWindow().pollEvent(currentEvent);
					//Update tile type to change to 
					tileInfo.setString("Tile ID: " + std::to_string(curTileID));
					brushInfo.setString("Brush Size: " + std::to_string(brush));
					//Handle clicking on tiles
					//Gets mouse position
					sf::Vector2i pos = sf::Mouse::getPosition(Window::GetWindow());
					
					//Checks to see if either mouse button has been pressed and if it is within the window
					if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Mouse::isButtonPressed(sf::Mouse::Right)) && pos.x < SCREEN_WIDTH && pos.y < SCREEN_HEIGHT && pos.x > 0 && pos.y > 0)
					{
						int tcurTileID;
						//Decides what tileID the current tiles should be set to- LeftClick chooses the selected tile - RightClick sets it to air
						if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
							tcurTileID = curTileID;
						else
							tcurTileID = AIR;

						//Loops through all tiles the current brush covers and sets them to tcurTileID(the current tile ID) if they are within the map
						for (int x = 0; x != brush; x++)
						{
							for (int y = 0; y != brush; y++)
							{
								//Calculates the tiles position in the level object manager
								int curTile = ((pos.x + 8) / 8) + (((pos.y + 2) / 8) * 128) + y + (x*MAP_WIDTH);
								//Changes the tile and redraws it if it is within the map
								if (curTile <= TILE_COUNT)
								{
									Level::GetObjectManager().Get(curTile)->Change(tcurTileID);
									Level::GetObjectManager().Get(curTile)->Draw(Window::GetWindow());
								}
							}
						}

					}
					//Updates the preview tile image to the correct tile image
					previewTile.setTextureRect(sf::IntRect((curTileID-1)*16, 0, 16, 16));
					//Draws everything to the window
					Window::GetWindow().clear(sf::Color(255, 255, 255));
					Level::Draw();
					Window::GetWindow().draw(tileInfo);
					Window::GetWindow().draw(brushInfo);
					Window::GetWindow().draw(rectangle);
					Window::GetWindow().draw(previewTile);
					Window::GetWindow().display();

					//Handles closed event and closes if true
					if (currentEvent.type == sf::Event::Closed) _state = Exiting;

					//Handles any keypress events
					if(currentEvent.type == sf::Event::KeyPressed)
					{
						switch (currentEvent.key.code)
						{
							//Changes state to exiting if escape is pressed
							case (sf::Keyboard::Escape): {_state = Exiting; break; }
							//Changes state to Saving if F2 is pressed
							case (sf::Keyboard::F2): {_state = Saving; break; }
							//Changes state to Loading if F1 is pressed
							case (sf::Keyboard::F1): {_state = Loading; break; }
							//Changes to the next tile type if D is pressed
							case (sf::Keyboard::Right): {curTileID += 1; break; }
							//Changes to the previous tile type if A is pressed
							case (sf::Keyboard::Left): {curTileID -= 1; break; }
							//Increase the tileID by 32 if W is pressed
							case (sf::Keyboard::Up): {curTileID += 32; break; }
							//Decrease the tileID by 32 if S is pressed
							case (sf::Keyboard::Down): {curTileID -= 32; break; }
							//Increase the brushsize by 1 if * is pressed
							case (sf::Keyboard::Multiply) : {brush += 1; break; }
							//Decrease the brushsize by 1 if / is pressed
							case (sf::Keyboard::Divide): {brush -= 1; break;}
						}
					}
				}

				break;
			}
			case LevelCreator::Saving:
			{
				//Saves the current level and changes state back to Editing
				Save();
				_state = Editing;
				break;
			}
			case LevelCreator::Loading:
			{
				//Loads a level and changes state back to Editing
				Load();
				_state = Editing;
				break;
			}
		}
	}
}

void LevelCreator::Save()
{
	//Gets input from console for the filename to save to
	std::cout << "Please enter the filename to save to" << std::endl;
	char * memblock;
	std::string filename;
	std::cin >> filename;
	//Declares an output filestream to the filename.bin specified
	std::ofstream ofile(filename +".bin", std::ios::binary);
	//Checks that file has been opened
	if (ofile.is_open())
	{
		//Creates a block of memory of 12288 bytes(char size)
		memblock = new char[12288];
		//Loops through all tiles and gets the tile IDS, putting them into the memory block
		for (int i = 0; i != 12288; i++)
		{
			memblock[i] = (char)Level::GetObjectManager().Get(i+1)->GetID();
		}
		//Writes the memory block to the file, closes the file and deletes the memory block
		ofile.seekp(0, std::ios::beg);
		ofile.write(memblock, 12288);
		ofile.close();
		delete[] memblock;
		//Outputs message to console
		std::cout << "File has been saved" << std::endl;
	}
	//Outputs message to console
	else std::cout << "Unable to open file";
}

void LevelCreator::Load()
{
	//Gets filename to load
	std::cout << "Please enter the file to load (type cancel to cancel loading)" << std::endl;
	std::string filename;
	std::cin >> filename;
	//Checks that filename isnt "cancel" - If true Loads the file using Level Load function
	if (filename != "cancel")
	{
		Level::Load(filename);
	}
}


int LevelCreator::brush = 2;
LevelCreator::State LevelCreator::_state = Uninitialized;