#pragma once
#include "VisibleGameObject.h"

class ObjectManager
{
public:	
	//Initialises object manager
	ObjectManager();
	~ObjectManager();

	//Adds a pair to the ObjectManagers map
	void Add(int name, VisibleGameObject* gameObject);
	//Removes a pair from the ObjectManagers map
	void Remove(int name);
	//Returns the number of pairs in the ObjectManagers map
	int GetObjectCount() const;
	//Returns a VisibleGameObject pointer from the ObjectManagers map
	VisibleGameObject* Get(int name) const;

	//Draws the VisibleGameObjects from every pair in the ObjectManagers map
	void DrawAll(sf::RenderWindow& renderWindow);
	//Returns how long the clock has been running and resets it
	float UpdateClock();

private:
	//Map that holds pairs of int IDs and VisibleGameObject pointers
	std::map<int , VisibleGameObject*> _gameObjects;

	//Clock
	sf::Clock clock;

	//Struct that handles the proper deletion of VisibleGameObjects in pairs
	struct GameObjectDeallocator
	{
		void operator()(const std::pair<int,VisibleGameObject*> & p) const
		{
			delete p.second;
		}
	};
};