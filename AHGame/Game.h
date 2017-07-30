#pragma once
#include "stdafx.h"
#include "ObjectManager.h"
#include "VisibleGameObject.h"
#include "Player.h"
#include "Tile.h"
#include "Door.h"
#include "Level.h"
#include "SplashScreen.h"
#include "ScoreHandler.h"
#include "NameEntry.h"
#include "Menu.h"
#include "Pause.h"
#include "EndOfLevel.h"
#include "Highscore.h"

class Game
{
public:
	//The initial function to be called when starting the game
	static void Play();
	//Fetches pointer to the games object manager
	const static ObjectManager& GetObjectManager();
	//Changes the state of the game
	static void ChangeGameState(GameState g);
	//Sets the score property of the Game Class to a value passed
	static void setScore(int score);
private:
	//Checks if game state is exiting
	static bool IsExiting();
	//The game loop - handles switching between gamestates
	static void GameLoop();
	//Displays splash screen image
	static void ShowSplashScreen();
	//Displays and updates the highscore screen
	static void ShowHighScores(sf::Event currentEvent);
	//Displays and updates the game during play levels
	static void PlayGame(sf::Event currentEvent);
	//Displays and updates the main menu 
	static void ShowMenu(sf::Event currentEvent);
	//Displays and updates the name entry screen
	static void GetName(sf::Event currentEvent);
	//Displays and updates the end of level screen
	static void ShowScore(sf::Event currentEvent);
	//Displays and updates the pause menu
	static void Pause(sf::Event currentEvent);
	//Displays and updates the game when in the hub zone
	static void PlayHub(sf::Event currentEvent);
	//Score property used to store the most recent level score
	static int RecentScore;
	//GameState enumarator which holds the current gamestate
	static GameState _gameState;
	//Object manager that contains all of the games visiblegameobjects. This includes: player, doors
	static ObjectManager _objectManager;

};
