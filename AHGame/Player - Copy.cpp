#pragma once
#include "StdAfx.h"
#include "Player.h"
#include "Game.h"

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
	VisibleGameObject::Draw(rw);
	if (!Level::IsHub())
		Window::GetWindow().draw(hungerbar);
}

void Player::Reset()
{
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
	if (onscreen(pos))
	{
		return (((int)pos.x) / 8) + ((((int)pos.y) / 8) * 128 + 1);
	}
	else
		return 0;
}

bool Player::onscreen(vec2f pos)
{
	return !(pos.x < (0) || pos.x > SCREEN_WIDTH || pos.y < (0) || pos.y > SCREEN_HEIGHT);
}

int Player::fetch(int check)
{
	if (check == 0)
		return 0;
	else
		return (Level::GetObjectManager().Get(check)->GetID());

}

bool Player::coll(int check)
{
	if (check == 0)
		return 0;
	else
		return (fetch(check) <= SOLID);
}

bool Player::powerup(int check)
{
	if (fetch(check) > DEATH && fetch(check) <= BOUNCE)
	{
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
	if (fetch(check) > BOUNCE && fetch(check) <= FOOD)
	{
		Level::GetObjectManager().Get(check)->Change(AIR);
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
	if (fetch(check) > LADDER && fetch(check) <= HUNGER)
	{
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
	if (fetch(check) > AIR && fetch(check) <= FINISH)
	{
		Level::Finish((int)(_foodcount * 10 * std::sqrt(1000.0f / _lvltime)));
		return (true);
	}
	else
	{
		return (false);
	}
}
bool Player::death(int check)
{
	if (fetch(check) > HUNGER && fetch(check) <= DEATH)
	{
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

	if (!_active)
	{
		_foodcount = 0;
		_lvltime = 0;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			_active = true;
	}

	//DECLARTIONS
	vec2f chkTile[] = { vec2f(4,0), vec2f(12,0), vec2f(20,0),
		vec2f(4,24), vec2f(12,24), vec2f(20,24),
		vec2f(0,4), vec2f(0,12), vec2f(0,20),
		vec2f(24,4), vec2f(24,12), vec2f(24,20),
		vec2f(24,-4), vec2f(0,-4) };
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


	//COLLISIONS
	//BOTTOM
	if (coll(check(pos + chkTile[3])) || coll(check(pos + chkTile[4])) || coll(check(pos + chkTile[5])))
		onSolid = true;
	if (onSolid)
	{
		GetSprite().move(0, -fmod(pos.y, 8));
		_yvelocity = 0;
	}
	//TOP
	if (coll(check(pos + chkTile[0])) || coll(check(pos + chkTile[1])) || coll(check(pos + chkTile[2])))
	{
		onHead = true;
	}
	if (onHead)
	{
		GetSprite().move(0, (8 - fmod(pos.y, 8)));
		_yvelocity = 0;
	}
	//RIGHT

	if (coll(check(pos + chkTile[9])) || coll(check(pos + chkTile[10])) || coll(check(pos + chkTile[11])))
		onRight = true;

	if (onRight && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		GetSprite().move(-fmod(pos.x, 8), 0);
		_xvelocity = 0;
		_animation = 0;
	}
	//LEFT

	if (coll(check(pos + chkTile[6])) || coll(check(pos + chkTile[7])) || coll(check(pos + chkTile[8])))
		onLeft = true;

	if (onLeft && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		GetSprite().move(8 - fmod(pos.x, 8), 0);
		_xvelocity = 0;
		_animation = 0;
	}


	//UPDATE VELOCITY AND ANIMATION

	//ANIMATION CYCLE
	if (_time > .1)
	{
		_time = 0;
		_animation += 1;
		if (_animation == 4) { _animation = 0; }

	}
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
	//HANDLES A AND D INPUT

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !onLeft)
	{
		_xvelocity -= 1000.0f;
		_direction = Left;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !onRight)
	{
		_xvelocity += 1000.0f;
		_direction = Right;
	}
	if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)))
	{
		_xvelocity = 0.0f;
		_animation = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		_xvelocity = 0.0f;
		_animation = 0;
	}
	//MAX VELOCITY AND GRAVITY
	if (!onSolid)
	{
		_animation = 1;
		_gravity = 1500;
	}
	else
	{
		_gravity = 0;
	}
	if (_xvelocity > _maxVelocity)
		_xvelocity = _maxVelocity;

	if (_xvelocity < -_maxVelocity)
		_xvelocity = -_maxVelocity;

	for (int i = 0; i < 12; i++)
		if (ladder(check(pos + chkTile[i])))
		{
			_gravity = 0;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !onHead)
			{
				_yvelocity -= 1000.0f;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !onSolid)
			{
				_yvelocity += 1000.0f;
			}
			if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)))
			{
				_yvelocity = 0.0f;
				_animation = 0;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				_yvelocity = 0.0f;
				_animation = 0;
			}

			if (_yvelocity > 300)
				_yvelocity = 300;
			if (_yvelocity < -300)
				_yvelocity = -300;
		}
	//JUMPING
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && onSolid && !onHead)
		_yvelocity = -400.0f;

	bool boost = false;
	for (int i = 0; i < 12; i++)
	{
		if (powerup(check(pos + chkTile[i])))
			boost = true;

		death(check(pos + chkTile[i]));
		finish(check(pos + chkTile[i]));
		if (hunger(check(pos + chkTile[i])))
			_hunger -= 100;
	}
	if (boost)
		_yvelocity = -500;

	if (Level::IsHub())
	{
		_active = false;
	}



	if (_active)
	{
		bool feed = false;
		for (int i = 0; i < 12; i++)
			if (food(check(pos + chkTile[i])))
				feed = true;
		if (feed)
			_hunger += 50;
		if (_hunger > 500)
			_hunger = 500;
		if (_hunger < 0)
			Level::Reset();
	}


	//UPDATE SPRITE

	hungerbar.setTextureRect(sf::IntRect(0, 0, float(_hunger) / 500.0 * (float)300, 25));
	GetSprite().setScale(sf::Vector2f(.75, .75));
	GetSprite().setTextureRect(sf::IntRect(_animation * 32, _direction * 32, 32, 32));
	sf::Vector2f displacement;
	displacement.x = _xvelocity * elapsedTime;
	float tempyvel = _yvelocity;
	_yvelocity += (_gravity*elapsedTime);
	displacement.y = (_yvelocity + tempyvel) / 2 * elapsedTime;
	GetSprite().move(displacement);
	pos = this->GetPosition();
	//RIGHT

	if (coll(check(pos + chkTile[9])) || coll(check(pos + chkTile[10])) || coll(check(pos + chkTile[11])))
		onRight = true;
	if (!coll(check(pos + chkTile[9])) && !onHead && onSolid && !coll(check(pos + chkTile[10])) && !coll(check(pos + chkTile[12])) && coll(check(pos + chkTile[11])))
	{
		GetSprite().move(sf::Vector2f(1, -9));
		onRight = false;
	}
	if (onRight && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		GetSprite().move(-fmod(pos.x, 8), 0);
		_xvelocity = 0;
		_animation = 0;
	}
	//LEFT

	if (coll(check(pos + chkTile[6])) || coll(check(pos + chkTile[7])) || coll(check(pos + chkTile[8])))
		onLeft = true;
	if (!coll(check(pos + chkTile[6])) && !onHead && onSolid && !coll(check(pos + chkTile[7])) && !coll(check(pos + chkTile[13])) && coll(check(pos + chkTile[8])))
	{
		GetSprite().move(sf::Vector2f(-1, -9));
		onLeft = false;
	}
	if (onLeft && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		GetSprite().move(8 - fmod(pos.x, 8), 0);
		_xvelocity = 0;
		_animation = 0;
	}




	if (pos.x < (0 - 24) || pos.x > SCREEN_WIDTH || pos.y < (0 - 24) || pos.y > SCREEN_HEIGHT)
		Level::Reset();
}


/*#pragma once
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
		int calculation = (((int)pos.x) / 8) + ((((int)pos.y) / 8) * 128 + 1);
		//Returns tile number that top left corner of player is in
		if (!(calculation < 1 || calculation > TILE_COUNT))
			return (((int)pos.x) / 8) + ((((int)pos.y) / 8) * 128 + 1);
	}
	return 0;
}

bool Player::onscreen(vec2f pos)
{
	//Returns whether the position passed is within the window
	return !(pos.x < (0) || pos.x > SCREEN_WIDTH || pos.y < (0) || pos.y > SCREEN_HEIGHT);
}

int Player::fetch(int check)
{
	//Validates that check passed is a tile number
	if (check == 0)
		return 0;
	else
	{
		//Returns the ID of the tile in position check
		return (Level::GetObjectManager().Get(check)->GetID());
	}
}

bool Player::coll(int check)
{
	//Returns true if current tile is within the SOLID range of tiles
	return (fetch(check) <= SOLID);
}

bool Player::powerup(int check)
{
	//Checks if current tile is within the BOUNCE range of tiles
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
	//Checks if current tile is within the FOOD range of tiles
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
	//Checks if current tile is within the HUNGER range of tiles
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
	//Checks if current tile is within the FINISH range of tiles
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
	//Checks if current tile is within the DEATH range of tiles
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
		//Checks for specific keyboard input
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)|| sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up) )
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
			GetSprite().move(0, -fmod(pos.y, 8));
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
			GetSprite().move(0, (8 - fmod(pos.y, 8)));
			_yvelocity = 0;
		}
		//RIGHT
		//Checks for collision
		if (coll(check(pos + chkTile[9])) || coll(check(pos + chkTile[10])) || coll(check(pos + chkTile[11])))
			onRight = true;
		//Corrects position if colliding and sets xvelocity to 0
		if (onRight && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			GetSprite().move(-fmod(pos.x, 8), 0);
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
			GetSprite().move(8 - fmod(pos.x, 8), 0);
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
			if (_animation == 4) { _animation = 0; }

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
		//HANDLES right AND left INPUT

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
		////Checks if xvelocity is less than -maxvelocity, if true set xvelocity to -maxvelocity
		if (_xvelocity < -_maxVelocity)
			_xvelocity = -_maxVelocity;


		//Loops through all tiles player is on checking if colliding with a ladder
		for (int i = 0; i < 12; i++)
			if (ladder(check(pos + chkTile[i])))
			{
				//If on a ladder tile set gravity to 0
				_gravity = 0;

				//Check for 
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !onHead)
				{
					_yvelocity -= 1000.0f;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !onSolid)
				{
					_yvelocity += 1000.0f;
				}
				if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)))
				{
					_yvelocity = 0.0f;
					_animation = 0;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					_yvelocity = 0.0f;
					_animation = 0;
				}

				if (_yvelocity > 300)
					_yvelocity = 300;
				if (_yvelocity < -300)
					_yvelocity = -300;
			}
		//JUMPING
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && onSolid && !onHead)
			_yvelocity = -400.0f;

		bool boost = false;
		for (int i = 0; i < 12; i++)
		{
			if (powerup(check(pos + chkTile[i])))
				boost = true;

			death(check(pos + chkTile[i]));
			finish(check(pos + chkTile[i]));
			if (hunger(check(pos + chkTile[i])))
				_hunger -= 100;
		}
		if (boost)
			_yvelocity = -500;

		if (Level::IsHub())
		{
			_active = false;
		}



		if (_active)
		{
			bool feed = false;
			for (int i = 0; i < 12; i++)
				if (food(check(pos + chkTile[i])))
					feed = true;
			if (feed)
				_hunger += 50;
			if (_hunger > 500)
				_hunger = 500;
			if (_hunger < 0)
				Level::Reset();
		}


		//UPDATE SPRITE

		hungerbar.setTextureRect(sf::IntRect(0, 0, float(_hunger) / 500.0 * (float)300, 25));
		GetSprite().setScale(sf::Vector2f(.75, .75));
		GetSprite().setTextureRect(sf::IntRect(_animation * 32, _direction * 32, 32, 32));
		sf::Vector2f displacement;
		displacement.x = _xvelocity * elapsedTime;
		float tempyvel = _yvelocity;
		_yvelocity += (_gravity*elapsedTime);
		displacement.y = (_yvelocity + tempyvel) / 2 * elapsedTime;
		GetSprite().move(displacement);
		pos = this->GetPosition();
		//RIGHT

		if (coll(check(pos + chkTile[9])) || coll(check(pos + chkTile[10])) || coll(check(pos + chkTile[11])))
			onRight = true;
		if (!coll(check(pos + chkTile[9])) && !onHead && onSolid && !coll(check(pos + chkTile[10])) && !coll(check(pos + chkTile[12])) && coll(check(pos + chkTile[11])))
		{
			GetSprite().move(sf::Vector2f(1, -9));
			onRight = false;
		}
		if (onRight && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			GetSprite().move(-fmod(pos.x, 8), 0);
			_xvelocity = 0;
			_animation = 0;
		}
		//LEFT

		if (coll(check(pos + chkTile[6])) || coll(check(pos + chkTile[7])) || coll(check(pos + chkTile[8])))
			onLeft = true;
		if (!coll(check(pos + chkTile[6])) && !onHead && onSolid && !coll(check(pos + chkTile[7])) && !coll(check(pos + chkTile[13])) && coll(check(pos + chkTile[8])))
		{
			GetSprite().move(sf::Vector2f(-1, -9));
			onLeft = false;
		}
		if (onLeft && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			GetSprite().move(8 - fmod(pos.x, 8), 0);
			_xvelocity = 0;
			_animation = 0;
		}
}



*/