/*
 * Class derived from the Slimes class that is responsible for the green Slimes movement and actions
 */

#pragma once
#include "stdafx.h"
#include "collision_checking.h"
#include "Pacman.h"
#include "slimes.h"

class Green : public Slimes
{
public:

	Green() {

		m_use_door = true;
		m_movement_mode = "scatter";
		m_position = { 0,0 };
		m_frightened = false;
	};

	//resets all of the variables back to their orginal values
	void reset(const Position& home);
	
	//outputs the sprite of the green slime into the GUI window
	void draw(sf::RenderWindow& window);

	//controls the movement of the Slime 
	void ghost_movement(std::array<std::array<Cell, g_MAP_HEIGHT>, g_MAP_WIDTH>& map, Pacman& pacman, int floor);

	//computes the target tile or the intended position that the slime should move to
	void new_target(int pacman_direction, const Position& pacman_position, int floor);
};