#include "game_objects.h"

void Character::move(const int xoffset, const int yoffset) {
    if (position_.x + xoffset >=0){
        position_.x += xoffset;
    }
    if (position_.y + yoffset >=0){
        position_.y += yoffset;
    }
}
