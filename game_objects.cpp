#include "game_objects.h"

void MapObject::move(Player& player, Map& map, const int xoffset, const int yoffset) {
    if ((position_.x + xoffset >=0) && (position_.x + xoffset < map.getsize().x)){
        position_.x += xoffset;
    }
    if ((position_.y + yoffset >=0) && (position_.y + yoffset < map.getsize().y)){
        position_.y += yoffset;
    }
}
