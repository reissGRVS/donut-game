#include "stdafx.h"
#include "NameEntry.h"

//Initialises the NameEntry class
void NameEntry::Init()
{
	font.loadFromFile("chocolate.otf");
	text.setString("Enter Your Name");
	text.setCharacterSize(80);
	text.setFont(font);
	text.setColor(sf::Color::Blue);
	background.loadFromFile("nameentry.png");
	back.setTexture(background);
}




void NameEntry::Draw(sf::RenderWindow & rw)
{
	//Draws the background and text to window
	rw.clear(sf::Color(255, 255, 255));
	rw.draw(back);

	//Outline effect
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f,0);
	text.setPosition(sf::Vector2f(SCREEN_WIDTH/ 2.0f, 300));
	text.setColor(sf::Color(0, 0, 0));
	text.move(1, 0);
	rw.draw(text);
	text.move(-2, 0);
	rw.draw(text);
	text.move(1, 1);
	rw.draw(text);
	text.move(0, -2);
	rw.draw(text);
	text.setColor(sf::Color(255, 255, 255));
	text.move(0, 1);
	rw.draw(text);

	rw.display();
}

void NameEntry::Update(sf::RenderWindow & rw)
{
	//Initialises entered 
	bool entered = false;
	//Loops until enter key is pressed and entered is changed to true
	while (!entered)
	{
		//Polls through all window events
		sf::Event event;
		while (rw.pollEvent(event))
		{
			//If the event type is text
			if (event.type == sf::Event::TextEntered)
			{
				//Checks if the text entered is a letter and that the current string length is less than 8
				if (((event.text.unicode < 123 && event.text.unicode > 96) || (event.text.unicode < 91 && event.text.unicode > 64)) && str.length() < 8)
				{
					//If the letter is uppercase - make it lowercase
					if ((event.text.unicode < 91 && event.text.unicode > 64)) event.text.unicode += 32;
					//Add the letter entered to the string
					str += static_cast<char>(event.text.unicode);
					//Set the string of the text object
					text.setString(str);
				}
				//If the key pressed was a back space and the string isnt already empty
				if (event.text.unicode == 8 && !str.empty())
				{
					//Take off the last character of the string
					str.pop_back();
					//Set the string of the text object
					text.setString(str);
				}
				//If the key pressed is enter and the string isnt empty - set entered to true(causing the loop to end)
				if (event.text.unicode == 13 && !str.empty())
					entered = true;
				
				//If the key pressed is escape - close the window, free the console and end the program
				if (event.text.unicode == 27)
				{
					rw.close();
					FreeConsole();
					exit(0);
				}
			}
			 
		}
		//Draw everything to screen
		Draw(rw);
	}
}

//Return the string that was entered
std::string NameEntry::GetName()
{
	return str;
}

std::string NameEntry::str;
sf::Text NameEntry::text;
sf::Font NameEntry::font;
sf::Texture NameEntry::background;
sf::Sprite NameEntry::back;