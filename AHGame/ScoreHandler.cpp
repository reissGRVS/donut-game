#include "stdafx.h"
#include "ScoreHandler.h"

void ScoreHandler::Initialise(std::string playername)
{
	//Sets the currentPlayer name to the string passed
	currentPlayer.name = playername;
	//Initliases the ScoreHandler
	newPlayer = true;
	//Loads the score file
	Load();
};

void ScoreHandler::Save()
{
	//Sorts alphabetically based on player names using an insertion sort
	InsertionSort();
	//Loops through all players and saves them each to the highscores.txt file
	std::ofstream myfile;
	myfile.open("highscores.txt");
	for (int i = 0; i != players.size(); i++)
	{
		std::string line;
		//Constructs a line to save to the file
		//Puts the player name in line
		line = players[i].name + " ";
		//Adds all level scores of current player to line
		for (int j = 0; j != 12; j++)
		{
			line = line + std::to_string(players[i].levelscore[j]) + " ";
		}
		//Adds player total score to line
		line = line + std::to_string(players[i].totalscore) + "\n";
		//Outputs line to the file
		myfile << line;
	}		
	//Closes the file
	myfile.close();
};

void ScoreHandler::Load()
{
	//Instantiates input file stream, temporary scoreentry, and string line
	std::ifstream myfile("highscores.txt");
	ScoreEntry temp;
	std::string line;
	//Loops till end of file
	while (myfile.good())
	{
		//Gets line from file
		std::getline(myfile, line);
		//Checks line isnt empty
		if (line != "")
		{
			//Tokenises the current line
			std::istringstream iss(line);
			std::vector<std::string> tokens{ std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{} };
			//Puts each token in appropriate property of the temporary Score Entry
			temp.name = tokens[0];
			for (int i = 1; i != 13; i++)
			{
				temp.levelscore[i - 1] = std::atoi(tokens[i].c_str());
				temp.totalscore += temp.levelscore[i - 1];
			}
			temp.totalscore = std::atoi(tokens[13].c_str());

			//Checks to see if the current line is the current players record
			if (temp.name == currentPlayer.name)
			{
				//Sets currentPlayer record to the current temp record and sets newplayer to false to stop the creation of a new record for the current player
				currentPlayer = temp; newPlayer = false;
			}
			//Pushes the current temp ScoreEntry onto the players vector
			players.push_back(temp);
		}
	}
	//Closes the file
	myfile.close();

	//If the current players record was not found(aka is a new player)
	if (newPlayer)
	{
		//Adds the currentplayer scoreentry to the players vector
		players.push_back(currentPlayer);
	}
	//Gets the current players record position in the players vector
	GetPos();
};

//A level and score are passed when a level is completed to this function
void ScoreHandler::Update(int level, int score)
{
	level--;
	//Checks to see if the currentplayers previous score for the passed level is less than the score passed
	if (currentPlayer.levelscore[level] < score)
	{
		//Updates the currentplayer totalscore
		currentPlayer.totalscore = currentPlayer.totalscore - currentPlayer.levelscore[level] + score;
		//Updates the current player levelscore
		currentPlayer.levelscore[level] = score;
		//Repeats for the copy of currentPlayers record in the players vector
		players[playerpos].levelscore[level] = score;
		players[playerpos].totalscore = currentPlayer.totalscore;
		//Saves the highscore file
		Save();
	}
}
std::string ScoreHandler::GetTopNames()
{
	std::string temp;
	//Sorts the players vector in order of score(non-ascending)
	std::sort(players.begin(), players.end());
	//Loops until either 10 or number of players in highscore file
	for (int i = 1; i != 11 && (i <= players.size()); i++)
	{
		//Adds to temp string the position i players name and goes onto next line
		temp += players[players.size() - i].name + "\n";
	}
	//Sorts players vector back into alphabetical order based on names
	InsertionSort();
	//Returns the created string
	return temp;
}

std::string ScoreHandler::GetTopScores()
{
	
	std::string temp;
	//Sorts the players vector in order of score(non-ascending)
	std::sort(players.begin(), players.end());
	//Loops until either 10 or number of players in highscore file
	for (int i = 1; i != 11 && (i <= players.size()); i++)
	{
		//Adds to temp string the position i players totalscore and goes onto next line
		temp += std::to_string(players[players.size() - i].totalscore) + "\n";
	}
	//Sorts players vector back into alphabetical order based on names
	InsertionSort();
	//Returns the created string
	return temp;
}
//Returns whether the passed level has been completed - by checking to see if the currentplayer has a score for the level
bool ScoreHandler::LevelComplete(int level)
{	
	if (level == -1)
		return true;
	else
		return (currentPlayer.levelscore[level] != 0);
}

//Returns newPlayer 
bool ScoreHandler::IsNewPlayer()
{
	return newPlayer;
}


void ScoreHandler::InsertionSort()
{

	int j;
	ScoreEntry temp;
	//Loops through all players
	for (int i = 0; i < players.size(); i++) {
		//Sets j to i
		j = i;
		//Loops if j is greater than 0 and names of position j and j-1 are in incorrect order
		while (j > 0 && players[j].name < players[j - 1].name) {
			//Swaps j and j-1 position
			temp = players[j];
			players[j] = players[j - 1];
			players[j - 1] = temp;
			//Decreases j by 1
			j--;
		}
	}

	//Gets position of the current player in the player vector
	GetPos();
};

void ScoreHandler::GetPos()
{
	//Loops through all positions of players vector
	for (int i = 0; i < players.size(); i++)
	{
		//Checks if current position is the currentplayers record
		if (players[i].name == currentPlayer.name)
		{
			//Sets playerposition to current index and exits loop
			playerpos = i;
			return;
		}
	}
};


ScoreEntry ScoreHandler::currentPlayer;
int ScoreHandler::playerpos;
std::vector<ScoreEntry> ScoreHandler::players;
bool ScoreHandler::newPlayer;