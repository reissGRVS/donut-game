#include "stdafx.h"
#include "ObjectManager.h"
#include "Game.h"

ObjectManager::ObjectManager()
{
}

ObjectManager::~ObjectManager()
{
	//Deletes all VisibleGameObjects stored in the _gameObjects map
	std::for_each(_gameObjects.begin(),_gameObjects.end(),GameObjectDeallocator());
}

void ObjectManager::Add(int name, VisibleGameObject* gameObject)
{
	//Adds a VisibleGameObject pointer to the _gameObjects map, along with an int ID
	_gameObjects.insert(std::pair<int, VisibleGameObject*>(name, gameObject));
}

void ObjectManager::Remove(int name)
{
	//Creates an iterator that stores the position of the object that is searched for(with int part of pair equal to the int passed)
	std::map<int, VisibleGameObject*>::iterator results = _gameObjects.find(name);
	//Check if pair was found
	if(results != _gameObjects.end() )
	{
		//Deletes the visiblegameobject associated to the pointer in the pair
		delete results->second;
		//Deletes the pair from the gameObjects map
		_gameObjects.erase(results);
	}
}

VisibleGameObject* ObjectManager::Get(int name) const
{
	//Creates an iterator that stores the position of the object that is searched for(with int part of pair equal to the int passed)
	std::map<int, VisibleGameObject*>::const_iterator results = _gameObjects.find(name);
	//Check if pair was found
	if(results == _gameObjects.end() )
		//If pair wasnt found return NULL
		return NULL;
	else
		//If pair was found return the visiblegameobject pointer
		return results->second;
	
}

int ObjectManager::GetObjectCount() const
{
	//Returns number of pairs in the gameObjects map
	return _gameObjects.size();
}


void ObjectManager::DrawAll(sf::RenderWindow& renderWindow)
{
	//Iterates through every pair in the gameObjects map
	std::map<int,VisibleGameObject*>::const_iterator itr = _gameObjects.begin();
	while(itr != _gameObjects.end())
	{
		//Draws the visiblegameobject associated with the pair to the game window
		itr->second->Draw(renderWindow);
		//Increases iterator by 1
		itr++;
	}
}

float ObjectManager::UpdateClock()
{
	//Resets the clock and returns the time stored by the clock
	return clock.restart().asSeconds();
}
