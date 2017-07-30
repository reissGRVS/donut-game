#include "stdafx.h"
#include "VisibleGameObject.h"


VisibleGameObject::VisibleGameObject()
	: _isLoaded(false)
{
	//_isLoaded = false; Slightly faster to use the above constructor initialization.
}


VisibleGameObject::~VisibleGameObject()
{
}

void VisibleGameObject::Load(std::string filename)
{
	//Attempts to load texture from passed filename
	if(_image.loadFromFile(filename) == false)
	{
		//If it fails to load the texture - sets the filename to empty - sets isLoaded to false
		_filename = "";
		_isLoaded = false;
	}
	else
	{
		//If it loads the texture - sets the filename to the string passed - sets the texture to the sprite - sets isLoaded to true
		_filename = filename;
		_sprite.setTexture(_image);
		_isLoaded = true;
	}
}

void VisibleGameObject::Draw(sf::RenderWindow & renderWindow)
{
	//Checks if a texture is loaded
	if(_isLoaded)
	{
		//Draws the sprite to the window passed
		renderWindow.draw(_sprite);
	}
}

void VisibleGameObject::Update(float elapsedTime)
{
}


int VisibleGameObject::GetID()
{
	return 0;
}

void VisibleGameObject::SetPosition(float x, float y)
{
	//Sets the sprites position if a a texture is loaded
	if(_isLoaded)
	{
		_sprite.setPosition(x,y);
	}
}

//Returns the sprites position if a texture is loaded
sf::Vector2f VisibleGameObject::GetPosition() const
{
  if(_isLoaded)
  {
    return _sprite.getPosition();
  }
  return sf::Vector2f();
}

//Returns the height of the sprite
float VisibleGameObject::GetHeight() const
{
	return _sprite.getLocalBounds().height;
}
//Returns the width of the sprite
float VisibleGameObject::GetWidth() const
{
	return _sprite.getLocalBounds().width;
}

//Returns the bounding rectangle of the sprite
sf::Rect<float> VisibleGameObject::GetBoundingRect() const
{
	return _sprite.getGlobalBounds();
}

//Returns pointer the the objects sprite
sf::Sprite& VisibleGameObject::GetSprite()
{
  return _sprite;
}

//Returns whether a texture has been loaded
bool VisibleGameObject::IsLoaded() const
{
  return _isLoaded;
}

//Forces _isLoaded to true without having to explicitly load a texture using Load()
void VisibleGameObject::Loaded()
{
	if (!_isLoaded) { _isLoaded = true; }
}

void VisibleGameObject::Change(int ida)
{
}
