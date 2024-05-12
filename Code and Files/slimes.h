//
// Base Class for the four slimes and contains all the function that involves controlling their movement and stuff
//

#pragma once
#include "stdafx.h"
#include "collision_checking.h"

class Slimes
{
public:

	//used to change the initial door position or the x and y coordinates of the door for the different floors
	void setDoorPosition(Position x) { m_door = x; };

	//checks to see if the slimes intercepted with pacman's or main character's position
	bool pacman_collision(const Position& pacman_position)
	{
		//pacman or the main character is a 20x20 pixel square it checks the x and y coordinates on both sides with a tolerance of 10 pixels because of the sprite size
		if (m_position.x > pacman_position.x -(g_CELL_SIZE/2) && m_position.x < (g_CELL_SIZE/2) + pacman_position.x)
		{
			if (m_position.y > pacman_position.y - (g_CELL_SIZE/2) && m_position.y < (g_CELL_SIZE/2) + pacman_position.y)
			{
				return true;
			}
		}

		return false;
	}

	//to access the slime's position or x and y coordinates
	Position get_position() {
		return m_position;
	};

	
	//to access the direction of the slime
	unsigned char get_direction()
	{
		return m_direction;
	};

	//to get the target distance
	double get_target_distance(int direction) {
		int x = m_position.x;
		int y = m_position.y;

		//calculates the intended direction of the slime 
		switch (direction) {
		case 0:
		{
			x += m_slime_speed;
			break;
		}
		case 1: {
			y -= m_slime_speed;
			break;
		}
		case 2:
		{
			x -= m_slime_speed;
			break;
		}
		case 3:
		{
			y += m_slime_speed;
			break;
		}
		default:
		{
			cout << "Invalid Direction " << endl;
		}
		}

		//uses distance formula d = sqrt((x2-x1)^2 + (y2-y1)^2) to calculate target
		return static_cast<float>(sqrt(pow(x - m_target.x, 2) + pow(y - m_target.y, 2)));
	};

	
	//to access the movement mode of the slimes (chase or scatter)
	string getMode() {
		return m_movement_mode;
	};

	//used to set the position of the slimes
	void set_position(int x, int y) {
		m_position = { x, y };
	};

	//used to switch or set the movement mode (scatter or chase)
	void switch_mode(string mode) { //can either be chase or scatter
		m_movement_mode = mode;
	};



protected:
	Position m_position;			//Position object used to store the x and y coordinates of the slimes
	string m_movement_mode;		//used to store the movement mode (chase or scatter)
	bool m_frightened;			// == true the slimes will be in frightened mode which causes the slimes to act more randomly and the sprites to turn dark blue
	int m_direction = 0;			//numerical value that is used to increment or deincrement the x and y coordinates of the slimes to move them in the appropriate direction
	static const int m_slime_speed = 2;			//numerical value that represents the slimes speed
	Position m_target;			//Position object that represents the slimes intended location that the slimes will attempt to move to
	Position m_home;				//Position object that represents the x and y coordinates of the starting position of the slimes (excluding red)
	Collision m_collision;				//object of the Collision class
	int m_frightened_speed_timer;			//numerical value represents the duration of the frightened mode
	bool m_use_door;						// == true slimes will target the door
	unsigned int m_animation_timer;		//numerical value that represents the duration of the animation frames for the slime sprite sheet
	Position m_door;			//Position object that holds the x and y coordinates of the door
};