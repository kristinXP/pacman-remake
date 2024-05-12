//
// This Header hold global variables and structures as well as inclusions
//

#pragma once

#include <iostream>
#include <string>
# include <vector>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <ctime>
#include <array>
#include <vector>
#include <cmath>
#include <SFML/Audio.hpp>

using namespace std;


//this represent each square of the grid or cell of the SFML gui windo
constexpr unsigned char g_CELL_SIZE = 20;		//each cell is a 20X20 pixel square

//this represents the height of the window so (23x20 pixels in height)
constexpr unsigned char g_MAP_HEIGHT = 23;

//represents the width of the window so (21x20 pixels wide)
constexpr unsigned char g_MAP_WIDTH = 21;



//used to define and organize the map array elements into their appropriate gui image counterparts
enum Cell
{
	Empty,		// nothing
	Wall,		// a wall will be created
	Pellet,		// the pellets or dots the character collects (10 pts each)
	PowerUp,	//	the potion bottle or energizer that changes the slimes to frightened
	Door,		// the entrace position for the slimes to leave the starting position (except for red)
	Map,		// the position where the map is
	
};

//used to store the x and y numerical coordinate values for convinece
struct Position
{
	int x;		//the x coordinate of an object
	int y;		//the y coordinate of an object

	//overloads the == so that it can make a comparision with the position object
	bool operator==(const Position& i_position)
	{
		//returns true if inputted position and the position it is being compared to x and y are the same
		return this->x == i_position.x && this->y == i_position.y;
	}
};

