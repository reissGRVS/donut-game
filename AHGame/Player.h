#pragma once
#include "VisibleGameObject.h"


class Player:
	public VisibleGameObject
	
{
	
public:
	//Initialises the player
	Player();
	~Player();

	//Updates the player - handles movement, gravity, standard collision, and collision with special tiles (e.g. death, hunger, food, ladder, powerup)
	void Update(float elapsedTime);
	//Draws the players sprite to the window
	void Draw(sf::RenderWindow& rw);
	//Resets the player
	void Reset();
	//Gets the players X velocity
	float GetXVelocity() const;
	//Gets the players Y velocity
	float GetYVelocity() const;

private:
	//Sets up alias for sf::Vector2f as vec2f
	typedef sf::Vector2f vec2f;
	//Speed in the x direction
	float _xvelocity;  // -- left ++ right
	//Speed in y direction
	float _yvelocity;  // -- up ++ down
	//Acceleration of gravity
	float _gravity;
	//Max velocity for x direction
	float _maxVelocity;
	//Various timers
	float _time;
	float _lvltime;
	float _hungertime;
	//Animation state
	int _animation;
	//Counter for food collected during a level
	int _foodcount;
	//Whether the hunger timing should be ticking 
	bool _active;
	//Direction the player is going - used for displaying the correct texture during animation
	enum Direction { Left, Right };
	Direction _direction;

	//Gets tile number a coordinate is in
	int check(vec2f pos);
	//Checks if a position is on screen
	bool onscreen(vec2f pos);
	//Fetches the tile id for a passed tile number
	int fetch(int check);
	//Checks if a tile is solid
	bool coll(int check);
	//Checks if a tile is a powerup
	bool powerup(int check);
	//Checks if a tile is food
	bool food(int check);
	//Checks if a tile is a ladder
	bool ladder(int check);
	//Checks if a tile is a hunger inducing tile
	bool hunger(int check);
	//Checks if a tile is a finishing tile
	bool finish(int check);
	//Checks if a tile is deadly
	bool death(int check);
	
	//Stores how much hunger the player has left
	int _hunger;
	//The image for the players hunger bar
	sf::Texture hungertexture;
	sf::Sprite hungerbar;
	//An array of positions that can be used to calculate tiles the player sprite is on
	vec2f chkTile[11];
};