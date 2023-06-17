#include "Blocks.h"
#include <SFML/Graphics.hpp>
#include <time.h>
#include <fstream> // added for file handling
#include <string>// adde for string manipulation
#include <iostream>


   

Block::Block(Texture& texture1, Texture& texture2, Texture& texture3, int resistance)
    : texture1(texture1), texture2(texture2), texture3(texture3), resistance(resistance)
{
    sprite.setTexture(texture1);
};
Block::Block() {};

    void Block:: setTexture() {
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
    };
