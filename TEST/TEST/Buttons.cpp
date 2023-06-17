#include "Buttons.h"

Button::Button(const sf::Vector2f& position,  const sf::Vector2f& size,  const sf::Color& fillColor, const std::string& tbuttonText, const sf::Font& font, int characterSize)
{
    buttonShape.setSize(size);
    buttonShape.setPosition(position);
    buttonShape.setFillColor(fillColor);

    buttonText.setString(tbuttonText);
    buttonText.setFont(font);
    buttonText.setCharacterSize(characterSize);
    buttonText.setPosition(position.x + (size.x - buttonText.getLocalBounds().width) / 2,
        position.y + (size.y - buttonText.getLocalBounds().height) / 2);
}

Button::~Button()
{
    
}

bool Button::isClicked(const sf::Vector2f& mousePos) const
{
    return buttonShape.getGlobalBounds().contains(mousePos);
}

void Button::draw(sf::RenderWindow& window)
{
    window.draw(buttonShape);
    window.draw(buttonText);
}

