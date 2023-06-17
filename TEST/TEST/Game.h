#pragma once
#include <SFML/Graphics.hpp>
#include <time.h>
#include <fstream> // added for file handling
#include <string>// adde for string manipulation
#include <iostream>
#include "Scoreboard.h"
#include "Blocks.h"
#include "Buttons.h"
class Game
{
	sf::RenderWindow window;
	Font font;
		bool gameStarted;
		bool gameOver;
		Clock countdownClock;
public: 
	Game(sf::RenderWindow window, Font font, bool gameStarted, bool gameOver, Clock countdownClock);
};

