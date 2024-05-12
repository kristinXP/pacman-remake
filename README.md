# pacman-remake

Installation
In order to successfully run this program the user must have at least Visual Studios 2017 or earlier and the version must match the version of SFML that you are installing. The SFML library can be downloaded from their website: https://www.sfml-dev.org/download/sfml/2.6.0/. For reference purposes, this project was made and run using SFML version 2.5.1 and used Visual Studio 2022 with the SFML Visual C++ 17 - 64 bit compatibility. It is recommended to follow the installation instructions outlined on the official SFML website: https://www.sfml-dev.org/tutorials/2.6/start-vc.php, but a brief installation summary of the configuration of what was done for this project will be given to ensure that the environments are the same. In ‘Project Properties’ under the ‘Linker’ tab and in ‘Input’ add the following libraries to additional dependencies: sfml-system-s.lib, sfml-audio-s.lib, sfml-window-s.lib, sfml-graphics-s.lib. Then in debug and release configuration under the ‘C/C++’ tab in ‘Preprocessor’ add SFML_STATIC to the ‘Preprocessor Definitions’. Compile and run the empty main.cpp file in visual studio so that a debug folder will appear where the solution and files are saved onto your computer, assuming you selected them to be saved to the same location. Navigate to the programs Debug folder and copy the appropriate .dll files that match what you added to the additional dependencies. Be careful when you do this not to mix up files because this will cause an error when trying to link the SFML library. In addition under ‘Configuration Properties’ under ‘Debugging’ in ‘Environment’ put in the path of where the SFML bin folder is stored on your computer. Use the code provided by the official SFML site to verify that you set up the environment correctly. If done correctly, a window with a green circle should appear.  Once the environment is set up and the code has been downloaded and uploaded into Visual Studios, the program should be compiled and started without debugging.

User Manual
The game will start and you can move the up and down arrows to navigate through the menu screen. To select an option you press the enter key and the selected option is colored in red. If you select the instructions option on the start menu, the game instructions will appear on the screen, and in order to go back to the main menu you press enter once.  On the character menu you move the right and left arrow keys and press enter to select. Once all the start options are selected, an image of a store background is displayed and you press enter go through the story dialogue. When the story dialogue is finished, a new window will open and the game will start. The player controls the character using the four arrow keys and can move the character in the corresponding direction of the arrow keys. The game consists of 5 levels or floors, and upon ascending each floor the required amount of points to make the map sprite appear in the maze increases. Each pellet or dot is worth 10 points and each energizer or potion bottle is worth 50 points. The only way to move to the next floor is to get the map icon. If the character is intercepted by a slime, the game is over and the game then prompts the user whether they would like to restart the floor or exit the game. The user uses the arrow keys to select the option and presses enter to make their selection. The score from the last previous level if applicable is carried over. While in the maze if the character intercepts with a potion bottle, the slimes will change to dark blue, indicating that they are in frightened mode and that the character is invulnerable to the slimes. If at any point the user wishes to pause the game while in the maze, the ‘ESC’ key will freeze character’s and the slimes’ movement. The game can be resumed again upon hitting the ‘ESC’ key again. The warp tunnels can be used to expedite moving from one side of the maze to another and the ghosts can also follow. If the user wishes to close the game in the middle of the game, the user can click on the ‘x’ button on the right side to close the window. 
