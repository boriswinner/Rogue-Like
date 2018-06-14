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
    }
}
