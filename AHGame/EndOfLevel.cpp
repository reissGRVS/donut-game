#include "stdafx.h"
#include "EndOfLevel.h"

//Initialises all objects within the EndOfLevel class
EndOfLvl::EndOfLvl(sf::Image image) : RetryB(Playing, sf::Vector2f(188, 500), "retrybutton.png"), HubB(Hub, sf::Vector2f(548, 500), "hubbutton.png")
{
	lvl.loadFromImage(image);
	back.setTexture(lvl);
	font.loadFromFile("chocolate.otf");
	text.setPosition(400, 287);
	textdisplay = "0000";
	text.setFont(font);
	text.setCharacterSize(102);
	text.setColor(sf::Color::White);
	background.loadFromFile("eolscreen.png");
	menu.setTexture(background);
	counter = 0;
	timepassed = 0;
}

void EndOfLvl::Draw()
{
	//Draws the background, menu, buttons and score text to the game window
	Window::GetWindow().draw(back);
	Window::GetWindow().draw(menu);
	RetryB.Draw(Window::GetWindow());
	HubB.Draw(Window::GetWindow());
	Window::GetWindow().draw(text);
}

void EndOfLvl::UpdateText( float elapsedTime)
{
	//Increases wait timer
	wait += elapsedTime;

	//Proceeds if the counter is less than the score
	if (score > counter)
	{
		//Checks that wait period is over
		if (wait > 1.5)
		{
			//Increases timepassed timer
			timepassed += elapsedTime;
			//If timepassed is past .05 seconds
			if (timepassed > .05)
			{
				//Resets timepassed
				timepassed = 0;
				//Increases the counter 
				counter += (score / 70);
				//Checks if the counter is greater than the score - if true sets the counter to the score
				if (counter > score) counter = score;
				//Sets the string textdisplay to the counter
				textdisplay = std::to_string(counter);
				//Pads out textdisplay to 4 characters with 0s
				if (textdisplay.length() < 4)
				{
					std::string s(4 - textdisplay.length(), '0');
					textdisplay = s + textdisplay;
				}
			}
		}
	}
	//Sets the text objects string to textdisplay
	text.setString(textdisplay);

}

void EndOfLvl::Update(sf::Vector2i vc, sf::Event e)
{
	//Checks if Retry button is pressed
	GameState temp = RetryB.Update(vc, e);
	if (temp != 0)
	{
		//Resets the level and changes gamestate to playing
		Level::Reset();
		Game::ChangeGameState(temp);
		return;
	}

	//Checks if Hub button is pressed
	temp = HubB.Update(vc, e);
	if (temp != 0)
	{
		//Changes gamestate to hub
		Game::ChangeGameState(temp);
	}
}
void EndOfLvl::SetScore(int scor)
{
	//Sets the score within the class to a score passed
	score = scor;
}
