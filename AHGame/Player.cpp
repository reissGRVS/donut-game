#pragma once
#include "StdAfx.h"
#include "Player.h"
#include "Game.h"

//Initialises player
Player::Player() :
	_xvelocity(0),
	_yvelocity(0),
	_maxVelocity(300.0f),
	_animation(0),
	_direction(Right),
	_time(0),
	_gravity(0),
	_hunger(500),
	_active(false)
{
	Load("LCharSprite.png");
	hungertexture.loadFromFile("hungerbar.png");
	hungerbar.setPosition((720), (740));
	hungerbar.setTexture(hungertexture);
}

Player::~Player()
{
}

void Player::Draw(sf::RenderWindow & rw)
{
	//Draws the player sprite
	VisibleGameObject::Draw(rw);
	//Draws the hunger bar if the level isnt the hub
	if(!Level::IsHub())
		Window::GetWindow().draw(hungerbar);
}

void Player::Reset()
{
	//Resets player position, hunger, and active state
	SetPosition(128, 700);
	_hunger = 500;
	_active = 0;
}

float Player::GetXVelocity() const
{
	return _xvelocity;
}

float Player::GetYVelocity() const
{
	return _yvelocity;
}

int Player::check(vec2f pos)
{
	//Validates that position passed is on screen
	if (onscreen(pos)) 
	{
		//Returns tile number that top left corner of player is in
		return (((int)pos.x) / 8) + ((((int)pos.y) / 8) * 128 + 1);
	}
	else
		return 0;
}

bool Player::onscreen(vec2f pos)
{
	//Returns whether the position passed is within the window
	return !(pos.x < (0) || pos.x > SCREEN_WIDTH || pos.y < (0) || pos.y > SCREEN_HEIGHT);
}

int Player::fetch(int check)
{
	//Validates that value passed is a tile number
	if (check == 0)
		return 0;
	else
		//Returns the ID of the tile in position check
		return (Level::GetObjectManager().Get(check)->GetID());
		
}

bool Player::coll(int check)
{
	//Returns true if current tile is within the SOLID range of tiles
	if (check == 0)
		return 0;
	else
		return (fetch(check) <= SOLID);
}

bool Player::powerup(int check)
{
	//Returns true if current tile is within the BOUNCE range of tiles
	if (fetch(check) > DEATH && fetch(check) <= BOUNCE)
	{
		//Changes the tile to an AIR tile
		Level::GetObjectManager().Get(check)->Change(AIR);
		return (true);
	}
	else
	{
		return (false);
	}
}

bool Player::food(int check)
{
	//Returns true if current tile is within the FOOD range of tiles
	if (fetch(check) > BOUNCE && fetch(check) <= FOOD)
	{
		//Changes the tile to an AIR tile
		Level::GetObjectManager().Get(check)->Change(AIR);
		//Increases foodcount
		_foodcount++;
		return (true);
	}
	else
	{
		return (false);
	}
}
bool Player::ladder(int check)
{
	//Returns true if current tile is within the LADDER range of tiles
	if (fetch(check) > FINISH && fetch(check) <= LADDER)
	{
		return (true);
	}
	else
	{
		return (false);
	}
}
bool Player::hunger(int check)
{
	//Returns true if current tile is within the HUNGER range of tiles
	if (fetch(check) > LADDER && fetch(check) <= HUNGER)
	{
		//Changes current tile to an AIR tile
		Level::GetObjectManager().Get(check)->Change(AIR);
		return (true);
	}
	else
	{
		return (false);
	}
}
bool Player::finish(int check)
{
	//Returns true if current tile is within the FINISH range of tiles
	if (fetch(check) > AIR && fetch(check) <= FINISH)
	{
		//Finishes the level - passing a score calculated
		Level::Finish((int)(_foodcount*10*std::sqrt(1000.0f/_lvltime)));
		return (true);
	}
	else
	{
		return (false);
	}
}
bool Player::death(int check)
{
	//Returns true if current tile is within the DEATH range of tiles
	if (fetch(check) > HUNGER && fetch(check) <= DEATH)
	{
		//Resets the level
		Level::Reset();
		return (true);
	}
	else
	{
		return (false);
	}
}

void Player::Update(float elapsedTime)
{
	//Checks to see if player is not active(level hasnt started yet)
	if (!_active)
	{
		//Initialises timers and foodcount
		_foodcount = 0;
		_lvltime = 0;
		//Checks for specific keyboard input and that level isnt hub
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left)|| sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && !Level::IsHub() )
			//Makes player active
			_active = true;
	}

	//DECLARATIONS
	vec2f chkTile[] = { vec2f(4,0), vec2f(12,0), vec2f(20,0), 
						vec2f(4,24), vec2f(12,24), vec2f(20,24), 
						vec2f(0,4), vec2f(0,12), vec2f(0,20),
						vec2f(24,4), vec2f(24,12), vec2f(24,20), 
						vec2f(24,-4), vec2f(0,-4)};
	if (elapsedTime > .02)
		elapsedTime = .02;
	_time += elapsedTime;
	_lvltime += elapsedTime;
	_hungertime += elapsedTime;
	bool onSolid = false;
	bool onHead = false;
	bool onRight = false;
	bool onLeft = false;
	vec2f pos = this->GetPosition();


	//Checks for collisions on every side of the player sprite
	//BOTTOM
	//Checks for collision
	if (coll(check(pos + chkTile[3])) || coll(check(pos + chkTile[4])) || coll(check(pos + chkTile[5])))
		onSolid = true;
	//Corrects position if colliding and sets yvelocity to 0
	if (onSolid)
	{
		GetSprite().move(0, -fmod(pos.y,8));
		_yvelocity = 0;
	}
	//TOP
	//Checks for collision
	if (coll(check(pos + chkTile[0])) || coll(check(pos + chkTile[1])) || coll(check(pos + chkTile[2])))
	{
		onHead = true;
	}
	//Corrects position if colliding and sets yvelocity to 0
	if (onHead)
	{
		GetSprite().move(0, (8-fmod(pos.y,8)));
		_yvelocity = 0;
	}
	//RIGHT
	//Checks for collision
	if (coll(check(pos + chkTile[9])) || coll(check(pos + chkTile[10])) || coll(check(pos + chkTile[11])))
		onRight = true;
	//Corrects position if colliding and sets xvelocity to 0
	if (onRight && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		GetSprite().move(- fmod(pos.x, 8), 0);
		_xvelocity = 0;
		_animation = 0;
	}
	//LEFT
	//Checks for collision
	if (coll(check(pos + chkTile[6])) || coll(check(pos + chkTile[7])) || coll(check(pos + chkTile[8])))
		onLeft = true;
	//Corrects position if colliding and sets xvelocity to 0
	if (onLeft && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		GetSprite().move(8 - fmod(pos.x,8), 0);
		_xvelocity = 0;
		_animation = 0;
	}
	

//UPDATE VELOCITY AND ANIMATION
	
	//ANIMATION CYCLE
	//Changes animation if .1 seconds has passed
	if (_time > .1)
	{
		_time = 0;
		_animation += 1;
		if (_animation == 4){_animation = 0;}
			
	}
	//Updates hunger if player is active
	if (_active)
	{
		if (_hungertime > .05)
		{

			_hunger -= _hungertime * 40;
			_hungertime = 0;
		}
	}
	else
		_hungertime = 0;
	
	//HANDLES RIGHT AND LEFT INPUT
	//Checks for input of left and that not colliding on the left side
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !onLeft)
	{
		//Updates xvelocity and direction
		_xvelocity -= 1000.0f;
		_direction = Left;
	}
	//Checks for input of right and that not colliding on the right side
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !onRight)
	{
		//Updates xvelocity and direction
		_xvelocity += 1000.0f;
		_direction = Right;
	}
	//Checks if neither right or left are being pressed   OR  both right and left are being pressed
	if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		//Sets velocity to 0 and sets animation to 0
		_xvelocity = 0.0f;
		_animation = 0;
	}
	//MAX VELOCITY AND GRAVITY
	//Checks if not on solid
	if (!onSolid)
	{
		//Changes animation phase
		_animation = 1;
		//Turns gravity on
		_gravity = 1500;
	}
	else
	{
		//Turns gravity off
		_gravity = 0;
	}
	//Checks if xvelocity is greater than maxvelocity, if true set xvelocity to maxvelocity
	if (_xvelocity > _maxVelocity)
		_xvelocity = _maxVelocity;
	//Checks if xvelocity is less than -maxvelocity, if true set xvelocity to -maxvelocity
	if (_xvelocity < -_maxVelocity)
		_xvelocity = -_maxVelocity;
	//Loops through all tiles player is on checking if colliding with a ladder
	for (int i = 0; i < 12; i++) if (ladder(check(pos + chkTile[i])))
	{
		//Turns gravity off
		_gravity = 0;

		//Check for movement keys being pressed and collision for each
		//Checks for up input and that not colliding on head
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !onHead)
		{
			//Updates yvelocity
			_yvelocity -= 1000.0f;
		}
		//Checks for down input and that not colliding on bottom
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !onSolid)
		{
			//Updates yvelocity
			_yvelocity += 1000.0f;
		}
		//Checks if both UP and DOWN are being pressed   OR  neither UP or DOWN are being pressed
		if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Down)))
		{
			//Updates yvelocity
			_yvelocity = 0.0f;
			//Changes animation cycle
			_animation = 0;
		}

		//Makes sure yvelocity does not exceed 300 in either direction
		if (_yvelocity > 300)
			_yvelocity = 300;
		if (_yvelocity < -300)
			_yvelocity = -300;
	}
	
	//JUMPING
	//Checks for UP input and checks that onSolid and not onHead
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && onSolid && !onHead)
		_yvelocity = -400.0f;
	
	//Initialises boost and feed
	bool boost = false;
	bool feed = false;
	//Checks each tile player sprite is touching
	for (int i = 0; i < 12; i++)
	{
		//If the tile is a powerup set boost to true
		if (powerup(check(pos + chkTile[i])))
			boost = true;
		//If tile is a food tile set feed to true
		if (food(check(pos + chkTile[i])))
				feed = true;
		//Check for death
		death(check(pos + chkTile[i]));
		//Check for level finish
		finish(check(pos + chkTile[i]));
		//Check if hunger tile
		if (hunger(check(pos + chkTile[i])))
			_hunger -= 100;
	}

	//If boost is true set yvelocity to -500
	if (boost)
		_yvelocity = -500;
	//If feed is true add 50 to hunger
	if (feed)
		_hunger += 50;
	
	//Checks if hunger is above limit - if true set it to limit
	if (_hunger > 500)
		_hunger = 500;
	//Checks if hunger is empty - If true resets the level
	if (_hunger <= 0 )
		Level::Reset();

//UPDATE SPRITE
	
	//Sets size of hungerbar
	hungerbar.setTextureRect(sf::IntRect(0,0,float(_hunger) / 500.0 * (float)300, 25));
	//Sets scale of player sprite and the texture that should be displayed
	GetSprite().setScale(sf::Vector2f(.75, .75));
	GetSprite().setTextureRect(sf::IntRect(_animation * 32, _direction * 32, 32, 32));

	//Calculates the displacement for the player based on velocity, gravity and time passed
	sf::Vector2f displacement;
	displacement.x = _xvelocity * elapsedTime;
	float tempyvel = _yvelocity;
	_yvelocity +=  (_gravity*elapsedTime);
	displacement.y = (_yvelocity+tempyvel)/2 * elapsedTime ;
	//Moves the player sprite by the calculated displacement
	GetSprite().move(displacement);
	//Updates the property pos to the players new position
	pos = this->GetPosition();

	//Repeats the collision code from earlier on in the function but only for LEFT and RIGHT
	//RIGHT
	//Findsa if colliding on RIGHT
	if (coll(check(pos + chkTile[9])) || coll(check(pos + chkTile[10])) || coll(check(pos + chkTile[11])))
		onRight = true;
	//Checks if player can step up a tile to its RIGHT
	if (!coll(check(pos + chkTile[9])) && !coll(check(pos + chkTile[10])) && !coll(check(pos + chkTile[12])) && !onHead && onSolid  && sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && coll(check(pos + chkTile[11])))
	{
		//Moves player up a tile and sets colliding on RIGHT to false
		GetSprite().move(sf::Vector2f(1, -9));
		onRight = false;
	}
	//Checks if colliding on left and RIGHT is being pressed
	if (onRight && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		//Corrects sprites position and resets velocity and animation
		GetSprite().move(-fmod(pos.x, 8), 0);
		_xvelocity = 0;
		_animation = 0;
	}
	//LEFT
	//Finds if colliding on left
	if (coll(check(pos + chkTile[6])) || coll(check(pos + chkTile[7])) || coll(check(pos + chkTile[8])))
		onLeft = true;
	//Checks if player can step up a tile to its LEFT
	if (!coll(check(pos + chkTile[6])) && !coll(check(pos + chkTile[7])) && !coll(check(pos + chkTile[13])) && !onHead && onSolid &&  sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && coll(check(pos + chkTile[8])))
	{
		//Moves player up a tile and sets colliding on LEFT to false
		GetSprite().move(sf::Vector2f(-1, -9));
		onLeft = false;
	}
	//Checks if colliding on left and LEFT is being pressed
	if (onLeft &&  sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		//Corrects sprites position and resets velocity and animation
		GetSprite().move(8 - fmod(pos.x, 8), 0);
		_xvelocity = 0;
		_animation = 0;
	}


	//Checks if player is out of screen
	if (pos.x < (0 - 24) || pos.x > SCREEN_WIDTH || pos.y < (0 - 24) || pos.y > SCREEN_HEIGHT)
		//Resets the level
		Level::Reset();
}