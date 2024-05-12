//
// Class that controlls all things related to pacman or the main character
//

#pragma once
#include "stdafx.h"
#include "collision_checking.h"

class Pacman
{
public:

	Pacman():m_position({ 0, 0 }),m_dead(false),m_direction(0),m_animation_timer(0), m_energizer_timer(0)
	{};

	
	//draws the main character into the gui window
	void draw(sf::RenderWindow& window, int character_selection);

	//to access whether or not the main character is died and game over
	bool isDead() {
		return m_dead;
	}

	//used to set and update the main characters position
	void set_position(int x, int y) {
		m_position = { x, y };
	};

	//to access the main character's position
	Position get_position() {
		return m_position;
	};

	//to get the direction of the main character which is used to increment the x and y position coordinates
	int get_direction()
	{
		return m_direction;
	};

	//to access the score from the collision class and pass it to main program
	int floorPelletScore() {
		return m_collision.getFloorPelletScore();
	};

	//to change the score in the collision class to the value in main (used to pass the score from the previous cleared floor to the next floor)
	void setFloorPelletScore(int r) {
		m_collision.setFloorPelletScore(r);
	};

	//to access the energizer timer 
	unsigned get_energizer_timer() {
		return m_energizer_timer;
	};

	//to acces the next floor boolean in the collision class and pass the information to main program
	bool getNext_Floor() {
		return m_collision.getNextFloor();
	};

	//used to act as a middle man between the collision class and the main program to reset the boolean value in the collision class back to it's original value 
	void resetNextFloor() { m_collision.resetNextFloor();};

	//the collision checking response to see if the intended move is valid or not
	void update(array<array<Cell, g_MAP_HEIGHT>, g_MAP_WIDTH>& map, int floor);

	//resets main character's values
	void reset() {
		m_dead = false;
		m_direction = 0;
	};

	//to change the main character's dead status and indicate whether or not to prompt game over
	void set_dead(bool current_state) {
		m_dead = current_state;
	};

	//used to change the energizer timer
	void set_energizer_timer(unsigned int t) { m_energizer_timer = t; };

	//used to set the energized or potion boolean
	void setEnergized(bool e) { m_energized = e; };
	
	//to access whether or not main character is in energized state (or collected potion)
	bool getEnergized() { return m_energized; };

private:
	Position m_position;			//Position object (x and y coordinates of main character)
	int m_direction = 0;			//numerical value used to change the x and y coordinate values
	const int m_speed = 2;		//speed of the main character 
	Collision m_collision;				//Collision object 
	bool m_dead;					// == true main character is dead game over
	bool m_energized = false;		// == true main character is temporarily involunerable to the ghosts
	unsigned int m_energizer_timer;		//numerical value used to measure how long the involunerable phase lasts
	unsigned int m_animation_timer;		//numerical value used to measure and keep track of the pictures on the sprite sheet
	
};