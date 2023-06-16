#pragma once
#include <vector>
#include <time.h>
#include <fstream> // added for file handling
#include <string>// adde for string manipulation
#include <iostream>

using namespace std;
class Scoreboard
{
private:
	vector<string> scores;
	int highScore;
public:
	Scoreboard();
	vector<string> sortScoreboard();
	vector<string> getScoreboard();
	void setScoreboard(vector<string> tscoreboard);
	int getHighScore();
	void setHighScore(int tHighScore);
	virtual ~Scoreboard();
	
};