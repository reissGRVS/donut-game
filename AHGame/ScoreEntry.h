#pragma once
#include "stdafx.h"
class ScoreEntry
{
public:
	//Constructor function - initliases all properties to 0 or ""
	ScoreEntry();
	//Stores the name of the player
	std::string name;
	//Stores the total score of all the levels a player has played
	int totalscore;
	//Stores a score for every level for a player
	int levelscore[12];
	//Redefines the < operator to compare totalscores when comparing objects of this class
	bool operator<(const ScoreEntry& other) const;
};

