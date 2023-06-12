#include <SFML/Graphics.hpp>
#include <time.h>
#include <fstream> // added for file handling
#include <string>// adde for string manipulation

using namespace sf;
struct Block {
    Sprite sprite;
    int resistance;
    Texture texture1;
    Texture texture2;

    Block() {};

    Block(Texture& texture1,Texture& texture2, int resistance) {
        this->texture1 = texture1;
        this->texture2 = texture2;
        sprite.setTexture(texture1);
        this->resistance = resistance;
    }

    void setTexture() {
        if (resistance > 1) {
            sprite.setTexture(texture1);
        }
        else
        {
            sprite.setTexture(texture2);
        }
    }
};

int main() {
    srand(time(0));

    RenderWindow app(VideoMode(1280, 720), "Arkanoid Game");
    app.setFramerateLimit(60);

    Texture t1, t2, t3, t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,t16;
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
    
    Sprite sBackground(t2), sBall(t3), sPaddle(t4);
    sPaddle.setPosition(640, 680);

    Texture barTexture;
    if (!barTexture.loadFromFile("./blocks/bar_text.png")) {

    }

    RectangleShape bar;
    bar.setSize(Vector2f(1280, 40)); //adjust size of bar
    bar.setTexture(&barTexture);
    bar.setTextureRect(IntRect(0, 0,1280,40));//adjujst texture of bar


    Block block[1000];

    int n = 0;
    int numBlocks = 10;
    int blockWidth = t1.getSize().x;
    int blockHight = t1.getSize().y;
 

    for (int i = 0; i < numBlocks*2.8; i++) {
        for (int j = 0; j < numBlocks*1.5; j++)
        {
            if (i == 0 || i ==27 || j==0||j==14 ) {
                block[n] = Block(t9,t10, 2);//first iron ring
                block[n].sprite.setPosition(blockWidth * (i + 1), blockHight * (j + 1)+40);//Center the bloks
                n++;
            }
            else if (i > 0 && i < 3 || i>24 && i < 27 || j>0 && j < 3 || j>11 && j < 14) {
                block[n] = Block(t5,t5, 1);//red ring
                block[n].sprite.setPosition(blockWidth * (i + 1), blockHight * (j + 1) + 40);//Center the bloks
                n++;
            }
            else if (((j >= 3||j<=11) && (i == 3||i==24)) || (i>3&&i<25 && (j == 3 || j==11)) ) {
                block[n] = Block(t9,t10, 2);//second iron ring
                block[n].sprite.setPosition(blockWidth * (i + 1), blockHight * (j + 1) + 40);//Center the bloks
                n++;
            }
            else if (i > 3 && i < 6 || i>22 && i < 24 || j>3 && j < 6 || j>8 && j < 11) {
                block[n] = Block(t6,t6, 1);//blue ring
                block[n].sprite.setPosition(blockWidth * (i + 1), blockHight * (j + 1) + 40);//Center the bloks
                n++;
            }
            else {
                block[n]=Block(t1,t1, 1);
                block[n].sprite.setPosition(blockWidth * (i + 1), blockHight * (j + 1) + 40);//Center the bloks
                n++;
            }
            
        }
        
    }
    
    /*for (int i = 1; i <= 27; i++)
        for (int j = 1; j <= 12; j++)
        {
            block[n].setTexture(t1);
            block[n].setPosition(i * 45, j * 20);
            n++;
        }*/

    float dx = 0;
    float dy = 5;
    float x = 640;
    float y = 450;

    int score = 0;//Variable to keep track of points
    int highScore = 0;//variable to keep track of the high score
    int currentLevel = 1; // Initialize with the starting level number

    //Load high score from file
    std::ifstream file("./highscore.txt");
    if (file.is_open()) {
        file >> highScore;
        file.close();
    }



    Font font; // Added for text rendering
    font.loadFromFile("./arial.ttf"); // replace with the path to your font file

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

    //Level text
    Text levelText;
    levelText.setFont(font);
    levelText.setCharacterSize(25);
    levelText.setFillColor(Color::Black);
    levelText.setPosition(1140, 4); // Adjust the position 

    while (app.isOpen())
    {
        Event e;
        while (app.pollEvent(e))
        {
            if (e.type == Event::Closed)
                app.close();
        }

        x += dx;
        y += dy;
        for (int i = 0; i < n; i++)
            if (FloatRect(x + 3, y + 3, 6, 6).intersects(block[i].sprite.getGlobalBounds()))
            {
                
                if (block[i].resistance > 1)
                {                    
                    block[i].resistance--;                    
                    block[i].setTexture();
                }

                else {                    
                    block[i].sprite.setPosition(-100, 0);                    
                    score++; // Increment the score when a block is hit
                }
                
                if ((dx >= 0|| dx <= 0) && dy<0) {
                    dy = -dy;
                }
                else {
                    dx = -dx;
                }
                
            }
        
        


        if (x < 0 || x > 1280)
            dx = -dx;
        if (y < 40)
            dy = -dy;
        if (y > 720) return 0;

        if (Keyboard::isKeyPressed(Keyboard::Right)&&sPaddle.getPosition().x+sPaddle.getLocalBounds().width<1280)
            sPaddle.move(8, 0);
        if (Keyboard::isKeyPressed(Keyboard::Left) && sPaddle.getPosition().x>0)
            sPaddle.move(-8, 0);

        if (FloatRect(x, y, 12, 12).intersects(sPaddle.getGlobalBounds())) {
            dy = -5;
            if (Keyboard::isKeyPressed(Keyboard::Right) && dx <= 0)
                dx = dx - 1;
            if (Keyboard::isKeyPressed(Keyboard::Left) && dx >= 0)
                dx = dx + 1;
        }

        //Update the high score
        if (score > highScore) {
            highScore = score;

            //Save high score to file
            std::ofstream file("./highscore.txt");
            if (file.is_open()) {
                file << highScore;
                file.close();
            }
        }
        //Update the text strings
        highScoreText.setString("High Score: " + std::to_string(highScore));
        scoreText.setString("Score: " + std::to_string(score));

        //Update the level text
        levelText.setString("Level: " + std::to_string(currentLevel));
        app.clear();
        
        app.draw(sBackground);
        app.draw(bar);
        app.draw(sBall);
        app.draw(sPaddle);
        sBall.setPosition(x, y);
        for (int i = 0; i < n; i++)
            app.draw(block[i].sprite);


        //Draw the text
        app.draw(highScoreText);
        app.draw(scoreText);
        app.draw(levelText);

        app.display();
    }

    return 0;
}
