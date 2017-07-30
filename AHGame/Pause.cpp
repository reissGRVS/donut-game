#include "stdafx.h"
#include "Pause.h"

//Initialise the pause menu - set up the background, pause menu and buttons
CPause::CPause(sf::Image image) : PlayB(Playing, sf::Vector2f(368, 342), "resumebutton.png"), HubB( Hub, sf::Vector2f(368, 424),  "hubbutton.png")
{
	background.loadFromImage(image);
	back.setTexture(background);
	texture.loadFromFile("pausemenu.png");
	pausemenu.setTexture(texture);
	pausemenu.setPosition(334, 250);
}

//Draw the background, pause menu and buttons to the window
void CPause::Draw()
{
	Window::GetWindow().draw(back);
	Window::GetWindow().draw(pausemenu);
	PlayB.Draw(Window::GetWindow());
	HubB.Draw(Window::GetWindow());
}

void CPause::Update(sf::Vector2i vc, sf::Event e)
{

	//Check if the play button has been clicked
	GameState temp = PlayB.Update(vc,e);
	if (temp != 0)
	{
		//Change gamestate to Playing
		Game::ChangeGameState(temp);
		return;
	}
	//Check if the hub button has been clicked
	temp = HubB.Update(vc,e);
	if (temp != 0)
	{
		//Change gamestate to PlayingHub
		Game::ChangeGameState(temp);
	}
}
