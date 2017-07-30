#include "stdafx.h"
#include "ScoreEntry.h"

ScoreEntry::ScoreEntry()
{
	//Initialises all values
	totalscore = 0;
	for (int i = 0; i != 12; i++)
	{
		levelscore[i] = 0;
	}
	name = " ";
};



bool ScoreEntry::operator<(const ScoreEntry & other) const
{
	//Redefines the < operator to compare the totalscore property
	return totalscore < other.totalscore;
};