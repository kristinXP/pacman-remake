/*
 * pacman game main program. (sfml gui interface)
 */


/*
* REFERENCES FOR LEARNING SFML
*		https://www.sfml-dev.org/tutorials/2.6/graphics-sprite.php
*		https://www.sfml-dev.org/tutorials/2.6/audio-sounds.php
*		https://www.sfml-dev.org/tutorials/2.6/start-vc.php
*		https://www.sfml-dev.org/tutorials/2.6/window-window.php
*		https://www.sfml-dev.org/tutorials/2.6/window-inputs.php
*		https://www.youtube.com/watch?v=Aaf2Y-96nsk
*		https://www.youtube.com/watch?v=_HI6yJ1DFPg
*		https://www.youtube.com/watch?v=4qCwzuFU_vE
*/


#include "stdafx.h"
#include "draw_map.h"
#include "Pacman.h"
#include <sstream>
#include "Pause.h"
#include "menu.h"
#include "CharSelect.h"
#include "Op.h"
#include "GameOverSelection.h"
#include "SlimeManager.h"

void main_game(int char_select, int start, int current_score);
void game_over(int char_select, int current_floor, int previous_score);
void winner(int final_score);
void openning(int char_select);
void character_selection();



//SFML TUTORIAL Series Cite later:
//https://www.youtube.com/watch?v=_HI6yJ1DFPg&list=PL21OsoBLPpMOO6zyVlxZ4S4hwkY_SLRW9&index=3
int main()
{
	
	//initializes the gui window to be displayed
	sf::RenderWindow menu_window(sf::VideoMode(600,600),"Main Menu");

	//creates and initializes the object of Menu
	Menu menu(menu_window.getSize().x,menu_window.getSize().y);
	
	//used to change the window into the instruction menu 
	bool instruct_clicked = false;

	//properties of the main menue
	sf::Font arial;
	arial.loadFromFile("PAC-FONT.ttf");
	std::ostringstream buffer;
	buffer << "Pacman";
	sf::Text title;
	title.setFillColor(sf::Color::Yellow);
	title.setCharacterSize(50);
	title.setPosition({ 150,30 });
	title.setFont(arial);
	title.setString(buffer.str());

	//picture properties for the main menu screen
	sf::Texture texture;
	if (!texture.loadFromFile("start.png"))
		return EXIT_FAILURE;
	sf::Sprite sprite;
	sprite.setTexture(texture);

	while (menu_window.isOpen()) {
		
		sf::Event menu_event;
		
		//listens for an event to happen
		while (menu_window.pollEvent(menu_event)) {
			switch (menu_event.type) {
			case sf::Event::KeyReleased:		//if key is pressed then released
				if (instruct_clicked == false) {		//controls the main menu selections
					switch (menu_event.key.code) {
					case sf::Keyboard::Up:
						menu.MoveUp();
						break;
					case sf::Keyboard::Down:
						menu.MoveDown();
						break;
					case sf::Keyboard::Return:				//if enter is released then it goes into the selected option
						switch (menu.getPressedItem()) {
						case 0:									//proceeds to the character selection function
							menu_window.close();
							//main_game();
							character_selection();
							break;
						case 1:								//signals that the instruction screen should be displayed
							instruct_clicked = true;
							break;
						case 2:
							menu_window.close();				//closes the window
							return 0;
						}
					}
				}
				else {
					switch(menu_event.type)				//waits to for the enter key to be pressed before going back to the main menu;
					case sf::Event::KeyReleased:
						switch (menu_event.key.code) {
						case sf::Keyboard::Enter:
							instruct_clicked = false;
							arial.loadFromFile("PAC-FONT.ttf");
							std::ostringstream buffer;
							buffer << "Pacman";
							sf::Text title;
							title.setFillColor(sf::Color::Yellow);
							title.setCharacterSize(50);
							title.setPosition({ 150,30 });
							title.setFont(arial);
							title.setString(buffer.str());
						}
					break;
				}

				break;
			case sf::Event::Closed:				//closes window if x button is pressed
				menu_window.close();
				break;
			}
		}

		//displays the instructions if instruction option was pressed
		if (instruct_clicked == true) {		
			std::ostringstream buffer1;
			buffer1 << "Instructions: \n\n\nPress enter to progress through the \nstory element of the game and to \nselect options.Use the arrow keys \nto move the character through \nthe maze and to avoid. When the map \nicon appears in the maze it will \nprogress the character to the next \nfloor. The potion bottles will make \nthe character temporarily \ninvoluerable to the slimes. \n\n\nPress enter to go back to main menu.";
			arial.loadFromFile("text.ttf");
			title.setFillColor(sf::Color::Yellow);
			title.setCharacterSize(15);
			title.setPosition({ 10,30 });
			title.setFont(arial);
			title.setString(buffer1.str());
		}
		menu_window.clear();
		menu_window.draw(title);
		
		//displays the main menu selections if instrutions was not selected
		if (instruct_clicked == false) {
			menu_window.draw(sprite);
			menu.draw(menu_window);
		}
		menu_window.display();
	}

	
	
    return 0;
}

/**/
 /*

 NAME

		 void game_over(int char_select, int current_floor, int previous_score)

 SYNOPSIS

		 game_over(int char_select, int current_floor, int previous_score)

			char_select		    --> is the value that holds which character the user selected in the beginning
			current_floor		--> numerical value that hold the current floor or maze map
			previous_score		--> numerical value that hold the score from the previously cleared floor if applicable defualt is 0


 DESCRIPTION

		 This function is responsible for prompting the game over gui window and menu. Asks user to either close game or retry the floor. If user selects retry the function 
		 will go back to the main_game function and if user selects exit game it will close the program.
 RETURNS

		 Returns void


 */
 /**/

void game_over(int char_select, int current_floor, int previous_score) {
	sf::RenderWindow game_over_window(sf::VideoMode(600, 600), "Game Over");
	GameOverSelection over_menu(game_over_window.getSize().x, game_over_window.getSize().y);
	
	//Uses the SFML library to set the font for the displayed text
	sf::Font arial1;
	arial1.loadFromFile("arial.ttf");
	std::ostringstream game_over;

	//text to be displayed
	game_over << "GAME \nOVER";
	sf::Text end;

	//text position, size and color settings
	end.setFillColor(sf::Color::Yellow);
	end.setPosition({ 150, 10 });
	end.setCharacterSize(75);
	end.setFont(arial1);
	end.setString(game_over.str());

	//while the window is open it will listen for an event to happen and then act accordingly 
	while (game_over_window.isOpen()) {
		sf::Event over;
		while (game_over_window.pollEvent(over)) {
			switch (over.type) {
			case sf::Event::KeyReleased:	//listen for a certain key to be pressed and then released
				switch (over.key.code) {
				case sf::Keyboard::Up:		//when up arrow is pressed 
					over_menu.MoveUp();
					break;
				case sf::Keyboard::Down:	//when down arrow is pressed 
					over_menu.MoveDown();
					break;
				case sf::Keyboard::Return:		//when enter is pressed
					switch (over_menu.getPressedItem()) {
					case 0:
						game_over_window.close();
						main_game(char_select, current_floor, previous_score);
						break;
					case 1:
						game_over_window.close();
						break;
					}
				}
				break;
			case sf::Event::Closed:			//if user selects the x button in the right corner window will close
				game_over_window.close();
				break;
			}
		}

		//clears window and refreshes the window to display any changes 
		game_over_window.clear();
		game_over_window.draw(end);
		over_menu.draw(game_over_window);
		game_over_window.display();
	}
}

/**/
 /*

 NAME

		 void winner(int final_score)

 SYNOPSIS

		void winner(int final_score)

			final_score		--> numerical value that hold the total score of the game


 DESCRIPTION

		 This function is responsible for displaying the "WIN" gui window and the total score of the game.
 RETURNS

		 Returns void


 */
 /**/

void winner(int final_score) {

	//creates the "win" gui window
	sf::RenderWindow you_win_window(sf::VideoMode(600, 600), "You Win");

	
	sf::Font winFont;
	winFont.loadFromFile("arial.ttf");
	
	std::ostringstream you_win;
	you_win << "YOU WIN\n\nScore: " << final_score;
	
	//properties of the text that is displayed in the gui window
	sf::Text winText;
	winText.setFillColor(sf::Color::Yellow);
	winText.setPosition({ 150,150 });
	winText.setCharacterSize(75);
	winText.setFont(winFont);
	winText.setString(you_win.str());

	//the window remains open until the user clicks the x button in the right corner
	while (you_win_window.isOpen()) {
		sf::Event over;
		while (you_win_window.pollEvent(over)) {
			switch (over.type) {
			case sf::Event::Closed:		//closes window upon clicking the x button
				you_win_window.close();
				break;
			}
		}

		//displays the text in the gui window
		you_win_window.draw(winText);
		you_win_window.display();
	}
}

/**/
 /*

 NAME

		 void main_game(int char_select, int start, int current_score)

 SYNOPSIS

		main_game(int char_select, int start, int current_score)
			char_select		--> is the value that holds which character the user selected in the beginning
			start			--> numerical value that holds the starting score. the default is 0 
			final_score		--> numerical value that holds the total score of the game


 DESCRIPTION

		 This function is responsible for the main game functions which include updating the window to reflect the main character's and slime's movement, checking to see if the game 
		 was won or loss, displaying the maze map, etc.
 RETURNS

		 Returns void


 */
 /**/

void main_game(int char_select, int start, int current_score) {
	
	//to make the game independent of frame-rate
	unsigned lag = 0;
	

	//screen resize or how big the screen is
	constexpr unsigned char g_SCREEN_RESIZE = 2;

	//the duration of every fame
	constexpr unsigned short g_FRAME_DURATION = 16667;
	
	//represents the current floor (1-5)
	int floor = start;

	//holds the scores that are need in order for the map to appear in the maze to proceed to the next floor
	int next_floor_score[] = { 1100, 2450, 4150, 6250, 8450 };

	//represents the floor iterator (0 -4)
	int i = start;

	//used to check if map used to proceed to the next floor should appear
	bool map_key = false;

	//used to make the game frame rate independent 
	std::chrono::time_point<std::chrono::steady_clock> previous_time;

	//text map sketches of the mazes that will be converted using the SFML library to images
	// all 5 maps are 21 X 23
	//flooor 1
	array<string, g_MAP_HEIGHT> map_sketch_f1 = { 
		"                     ",
		" ################### ",
		" #........#........# ",
		" #e##.###.#.###.##e# ",
		" #.................# ",
		" #.##.#.#####.#.##.# ",
		" #....#...#...#....# ",
		" ####.###.K.###.#### ",
		"    #.#...0...#.#    ",
		"#####.#.##D##.#.#####",
		"     ...#123#...     ",
		"#####.#.#####.#.#####",
		"    #.#.......#.#    ",
		" ####.#.#####.#.#### ",
		" #........#........# ",
		" #.##.###.#.###.##.# ",
		" #e.#.....P.....#.e# ",
		" ##.#.#.#####.#.#.## ",
		" #....#...#...#....# ",
		" #.######.#.######.# ",
		" #.................# ",
		" ################### ",
		"                      "
	}; //total of 173 dots, needs 1100 for map key to progress to the next floor

	//floor 2
	array<string, g_MAP_HEIGHT> map_sketch_f2 = {  
		"      # ##### #      ",
		" ###### ##### ###### ",
		" #....#.#...#.#....# ",
		" #e##.....#.....##e# ",
		" #........#........# ",
		" #.##.#.#####.#.##.# ",
		" #....#.......#....# ",
		" ####.###.P.###.#### ",
		"    #.#.......#.#    ",
		"#####.#.##.##.#.#####",
		"     ...##.##...     ",
		"#####.#.##.##.#.#####",
		"    #.#.......#.#    ",
		" ####.#.#####.#.#### ",
		" #........K........# ",
		" #.##.###.#.###.##.# ",
		" #..#...........#..# ",
		"##..#.#.#####.#.#..##",
		"#.....#...0...#.....#",
		"#.##....##D##....##.#",
		"#e....#.#123#.#....e#",
		"####### ##### #######",
		"      # ##### #       "
	};

	//floor 3
	array<string, g_MAP_HEIGHT> map_sketch_f3 = { 
		"   # #         # #   ",
		" ### ########### ### ",
		" ###.####123####.### ",
		" #e...####D####...e# ",
		" #.##.....0.....##.# ",
		" #.##.#.#####.#.##.# ",
		" #....#...#...#....# ",
		" ####.###.#.###.#### ",
		" #....K.......#....# ",
		"#####.#.#####.#.#####",
		"#...................#",
		"#.###.#.#####.#.###.#",
		"#.....#.......#.....#",
		"#.#.#.#.#####.#.#.#.#",
		"#.........#.........#",
		"##e##.###.#.###.##e##",
		" #.................# ",
		" ####.#..###..#.#### ",
		" ###..#...#...#..### ",
		" #.................# ",
		" #........P........# ",
		" ### ########### ### ",
		"   # #         # #    "
	};

	//floor 4
	array<string, g_MAP_HEIGHT> map_sketch_f4 = { 
		"          ###########",
		" ##########.........#",
		" #........#.#.#.##..#",
		" #e##..K....#......e#",
		" #........#.#.......#",
		" #.##.#.###.#.#.###.#",
		" #..........#.......#",
		"##..#.###...###.#.#.#",
		"#...#.#...P...#.#...#",
		"#.###.#.##.##.#.#####",
		"#.......##.##.....#1#",
		"#.###.#.##.##.#.#0D2#",
		"#.................#3#",
		"####.#..#####.#..####",
		" #.................# ",
		" #.##.###...###.##.# ",
		" #.................# ",
		" #..#.#.#####.#.#..# ",
		" #....#.......#....# ",
		"##.##.....#.....##.##",
		"  ......#.e.#......  ",
		"#####################",
		"                     "
	};

	//floor 5
	array<string, g_MAP_HEIGHT> map_sketch_f5 = { 
		"                # # ",
		"################# ###",
		"#...................#",
		"#e#....##...##....#e#",
		"#.#.##.........##.#.#",
		"#...#####.#.#####...#",
		"#...................#",
		"###.#.##.#.#.##.#.###",
		"#.....#..#.#..#.....#",
		"#.###.#.## ##.#.###.#",
		"#.........P.........#",
		"#####.#.##.##.#.#####",
		"##......##.##......##",
		"##.##.#.......#.##.##",
		"#...................#",
		"#..###..#####..###..#",
		"#..###...###...###..#",
		"#..###....K....###..#",
		"#.........0.........#",
		"#.##e## ##D## ##e##.#",
		"#.......#123#.......#",
		"################# ###",
		"                # #   "
	};

	//used to hold the map sketch information
	array<array<Cell, g_MAP_HEIGHT>, g_MAP_WIDTH> map{};

	//used to hold the positions of the slimes
	array<Position, 4> slime_positions;

	//used to hold the position of the door
	Position door;

	//creates an sfml event object
	sf::Event event;

	// videoMode contains the width and height and name as a paramerter
	// style is  the additiona features the windows can do like close, defualt, resize, title bar
	sf::RenderWindow window(sf::VideoMode(g_CELL_SIZE * g_MAP_WIDTH * g_SCREEN_RESIZE, g_CELL_SIZE * g_MAP_HEIGHT * g_SCREEN_RESIZE), "Pac-Man", sf::Style::Close);
	
	//sets the window size
	window.setView(sf::View(sf::FloatRect(0, 0, g_CELL_SIZE * g_MAP_WIDTH, g_CELL_SIZE * g_MAP_HEIGHT)));
	
	//creates a DrawMap object
	DrawMap drawMap;

	//creates a Pacman object
	Pacman pacman;

	//creates a Managaer object
	Manager ghost_manager;

	//creates a PauseGame object 
	PauseGame pause;


	//https://www.youtube.com/watch?v=x4A2o6YFiw4  cite this later used for the adding text 
	
	//hold the score to be displayed to the screen
	int score = current_score;

	//holds the score of the previous floor when game is restarted
	int previous_score = current_score;

	//passes the current score to the collision class in order to properly increment the new score
	pacman.setFloorPelletScore(current_score);

	//font settings for the score text that is displayed to the window
	sf::Font arial;
	arial.loadFromFile("arial.ttf");
	std::ostringstream buffer;
	buffer << "Score: " << score;

	sf::Text playerscore;

	playerscore.setCharacterSize(10);
	playerscore.setPosition({ 1,1 });
	playerscore.setFont(arial);
	playerscore.setString(buffer.str());

	//font setting for the next floor screen when the player clears the floor
	sf::Font nextFloor;
	nextFloor.loadFromFile("text.ttf");
	std::ostringstream nxtfloor;
	std::ostringstream nxtfloorScore;
	sf::Text winText;
	sf::Text nxtfloorscore;

	//music settings for the background game music
	sf::Music music;

	if (!music.openFromFile("UltimateFirstSection.ogg")) {
		std::cout << "Error" << std::endl;
	}
	music.setLoop(true);

	//sets the appropriate floor map sketch to the right floor
	switch (floor) {
	case 0:
		map = drawMap.convert_sketch(map_sketch_f1, pacman, slime_positions, door);
		break;
	case 1:
		map = drawMap.convert_sketch(map_sketch_f2, pacman, slime_positions, door);
		break;
	case 2:
		map = drawMap.convert_sketch(map_sketch_f3, pacman, slime_positions, door);
		break;
	case 3:
		map = drawMap.convert_sketch(map_sketch_f4, pacman, slime_positions, door);
		break;
	case 4:
		map = drawMap.convert_sketch(map_sketch_f5, pacman, slime_positions, door);
		break;
	default:
		cout << "Floor value is out of bounds";
	}

	//holds the current time
	previous_time = std::chrono::steady_clock::now();

	//initializes the slimes
	ghost_manager.reset_position(slime_positions, door);

	//plays the background music
	music.play();


	//start of game loop so the window does not instantly close
	while (1 == window.isOpen()) {

		//used to compute the lag which is used to make the game frame rate independent
		unsigned delta_time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - previous_time).count();

		previous_time += std::chrono::microseconds(delta_time);
		
		lag += delta_time;
		
		//this checks to see if the window was forcible closed if the user presses the x button in the right corner and if the game is paused
		while (g_FRAME_DURATION <= lag)
		{
			lag -= g_FRAME_DURATION;

			while (1 == window.pollEvent(event))
			{
				//listens to see if event happens and will listen for them at any point in the main game
				switch (event.type) {
				case sf::Event::Closed:			//closes window
					window.close();
					break;
	
				case sf::Event::KeyReleased:		//pauses character movement (main character and slimes)
					switch (event.key.code) {
					case sf::Keyboard::Escape:
						pause.toggle();

					}
					break;

				}

			}

			//checks to see if the score was reached to proceed to the next floor
			
			if (pacman.floorPelletScore() >= next_floor_score[i] && floor < 5) {
				map_key = true;
			}
			else if (floor == 5) {
				// if all floors were cleared then it prompts the win window
				window.close();
				winner(score);
			}

			//checks to see if the character can proceed to the next floor
			if (pacman.getNext_Floor() == true) {

				//checks to see if it's not the first of last floor
				if (floor != 4) {
					//clears window
					window.clear();

					//text output for the window settings
					nxtfloor << "Next Floor";

					sf::Text floorText;
					floorText.setFillColor(sf::Color::White);
					floorText.setPosition({ 125,200 });
					floorText.setCharacterSize(20);
					floorText.setFont(nextFloor);
					floorText.setString(nxtfloor.str());

					//gets the score from the cleard level and store it in score to be displayed to the window
					score = pacman.floorPelletScore();

					//stores the score from the floor to be used if the player dies on the next floor to carry over to the next attempt
					previous_score = pacman.floorPelletScore();

					//sets the score text settings to be displayed to the window
					nxtfloorScore << "Score: " << score;
					nxtfloorscore.setFillColor(sf::Color::White);
					nxtfloorscore.setPosition({ 125,250 });
					nxtfloorscore.setCharacterSize(18);
					nxtfloorscore.setFont(nextFloor);
					nxtfloorscore.setString(nxtfloorScore.str());

					//outputs the floor and score text to the window and displays them
					window.draw(floorText);
					window.draw(nxtfloorscore);
					window.display();

					//resets the score and floor strings 
					nxtfloor.str("");
					nxtfloorScore.str("");

					window.clear();

					//this is because the game is frame rate independent sometime there will be a lot of lag between the screen changes so it's to speed things up in this scenario
					if (lag != g_FRAME_DURATION || lag > g_FRAME_DURATION) {
						lag = g_FRAME_DURATION - 1;
					}
				}
				else {
					//if user wins the game meaning cleared the last floor goes to the winner function
					window.close();
					winner(score);
				}
			}

			if (g_FRAME_DURATION > lag)
			{
				//listens to see if user presses enter to proceed to the next screen in the case the the player clears the floor 
				if ((1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && pacman.getNext_Floor() == true) || pacman.getNext_Floor() == false) {
					window.clear();

					//checks to see if map key should appear in the maze
					if (map_key == true) {
						drawMap.unlock_map(map, map_key);
					}

					//outputs the map, score, pacman character, and slimes to the gui window
					drawMap.draw_map(map, window);
					window.draw(playerscore);
					pacman.draw(window, char_select);
					ghost_manager.draw_ghosts(window);

					//checks to see if the player should proceed to the next floor
					if (pacman.getNext_Floor() == true) {
						//increments the floor/floor iteraitor
						floor++;
						i++;
						//resets the map key back to false so it does not appear in the new floor until the score is reached
						map_key = false;

						//resets the nextfloor boolean back to false in the collision class
						pacman.resetNextFloor();

						//if the floor is 5 then the player won the game
						if (floor == 5) {
							
							window.close();
							winner(score);
						}

						//checks to see which map should be drawn
						switch (floor) {
						case 1:
						{
							map = drawMap.convert_sketch(map_sketch_f2, pacman, slime_positions, door);
							break;
						}
						case 2:
						{
							map = drawMap.convert_sketch(map_sketch_f3, pacman, slime_positions, door);
							break;
						}
						case 3:
						{
							map = drawMap.convert_sketch(map_sketch_f4, pacman, slime_positions, door);
							break;
						}
						case 4:
						{
							map = drawMap.convert_sketch(map_sketch_f5, pacman, slime_positions, door);
							break;
						}
						default:
							cout << "Floor boundaries are exceed!";
						}

						//resets the slimes settings
						ghost_manager.reset_position(slime_positions, door);

					}

					//listens to see if the game should be paused or window should be closed
					while (window.pollEvent(event)) {

						switch (event.type) {
						case sf::Event::Closed:
							window.close();
							break;
						case sf::Event::KeyReleased:
							switch (event.key.code) {
							case sf::Keyboard::Escape:
								pause.toggle();
								cout << "Pause: " << pause.getPauseGame() << endl;

							}
							break;
						}
					}

					//checks to see if pacman character collided with a slime not in the frightened phase
					//and prompts the gameover function
					if (pacman.isDead() == true) {

						//properties of the pacman death soound
						sf::SoundBuffer effects;
						if (!effects.loadFromFile("pacman_death.wav")) {
							cout << "ERROR" << endl;
						}

						sf::Sound deadSound;
						deadSound.setVolume(20.f);
						deadSound.setBuffer(effects);
						deadSound.play();

						//closes the window, stops the background music, and prompts the game_over function
						window.close();
						music.stop();
						game_over(char_select, floor, previous_score);
					}


					if (pause.getPauseGame() == false) {

						//checks if a key is held down right now not if it was pressed will return a bool
						if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || 1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || 1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || 1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
							
							//updates pacman's movement 
							pacman.update(map, floor);
							//takes in coordinates (x,y)
							// the top left corner is (0,0)
							// bottom left corner (0, sceen hieght)
							// top right screen (screeb width, 0)
							// bottom right screen (screen width, screen height)

							//sets the score held in the collision class to score to be outputed onto the screen
							score = pacman.floorPelletScore();
							buffer.str("");
							buffer << "Score: " << score;
							playerscore.setString(buffer.str());
						}
						
						//moves the slimes
						ghost_manager.update(map, pacman, floor);

					}

					//prints out window (front buffer)
					window.display(); 
				}

			}
		}
	}
}

/**/
 /*

 NAME

		void openning(int char_select)

 SYNOPSIS

		void openning(int char_select)
			char_select		--> is the value that holds which character the user selected in the beginning


 DESCRIPTION

		 This function is responsible for the game's story sequence.
 RETURNS

		 Returns void


 */
 /**/

void openning(int char_select) {
	
	//screen resize or how big the screen is
	constexpr unsigned char g_SCREEN_RESIZE = 2;

	//used to hold the filename of the character image
	string character_png;

	//initializes the gui window
	sf::RenderWindow op(sf::VideoMode(g_CELL_SIZE * g_MAP_WIDTH * g_SCREEN_RESIZE, g_CELL_SIZE * g_MAP_HEIGHT * g_SCREEN_RESIZE), "Intro", sf::Style::Close);
	
	//creates an event object
	sf::Event event;

	//creates an Intro object
	Intro Op;

	//creates a font SFML object
	sf::Font text;

	//font/text settings 
	text.loadFromFile("text.ttf");
	std::ostringstream dialogBuffer;
	sf::Text Chardialog;

	Chardialog.setCharacterSize(10);
	Chardialog.setPosition(sf::Vector2f(op.getSize().x * 0.08, op.getSize().y * 0.85));
	Chardialog.setFont(text);
	Chardialog.setFillColor(sf::Color::Black);
	Chardialog.setCharacterSize(18);

	//sets the background of the introduction to the image
	sf::Texture background;
	if (!background.loadFromFile("background master.png")) {}

	//creates a sprite SFML object that is used to display an image
	sf::Sprite spriteBackground;
	spriteBackground.setTexture(background);

	sf::RectangleShape textbox;


	while (1 == op.isOpen()) {
		//clears the window
		op.clear();

		//listens for an event to happen
		while (op.pollEvent(event)) {

			switch (event.type) {
			case sf::Event::Closed:		//if window is closed
				op.close();
				break;
			case sf::Event::KeyReleased:		//listens for the enter key to be pressed then release the proceed through the openning story
				switch (event.key.code) {
				case sf::Keyboard::Enter:

					//checks to see if the openning scenes are within the bounds
					if (Op.getSceneNumber() <= 14 || Op.getSceneNumber() == 0) {

						
						Op.SceneDialog(char_select);
						character_png = Op.getPicture();
						cout << "Scene: " << Op.getSceneNumber() << endl;

						//properties for the text box for the dialog 
						dialogBuffer.str("");
						dialogBuffer << Op.getSceneDialog();
						Chardialog.setString(dialogBuffer.str());
						textbox.setSize(sf::Vector2f(725, 140));
						textbox.setFillColor(sf::Color::White);
						textbox.setOutlineColor(sf::Color::Black);
						textbox.setOutlineThickness(3);
						textbox.setPosition(op.getSize().x * 0.08 - 25, op.getSize().y * 0.85 - 25);

					}
					else {
						//closes the character selection and proceeds to the main game function
						op.close();
						main_game(char_select, 0, 0);
					}
					break;
				}
				break;
			}

		}

		//output the sprites, backgrounds, and text to the gui window
		op.draw(spriteBackground);
		Op.drawPicture(op);
		if (Op.getSceneNumber() <= 14) {
			op.draw(textbox);
		}
		op.draw(Chardialog);
		op.display();
	}
}

/**/
 /*

 NAME

		character_selection()

 SYNOPSIS

		character_selection()


 DESCRIPTION

		 This function is responsible for allowing the user to select which character wants to be.
 RETURNS

		 Returns void


 */
 /**/
void character_selection() {
	
	//represents how big the window is
	constexpr unsigned char g_SCREEN_RESIZE = 2;

	// videoMode contains the width and height and name as a paramerter
	//	window settings
	sf::RenderWindow char_window(sf::VideoMode(g_CELL_SIZE * g_MAP_WIDTH * g_SCREEN_RESIZE, g_CELL_SIZE * g_MAP_HEIGHT * g_SCREEN_RESIZE), "Character Selection", sf::Style::Close);

	// creates and intializes the character selection menu
	Selection Selection(char_window.getSize().x, char_window.getSize().y);

	// properties of the text used to display in the screen
	sf::Font arial;
	arial.loadFromFile("arial.ttf");
	std::ostringstream buffer;
	buffer << "Select Character";
	sf::Text title;
	title.setFillColor(sf::Color::White);
	title.setCharacterSize(50);
	title.setPosition({ 250,30 });
	title.setFont(arial);
	title.setString(buffer.str());

	//gets the file and sets the propereties for the boy image to be displayed in the screen
	sf::Texture texture_boy;
	if (!texture_boy.loadFromFile("boy.png")) {
		cout << "image not found";
	}

	sf::Sprite boy;
	boy.setPosition(75, 110);
	boy.setTexture(texture_boy);

	//gets the file and sets the propereties for the girl image to be displayed in the screen
	sf::Texture texture_girl;
	if (!texture_girl.loadFromFile("girl.png")) {
		cout << "image not found";
	}

	sf::Sprite girl;
	girl.setPosition(500, 100);
	girl.setTexture(texture_girl);


	while (char_window.isOpen()) {

		//clears the window
		char_window.clear();
		sf::Event char_event;

		//listens for an event to happen
		while (char_window.pollEvent(char_event)) {
			switch (char_event.type) {
			case sf::Event::KeyReleased:			//listens for a key to be pressed then released
				switch (char_event.key.code) {
				case sf::Keyboard::Left:
					Selection.MoveLeft();
					break;
				case sf::Keyboard::Right:
					Selection.MoveRight();
					break;
				case sf::Keyboard::Return:			//listens for enter to be pressed and released 
					switch (Selection.getPressedItem()) {		//selects which option the user selected
					case 0:			//goes to openning story
						char_window.close();
						openning(1);
						break;
					case 1:			//closes the game
						char_window.close();
						openning(2);
						break;
					}
				}

				break;
			case sf::Event::Closed:			//closes the game if the x button is pressed in the right corner of the screen
				char_window.close();
				break;
			}
		}

		//outputs the images and text to the window
		char_window.draw(title);
		char_window.draw(boy);
		char_window.draw(girl);
		Selection.draw(char_window);
		char_window.display();

	}

}