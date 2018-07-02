#include "game_objects.h"

void MapObject::move(const Map &map, int xoffset, int yoffset) {
    previous_position_ = position_;
    //does MapObject really need to know map borders?
    if ((position_.x + xoffset >= 0) && (position_.x + xoffset < map.getsize().x)) {
        position_.x += xoffset;
    }
    if ((position_.y + yoffset >= 0) && (position_.y + yoffset < map.getsize().y)) {
        position_.y += yoffset;
    }
}

void Monster::move(const Map &map, int xoffset, int yoffset) {
    MapObject::move(map, xoffset, yoffset);
    (rand() > RAND_MAX / 2) ?
            position_.x -= SGN(position_.x - map.player->get_position().x) :
            position_.y -= SGN(position_.y - map.player->get_position().y);
}

void Monster::collide(MapObject &that) {
    that.collide(*this);
}

void Monster::collide(Player &that) {
    that.collide(*this);
}

void Monster::collide(Wall &that) {
    this->move_back();
}

void Monster::collide(Monster &that) {
}

void Monster::collide(Healer &that) {
    Character::collide(that);
}

void Monster::collide(Bullet &that) {
    that.collide(*this);
}

void Map::read_objects_from_file(const string &filename) {
    ifstream map_file;
    map_file.open(filename);
    int size, mapsize_x, mapsize_y;
    map_file >> size >> mapsize_x >> mapsize_y;
    objs_.reserve(size);
    setsize(mapsize_x, mapsize_y);
    char symbol = ' ';
    int damage, hp, x = 0, y = 0;
    for (int i = 0; i < size; ++i) {
        map_file.get(symbol); //to skip newline
        map_file.get(symbol);
        map_file >>  x >> y >> damage >> hp;
        if (symbol == ' ') {
            objs_.push_back(make_shared<Floor>(Floor(pnt{x, y},' ')));
        } else if (symbol == 'P') {
            player = make_shared<Player>(pnt{x, y}, hp, damage,'P');
            objs_.push_back(player);
        } else if (symbol == '&') {
            objs_.push_back(make_shared<Monster>(pnt{x, y}, hp, damage,'&'));
        } else if (symbol == '#') {
            objs_.push_back(make_shared<Wall>(pnt{x, y},'#'));
        } else if (symbol == '@') {
            objs_.push_back(make_shared<Healer>(pnt{x, y}, damage, '@'));
        } else if (symbol == '+'){
            princess = make_shared<Princess>(pnt{x, y}, hp, damage, '+');
            objs_.push_back(princess);
        }
    }
}

void Map::recontruct() {
    for (int i = 0; i < sizey_; ++i) {
        for (int j = 0; j < sizex_; ++j) {
            cells[i][j].clear();
        }
    }
    for (int i = 0; i < objs_.size(); ++i) {
        if (objs_[i]->exists()) {
            pnt pos = objs_[i]->get_position();
            cells[pos.y][pos.x].push_back(objs_[i]);
        }
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
    this->move_back();
}

void Player::collide(MapObject &that) {
    that.collide(*this);
}

void Player::collide(Player &that) {
}

void Player::collide(Monster &that) {
    this->damage(that.get_damage());
    that.damage(this->get_damage());
    if (that.get_hp() <= 0) {
        that.remove();
    }
    if (this->get_hp() <= 0) {
        this->remove();
    }
}

void Player::collide(Healer &that) {
    that.collide(*this);
}

void Player::collide(Princess &that) {
    that.collide_with_player();
}

void Floor::collide(Player &that) {
}

void Floor::collide(Wall &that) {
}

void Floor::collide(Monster &that) {
}

void Floor::collide(MapObject &that) {
}

void Floor::collide(Healer &that) {

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

void Wall::collide(Healer &that) {
    Obstacle::collide(that);
}

void Wall::collide(Bullet &that) {
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

void Actor::collide(Healer &that) {

}

void Character::collide(MapObject &that) {
}

void Character::collide(Player &that) {
}

void Character::collide(Wall &that) {
}

void Character::collide(Monster &that) {
}

void Character::collide(Healer &that) {
    Actor::collide(that);
}

void Princess::collide(MapObject &that) {
    that.collide(*this);
}

void Princess::collide(Player &that) {
    that.collide(*this);
}

void Princess::collide(Wall &that) {
}

void Princess::collide(Monster &that) {
}

void Princess::collide(Healer &that) {
    Character::collide(that);
}

void Healer::collide(MapObject &that) {
    that.collide(*this);
}

void Healer::collide(Player &that) {
    that.heal(this->get_heal_value());
    this->remove();
}

void Healer::collide(Healer &that) {
}

void Healer::collide(Wall &that) {
}

void Healer::collide(Monster &that) {
}

void Bullet::collide(Monster &that) {
    that.damage(this->get_damage());
    if (that.get_hp() <= 0) that.remove();
    this->remove();
}

void Bullet::move(const Map &map, int xoffset, int yoffset) {
    MapObject::move(map, get_direction().x, get_direction().y);
}

void Bullet::collide(Wall &that) {
    this->remove();
}
