#include <time.h>
#include <fstream> // added for file handling
#include <string>// adde for string manipulation
#include <iostream>
#include "Scoreboard.h"
#include "Blocks.h"
#include "Buttons.h"
#include "Txtrs.h"
#include "Texts.h"
#include "Player.h"
using namespace sf;
int main() {
    Scoreboard scoreboard; //scoreboard data
    Txtrs txtrs;
    
    //basic game states vars
    bool gameStarted = false;
    bool gameOver = false;
    bool gameWin = false;
    bool showScoreBoard = false;
    bool addedEntry = true;
    int countdown = 5; //Main menu countdown after game over
    Clock countdownClock; //added to implement counter
    Font font; // Added to handle fonts
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Arcanoid"); //windows size
    window.setFramerateLimit(60); //fps limit
    font.loadFromFile("./arial.ttf"); // replace with the path to your font file
    //buttons
    Button newGameButton(sf::Vector2f(540, 310), sf::Vector2f(200, 50), sf::Color::Green, "New Game", font, 24);
    Button scoreboardButton(sf::Vector2f(540, 370), sf::Vector2f(200, 50), sf::Color::Blue, "Scoreboard", font, 24);
    Button exitButton(sf::Vector2f(540, 490), sf::Vector2f(200, 50), sf::Color::Red, "Exit", font, 24);
    Button returnToMenuButton(sf::Vector2f(540, 50), sf::Vector2f(200, 50), sf::Color::Red, "Return", font, 24);
    
    sf::RectangleShape inputBox(sf::Vector2f(200.f, 30.f));
    inputBox.setPosition(540, 150);
    inputBox.setFillColor(sf::Color::White);
    inputBox.setOutlineColor(sf::Color::Black);

    sf::Text inputText("Player 1", font, 20);
    inputText.setPosition(540, 150);
    inputText.setFillColor(sf::Color::Black);
    string name = "Player 1";

    sf::Text enterYourNameText("Enter your name", font, 20);
    enterYourNameText.setPosition(540, 100);
    enterYourNameText.setFillColor(sf::Color::White);
  
    while (window.isOpen())
    {
        
        gameStarted = false;
        gameWin = false;
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            //Main menu 
            if (event.type == sf::Event::TextEntered && name.length() < 10) {
                if (event.text.unicode < 128 && event.text.unicode != '\r') {
                    char z= static_cast<char>(event.text.unicode) ;
                    name.push_back( z );
                    inputText.setString(name);
                }
            }
             
                if ( event.key.code == sf::Keyboard::Backspace && !name.empty()) {
                    name.resize(name.size() - 1);
                    
                }
            
            if (event.type == sf::Event::MouseButtonReleased)
            {
                
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    
                    sf::Vector2f mousePos = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
                    if (newGameButton.isClicked(mousePos))
                    {
                        // New Game button clicked, start the game here
                        if (name.empty()) name = "Player 1";
                        gameStarted = true;
                        addedEntry = false;
                        gameOver = false;

                    }
                    else if (scoreboardButton.isClicked(mousePos))
                    {
                        //Scoreboard button clicked, show scorboard
                        showScoreBoard = true;


                    }
                    else if (exitButton.isClicked(mousePos))
                    {
                        window.close();
                    }
                }
            }
        }

        window.clear();

        if (gameStarted && !gameOver)
        {

            srand(time(0));



            
            

            Sprite sBackground(txtrs.t2), sBall(txtrs.t3), sPaddle(txtrs.t4);


            sPaddle.setPosition(640, 680);

            Texture barTexture;
            if (!barTexture.loadFromFile("./blocks/bar_text.png")) {

            }

            RectangleShape bar;
            bar.setSize(Vector2f(1280, 40)); //adjust size of bar
            bar.setTexture(&barTexture);
            bar.setTextureRect(IntRect(0, 0, 1280, 40));//adjujst texture of bar

            Texture gameOverBoxTexture;
            if (!gameOverBoxTexture.loadFromFile("./blocks/gameOverBox.png")) {

            }

            RectangleShape gameOverBox;
            gameOverBox.setSize(Vector2f(390, 190)); //adjust size of bar
            gameOverBox.setTexture(&gameOverBoxTexture);

            gameOverBox.setPosition((window.getSize().x - gameOverBox.getSize().x) / 2, 180);


            //Block block[1000];
            Block block[1000];
            int n = 0;
            int numBlocks = 10;
            int blockWidth = txtrs.t1.getSize().x;
            int blockHight = txtrs.t1.getSize().y;

            //ball pos and move
            //move
            float dx = 0;
            float dy = 5;
            //pos
            float x = 640;
            float y = 450;

            int score = 0;//Variable to keep track of points
            int highScore = scoreboard.getHighScore(); //variable to keep track of the high score

            //set blocks patern
            for (int i = 0; i < numBlocks * 2.8; i++) {
                for (int j = 0; j < numBlocks * 1.5; j++)
                {


                    if (i == 0 || i == 27 || j == 0 || j == 14) {
                        block[n] = Block(txtrs.t9, txtrs.t9, txtrs.t10, 2);//first iron ring
                        block[n].sprite.setPosition(blockWidth * (i + 1), blockHight * (j + 1) + 40);//Center the bloks
                        n++;
                    }
                    else if (i > 0 && i < 3 || i>24 && i < 27 || j>0 && j < 3 || j>11 && j < 14) {
                        block[n] = Block(txtrs.t5, txtrs.t5, txtrs.t5, 1);//red ring
                        block[n].sprite.setPosition(blockWidth * (i + 1), blockHight * (j + 1) + 40);//Center the bloks
                        n++;
                    }
                    else if (((j >= 3 || j <= 11) && (i == 3 || i == 24)) || (i > 3 && i < 25 && (j == 3 || j == 11))) {
                        block[n] = Block(txtrs.t11, txtrs.t12, txtrs.t13, 3);//gold ring
                        block[n].sprite.setPosition(blockWidth * (i + 1), blockHight * (j + 1) + 40);//Center the bloks
                        n++;
                    }
                    else if (i > 3 && i < 6 || i>22 && i < 24 || j>3 && j < 6 || j>8 && j < 11) {
                        block[n] = Block(txtrs.t6, txtrs.t6, txtrs.t6, 1);//blue ring
                        block[n].sprite.setPosition(blockWidth * (i + 1), blockHight * (j + 1) + 40);//Center the bloks
                        n++;
                    }
                    else {
                        block[n] = Block(txtrs.t14, txtrs.t14, txtrs.t15, 2);
                        block[n].sprite.setPosition(blockWidth * (i + 1), blockHight * (j + 1) + 40);//Center the bloks
                        n++;
                    }



                }

            }









            Texts texts(font);


            while (window.isOpen())
            {
                Event e;
                while (window.pollEvent(e))
                {
                    if (e.type == Event::Closed)
                        window.close();
                }

                x += dx;
                y += dy;

                //balll collision with block
                for (int i = 0; i < n; i++)
                    if (FloatRect(x + 3, y + 3, 6, 6).intersects(block[i].sprite.getGlobalBounds()))
                    {
                        if (y > block[i].sprite.getPosition().y && y  < block[i].sprite.getPosition().y + blockHight && y + 6 > block[i].sprite.getPosition().y && y + 6 < block[i].sprite.getPosition().y + blockHight) {
                            // Ball hit the left or right side of the block
                            dx = -dx;;
                        }
                        else if (x > block[i].sprite.getPosition().x && x  < block[i].sprite.getPosition().x + blockWidth && x + 6 > block[i].sprite.getPosition().x && x + 6 < block[i].sprite.getPosition().x + blockWidth) {
                            // Ball hit the bottom or top side of the block
                            dy = -dy;
                        }

                        if (block[i].resistance > 1)
                        {
                            block[i].resistance--;
                            block[i].setTexture();
                        }
                        else {
                            block[i].sprite.setPosition(-100, 0);
                            score++; // Increment the score when a block is hit
                            
                        }
                        if (score == n)
                        {
                            gameWin = true;
                            dy = 0;
                            dx = 0;
                        }


                    }
                //ball collision edge of screen
                if (x < 0 || x + 6 > 1280)
                    dx = -dx;
                if (y < 40)
                    dy = -dy;
                if (y > 710) {
                    gameOver = true;
                    dx = 0; 
                    dy = 0;
                }
                //Move paddle
                if (Keyboard::isKeyPressed(Keyboard::Right) && sPaddle.getPosition().x + sPaddle.getLocalBounds().width < 1280)
                    sPaddle.move(8, 0);
                if (Keyboard::isKeyPressed(Keyboard::Left) && sPaddle.getPosition().x > 0)
                    sPaddle.move(-8, 0);
                //rebounce while paddle moving
                if (FloatRect(x , y , 6, 6).intersects(sPaddle.getGlobalBounds())) {
                    dy = -dy;
                    if (Keyboard::isKeyPressed(Keyboard::Right))
                    {
                        if (dx == 0)
                        {
                            dx = dx + 3;
                        }
                        else if (dx < 0)
                        {
                            dx = dx + 1;
                        }
                        else if (dx > 0)
                        {
                            dx = dx + 1;
                        }

                    }

                    if (Keyboard::isKeyPressed(Keyboard::Left))
                    {
                        if (dx == 0)
                        {
                            dx = dx - 3;
                        }
                        else if (dx < 0)
                        {
                            dx = dx - 1;
                        }
                        else if (dx > 0)
                        {
                            dx = dx - 1;
                        }
                    }

                }

                if (score > highScore) {
                    highScore = score;
                    scoreboard.setHighScore(highScore);

                }

                //Update the text strings
                
                texts.highScoreText.setString("High Score: " + std::to_string(highScore));
                texts.scoreText.setString("Score: " + std::to_string(score));

                window.clear();

                window.draw(sBackground);
                window.draw(bar);
                window.draw(sBall);
                window.draw(sPaddle);
                sBall.setPosition(x, y);
                for (int i = 0; i < n; i++)
                    window.draw(block[i].sprite);
                if (gameOver) {
                    //Game Over screen
                    if (!addedEntry) {
                        scoreboard.addEntry(name, score);
                        addedEntry = true;
                    }
                    
                    
                    Text gameOverText("Game Over", font, 48);
                    sf::FloatRect textBounds1 = gameOverText.getLocalBounds();
                    gameOverText.setPosition((window.getSize().x - textBounds1.width) / 2, 200);
                    gameOverText.setFillColor(Color::White);


                    Text countdownText("Returning to menu in: " + std::to_string(countdown) + " s", font, 24);
                    sf::FloatRect textBounds2 = countdownText.getLocalBounds();
                    countdownText.setPosition((window.getSize().x - textBounds2.width) / 2, 300);
                    countdownText.setFillColor(Color::White);


                    if (countdownClock.getElapsedTime().asSeconds() >= 1.0f)
                    {
                        countdown--;
                        countdownClock.restart();
                    }

                    if (countdown >= 0)
                    {
                        window.draw(gameOverBox);
                        window.draw(gameOverText);
                        window.draw(countdownText);
                        

                    }
                    else
                    {
                        //return to menu

                        countdown = 5;
                        gameStarted = false;
                        break;
                    }
                }
                else if (gameWin) {
                    //Game Win screen
                    if (!addedEntry) {
                        scoreboard.addEntry(name, score);
                        addedEntry = true;
                    }
                    //scoreboard.addEntry(name, score);
                    Text gameWinText("You Win!!!", font, 48);
                    sf::FloatRect textBounds1 = gameWinText.getLocalBounds();
                    gameWinText.setPosition((window.getSize().x - textBounds1.width) / 2, 200);
                    gameWinText.setFillColor(Color::White);


                    Text countdownText("Returning to menu in: " + std::to_string(countdown) + " s", font, 24);
                    sf::FloatRect textBounds2 = countdownText.getLocalBounds();
                    countdownText.setPosition((window.getSize().x - textBounds2.width) / 2, 300);
                    countdownText.setFillColor(Color::White);


                    if (countdownClock.getElapsedTime().asSeconds() >= 1.0f)
                    {
                        countdown--;
                        countdownClock.restart();
                    }

                    if (countdown >= 0)
                    {
                        window.draw(gameOverBox);
                        window.draw(gameWinText);
                        window.draw(countdownText);


                    }
                    else
                    {
                        //return to menu

                        countdown = 5;

                        break;
                    }
                }
                
                //Draw the text
                texts.draw(window);
             


                window.display();


            }
        }
        else if (showScoreBoard)
        {
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2f mousePos = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);

                if (returnToMenuButton.isClicked(mousePos))
                {
                    // New Game button clicked, start the game here
                    showScoreBoard = false;
                }
            }
            //draw scoreboard data
            sf::Text scoreboardText;
            scoreboardText.setFont(font);
            scoreboardText.setCharacterSize(24);
            scoreboardText.setFillColor(sf::Color::White);
            sf::Text scoreboardText2;
            scoreboardText2.setFont(font);
            scoreboardText2.setCharacterSize(24);
            scoreboardText2.setFillColor(sf::Color::White);
            float pos_scoreboard_y = 120.f;//starting position fo scoreboard text

            scoreboard.sortScoreboard();
            int titeration = 0;
            for (const Player& entry : scoreboard.getScoreboard()) {
                titeration++;
                scoreboardText.setString(entry.name);
                scoreboardText2.setString(to_string(entry.score));
                scoreboardText.setPosition(540, pos_scoreboard_y);
                scoreboardText2.setPosition(700, pos_scoreboard_y);
                
                window.draw(scoreboardText);
                window.draw(scoreboardText2);
                pos_scoreboard_y += 30.0f;//adjust vertical spacing between entries
                if (titeration > 9) break;
            }
            returnToMenuButton.draw(window);

        }
        else
        {
            // Draw buttons and labels
            //inputBox.draw(window);
            window.draw(enterYourNameText);
            window.draw(inputBox);
            window.draw(inputText);
            newGameButton.draw(window);
            scoreboardButton.draw(window);
            exitButton.draw(window);
        }



        window.display();
    }
    scoreboard.setScoreboard();
        return 0;
    }
