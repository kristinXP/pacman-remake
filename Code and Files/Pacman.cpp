/*
 * Pacman (main character)
 */

#include "Pacman.h"

/**/
 /*

 NAME

		 void Pacman::draw(sf::RenderWindow& window, int character_selection)

 SYNOPSIS

		 draw(sf::RenderWindow& window, int character_selection)
			
			window            --> is the sfml window that is responsible for displaying the gui
			character_selection --> is the value that holds which character the user selected in the beginning


 DESCRIPTION

		 This function is responsible for drawing "pacman" or the main character sprite based on the user's input and uses the SFML library
 RETURNS

		 Returns void
REFERNCES
		https://gamefromscratch.com/sfml-c-tutorial-spritesheets-and-animation/
		https://stackoverflow.com/questions/52655335/animating-sprites-in-sfml-from-a-sprite-sheet

 */
 /**/
void Pacman::draw(sf::RenderWindow& window, int character_selection)
{

	unsigned char frame = static_cast<unsigned char>(floor(m_animation_timer / static_cast<float>(4)));

	sf::Sprite sprite;

	sf::Texture texture;

	sprite.setPosition(m_position.x, m_position.y);

	if (character_selection == 1) {
		texture.loadFromFile("boy_sprite.png");
	}
	else {
		texture.loadFromFile("girl_sprite.png");
	}
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(g_CELL_SIZE * frame, g_CELL_SIZE * m_direction, g_CELL_SIZE, g_CELL_SIZE));

	window.draw(sprite);

	m_animation_timer = (1 + m_animation_timer) % (6 * 4);

};

/*

NAME

		void Pacman::update(array<array<Cell, g_MAP_HEIGHT>, g_MAP_WIDTH>& map, int floor)

SYNOPSIS

		void Pacman::update(array<array<Cell, g_MAP_HEIGHT>, g_MAP_WIDTH>& map, int floor)
		   
		   map            --> is an array of size 21 (g_MAP_WIDTH) of arrays of CELL(enum values holding the map elemnts) of size 23 (g_MAP_HEIGHT). 
								 this holds the elements of the map that is used to convert the string text value of the map into the gui image using the SFML library
		   floor			 --> is used to hold the value of which map or floor and is used to pass to the function that is called within this function to calculate the new target tile in scatter mode


DESCRIPTION

		This function is responsible for "pacman" or the main character's movement by incrementing the character's x and y coordinate position according the appropriate
		arrow keys that the user presses if the movement is valid
RETURNS

		Returns void

REFERENCES
		https://gameinternals.com/understanding-pac-man-ghost-behavior
		https://www.youtube.com/watch?v=ZXnK0vlSJV8
		https://www.youtube.com/watch?v=vC0d1rDmPBs

*/
/**/
void Pacman::update(array<array<Cell, g_MAP_HEIGHT>, g_MAP_WIDTH>& map, int floor)
{
	//there can only be four walls one in each of the cardinal positions
	array<bool, 4> walls{};
	
	//checks to see if there is a wall
	//pacman cannot enter the ghost house
	walls[0] = m_collision.map_collision(true, false, m_speed + m_position.x, m_position.y, map);
	walls[1] = m_collision.map_collision(true, false, m_position.x, m_position.y - m_speed, map);
	walls[2] = m_collision.map_collision(true, false, m_position.x - m_speed, m_position.y, map);
	walls[3] = m_collision.map_collision(true, false, m_position.x, m_speed + m_position.y, map);

	//checks to see if there is a wall in the intended direction the user wants to move pacman
	if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (false == walls[0]) //prevents from going into a wall stops
		{
			m_direction = 0;
		}
	}

	if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (false == walls[1])
		{
			m_direction = 1;
		}
	}

	if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (false == walls[2])
		{
			m_direction = 2;
		}
	}

	if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (false == walls[3])
		{
			m_direction = 3;
		}
	}

	//controls the direction of pacman in the appropriate direction
	//speed is set to move one cell at a time
	if (false == walls[m_direction])
	{
		switch (m_direction)
		{
		case 0:
		{
			m_position.x += m_speed;

			break;
		}
		case 1:
		{
			m_position.y -= m_speed;

			break;
		}
		case 2:
		{
			m_position.x -= m_speed;

			break;
		}
		case 3:
		{
			m_position.y += m_speed;
		}
		default:
		{
			
		}
		}



	}

	//warp tunnel left and right
	if (-g_CELL_SIZE >= m_position.x)
	{
		m_position.x = g_CELL_SIZE * g_MAP_WIDTH - m_speed;
	}
	else if (m_position.x >= g_CELL_SIZE * g_MAP_WIDTH)
	{
		m_position.x = m_speed - g_CELL_SIZE;
	}

	//warp tunnel up and down
	if (-g_CELL_SIZE >= m_position.y)
	{
		m_position.y = g_CELL_SIZE * g_MAP_WIDTH - m_speed;
	}
	else if (m_position.y >= g_CELL_SIZE * g_MAP_WIDTH)
	{
		m_position.y = m_speed - g_CELL_SIZE;
	}

	
	//when pacman eats and engerizer or potion
	if (m_collision.getEnergized() == true && m_energized == false)
	{

		m_energizer_timer = static_cast<unsigned short>(216 / pow(2, 1));
		m_collision.setEnergized(false);
		m_energized = true;
		

	}
	else
	{
		//deincrements the enegrizer timer for how long pacman is involunerable to the ghosts
		if (m_energizer_timer > 0) {
			m_energizer_timer -= 1;
		}

		//prevents if energizer timer accidentally becomes negative
		if (m_energizer_timer < 0) {
			m_energizer_timer = 0;
		}
		
	}



};

