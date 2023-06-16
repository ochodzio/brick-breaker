#include <SFML/Graphics.hpp>
#include <time.h>
#include <fstream> // added for file handling
#include <string>// adde for string manipulation
#include <iostream>
#include "Scoreboard.h"
#include "Blocks.h"
#include "Buttons.h"


using namespace sf;
struct Block {
    Sprite sprite;
    int resistance;
    Texture texture1;
    Texture texture2;
    Texture texture3;

    Block() {};

    Block(Texture& texture1, Texture& texture2, Texture& texture3, int resistance) {
        this->texture1 = texture1;
        this->texture2 = texture2;
        this->texture3 = texture3;
        sprite.setTexture(texture1);
        this->resistance = resistance;
    }

    void setTexture() {
        if (resistance > 2) {
            sprite.setTexture(texture1);
        }
        else if (resistance == 2)
        {
            sprite.setTexture(texture2);
        }
        else
        {
            sprite.setTexture(texture3);
        }
    }
};

Scoreboard scoreboard;

int main() {


    sf::RenderWindow window(sf::VideoMode(1280, 720), "Arcanoid");
    window.setFramerateLimit(60);

    Font font; // Added for text rendering
    font.loadFromFile("./arial.ttf"); // replace with the path to your font file

    // Create buttons
    sf::RectangleShape newGameButton(sf::Vector2f(200, 50));
    newGameButton.setPosition(540, 310);
    newGameButton.setFillColor(sf::Color::Green);

sf:RectangleShape scoreboardButton(sf::Vector2f(200, 50));
    scoreboardButton.setPosition(540, 370);
    scoreboardButton.setFillColor(sf::Color::Blue);

    sf::RectangleShape exitButton(sf::Vector2f(200, 50));
    exitButton.setPosition(540, 490);
    exitButton.setFillColor(sf::Color::Red);

    sf::RectangleShape return_to_menu_Button(sf::Vector2f(200, 50));
    return_to_menu_Button.setPosition(540, 50);
    return_to_menu_Button.setFillColor(sf::Color::Red);



    // Create button labels
    

    sf::Text newGameText("New Game", font, 24);
    newGameText.setPosition(570, 320);
    newGameText.setFillColor(sf::Color::White);

    sf::Text scoreboardText("Scoreboard", font, 24);
    scoreboardText.setPosition(570, 380);
    scoreboardText.setFillColor(sf::Color::White);

    sf::Text exitText("Exit", font, 24);
    exitText.setPosition(570, 500);
    exitText.setFillColor(sf::Color::White);

    sf::Text return_to_menuText("Return", font, 24);
    return_to_menuText.setPosition(570, 60);
    return_to_menuText.setFillColor(sf::Color::White);




    bool gameStarted = false;
    bool gameOver = false;
    bool gameWin=false;
    bool showScoreBoard = false;


    int countdown = 5; //Countdown in seconds
    Clock countdownClock;

    std::vector<std::string> scoreboardData;



    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2f mousePos = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);

                    if (newGameButton.getGlobalBounds().contains(mousePos))
                    {
                        // New Game button clicked, start the game here
                        //
                        gameStarted = true;
                        gameOver = false;

                    }
                    else if (scoreboardButton.getGlobalBounds().contains(mousePos))
                    {
                        //Scoreboard button clicked, show scorboard
                        showScoreBoard = true;
                        scoreboardData = scoreboard.getScoreboard();

                    }
                    else if (exitButton.getGlobalBounds().contains(mousePos))
                    {
                        window.close();
                    }
                }
            }
        }

        window.clear();

        if (gameStarted&&!gameOver)
        {


            srand(time(0));

            

            Texture t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16;
            t1.loadFromFile("./block01.png");
            t2.loadFromFile("./background.jpg");
            t3.loadFromFile("./ball.png");
            t4.loadFromFile("./paddle.png");
            t5.loadFromFile("./block02.png");
            t6.loadFromFile("./block03.png");
            t7.loadFromFile("./block04.png");
            t8.loadFromFile("./block05.png");
            t9.loadFromFile("./blocks/block_iron.png");
            t10.loadFromFile("./blocks/block_iron_damage.png");
            t11.loadFromFile("./blocks/block_gold.png");
            t12.loadFromFile("./blocks/block_gold_damage.png");
            t13.loadFromFile("./blocks/block_gold_damage_strong.png");
            t14.loadFromFile("./blocks/invi_glass.png");
            t15.loadFromFile("./blocks/invi_glass_damage.png");
            t16.loadFromFile("./blocks/immortal.png");


            Sprite sBackground(t2), sBall(t3), sPaddle(t4);


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


            Block block[1000];

            int n = 0;
            int numBlocks = 10;
            int blockWidth = t1.getSize().x;
            int blockHight = t1.getSize().y;

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
                        block[n] = Block(t9,t9, t10, 2);//first iron ring
                        block[n].sprite.setPosition(blockWidth * (i + 1), blockHight * (j + 1) + 40);//Center the bloks
                        n++;
                    }
                    else if (i > 0 && i < 3 || i>24 && i < 27 || j>0 && j < 3 || j>11 && j < 14) {
                        block[n] = Block(t5,t5, t5, 1);//red ring
                        block[n].sprite.setPosition(blockWidth * (i + 1), blockHight * (j + 1) + 40);//Center the bloks
                        n++;
                    }
                    else if (((j >= 3 || j <= 11) && (i == 3 || i == 24)) || (i > 3 && i < 25 && (j == 3 || j == 11))) {
                        block[n] = Block(t11, t12,t13, 3);//gold ring
                        block[n].sprite.setPosition(blockWidth * (i + 1), blockHight * (j + 1) + 40);//Center the bloks
                        n++;
                    }
                    else if (i > 3 && i < 6 || i>22 && i < 24 || j>3 && j < 6 || j>8 && j < 11) {
                        block[n] = Block(t6,t6, t6, 1);//blue ring
                        block[n].sprite.setPosition(blockWidth * (i + 1), blockHight * (j + 1) + 40);//Center the bloks
                        n++;
                    }
                    else {
                        block[n] = Block(t14, t14,t15, 2);
                        block[n].sprite.setPosition(blockWidth * (i + 1), blockHight * (j + 1) + 40);//Center the bloks
                        n++;
                    }



                }

            }


            
           



            

            //High Score Text
            Text highScoreText;
            highScoreText.setFont(font);
            highScoreText.setCharacterSize(25);
            highScoreText.setFillColor(Color::Black);
            highScoreText.setPosition(7, 4);

            //Score text
            Text scoreText;
            scoreText.setFont(font);
            scoreText.setCharacterSize(25);
            scoreText.setFillColor(Color::Black);
            scoreText.setPosition(600, 4);
            scoreText.setOrigin(scoreText.getLocalBounds().width / 2.0f, 0); // center the text horizontally



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
                        if (y  > block[i].sprite.getPosition().y && y  < block[i].sprite.getPosition().y + blockHight&&y + 6 > block[i].sprite.getPosition().y && y+6 < block[i].sprite.getPosition().y + blockHight) {
                            // Ball hit the left or right side of the block
                            dx = -dx;;
                        }
                        else if (x  > block[i].sprite.getPosition().x && x  < block[i].sprite.getPosition().x + blockWidth&&x+6 > block[i].sprite.getPosition().x && x+6 < block[i].sprite.getPosition().x + blockWidth) {
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
                            if (score == n)
                            {
                                gameWin == true;
                            }
                        }



                    }
                //ball collision edge of screen
                if (x < 0 || x+6 > 1280)
                    dx = -dx;
                if (y < 40)
                    dy = -dy;
                if (y > 720) {
                    gameOver = true;

                }
                //Move paddle
                if (Keyboard::isKeyPressed(Keyboard::Right) && sPaddle.getPosition().x + sPaddle.getLocalBounds().width < 1280)
                    sPaddle.move(8, 0);
                if (Keyboard::isKeyPressed(Keyboard::Left) && sPaddle.getPosition().x > 0)
                    sPaddle.move(-8, 0);
                //rebounce while paddle moving
                if (FloatRect(x+3, y+3, 6, 6).intersects(sPaddle.getGlobalBounds())) {
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
                            dx = dx -3;
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
                highScoreText.setString("High Score: " + std::to_string(highScore));
                scoreText.setString("Score: " + std::to_string(score));

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
                        gameStarted = false;
                        gameWin = false;
                        break;
                    }
                }

                //Draw the text
                window.draw(highScoreText);
                window.draw(scoreText);


                window.display();


            }


        }
        else if (showScoreBoard)
        {
            if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2f mousePos = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);

                    if (return_to_menu_Button.getGlobalBounds().contains(mousePos))
                    {
                        // New Game button clicked, start the game here
                        showScoreBoard = false;
                    }

                }
            }
            //draw scoreboard data
            sf::Text scoreboardText;
            scoreboardText.setFont(font);
            scoreboardText.setCharacterSize(24);
            scoreboardText.setFillColor(sf::Color::White);

            float pos_scoreboard_y = 120.f;//starting position fo scoreboard text


            for (const std::string& entry : scoreboardData) {

                scoreboardText.setString(entry);
                scoreboardText.setPosition(540, pos_scoreboard_y);

                window.draw(scoreboardText);

                pos_scoreboard_y += 30.0f;//adjust vertical spacing between entries

            }

            window.draw(return_to_menu_Button);
            window.draw(return_to_menuText);
        }
        else
        {
            // Draw buttons and labels
            window.draw(newGameButton);
            window.draw(scoreboardButton);

            window.draw(exitButton);
            window.draw(newGameText);
            window.draw(scoreboardText);

            window.draw(exitText);
        }



        window.display();
    }

    return 0;
}