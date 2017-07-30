#pragma once
#include "stdafx.h"
#include "ObjectManager.h"
#include "VisibleGameObject.h"
#include "Tile.h"
#include "Level.h"


class LevelCreator
{
public:
	//The starting function for the level creator - Initialises anything necessary
	static void Start();
	//Creation loop handles the switching of gamestates and updating and drawing in the main state (editing)
	static void CreationLoop();
	//Saves the current level data to a file (filename is input in console)
	static void Save();
	//Loads a level data file from a file (filename is input in console)
	static void Load();
	
private:
	//Enumarator of possible states
	enum State {
		Uninitialized, Editing,
		Loading, Saving, Exiting
	};
	//Current state of level creator
	static State _state;
	//Brush size
	static int brush;
};
