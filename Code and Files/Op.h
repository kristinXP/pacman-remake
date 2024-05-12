//
// Class to draw and make the dialog for the intro story sequence of the game
//

/*
* REFERENCES
*		https://www.youtube.com/watch?v=bOG8667yePY
*		https://www.youtube.com/watch?v=4Vg9d1pjL20
*/

#pragma once
#include "stdafx.h"

class Intro {
public:

	Intro():m_sceneNumber(0),m_dialog(""),m_picture("") {};

	//to access the dialog associated with the scene
	string getSceneDialog() { return m_dialog; };

	//to access the scene number which is the indicator used to match the dialog with the picture
	int getSceneNumber() { return m_sceneNumber; };
	
	//to access the file name of the picture
	string getPicture() { return m_picture; };

	//used to link the associated dialog with the picture in the story sequence
	string SceneDialog(int char_select);

	//draws the picture and prints the dialog into the gui window 
	void drawPicture(sf::RenderWindow& window);

private:
	int m_sceneNumber = 0;		//the numerical value that represents the sequence of the images and pictures
	string m_picture;				//file name of the picture 
	string m_dialog;				//text of the dialog of the characters for the scene
	sf::Texture m_char_pic;		//SFML Texture object used to use the functions in the Texture class
	sf::Sprite m_sprite_character[2];			//SFML sprite object
};