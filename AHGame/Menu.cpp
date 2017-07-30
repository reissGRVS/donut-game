#include "stdafx.h"
#include "Menu.h"

//Initialises the menu class, this includes setting up the background and the buttons
Menu::Menu(): PlayB(Hub, sf::Vector2f(382,145),"playbutton.png"), HighB(Highscore, sf::Vector2f(382, 230), "highbutton.png"), ExitB(Exiting, sf::Vector2f(382,315), "exitbutton.png")
{
	background.loadFromFile("mainmenu2.png");
	sprite.setTexture(background);

}

void Menu::Draw()
{
	//Draws the background and buttons to the window
	Window::GetWindow().draw(sprite);
	PlayB.Draw(Window::GetWindow());
	HighB.Draw(Window::GetWindow());
	ExitB.Draw(Window::GetWindow());
	
}

void Menu::Update(sf::Vector2i vc, sf::Event e)
{
	//Checks if the play button is pressed
	GameState temp = PlayB.Update(vc,e);
	if( temp != 0)
	{
		//Changes gamestate
		Game::ChangeGameState(temp);
		return;
	}
	//Checks if the exit button is pressed
	temp = ExitB.Update(vc,e);
	if (temp != 0)
	{
		//Changes gamestate
		Game::ChangeGameState(temp);
	}
	//Checks if the highscore button is pressed
	temp = HighB.Update(vc,e);
	if (temp != 0)
	{
		//Changes gamestate
		Game::ChangeGameState(temp);
	}
}
