#include "StdAfx.h"
#include "SplashScreen.h"

void SplashScreen::Show(sf::RenderWindow & renderWindow)
{
	sf::Texture image;
	//Checks that texture is loaded - if not loaded returns early
	if(image.loadFromFile("splash.png") != true)
	{
		return;
	}
	//Declare sprite with the texture loaded and displays to window
	sf::Sprite sprite(image);
	renderWindow.draw(sprite);
	renderWindow.display();
	return;
}