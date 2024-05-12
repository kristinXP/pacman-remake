#include "collision_checking.h"

/**/
 /*

 NAME

		 bool Collision::map_collision(bool collect_pellets, bool useDoor, int x, int y, array<array<Cell, g_MAP_HEIGHT>, g_MAP_WIDTH>& map)

 SYNOPSIS

		 map_collision(bool collect_pellets, bool useDoor,  int x, int y, array<array<Cell, g_MAP_HEIGHT>, g_MAP_WIDTH>& map)
			collect_pellets            --> represents where it is pacman or the slimes the purpose is to prevent the slimes from removing the pellets from the map
			useDoor					   --> helps the slimes leave the starting position faster
			x						   --> represents the x direction of the intended position 
			y						   --> represents the y direction of the intended position
			map					   --> is an array of size 21 (g_MAP_WIDTH) of arrays of CELL(enum values holding the map elemnts) of size 23 (g_MAP_HEIGHT). 
										   this holds the elements of the map that is used to convert the string text value of the map into the gui image using the SFML library

 DESCRIPTION

		 This function is responsible for checking if the character next movement is valid or not and prevents the characters from making any illegal moves outside the bounds of the map
 RETURNS

		 Returns a boolean representing if the intended move position is a wall or not


 */
 /**/
bool Collision::map_collision(bool collect_pellets, bool useDoor, int x, int y, array<array<Cell, g_MAP_HEIGHT>, g_MAP_WIDTH>& map) {
	
	//initalizes the output of the function to false
	bool output = false;

	//exact position
	float cell_x = x / static_cast<float>(g_CELL_SIZE);
	float cell_y = y / static_cast<float>(g_CELL_SIZE);

	//Pacman can intersect 4 cells
	for (int a = 0; a < 4; a++)
	{
		int x = 0;
		int y = 0;

		switch (a)
		{
		case 0: //Top left cell
		{
			x = static_cast<int>(floor(cell_x));
			y = static_cast<int>(floor(cell_y));

			break;
		}
		case 1: //Top right cell
		{
			x = static_cast<int>(ceil(cell_x));
			y = static_cast<int>(floor(cell_y));

			break;
		}
		case 2: //Bottom left cell
		{
			x = static_cast<int>(floor(cell_x));
			y = static_cast<int>(ceil(cell_y));

			break;
		}
		case 3: //Bottom right cell
		{
			x = static_cast<int>(ceil(cell_x));
			y = static_cast<int>(ceil(cell_y));
			break;
		}
		default:
		{
			cout << "invalid: out of bounds" << endl;
		}
	
		}

		//checks to see if slimes collided with something
		if (0 <= x && 0 <= y && g_MAP_HEIGHT > y && g_MAP_WIDTH > x) {
			if (false == collect_pellets) {

				if (Cell::Wall == map[x][y])
				{
					output = true;
				}
				else if (useDoor == false && Cell::Door == map[x][y]) {
					output = true;
				}
			}
			else {
				//checks to see if pacman collided with something
				if (Cell::PowerUp == map[x][y]) {

					output = true;
					m_energized = true;
					m_floor_pellet_score += 50;

					//removes the map item from the maze
					map[x][y] = Cell::Empty;
				}
				else if (Cell::Wall == map[x][y] || Cell::Door == map[x][y])		//pacman can not enter the ghost house so it is treated as a wall
				{
					output = true;
				}
				else if (Cell::Pellet == map[x][y] && collect_pellets == true) {		//when pellet is collect it is removed from map
					map[x][y] = Cell::Empty;

					m_floor_pellet_score += 10;
				}
				else if (Cell::Map == map[x][y]) {		//if the map is collect can move to the next floor
					m_next_floor = true;
				}
			}

		}

	}

	return output;
};