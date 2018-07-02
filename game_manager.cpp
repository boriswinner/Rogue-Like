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

void MapEditorManager::make_move(int key, int hp, int dmg) {
//        map_.recontruct();
    check_keys(key, hp, dmg);
    map_.recontruct();
}

void MapEditorManager::check_keys(int key, int hp, int dmg) {
    GameManager::check_keys(key);
    if (key == '1') {
        replace_player_cell(
                make_shared<Wall>(pnt{map_.player->get_position().x, map_.player->get_position().y}, '#'));
    } else if (key == '2') {
        replace_player_cell(
                make_shared<Monster>(pnt{map_.player->get_position().x, map_.player->get_position().y}, hp, dmg,
                                     '&'));
    } else if (key == '3') {
        replace_player_cell(
                make_shared<Healer>(pnt{map_.player->get_position().x, map_.player->get_position().y}, hp, '@'));
    } else if (key == '4') {
        clear_player_cell();
    } else if (key == '0'){
        export_to_file();
    } else if (key == '5'){
        replace_player_cell(
                make_shared<Princess>(pnt{map_.player->get_position().x, map_.player->get_position().y}, 1, 0, '+'));
    }
}

void MapEditorManager::replace_player_cell(const shared_ptr<MapObject> &obj) {
    clear_player_cell();
    map_.add_object(obj);
}

void MapEditorManager::clear_player_cell() {
    for (int i = 0; i < cells_[map_.player->get_position().y][map_.player->get_position().x].size(); ++i) {
        cells_[map_.player->get_position().y][map_.player->get_position().x][i]->remove();
    }
    map_.player->deremove();
    map_.add_object(make_shared<Floor>(pnt{map_.player->get_position().x, map_.player->get_position().y}, ' '));
}

void MapEditorManager::export_to_file() {
    ofstream out;
    vector<string> objects_strings;
    out.open("output.txt");
    out << map_.objs_count() << ' ' << map_.getsize().x << ' ' << map_.getsize().y << '\n';
    for (int i = 0; i < map_.get_objs().size(); ++i){
        if (map_.get_objs()[i]->exists()) {
            objects_strings.push_back(map_.get_objs()[i]->export_obj() + string{'\n'});
        }
    }
    sort (objects_strings.begin(), objects_strings.end());
    for (int i = 0; i < objects_strings.size(); ++i){
        out << objects_strings[i];
    }
    out.close();
}
