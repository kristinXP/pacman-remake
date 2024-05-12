/*
 * Class derived from the Slimes class that is responsible for the Blue Slimes movement and actions
 */

#pragma once
#include "stdafx.h"
#include "collision_checking.h"
#include "Pacman.h"
#include "slimes.h"
#include "red.h"

class Blue : public Slimes
{
public:

	Blue() {

		m_use_door = true;
		m_movement_mode = "scatter";
		m_position = { 0,0 };
		m_frightened = false;
	};

	//resets all of the variables back to their orginal values
	void reset(const Position& home);
	
	//outputs the sprite of the blue slime into the GUI window
	void draw(sf::RenderWindow& window);
	
	//controls the movement of the Blue Slime 
	void ghost_movement(std::array<std::array<Cell, g_MAP_HEIGHT>, g_MAP_WIDTH>& map, Pacman& pacman, Red& red, int floor); 
	
	//computes the target tile or the intended position that the slime should move to
	void new_target(int pacman_direction, const Position& pacman_position, const Position& red, int floor); 
};