#ifndef BUTTONS_H
#define BUTTONS_H
#include <SFML/Graphics.hpp>
#include <stdlib.h>
using namespace std;
class Button 
{
private:
    sf::RectangleShape buttonShape;
    sf::Text buttonText;

public:
    
    Button(const sf::Vector2f& position,  const sf::Vector2f& size,  const sf::Color& fillColor, const std::string& buttonText, const sf::Font& font, int characterSize);

    bool isClicked(const sf::Vector2f& mousePos) const;
    void draw(sf::RenderWindow& window);

    ~Button();
};

#endif
