// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once
//Height and width of screen when playing game
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
//Height and width of levels in tiles
#define MAP_WIDTH 128
#define MAP_HEIGHT 96
//Number of tiles in a level
#define TILE_COUNT 12288
//Tile ranges for different tile types
#define SOLID 64
#define AIR 92
#define FINISH 96
#define LADDER 102
#define HUNGER 103
#define DEATH 110
#define BOUNCE 112
#define FOOD 128 
//Players ID in the Game ObjectManager
#define PLAYER 5000 
#define NOLEVELS 13

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>



// TODO: reference additional headers your program requires here
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include <vector>
#include <map>
#include <iostream>
#include <cassert>
#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <array>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <cstdint>
#include "Window.h"

//Possible states that game can be in
enum GameState {
	Uninitialized, Paused,
	ShowingMenu, GettingName, EndOfLevel, Playing, Exiting, Hub, Tutorial, Highscore
};