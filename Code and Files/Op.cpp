/*
 * Openning sequence
 */

#include "Op.h"

 /**/
  /*

  NAME

		 string Intro::SceneDialog(int char_select)

  SYNOPSIS

		  SceneDialog(int char_select)

			 char_select            --> is the value that holds which character the user selected in the beginning


  DESCRIPTION

		  This function is responsible for linking the right dialog and picture file name with the scene number for the openning story sequence at the beginning of the game
  RETURNS

		  Returns the dialog string that will be outputed into the gui window


  */
  /**/

string Intro::SceneDialog(int char_select) {
	
	//increments the scene number which starts at 0
	++m_sceneNumber;

	//this matches the scene number with the dialog text and picture file name
	switch (m_sceneNumber) {
	case 1:
	{
		m_dialog = "Hey, what's with the long face, kid?";
		m_picture = "shop2.png";
		m_sprite_character[0].setPosition(85, 30);
		break;
	}
	case 2:
	{
		m_dialog = "It's just that... at this rate I won't \neven have enough to make ends meet, \nlet alone pay off my debt.";
		if (char_select == 1) {
			m_picture = "boy2.png";
		}
		else {
			m_picture = "girl3.png";
		}

		break;
	}
	case 3:
	{
		m_dialog = "They're gonna kill me for sure.";
		if (char_select == 1) {
			m_picture = "boy3.png";
		}
		else {
			m_picture = "girl4.png";
		}
		break;
	}
	case 4:
	{
		m_dialog = "Well there's no doubt that you're a \nhell of a tallented artist, but most \nof the folks around here couldn't \ngive damn about fancy pictures \nand whatnot.";
		m_picture = "shop4.png";
		break;
	}
	case 5:
	{
		m_dialog = "Hmm... I got a business proposition \nfor ya, if you're interested.";
		m_picture = "shop3.png";
		break;
	}
	case 6:
	{
		m_dialog = "I'd honestly take anything at this \npoint.";
		if (char_select == 1) {
			m_picture = "boy2.png";
		}
		else {
			m_picture = "girl4.png";
		}
		break;
	}
	case 7:
	{
		m_dialog = "I've been getting a lot of new \nadventures coming to buy some odds \nand ends to explore the dungeon \nnearby.";
		m_picture = "shop4.png";
		break;
	}
	case 8:
	{
		m_dialog = "Why don't you put you're artistic \ngenius to some good use and draw a \nmap of it. I know those adventurers \nwould for sure pay a pretty coin \nfor it.";
		m_picture = "shop3.png";
		break;
	}
	case 9:
	{
		m_dialog = "But I don't have any combat \nexperience, not to meantion...";
		if (char_select == 1) {
			m_picture = "boy3.png";
		}
		else {
			m_picture = "girl2.png";
		}
		break;
	}
	case 10:
	{
		m_dialog = "None, needed. There are some slimes \nthat hang out in there but I'm pretty \nsure you can just do your best \nand avoid them.";
		m_picture = "shop2.png";
		break;
	}
	case 11:
	{
		m_dialog = "After all you avoided those debt \ncollectors for years now. \nHA HA HA";
		m_picture = "shop1.png";
		break;
	}
	case 12:
	{
		m_dialog = "...don't remind me. But yeah, \nI really appreciate it";
		if (char_select == 1) {
			m_picture = "boy1.png";
		}
		else {
			m_picture = "girl1.png";
		}
		break;
	}
	case 13:
	{
		m_dialog = "The more detailed the map is the \nhigher it'll sell for.";
		m_picture = "shop4.png";
		break;
	}
	case 14:
	{
		m_dialog = "Just be careful kid, I don't want my \nnew business partner to go off dying \non me ya' know.";
		m_picture = "shop1.png";
		break;
	}
	default:
		m_dialog = "";
		m_picture = "";
	}

	return m_dialog;

};

/**/
 /*

 NAME

		void Intro::drawPicture(sf::RenderWindow& window)

 SYNOPSIS

		 drawPicture(sf::RenderWindow& window)

			window            --> is the sfml window that is responsible for displaying the gui


 DESCRIPTION

		 This function is responsible for drawing the approriate sprite and checks to see if main character or shopkeeper image should be displayed based on scene number
 RETURNS

		 Returns void


 */
 /**/
void Intro::drawPicture(sf::RenderWindow& window) {
	if (!m_char_pic.loadFromFile(m_picture)) {
		//cout << "picture not found" << endl;
	}
	if (m_sceneNumber == 1 || m_sceneNumber == 4 || m_sceneNumber == 5 || m_sceneNumber == 7 || m_sceneNumber == 8 || m_sceneNumber == 10 || m_sceneNumber == 11 || m_sceneNumber == 13 || m_sceneNumber == 14) {
		m_sprite_character[0].setTexture(m_char_pic);
		window.draw(m_sprite_character[0]);

	}
	else if (m_sceneNumber == 2 || m_sceneNumber == 3 || m_sceneNumber == 6 || m_sceneNumber == 9 || m_sceneNumber == 12) {
		m_sprite_character[1].setTexture(m_char_pic);
		window.draw(m_sprite_character[1]);
	}

	return;
};