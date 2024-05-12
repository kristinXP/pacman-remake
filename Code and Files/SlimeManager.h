//
// Class that manages the four different slime colors and links their timers and movement modes together
//


/*
* REFERENCES
*		https://gameinternals.com/understanding-pac-man-ghost-behavior
*/


#pragma once
#include "stdafx.h"
#include "red.h"
#include "Pacman.h"
#include "purple.h"
#include "green.h"
#include "blue.h"

class Manager {
public:
	Manager() :m_current_wave(0), m_wave_timer(m_scatter_duration) {};

	//outputs the sprite of the slimes into the GUI window
	void draw_ghosts(sf::RenderWindow& window) {
		
		red.draw(window);
		purple.draw(window);
		blue.draw(window);
		green.draw(window);
	};

	//resets the initial values and position of the slimes according to the specific map
	void reset_position(const array<Position, 4>& ghost_position, const Position& door) {

		//the game starts with the slimes in scatter mode
		//sets the wave timer equal to the how long the scatter mode should last
		m_wave_timer = static_cast<unsigned int>(m_scatter_duration / pow(2, 1));
		
		//sets the door postion for all four slimes
		red.setDoorPosition(door);
		purple.setDoorPosition(door);
		blue.setDoorPosition(door);
		green.setDoorPosition(door);

		//sets the initial start positions for all four slimes
		red.set_position(ghost_position[0].x, ghost_position[0].y);
		purple.set_position(ghost_position[1].x, ghost_position[1].y);
		blue.set_position(ghost_position[2].x, ghost_position[2].y);
		green.set_position(ghost_position[3].x, ghost_position[3].y);

		//sets the resest values for all four slimes
		red.reset(purple.get_position());
		purple.reset(purple.get_position());
		blue.reset(purple.get_position());
		green.reset(purple.get_position());
	};

	//updates the slimes movement, movement mode, and timers
	void update(array<std::array<Cell, g_MAP_HEIGHT>, g_MAP_WIDTH>& map, Pacman& pacman, int floor)
	{
		//if the wave_timer is == to zero it checks to see if the movement mode should be switched
		if (0 == m_wave_timer)
		{
			//the original pacman game is made in 3 cycles or waves of scatter then chase before permanently switching to chase mode
			//if the 3 cycles have yet to be complete it will switch the movement mode
			if (7 > m_current_wave)
			{
				//switches movement mode of the four slimes to scatter
				if (red.getMode() == "chase") {
					red.switch_mode("scatter");
					purple.switch_mode("scatter");
					blue.switch_mode("scatter");
					green.switch_mode("scatter");


				}
				else {
					//switches the movement mode of the four slimes to chase
					red.switch_mode("chase");
					purple.switch_mode("chase");
					blue.switch_mode("chase");
					green.switch_mode("chase");

				}

				//increments the current wave counter that keeps track of the cycles (current wave/2)
				m_current_wave++;

			}

			//if the current wave timer is odd it will use the chase timer duration
			if (1 == m_current_wave % 2)
			{
				m_wave_timer = m_chase_duration;
			}
			else if (0 == m_current_wave %2) //if the current timer isevern it will use the scatter mode time duration
			{
				m_wave_timer = m_scatter_duration;
			}

			//if the wave timer is 7 it will reset and cycle through the again
			if (m_current_wave == 7) {
				m_current_wave = 0;
			}
			
		}
		else
		{
			m_wave_timer--;
		}
		
		red.ghost_movement(map, pacman, floor);
		purple.ghost_movement(map, pacman, floor);
		blue.ghost_movement(map, pacman, red, floor);
		green.ghost_movement(map, pacman, floor);

	
	};


private:
	int m_current_wave;		//numerical value associated with keeping track of when to switch the value of the wave timer 
	int m_wave_timer;			//numerical value associated with keeping trakc of how long each movement mode lasts
	Red red;				//Red object
	Purple purple;			//Purple object
	Blue blue;				//Blue object
	Green green;			//Green object

	//they are measured in terms of frames
	const unsigned int m_chase_duration = 300;		//numerical value that represents the duration of how long the chase mode lasts
	const int m_scatter_duration = 150;				//numerical value that represents the duration of how long the scatter mode lasts

};
