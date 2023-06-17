#pragma once
#include <SFML/Graphics.hpp>
#include <time.h>
#include <fstream> // added for file handling
#include <string>// adde for string manipulation
#include <iostream>
using namespace sf;
class Texts
{

	
public:
Text highScoreText;
	Text scoreText;

	Texts(const sf::Font& font);
	void draw(sf::RenderWindow& window);

};

