#pragma once
#include "stdafx.h"
#include "ScoreEntry.h"
class ScoreHandler
{
public:
	//Initialises
	static void Initialise(std::string playername);
	//Saves all player data to a file
	static void Save();
	//Loads all player data from a file
	static void Load();
	//Updates the player data
	static void Update(int level, int score);
	//Returns the top 10 highest scores as a string
		//NAMES
		static std::string GetTopNames();
		//SCORES
		static std::string GetTopScores();
	//Returns whether or not the current player has completed a level
	static bool LevelComplete(int level);
	//Returns whether the player has launched the game before
	static bool IsNewPlayer();
private:
	//Stores the position of the current player in the players vector
	static int playerpos;
	//Stores all information on the current player
	static ScoreEntry currentPlayer;
	//Stores all information on all players
	static std::vector<ScoreEntry> players;
	//Whether or not the player has launched the game before
	static bool newPlayer;
	//Sorts players vector alphabetically by name
	static void InsertionSort();
	//Gets the position of the current player in the players vector
	static void GetPos();
};
