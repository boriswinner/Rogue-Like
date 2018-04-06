#include "game_objects.h"

void Character::move(const int xoffset, const int yoffset) {
    /*vector <vector <vector <shared_ptr<MapObject>>>> &cells = map.get_map();
    for (int i = 0; i < cells[position_.x][position_.y].size(); ++i){
        if (cells[position_.x][position_.y][i] == this){
            cells[position_.x][position_.y].erase(cells[position_.x][position_.y].begin() + i);
        }
    }*/
    position_.x += xoffset;
    position_.y += yoffset;
    //map.add_to_cell(position_.x,position_.y,this);
}
