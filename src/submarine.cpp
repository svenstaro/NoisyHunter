#include "submarine.hpp"

Submarine::Submarine(float init_pos_x, float init_pos_y, std::string image_path) {
    mPosX = init_pos_x;
    mPosY = init_pos_y;

    if(!mImage.LoadFromFile(image_path)) {
        std::cout << "WARNING: Failed to load image " << image_path << " for Submarine" << std::endl;
        mImage.LoadFromFile("gfx/missing.png"); // dummy texture
    }
    mSprite.SetImage(mImage);
}

sf::Drawable& Submarine::GetDrawable() {
    return mSprite;
}

void Submarine::Update(float dt) {
}
