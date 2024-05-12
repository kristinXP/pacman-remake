//
// Class convert and draw the map elements in the SFML GUI
//

#pragma once
#include "stdafx.h"
#include "Pacman.h"



class DrawMap{
public:

	//draws all the elements as their appropriate sprite images into the GUI
	void draw_map(const array<array<Cell, g_MAP_HEIGHT>, g_MAP_WIDTH>& map, sf::RenderWindow& window);

	//if the threshold score for the associated floor is reached than the designated wall will be changed to a sprite of a map and can be collected by the character
	void unlock_map(array<array<Cell, g_MAP_HEIGHT>, g_MAP_WIDTH>& map, bool map_key);

	//loops through the map sketch array and assigns the appropriate enum value to it and stores the position of the door, pacman, and the slimes, the map  
	array<array<Cell, g_MAP_HEIGHT>, g_MAP_WIDTH> convert_sketch(const array<string, g_MAP_HEIGHT>& map_sketch, Pacman& pacman, array<Position, 4>& ghost_positions, Position& door);

	

private:
	Position Kmap;		//Used to hold the position of the map sprite
	
};