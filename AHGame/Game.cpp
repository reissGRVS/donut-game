#include "stdafx.h"
#include "Game.h"




void Game::Play(void)
{
	//Checks that game hasnt already been initialised - If it has, returns to caller
	if(_gameState != Uninitialized)
		return;

	//Creates/initialises an actual window in Window class
	Window::GetWindow().create(sf::VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,32),"MMM FOOD!!!", sf::Style::None);

	//Displays loading screen image to window
	ShowSplashScreen();

	//Initialise player, level tiles, and hub doors
	Level::Init();
	Player *player1 = new Player();
	player1->SetPosition((128), (720));
	_objectManager.Add(PLAYER, player1);
	for (int i = 0; i != 3; i++)
	{
		for (int j = 1; j != 5; j++)
		{

			int spacer;
			if (j < 3)
				spacer = -40;
			else
				spacer = 140;
			Door *door = new Door(175 * j + spacer, 570 - (180 * (i + 1) - 80), std::to_string(j + (4 * i)));
			_objectManager.Add(j + (4 * i), door);
		}
	}

	//Starts game loop - game loop only stops when game state is exiting
	while (!IsExiting())
	{
		GameLoop();
	}
	return;
}

//Returns bool based on whether the gamestate is exiting or not
bool Game::IsExiting()
{
	if(_gameState == Exiting) 
		return true;
	else 
		return false;
}

//Returns address for the objectManager instantiated in the game class
const ObjectManager& Game::GetObjectManager()
{
	return Game::_objectManager;
}

//Takes a Gamestate value to update the actual gamestate to
void Game::ChangeGameState(GameState g)
{
	_gameState = g;
}


void Game::GameLoop()
{
	//Defines event for window input
	sf::Event currentEvent;
	
	//Handles the gamestate and runs appropriate function depending on the gamestate
	switch(_gameState)
	{
		case ShowingMenu:
			{
				ShowMenu(currentEvent);
				break;
			}
		case Paused:
			{
				Pause(currentEvent);
				break;
			}
		case GettingName:
			{
				GetName(currentEvent);
				break;
			}
		
		case EndOfLevel:
			{
				ShowScore(currentEvent);
				break;
			}
		
		case Playing:
			{
				PlayGame(currentEvent);
				break;
			}
		case Highscore:
		{
			ShowHighScores(currentEvent);
			break;
		}
		case Hub:
			{
				//Loops through each door object, changes texture of door and ability to enter if unlocked by current player
				for (int i = 0; i != 3; i++)
				{
					for (int j = 1; j != 5; j++)
					{
						dynamic_cast<Door*>(_objectManager.Get(j + (i * 4)))->Activate(ScoreHandler::LevelComplete(j - 2 + (i * 4)));
					}
				}
				//Resets the players character
				dynamic_cast<Player*>(_objectManager.Get(PLAYER))->Reset();
				//Loads hub level
				Level::Load("hub");

				PlayHub(currentEvent);
				break;
			}
	}
};

void Game::ShowSplashScreen()
{
	//Instantiates splashscreen object
	SplashScreen _splashScreen;

	//Displays splash screen on the window
	_splashScreen.Show(Window::GetWindow());
	//Changes the game state to getting name
	_gameState = GettingName;
}

void Game::ShowHighScores(sf::Event currentEvent)
{
	HighscoreScreen HSS;
	//Keeps looping whilst gamestate is not changed
	while (_gameState == Highscore)
	{
		//Polls through all window events and handles the events accordingly
		while (Window::GetWindow().pollEvent(currentEvent))
		{
			//Updates and draws highscore screen
			Window::GetWindow().clear(sf::Color(255, 255, 255));
			HSS.Update(sf::Mouse::getPosition(Window::GetWindow()),currentEvent);
			HSS.Draw();
			Window::GetWindow().display();
			if (currentEvent.type == sf::Event::Closed) _gameState = Exiting;
		}
	}
}


void Game::PlayGame(sf::Event currentEvent)
{
	//Keeps looping whilst gamestate is not changed
	while (_gameState == Playing)
	{
		//Updates/draws player and draws level
		Window::GetWindow().clear(sf::Color(255, 255, 255));
		float timeDelta = _objectManager.UpdateClock();
		_objectManager.Get(PLAYER)->Update(timeDelta);
		Level::Draw();
		_objectManager.Get(PLAYER)->Draw(Window::GetWindow());
		Window::GetWindow().display();

		//Checks to see if level is hub and changes gamestate if true
		if (Level::IsHub())
			_gameState = Hub;

		//Checks for various events
		while (Window::GetWindow().pollEvent(currentEvent))
		{
			if (currentEvent.type == sf::Event::Closed) _gameState = Exiting;

			if (currentEvent.type == sf::Event::KeyPressed)
			{
				if (currentEvent.key.code == sf::Keyboard::F1) Level::Reset();
				if (currentEvent.key.code == sf::Keyboard::Escape) _gameState = Paused;
			}
		}

	}
}

void Game::PlayHub(sf::Event currentEvent)
{
	//Keeps looping whilst gamestate is not changed
	while (_gameState == Hub)
	{
		//Updates/draws player and draws level
		Window::GetWindow().pollEvent(currentEvent);
		Window::GetWindow().clear(sf::Color(255, 255, 255));
		float timeDelta = _objectManager.UpdateClock();
		_objectManager.Get(PLAYER)->Update(timeDelta);
		Level::Draw();
		_objectManager.DrawAll(Window::GetWindow());
		Window::GetWindow().display();

		//Checks that current level is hub, if it isnt, changes gamestate to playing
		if (!Level::IsHub())
			_gameState = Playing;

		//Polls through all window events and handles the events accordingly
		while (Window::GetWindow().pollEvent(currentEvent))
		{
			//Checks for various events
			if (currentEvent.type == sf::Event::Closed) _gameState = Exiting;

			if (currentEvent.type == sf::Event::KeyPressed)
			{
				if (currentEvent.key.code == sf::Keyboard::F1) Level::Reset();
				if (currentEvent.key.code == sf::Keyboard::Escape) _gameState = ShowingMenu;
				//Updates each door object when Enter/Return key is pressed
				if (currentEvent.key.code == sf::Keyboard::Return)
				{
					for (int i = 1; i != NOLEVELS; i++)
					{
						_objectManager.Get(i)->Update(0);
					}
				}
			}
		}
	}

}

//Sets score in game to a passed value
void Game::setScore(int score)
{
	RecentScore = score;
}


void Game::ShowMenu(sf::Event currentEvent)
{
	Menu menu;
	//Loops whilst gamestate isnt changed	
	while (_gameState == ShowingMenu)
	{
		//Polls through all events in the game window
		while (Window::GetWindow().pollEvent(currentEvent))
		{
			//Updates and draws menu to screen
			Window::GetWindow().clear(sf::Color(255, 255, 255));
			menu.Update(sf::Mouse::getPosition(Window::GetWindow()), currentEvent);
			menu.Draw();
			Window::GetWindow().display();
			//Checks for closed events and closes if found
			if (currentEvent.type == sf::Event::Closed) _gameState = Exiting;

		}
	}
}

void Game::GetName(sf::Event currentEvent)
{
	//Initialises NameEntry class
	NameEntry::Init();
	//Runs NameEntry update loop to get playername
	NameEntry::Update(Window::GetWindow());
	//Initialises ScoreHandler class by passing the inputted playername
	ScoreHandler::Initialise(NameEntry::GetName());
	//Changes gamestate to ShowingMenu
	_gameState = ShowingMenu;
}

void Game::ShowScore(sf::Event currentEvent)
{

	//Initialise End of level screen
	EndOfLvl EoL(Window::GetWindow().capture());
	EoL.SetScore(Game::RecentScore);
	sf::Texture texture;
	texture.update(Window::GetWindow());
	sf::Sprite background;
	background.setTexture(texture);

	//Loop until gamestate changes
	while (_gameState == EndOfLevel)
	{
			//Draws and updates the End of Level screen
			Window::GetWindow().clear(sf::Color(255, 255, 255));
			float timeDelta = _objectManager.UpdateClock();
			EoL.UpdateText(timeDelta);
			Window::GetWindow().draw(background);
			EoL.Draw();
			Window::GetWindow().display();

			//Polls through all events in the game window
			while (Window::GetWindow().pollEvent(currentEvent))
			{
				//Checks for button clicks
				EoL.Update(sf::Mouse::getPosition(Window::GetWindow()), currentEvent);
				//Checks for closed event and closes if true
				if (currentEvent.type == sf::Event::Closed) _gameState = Exiting;
			}
	}
}

void Game::Pause(sf::Event currentEvent)
{
	//Initialises the pause menu, passing an image of the current level 
	CPause cpause(Window::GetWindow().capture());
	//Loops until gamestate changes
	while (_gameState == Paused)
	{
		//Polls through all events in the game window
		while (Window::GetWindow().pollEvent(currentEvent))
		{
			//Draws/Updates the Pause menu screen
			Window::GetWindow().clear(sf::Color(255, 255, 255));
			cpause.Update(sf::Mouse::getPosition(Window::GetWindow()), currentEvent);
			cpause.Draw();
			Window::GetWindow().display();
			//Checks for closed event and closes if true
			if (currentEvent.type == sf::Event::Closed) _gameState = Exiting;
		}
	}
}

GameState Game::_gameState = Uninitialized;
ObjectManager Game::_objectManager;
int Game::RecentScore;