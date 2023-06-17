#include "Texts.h"

Texts::Texts(const sf::Font& font)
{
    highScoreText.setFont(font);
    highScoreText.setCharacterSize(25);
    highScoreText.setFillColor(Color::Black);
    highScoreText.setPosition(7, 4);

    scoreText.setFont(font);
    scoreText.setCharacterSize(25);
    scoreText.setFillColor(Color::Black);
    scoreText.setPosition(600, 4);
    scoreText.setOrigin(scoreText.getLocalBounds().width / 2.0f, 0); // center the text horizontally
}
void Texts::draw(sf::RenderWindow& window)
{
    window.draw(highScoreText);
    window.draw(scoreText);
}
