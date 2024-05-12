//
// Class to provide collision checking
//

#pragma once
#include "stdafx.h"

/*
* REFERENCES
*		https://www.youtube.com/watch?v=l2iCYCLi6MU
*		https://www.youtube.com/watch?v=C_ZStbJx5uU
*/

//AABB Collision checking
//access aligned bounding boxes
//1. needs center position 
//2. need half size 
//3. delta of center of shapes
//4. take the absolute value of delta and subtract both half sizes if positive outside if negative inside (intersect)

class Collision{
public:


	// to set the score used to carry over score from previous cleared floor
	void setFloorPelletScore(int x) {
		m_floor_pellet_score = x;
	}

	// to access score
	int getFloorPelletScore() {
		return m_floor_pellet_score;
	}
	

	//checks to see if the intended move is valid or not
	bool map_collision(bool collect_pellets, bool useDoor, int x, int y, array<array<Cell, g_MAP_HEIGHT>, g_MAP_WIDTH>& map);

	//sets the whether or not energizer or potion was collected
	void setEnergized(bool e) {
		m_energized = e;
	};

	//to access whether a potion (energizer) was collected
	bool getEnergized() {
		return m_energized;
	};

	//to access whether or not proceed to the next floor or map
	bool getNextFloor() {
		return m_next_floor;
	}

	//resets next floor boolean back to orignal value
	void resetNextFloor() { m_next_floor = false; };

private:
	int m_floor_pellet_score = 0;			//the numerical value of the total score of the pellets collected
	bool m_energized = false;				// == true if a potion or energizer was collected
	bool m_next_floor = false;			// == true to proceed to the next floor
};