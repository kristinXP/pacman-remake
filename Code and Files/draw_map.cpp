/*
 * DrawMap - Draws the map and converts the map into the appropriate value to be converted by the SFML library
 */
#include "draw_map.h"


 /**/
 /*

 NAME

		 void DrawMap::draw_map(const array<array<Cell, g_MAP_HEIGHT>, g_MAP_WIDTH>& map, sf::RenderWindow& window)

 SYNOPSIS

		 draw_map(const array<array<Cell, g_MAP_HEIGHT>, g_MAP_WIDTH>& map, sf::RenderWindow& window)
			map            --> is an array of size 21 (g_MAP_WIDTH) of arrays of CELL(enum values holding the map elemnts) of size 23 (g_MAP_HEIGHT). 
								 this holds the elements of the map that is used to convert the string text value of the map into the gui image using the SFML library
			window            --> is the sfml window that is responsible for displaying the gui


 DESCRIPTION

		 This function is responsible for drawing all of the elements like the pellets (circles) and walls (rectangles) and sprites on the SFML GUI interface
 RETURNS

		 Returns void

REFERENCES
		https://www.youtube.com/watch?v=_RLFI1D99Ow
		https://www.youtube.com/watch?v=ZXnK0vlSJV8
		https://www.youtube.com/watch?v=vC0d1rDmPBs
		https://www.youtube.com/watch?v=h8LtwbS-1p0
 */
 /**/
void DrawMap::draw_map(const array<array<Cell, g_MAP_HEIGHT>, g_MAP_WIDTH>& map, sf::RenderWindow& window)
{
	
	//rectangleshape creates a rectangle 
	//vector2f takes a width and a height the f is a type float 
	sf::RectangleShape cell_shape(sf::Vector2f(g_CELL_SIZE, g_CELL_SIZE));
	
	//CircleShapee creates a circle
	sf::CircleShape circle_shape;
	circle_shape.setFillColor(sf::Color(255, 182, 170));

	for (unsigned char a = 0; a < g_MAP_WIDTH; a++)
	{
		for (unsigned char b = 0; b < g_MAP_HEIGHT; b++)
		{

			switch (map[a][b])
			{
			case Cell::Wall:
			{
				cell_shape.setFillColor(sf::Color(131, 67, 51));		//can change the color takes rbg color code
				cell_shape.setPosition(g_CELL_SIZE * a, g_CELL_SIZE * b);
				window.draw(cell_shape); 
				break;

			}
			case Cell::Pellet:
			{
				circle_shape.setRadius(g_CELL_SIZE / 8);
				circle_shape.setPosition(g_CELL_SIZE * a + (g_CELL_SIZE / 2 - circle_shape.getRadius()), g_CELL_SIZE * b + (g_CELL_SIZE / 2 - circle_shape.getRadius()));
				window.draw(circle_shape);
				break;
			}
			case Cell::PowerUp:
			{
				sf::Sprite potion;
				sf::Texture potion_texture;

				potion.setPosition(g_CELL_SIZE * a, g_CELL_SIZE * b);
				potion_texture.loadFromFile("potion_sprite.png");

				potion.setTexture(potion_texture);

				window.draw(potion);

				break;

			}
			case Cell::Map:
			{
				sf::Sprite sprite;

				sf::Texture texture;

				sprite.setPosition(g_CELL_SIZE * a, g_CELL_SIZE * b);


				texture.loadFromFile("pixelart map.png");

				sprite.setTexture(texture);


				window.draw(sprite);

				break;
			}
			default:
			{

			}


			}


		}
	}
}


/**/
/*

NAME

		void DrawMap::unlock_map(array<array<Cell, g_MAP_HEIGHT>, g_MAP_WIDTH>& map, bool map_key) 

SYNOPSIS

		void DrawMap::unlock_map(array<array<Cell, g_MAP_HEIGHT>, g_MAP_WIDTH>& map, bool map_key) 
		   map            --> is an array of size 21 (g_MAP_WIDTH) of arrays of CELL(enum values holding the map elemnts) of size 23 (g_MAP_HEIGHT).
								this holds the elements of the map that is used to convert the string text value of the map into the gui image using the SFML library
		   map_key          --> a boolean used to keeps track whether or not one of the designated walls should be changed into an interactable map if a certain score defined in main is reached


DESCRIPTION

		This function is responsible for checking whether or not on of the designated walls should be changed into an interactable map
RETURNS

		Returns void


*/
/**/
void DrawMap::unlock_map(array<array<Cell, g_MAP_HEIGHT>, g_MAP_WIDTH>& map, bool map_key) {
	if (map_key == true) {
		map[Kmap.x][Kmap.y] = Cell::Map;
	}
}

//loops through the map and finds all the walls and pacman
/**/
/*

NAME

		array<array<Cell, g_MAP_HEIGHT>, g_MAP_WIDTH> DrawMap::convert_sketch(const array<string, g_MAP_HEIGHT>& map_sketch, Pacman& pacman, array<Position, 4>& ghost_positions, Position& door)

SYNOPSIS

		convert_sketch(const array<string, g_MAP_HEIGHT>& map_sketch, Pacman& pacman, array<Position, 4>& ghost_positions, Position& door)
		   map_sketch     --> is an array of characters (string) of size 23 (g_MAP_HEIGHT) that holds the map character elements to converted into enum defined values to be converted into the SFML GUI images
								
		   pacman          --> is used the hold the and change the class object Pacman
		   ghost_positions --> is an array of the x and y cooridinates of the four slimes (Position)
		   door				 --> is the x and y coordinates of the door which the slimes use its location to exit the "ghost house" or their starting location easier


DESCRIPTION

		This function is responsible converting the map which is originally an array of strings into an array of array of enum values which will be used to translate it to the appropriate gui image
RETURNS

		Returns array<array<Cell, g_MAP_HEIGHT>, g_MAP_WIDTH> - an array of array of enum values 

REFERENCES
		https://www.youtube.com/watch?v=_RLFI1D99Ow
		https://www.youtube.com/watch?v=ZXnK0vlSJV8
		https://www.youtube.com/watch?v=vC0d1rDmPBs
		https://www.youtube.com/watch?v=h8LtwbS-1p0
*/
/**/
array<array<Cell, g_MAP_HEIGHT>, g_MAP_WIDTH> DrawMap::convert_sketch(const array<string, g_MAP_HEIGHT>& map_sketch, Pacman& pacman, array<Position, 4>& ghost_positions, Position& door) {
	array<array<Cell, g_MAP_HEIGHT>, g_MAP_WIDTH> output_map{};

	//loops throught the map array
	//assigns the appropriate map elements to and in some cases stores the position
	for (unsigned char a = 0; a < g_MAP_HEIGHT; a++) {
		for (unsigned char b = 0; b < g_MAP_WIDTH; b++) {
			switch (map_sketch[a][b]) {

			case '#':		//wall
			{
				output_map[b][a] = Cell::Wall;
				break;
			}
			case 'P':		//pacman's start position
			{
				pacman.set_position(g_CELL_SIZE * b, g_CELL_SIZE * a);
				break;
			}
			case '0':		//red slime's start position
			{
				ghost_positions[0].x = g_CELL_SIZE * b;
				ghost_positions[0].y = g_CELL_SIZE * a;
				break;
			}
			case '1':		//purple slime's start position
			{
				ghost_positions[1].x = g_CELL_SIZE * b;
				ghost_positions[1].y = g_CELL_SIZE * a;
				break;
			}
			case '2':		//blue slime's start position
			{
				ghost_positions[2].x = g_CELL_SIZE * b;
				ghost_positions[2].y = g_CELL_SIZE * a;
				break;
			}
			case '3':			//orange slime's start position
			{
				ghost_positions[3].x = g_CELL_SIZE * b;
				ghost_positions[3].y = g_CELL_SIZE * a;
				break;
			}
			case '.':		//pellets
			{
				output_map[b][a] = Cell::Pellet;
				break;

			}
			case 'e':		//energizers or potions
			{
				output_map[b][a] = Cell::PowerUp;
				break;
			}
			case 'D':			//door
			{
				door.x = g_CELL_SIZE * b;
				door.y = g_CELL_SIZE * a;
				break;
			}
			case 'K':		//map or key to the next floor (it will initially be a wall until a certain score is obtained)
			{
				output_map[b][a] = Cell::Wall;
				Kmap.x = b;
				Kmap.y = a;
				break;

			}
			default:
			{
				output_map[b][a] = Cell::Empty;
			}
			}

		}
	}

	return output_map;

};