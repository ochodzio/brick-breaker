#include "Txtrs.h"

Txtrs::Txtrs()
{
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
}

Texture Txtrs::getTxt(Texture txt)
{
	return txt;
}
