#include "Scoreboard.h"



Scoreboard::Scoreboard()
{
	string filename = "./scoreboard.txt";

    ifstream file(filename);

    if (file.is_open()) {
          string line;
        while (std::getline(file, line)) {
            scores.push_back(line);
        }

        file.close();
    }
    //Load high score from file
    std::ifstream file2("./highscore.txt");
    if (file2.is_open()) {
        file2 >> highScore;
        file2.close();
    }
}

vector<string> Scoreboard::sortScoreboard()
{
       
    return vector<string>();
}

vector<string> Scoreboard::getScoreboard()
{
	return scores;
}

void Scoreboard::setScoreboard(vector<string> tscoreboard)
{
    scores = tscoreboard;
}

int Scoreboard::getHighScore()
{
    return highScore;
}

void Scoreboard::setHighScore(int tHighScore)
{
    highScore = tHighScore;
    //Update the high score
        highScore = tHighScore;

        //Save high score to file
        std::ofstream file("./highscore.txt");
        if (file.is_open()) {
            file << highScore;
            file.close();
    }
}



Scoreboard::~Scoreboard()
{
}
