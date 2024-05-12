//
// Class that controlls the pause feature of the game
//

/*
* REFERENECES
*		https://www.youtube.com/watch?v=knoQ-TEFivE
*		https://www.youtube.com/watch?v=JxPZHEHXOGI
*/

#pragma once
#include "stdafx.h"
#include <memory>

class PauseGame
{
public:
	PauseGame() :m_pauseGame(false){};

	//to access the pause status
	bool getPauseGame() const {
		return m_pauseGame;
	};

	//to switch the pause status
	void toggle() {
		m_pauseGame = m_pauseGame? false : true;
	};

private:
	bool m_pauseGame;		// == true game is paused and all movement of character (exluding animation sequence) is freezed 
};
