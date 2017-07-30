#pragma once
#include "stdafx.h"
class VisibleGameObject
{
	//Note that all functions are virtual so they can be changed by classes that inherit from this class
public:
	//Initialise VisibleGameObject
	VisibleGameObject();
	virtual ~VisibleGameObject();
	
	//Attempts to load a texture and applies it to the objects _sprite
	virtual void Load(std::string filename);	
	//Forces a loaded state
	virtual void Loaded();
	//Changes the id property
	virtual void Change(int ida);
	//Draws the _sprite to screen
	virtual void Draw(sf::RenderWindow & window);
	virtual void Update(float elapsedTime);
	//Returns the id property
	virtual int GetID();
	//Sets the position of the objects _sprite 
	virtual void SetPosition(float x, float y);
	//Gets the position of the objects _sprite 
	virtual sf::Vector2f GetPosition() const;
	//Gets the width of the objects _sprite 
	virtual float GetWidth() const;
	//Gets the height of the objects _sprite 
	virtual float GetHeight() const;
	//Gets the bounding rectangle of the objects _sprite 
	virtual sf::Rect<float> GetBoundingRect() const;
	//Returns _isLoaded
	virtual bool IsLoaded() const;

protected:
	//Returns a pointer to _sprite
	sf::Sprite& GetSprite();

private:
	//Sprite and its texture
	sf::Sprite  _sprite;
	sf::Texture _image;
	//Name of file texture is loaded from
	std::string _filename;
	//id
	int id;
	//Whether a texture has been loaded or not
	bool _isLoaded;
	
};
