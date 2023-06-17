#pragma once
#include <vector>
#include <time.h>
#include <fstream> // added for file handling
#include <string>// adde for string manipulation
#include <iostream>
#include "Player.h"

using namespace std;
class Scoreboard
{
private:
	vector<Player> scores;
	int highScore;
public:
	Scoreboard();
	vector<Player> sortScoreboard();
	vector<Player> getScoreboard();
	void addEntry(const string& name, int score);
	void setScoreboard();
	int getHighScore();
	void setHighScore(int tHighScore);
	virtual ~Scoreboard();
	
};