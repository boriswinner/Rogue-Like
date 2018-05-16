#include "game_objects.h"

void MapObject::move(Player &player, Map &map, int xoffset, int yoffset) {
    previous_position_ = position_;
    if ((position_.x + xoffset >= 0) && (position_.x + xoffset < map.getsize().x)) {
        position_.x += xoffset;
    }
    if ((position_.y + yoffset >= 0) && (position_.y + yoffset < map.getsize().y)) {
        position_.y += yoffset;
    }
}

void Monster::move(Player &player, Map &map, int xoffset, int yoffset) {
    (rand() > RAND_MAX / 2) ?
            position_.x -= SGN(position_.x - player.get_position().x) :
            position_.y -= SGN(position_.y - player.get_position().y);
}

void Map::read_objects_from_file(const string &filename) {
    ifstream map_file;
    map_file.open(filename);
    int size, mapsize_x, mapsize_y;
    map_file >> size >> mapsize_x >> mapsize_y;
    objs.reserve(size);
    setsize(mapsize_x, mapsize_y);
    char symbol = '*';
    int damage, hp, x = 0, y = 0;
    for (int i = 0; i < size; ++i) {
        map_file >> symbol >> x >> y >> damage >> hp;
        if (symbol == '*') {
            objs.push_back(make_shared<MapObject>(MapObject(pnt{x, y})));
        } else if (symbol == 'P') {
            player = make_shared<Player>(pnt{x, y}, hp, damage);
            objs.push_back(player);
        } else if (symbol == '#') {
            objs.push_back(make_shared<Monster>(pnt{x, y}, hp, damage));
        } else if (symbol == '&') {
            objs.push_back(make_shared<Wall>(pnt{x, y}));
        }
    }
}

void Map::recontruct() {
    for (int i = 0; i < sizey_; ++i) {
        for (int j = 0; j < sizex_; ++j) {
            cells[i][j].clear();
        }
    }
    for (int i = 0; i < objs.size(); ++i) {
        pnt pos = objs[i]->get_position();
        cells[pos.y][pos.x].push_back(objs[i]);
    }
}

Map::Map(const string &filename) {
    read_objects_from_file(filename);
    cells.resize(sizey_);
    for (int i = 0; i < sizey_; ++i) {
        cells[i].resize(sizex_);
    }
    recontruct();
}
