#include "game_manager.h"

void GameManager::make_move(int key) {
    for (int i = 0; i < cells_.size(); i++) {
        for (int j = 0; j < cells_[i].size(); j++) {
            for (int z = 0; z < cells_[i][j].size(); z++) {
                cells_[i][j][z]->move(map_, 0, 0);
            }
        }
    }
    check_keys(key);
    map_.recontruct();

    for (int i = 0; i < cells_.size(); i++) {
        for (int j = 0; j < cells_[i].size(); j++) {
            for (int z = 0; z < cells_[i][j].size(); z++) {
                if (z < cells_[i][j].size() - 1) {
                    for (int f = z + 1; f < cells_[i][j].size(); ++f) {
                        cells_[i][j][z]->collide(*cells_[i][j][f]);
                    }
                }
            }
        }
    }
    map_.recontruct();
    if (map_.player->get_hp() <= 0){
        lose_game();
    }
    if (map_.princess->collided_with_player()){
        win_game();
    }
}

void GameManager::check_keys(int key) {
    if (key == 's') {
        map_.player->move(map_, 0, 1);
    } else if (key == 'w') {
        map_.player->move(map_, 0, -1);
    } else if (key == 'a') {
        map_.player->move(map_, -1, 0);
    } else if (key == 'd') {
        map_.player->move(map_, 1, 0);
    } else if (key == 'i') {
        int x = map_.player->get_position().x;
        int y = map_.player->get_position().y;
        map_.add_object(make_shared<Bullet>(pnt{x, y-1}, pnt{0,-1}, 10, '*'));
    } else if (key == 'k') {
        int x = map_.player->get_position().x;
        int y = map_.player->get_position().y;
        map_.add_object(make_shared<Bullet>(pnt{x, y+1}, pnt{0,1}, 10, '*'));
    } else if (key == 'j') {
        int x = map_.player->get_position().x;
        int y = map_.player->get_position().y;
        map_.add_object(make_shared<Bullet>(pnt{x-1, y}, pnt{-1,0}, 10, '*'));
    } else if (key == 'l') {
        int x = map_.player->get_position().x;
        int y = map_.player->get_position().y;
        map_.add_object(make_shared<Bullet>(pnt{x+1, y}, pnt{1,0}, 10, '*'));
    } else if (key == 'x'){
        win_game();
    }
}
