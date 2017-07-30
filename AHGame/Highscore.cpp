#include "stdafx.h"
#include "Highscore.h"

//Initialises all the objects in the highscore screen class
HighscoreScreen::HighscoreScreen() : MainB(ShowingMenu, sf::Vector2f(382, 680), "exitbutton.png")
{
	font.loadFromFile("chocolate.otf");
	text.setPosition(350, 120);
	text.setFont(font);
	text.setCharacterSize(42);
	text.setColor(sf::Color(255,255,255));
	//Fetches highscorers names
	text.setString(ScoreHandler::GetTopNames());
	stext.setPosition(600, 120);
	stext.setFont(font);
	stext.setCharacterSize(42);
	stext.setColor(sf::Color(255, 255, 255));
	//Fetches highscorers scores
	stext.setString(ScoreHandler::GetTopScores());
	background.loadFromFile("highscorebackground.png");
	back.setTexture(background);
}

void HighscoreScreen::Draw()
{
	//Draws the background, buttons, and text to the window
	
	Window::GetWindow().draw(back);
	MainB.Draw(Window::GetWindow());
	
	//Achieves outline effect by moving the text around to draw black outline
	text.setColor(sf::Color(0, 0, 0));
	text.move(1, 0);
	Window::GetWindow().draw(text);
	text.move(-2, 0);
	Window::GetWindow().draw(text);
	text.move(1,1);
	Window::GetWindow().draw(text);
	text.move(0, -2);
	Window::GetWindow().draw(text);
	text.setColor(sf::Color(255, 255, 255));
	text.move(0, 1);
	Window::GetWindow().draw(text);

	//Achieves outline effect by moving the text around to draw black outline
	stext.setColor(sf::Color(0, 0, 0));
	stext.move(1, 0);
	Window::GetWindow().draw(stext);
	stext.move(-2, 0);
	Window::GetWindow().draw(stext);
	stext.move(1, 1);
	Window::GetWindow().draw(stext);
	stext.move(0, -2);
	Window::GetWindow().draw(stext);
	stext.setColor(sf::Color(255, 255, 255));
	stext.move(0, 1);
	Window::GetWindow().draw(stext);
}

void HighscoreScreen::Update(sf::Vector2i vc, sf::Event e)
{
	//Checks if Main button has been pressed
	GameState temp = MainB.Update(vc,e);
	if (temp != 0)
	{
		//Changes gamestate
		Game::ChangeGameState(temp);
	}
}
