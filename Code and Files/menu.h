//
// Class to provide and control the start menu - intended selected options font is changed to red
//

/*
* REFERENCES
*		https://www.youtube.com/watch?v=bOG8667yePY
*		https://www.youtube.com/watch?v=4Vg9d1pjL20
*/

#pragma once
#include "stdafx.h"

class Menu {
public:
	//unsigned char MAP_HEIGHT = 23;
	//MAP_WIDTH = 21;
	
	//construtor that takes the width and height of the gui window in order to position the selection menu text 
	Menu(float width, float height) {

		//loads the font file and prints an error if file not found
		if (!font.loadFromFile("arial.ttf")) {
			//handle error
		}
		
		//sets the initial properties of the first selection item
		menu[0].setFont(font);
		menu[0].setFillColor(sf::Color::Red);
		menu[0].setString("Play");
		menu[0].setPosition(sf::Vector2f(width / 2, height/3*1));

		//sets the initial properties of the second selection item
		menu[1].setFont(font);
		menu[1].setFillColor(sf::Color::White);
		menu[1].setString("Instructions");
		menu[1].setPosition(sf::Vector2f(width / 2, height / 3 * 1.5));

		//sets the initial properties of the third selection item
		menu[2].setFont(font);
		menu[2].setFillColor(sf::Color::White);
		menu[2].setString("Close");
		menu[2].setPosition(sf::Vector2f(width / 2, height / 3 * 2));

		//initializes the selected item to the first string 
		m_selected = 0;

	};

	//to access the selected item
	int getPressedItem() { return m_selected; }
	
	//to draw the menu items to the gui window
	void draw(sf::RenderWindow& window) {
		for (int i = 0; i < 3; i++) {
			window.draw(menu[i]);
		}

	};

	//changes the font color of the intended selected menu option to red and sets the selected item to one above the previous
	void MoveUp() {

		//bound checking to make sure the selected elemnt does not exceed the number of selectable options
		if (m_selected - 1 >= 0)
		{
			//changes the color of the previous red colored option to white 
			menu[m_selected].setFillColor(sf::Color::White);

			//deincrements the selected count to change the selected menu option
			m_selected--;

			//changes the color of next bottom option text to red  
			menu[m_selected].setFillColor(sf::Color::Red);

		}
	};

	//changes the font color of the intended selected menu option to red and sets the selected item to one below the previous
	void MoveDown() {
		if (m_selected + 1 <= 2)
		{
			//changes the color of the previous red colored option to white 
			menu[m_selected].setFillColor(sf::Color::White);

			//increments the selected count to change the selected menu option
			m_selected++;

			//changes the color of next top option text to red 
			menu[m_selected].setFillColor(sf::Color::Red);

		}
	};

private:
	int m_selected;		// the numerical value that represents the selected option
	sf::Font font;		// used to gain access to the font class functions in the SFML library
	sf::Text menu[3];	//	Text object

};