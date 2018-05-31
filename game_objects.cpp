#include "game_objects.h"

void MapObject::move(Map &map, int xoffset, int yoffset) {
    previous_position_ = position_;
    if ((position_.x + xoffset >= 0) && (position_.x + xoffset < map.getsize().x)) {
        position_.x += xoffset;
    }
    if ((position_.y + yoffset >= 0) && (position_.y + yoffset < map.getsize().y)) {
        position_.y += yoffset;
    }
}

void Monster::move(Player &player, Map &map, int xoffset, int yoffset) {
    MapObject::move(map,xoffset,yoffset);
    (rand() > RAND_MAX / 2) ?
            position_.x -= SGN(position_.x - player.get_position().x) :
            position_.y -= SGN(position_.y - player.get_position().y);
}

void Monster::collide(MapObject &that) {
    that.collide(*this);
}

void Monster::collide(Player &that) {
    that.collide(*this);
}

void Monster::collide(Wall &that) {
    if (that.get_position() == this->get_position()) {
        this->move_back();
    }
}

void Monster::collide(Monster &that) {
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
            objs.push_back(make_shared<Obstacle>(Obstacle(pnt{x, y})));
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

void Player::collide(Wall &that) {
    if (that.get_position() == this->get_position()) {
        this->move_back();
    }
}

void Player::collide(MapObject &that) {
    that.collide(*this);
}

void Player::collide(Player &that) {
}

void Player::collide(Monster &that) {
    this->damage(that.get_damage());
    that.damage(this->get_damage());
}

void Obstacle::collide(Player &that) {
}

void Obstacle::collide(Wall &that) {
}

void Obstacle::collide(Monster &that) {
}

void Obstacle::collide(MapObject &that) {
}

void Wall::collide(MapObject &that) {
    that.collide(*this);
}

void Wall::collide(Wall &that) {
}

void Wall::collide(Monster &that) {
    that.collide(*this);
}

void Wall::collide(Player &that) {
    that.collide(*this);
}

void Actor::collide(MapObject &that) {
}

void Actor::collide(Player &that) {
}

void Actor::collide(Wall &that) {
}

void Actor::collide(Monster &that) {
}

void Character::collide(MapObject &that) {
}

void Character::collide(Player &that) {
}

void Character::collide(Wall &that) {
}

void Character::collide(Monster &that) {
}

void Princess::collide(MapObject &that) {
}

void Princess::collide(Player &that) {
}

void Princess::collide(Wall &that) {
}

void Princess::collide(Monster &that) {
}
