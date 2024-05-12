//
// Class to provide and control the character selection menu - intended selected options font is changed to red
//

/*
* REFERENCES
*		https://www.youtube.com/watch?v=bOG8667yePY
*		https://www.youtube.com/watch?v=4Vg9d1pjL20
*/

#pragma once
#include "stdafx.h"

class Selection {
public:
	
	//construtor that takes the width and height of the gui window in order to position the selection menu text 
	Selection(float width, float height) {

		//loads the font file and prints an error if file not found
		if (!font.loadFromFile("arial.ttf")) {
			//handle error
		}
		
		//sets the initial properties of the first selection item
		menu[0].setFont(font);												//sets the font 
		menu[0].setFillColor(sf::Color::Red);								//sets the color
		menu[0].setString("Boy");											//set the string
		menu[0].setPosition(sf::Vector2f(width/2.55, height / 3 *2));		//sets the position of the string in the gui window

		//sets the initial properties of the second selection item
		menu[1].setFont(font);
		menu[1].setFillColor(sf::Color::White);
		menu[1].setString("Girl");
		menu[1].setPosition(sf::Vector2f(width / 1.55, height / 3 *2));

		//initializes the selected item to the first string 
		m_selected = 0;

	};

	//to access the selected item
	int getPressedItem() { return m_selected; };

	//to draw the menu items to the gui window
	void draw(sf::RenderWindow& window) {
		for (int i = 0; i < 2; i++) {
			window.draw(menu[i]);
		}

	};

	//changes the font color of the first menu option to red and sets the selected item to the left most option
	void MoveLeft() {
		//bound checking to make sure the selected elemnt does not exceed the number of selectable options
		if (m_selected - 1 >= 0)
		{
			//changes the color of the right option to white 
			menu[m_selected].setFillColor(sf::Color::White);

			//deincrements the selected count to change the selected menu option
			m_selected--;
			
			//changes the color of the left option text to red  
			menu[m_selected].setFillColor(sf::Color::Red);

		}
	};

	//changes the font color of the second menu option to red and sets the selected item to the right most option
	void MoveRight() {
		//bound checking to make sure the selected elemnt does not exceed the number of selectable options
		if (m_selected + 1 <= 1)
		{
			//changes the color of the left option to white
			menu[m_selected].setFillColor(sf::Color::White);

			//increments the selected count to change the selected menu option
			m_selected++;

			//changes the color of the right option text to red 
			menu[m_selected].setFillColor(sf::Color::Red);

		}
	};

private:
	int m_selected;		// the numerical value that represents the selected option
	sf::Font font;		// used to gain access to the font class functions in the SFML library
	sf::Text menu[2];	//	Text object

};