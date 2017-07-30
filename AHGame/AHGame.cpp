// AHGame.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Game.h"
#include "LevelCreator.h"
#include "Button.h"
#include <windows.h>

int main()
{
	
	//Gets user input
	int choice;
	std::cin >> choice;
	//If the input is not 0 starts levelcreator, if input is 0 then game starts
	if(choice)
		LevelCreator::Start();
	else
		Game::Play();

	return 0;
}