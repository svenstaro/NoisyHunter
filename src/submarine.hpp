#ifndef SUBMARINE_HPP_INCLUDED
#define SUBMARINE_HPP_INCLUDED

#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>

#include "entity.hpp"

// Submarine is a player controlled submarine
class Submarine : public IEntity {
public:
    Submarine(float init_pos_x, float init_pos_y, std::string image_path);
    sf::Drawable& GetDrawable();
    void Update(float dt);

private:
    float mPosX;
    float mPosY;
    sf::Image mImage;
    sf::Sprite mSprite;
};

#endif
