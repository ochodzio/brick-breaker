#include "Scoreboard.h"


Scoreboard::Scoreboard()
{
	//scoreboard from file
    ifstream file("./scoreboard.csv");
    if (file.is_open()) {
          string line;
        while (std::getline(file, line)) {
            string pname = "player1";
            int pscore = 0;
            size_t commaPos = line.find(',');
            if (commaPos != std::string::npos) {
               pname = line.substr(0, commaPos);
               pscore = std::stoi(line.substr(commaPos + 1));
            }
            scores.push_back(Player(pname,pscore));
        }

        
    }
    //high score from file
    ifstream file2("./highscore.txt");
    if (file2.is_open()) {
        file2 >> (highScore);
        file2.close();
    }
}

vector<Player> Scoreboard::sortScoreboard()
{
    int n = scores.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (scores[j].score < scores[j + 1].score) {
                std::swap(scores[j], scores[j + 1]);
            }
        }
    }
    return scores;
}

vector<Player> Scoreboard::getScoreboard()
{

	return scores;
}

void Scoreboard::setScoreboard()
{
   
    std::ofstream file("./scoreboard.csv");
    string result;
    if (file.is_open()) {
    
        int i = 0;
        for (int i = 0; i < scores.size(); i++) {
            result += scores[i].name + ", " + to_string(scores[i].score) + "\n";  
        }
    }
    file << result;
    file.close();
}

int Scoreboard::getHighScore()
{
    return highScore;
}

void Scoreboard::setHighScore(int tHighScore)
{
    highScore = tHighScore;
        //Save high score to file
        std::ofstream file("./highscore.txt");
        if (file.is_open()) {
            file << highScore;
            file.close();
        }
}
void Scoreboard:: addEntry(const string& name,int score)
{
    scores.push_back(Player(name, score));
    sortScoreboard();
};

Scoreboard::~Scoreboard()
{
}
