#pragma once
#include <SFML/Graphics.hpp>
#include <time.h>
#include <fstream> // added for file handling
#include <string>// adde for string manipulation
#include <iostream>
using namespace sf;
struct Block {
    public:
    Sprite sprite;
    int resistance;
    Texture texture1;
    Texture texture2;
    Texture texture3;
    Block(Texture& texture1, Texture& texture2, Texture& texture3, int resistance);
    Block();
    void setTexture();
};

