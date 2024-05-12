/*
 * Green Slime (orange Ghost)
 */

#include "stdafx.h"
#include "collision_checking.h"
#include "Pacman.h"
#include "slimes.h"
#include "green.h"

 /**/
  /*

  NAME

		 void Green::reset(const Position& home) - resets all the variables back to the original values

  SYNOPSIS

		  reset(const Position& home)
			 home            --> a Position struct variable that stores the x and y cooridinates of the ghost home or the starting position
								   of the slime (or ghost)


  DESCRIPTION

		  This function is responsible for resetting all the variables that change as the slime character moves throught the maze back to their original
		  values
  RETURNS

		  Returns void


  */
  /**/

void Green::reset(const Position& home)
{
	m_movement_mode = "chase";
	m_use_door = true;
	m_direction = 0;
	m_frightened = 0;
	m_frightened_speed_timer = 0;
	m_home = home;
	m_target = m_door;
	m_animation_timer = 0;
};

/**/
/*

NAME

		void Green::draw(sf::RenderWindow& window)

SYNOPSIS

		void Green::draw(sf::RenderWindow& window)
			window            --> is the sfml window that is responsible for displaying the gui


DESCRIPTION

		This function draws the blue slime using the sfml library and outputs the image into the window in the main program

RETURNS

		Returns void

REFERNCES
		https://gamefromscratch.com/sfml-c-tutorial-spritesheets-and-animation/
		https://stackoverflow.com/questions/52655335/animating-sprites-in-sfml-from-a-sprite-sheet
		https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1RectangleShape.php
*/
/**/

void Green::draw(sf::RenderWindow& window)
{
	//draws ghosts as retangles
	//https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1RectangleShape.php
	// width and height as a Vector2f
	//sf::RectangleShape ghost_body(sf::Vector2f(g_CELL_SIZE, g_CELL_SIZE));



	unsigned char body_frame = static_cast<unsigned char>(floor(m_animation_timer / static_cast<float>(4)));

	sf::Sprite body;
	sf::Sprite face;

	sf::Texture texture;
	texture.loadFromFile("green.png");
	sf::Texture scared;
	scared.loadFromFile("frightened.png");


	body.setPosition(m_position.x, m_position.y);

	body.setTextureRect(sf::IntRect(g_CELL_SIZE * body_frame, 0, g_CELL_SIZE, g_CELL_SIZE));



	if (m_frightened == false) {
		body.setTexture(texture);
		window.draw(body);
	}
	else {

		body.setTexture(scared);
		window.draw(body);
	}

	m_animation_timer = (1 + m_animation_timer) % (6 * 4);

}

/**/
/*

NAME

		void Green::ghost_movement(std::array<std::array<Cell, g_MAP_HEIGHT>, g_MAP_WIDTH>& map, Pacman& pacman, int floor)

SYNOPSIS

		ghost_movement(std::array<std::array<Cell, g_MAP_HEIGHT>, g_MAP_WIDTH>& map, Pacman& pacman, int floor)
			map            --> is an array of size 21 (g_MAP_WIDTH) of arrays of CELL(enum values holding the map elemnts) of size 23 (g_MAP_HEIGHT).
								 this holds the elements of the map that is used to convert the string text value of the map into the gui image using the SFML library
			pacman			 --> is used the hold the and change the class object Pacman
			floor			 --> is used to hold the value of which map or floor and is used to pass to the function that is called within this function to calculate the new target tile in scatter mode
DESCRIPTION

		This function controls the blue slimes movement by checking if the computed target tile

RETURNS

		Returns void

REFERENCES
		https://gameinternals.com/understanding-pac-man-ghost-behavior
		https://www.youtube.com/watch?v=ZXnK0vlSJV8
		https://www.youtube.com/watch?v=vC0d1rDmPBs


*/
/**/
void Green::ghost_movement(std::array<std::array<Cell, g_MAP_HEIGHT>, g_MAP_WIDTH>& map, Pacman& pacman, int floor) {
	//stores whether or not movement is possible
	//represents how many possible moves there are up to 4
	bool move = false;

	//used to increase the speed of the original slime speed
	int possible_moves = 0;

	//used to check if there is a wall in the four coordinate positions
	int speed = m_slime_speed;

	//used to check if there is a wall in the four coordinate positions
	array<bool, 4> walls{};



	//checks to see if the slimes should enter frightened mode
	if (m_frightened == false && pacman.get_energizer_timer() == (216 / pow(2, 1))) { //this must be the same as the one in pacman
		m_frightened_speed_timer = 3;
		m_frightened = true;

		pacman.setEnergized(false);
	}
	else if (m_frightened == true && pacman.get_energizer_timer() == 0) {
		m_frightened = false;
		m_collision.setEnergized(false);

	}
	else if (pacman.get_energizer_timer() > 0 && pacman.get_energizer_timer() >= (216 / pow(2, floor))) {
		pacman.set_energizer_timer(pacman.get_energizer_timer() - 1);
	}

	//computes the target tile for the slime using the function
	new_target(pacman.get_direction(), pacman.get_position(), floor);

	//checks the four directions to see if there is a wall or values move
	walls[0] = m_collision.map_collision(false, m_use_door, speed + m_position.x, m_position.y, map);
	walls[1] = m_collision.map_collision(false, m_use_door, m_position.x, m_position.y - speed, map);
	walls[2] = m_collision.map_collision(false, m_use_door, m_position.x - speed, m_position.y, map);
	walls[3] = m_collision.map_collision(false, m_use_door, m_position.x, speed + m_position.y, map);

	//computes the optimal direction
	if (m_frightened == false) {
		//this is because the slimes are limited to only four directions
		int optimal_direction = 4;


		//checks to see if there is a possible move
		for (int i = 0; i < 4; i++) {
			if (i == (2 + m_direction) % 4) {
				continue;
			}
			else if (false == walls[i]) {
				if (4 == optimal_direction) {
					optimal_direction = i;
				}


				if (get_target_distance(i) < get_target_distance(optimal_direction)) {
					optimal_direction = i;
				}
				possible_moves++;
			}
		}

		//since the slimes cannot move backwards and can only move in three direction it prioritzes moving the the best move if there is more than 1 possible move
		if (1 < possible_moves)
		{
			m_direction = optimal_direction;

		}
		else {
			//otherwise it just tries to move
			if (4 == optimal_direction) {
				m_direction = (2 + m_direction) % 4;
			}
			else
			{
				//will try to move randomly
				int new_direction = rand() % 4;
				cout << new_direction << endl;

				if (0 == walls[new_direction] && new_direction != (2 + m_direction) % 4) {
					m_direction = new_direction;
				}
			}

		}
	}
	else {
		//if the slime is in frightend mode the movements will be random
		int random_direction = rand() % 4;

		if (0 == m_frightened_speed_timer) {

			m_frightened_speed_timer = 3;

			//it will check to see if a possible move is available 
			for (int i = 0; i < 4; i++) {
				if (i == (2 + m_direction) % 4) {
					continue;
				}
				else if (false == walls[i]) {
					possible_moves++;
				}
			}
			//if there is a possible move it will tru to move in the direction 
			if (0 < possible_moves) {
				while (true == walls[random_direction] || random_direction == (2 + m_direction) % 4) {
					random_direction = rand() % 4;
				}
				m_direction = random_direction;
			}
			else {
				m_direction = (2 + m_direction) % 4;
			}
		}
		else {
			m_frightened_speed_timer--;
		}
	}

	//if there isn't a wall the position of the slime is changes (this is same as in the pacman function)
	if (false == walls[m_direction])
	{
		switch (m_direction)
		{
		case 0:
		{
			m_position.x += speed;

			break;
		}
		case 1:
		{
			m_position.y -= speed;

			break;
		}
		case 2:
		{
			m_position.x -= speed;

			break;
		}
		case 3:
		{
			m_position.y += speed;
		}
		default:
		{
			
		}
		}

		if (-g_CELL_SIZE >= m_position.x)
		{
			m_position.x = g_CELL_SIZE * g_MAP_WIDTH - speed;
		}
		else if (m_position.x >= g_CELL_SIZE * g_MAP_WIDTH)
		{
			m_position.x = speed - g_CELL_SIZE;
		}

		if (-g_CELL_SIZE >= m_position.y)
		{
			m_position.y = g_CELL_SIZE * g_MAP_WIDTH - speed;
		}
		else if (m_position.y >= g_CELL_SIZE * g_MAP_WIDTH)
		{
			m_position.y = speed - g_CELL_SIZE;
		}

	}
	//checks to see if the slime collided with pacman
	if (1 == pacman_collision(pacman.get_position()))
	{
		if (m_frightened == false) {
			pacman.set_dead(true);
		}
		else {
			m_use_door = true;

			m_target = m_home;
		}

	}
};

/**/
/*

NAME

		void Green::new_target(int pacman_direction, const Position& pacman_position, int floor)

SYNOPSIS

		new_target(int i_pacman_direction, const Position& i_pacman_position, int floor)
			pacman_direction            --> is the sfml window that is responsible for displaying the gui
			pacman_position			  --> the x and y coordinate location of pacman
			floor						  --> represents which maze map is currently being used and changes the target tile accordingly in scatter mode

DESCRIPTION

		This function changes the target tile of the blue slime depending on the movement mode and the floor or maze map

RETURNS

		Returns void

REFERENCES
		https://gameinternals.com/understanding-pac-man-ghost-behavior
		https://www.youtube.com/watch?v=ZXnK0vlSJV8
		https://www.youtube.com/watch?v=vC0d1rDmPBs
*/
/**/

void Green::new_target(int pacman_direction, const Position& pacman_position, int floor) {
	//targets the door if was eaten in frightened mode and helps the slimes to exit faster
	if (m_use_door == true) {
		if (m_position == m_target) {
			if (m_door == m_target) {
				m_use_door = false;

			}
			else if (m_home == m_target) {
				m_frightened = false;

				m_target = m_door;
			}
		}

	}
	else if ("scatter" == m_movement_mode) //The scatter mode
	{
		//switches the target tile to a tile out side of the window range and it changes depending on floor
		//0,320

		switch (floor)
		{
		case 0:
		{
			m_target = { g_CELL_SIZE * 0, g_CELL_SIZE * (g_MAP_HEIGHT - 1) };
			break;
		}
		case 1:
		{
			m_target = { g_CELL_SIZE * 0, g_CELL_SIZE * (g_MAP_HEIGHT - 1) };
		}
		case 2:
		{
			m_target = { g_CELL_SIZE * (g_MAP_WIDTH + 4), g_CELL_SIZE * (g_MAP_HEIGHT - 7) };
			break;
		}
		case 3:
		{
			m_target = m_target = { g_CELL_SIZE * 0, g_CELL_SIZE * (g_MAP_HEIGHT - 8) };
			break;
		}
		case 4:
		{
			m_target = { g_CELL_SIZE * 0, g_CELL_SIZE * (g_MAP_HEIGHT - 1) };
			break;
		}
		default:
		{
			cout << "invalid floor" << endl;
		}
		}



	}
	else if ("chase" == m_movement_mode)//The chase mode
	{
		//the green slime is basically the orange ghost a
		//it will chase pacman when it is 6 tiles away so similar to the red slimes' movement
		//but when it gets close to pacman it will switch to scatter mode
		if (g_CELL_SIZE * 6 <= sqrt(pow(m_position.x - pacman_position.x, 2) + pow(m_position.y - pacman_position.y, 2))) {
			m_target = pacman_position;

		}
		else {
			switch (floor)
			{
			case 0:
			{
				m_target = { g_CELL_SIZE * 0, g_CELL_SIZE * (g_MAP_HEIGHT - 1) };
				break;
			}
			case 1:
			{
				m_target = { g_CELL_SIZE * 0, g_CELL_SIZE * (g_MAP_HEIGHT - 1) };
			}
			case 2:
			{
				m_target = { g_CELL_SIZE * (g_MAP_WIDTH + 4), g_CELL_SIZE * (g_MAP_HEIGHT - 7) };
				break;
			}
			case 3:
			{
				m_target = m_target = { g_CELL_SIZE * 0, g_CELL_SIZE * (g_MAP_HEIGHT - 8) };
				break;
			}
			case 4:
			{
				m_target = { g_CELL_SIZE * 0, g_CELL_SIZE * (g_MAP_HEIGHT - 1) };
				break;
			}
			default:
			{
				cout << "invalid floor" << endl;
			}
			}

		}

	}
};