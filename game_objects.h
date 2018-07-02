#pragma once
#include <vector>
#include <memory>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>

#pragma once
#define SGN(x) (((x) > 0) - ((x) < 0))


typedef struct Point {
    int x, y;

    bool operator==(const Point &that) {
        return (this->x == that.x && this->y == that.y);
    }
} pnt;

using namespace std;

class Map;

class Player;

class Wall;

class Monster;

class Healer;

class Bullet;

class Bomb;

class Princess;

class MapObject {
public:
    explicit MapObject(pnt position, char image) : image_(image), position_(position),
                                                   previous_position_(pnt{0, 0}), exists_(true) {}

    pnt get_position() const {
        return position_;
    }

    void set_position(pnt position) {
        position_ = position;
    }

    char get_image() const {
        return image_;
    }

    virtual void move(const Map &map, int xoffset, int yoffset);

    void move_back() {
        position_ = previous_position_;
    }

    void remove() {
        exists_ = false;
    }

    void deremove(){
        exists_ = true;
    }

    bool exists() const {
        return exists_;
    }

    virtual string export_obj() const{
        stringstream ss;
        ss << get_image() << " " << get_position().x << " " << get_position().y << " ";
        return ss.str();
    }

    virtual void collide(MapObject &that) = 0;

    virtual void collide(Player &that) = 0;

    virtual void collide(Wall &that) = 0;

    virtual void collide(Monster &that) = 0;

    virtual void collide(Healer &that) = 0;

    virtual void collide(Bullet &that) = 0;

    virtual void collide(Bomb &that) = 0;

    virtual void collide(Princess &that) = 0;

protected:
    pnt position_;
    pnt previous_position_;
    const char image_;
    bool exists_;
};

class Obstacle : public MapObject {
public:
    explicit Obstacle(pnt position, char image) : MapObject(position, image) {
    }

    void collide(MapObject &that) override{}

    void collide(Player &that) override{}

    void collide(Wall &that) override {}

    void collide(Monster &that) override {}

    void collide(Healer &that) override {}

    void collide(Bullet &that) override {}

    void collide(Bomb &that) override {}

    void collide(Princess &that) override {}
};

class Floor : public Obstacle {
public:
    explicit Floor(pnt position, char image) : Obstacle(position, image) {
    }
    void collide(MapObject &that) override;

    void collide(Player &that) override;

    void collide(Wall &that) override;

    void collide(Monster &that) override;

    void collide(Healer &that) override;

    void collide(Bullet &that) override {}

    void collide(Bomb &that) override {}

    void collide(Princess &that) override {}

    string export_obj() const override {
        stringstream ss;
        ss << MapObject::export_obj() << "0 0";
        return ss.str();
    }

};

class Wall : public Obstacle {
public:
    explicit Wall(pnt position, char image) : Obstacle(position, image) {
    }

    void collide(MapObject &that) override;

    void collide(Player &that) override;

    void collide(Wall &that) override;

    void collide(Monster &that) override;

    void collide(Healer &that) override;

    void collide(Bullet &that) override;

    void collide(Bomb &that) override {}

    void collide(Princess &that) override {}

    string export_obj() const override {
        stringstream ss;
        ss << MapObject::export_obj() << "0 0";
        return ss.str();
    }
};

class Healer : public Obstacle {
private:
    int healValue_;
public:
    explicit Healer(pnt position, int healValue, char image) : Obstacle(position, image), healValue_(healValue) {
    }

    int get_heal_value() const {
        return healValue_;
    }

    void collide(MapObject &that) override;

    void collide(Player &that) override;

    void collide(Wall &that) override;

    void collide(Monster &that) override;

    void collide(Healer &that) override;

    void collide(Bullet &that) override {}

    void collide(Bomb &that) override {}

    void collide(Princess &that) override {}

    string export_obj() const override {
        stringstream ss;
        ss << MapObject::export_obj() << healValue_ << " 0";
        return ss.str();
    }
};

class Weapon: public Obstacle{
public:
    explicit Weapon(pnt position, pnt direction, int damage, char image): Obstacle(position, image), direction_(direction), damage_(damage){}

    int get_damage(){
        return damage_;
    }

    pnt get_direction(){
        return direction_;
    }
private:
    int damage_;
    pnt direction_;
};

class Bullet: public Weapon{
public:
    explicit Bullet(pnt position, pnt direction, int damage, char image): Weapon(position, direction, damage, image){}

    void move(const Map &map, int xoffset = 0, int yoffset = 0) override;

public:
    void collide(MapObject &that) override {};

    void collide(Player &that) override {};

    void collide(Wall &that) override;

    void collide(Monster &that) override;

    void collide(Healer &that) override {};

    void collide(Bullet &that) override {}

    void collide(Bomb &that) override {}

    void collide(Princess &that) override {}
};

class Bomb: public Weapon{
public:
    explicit Bomb(pnt position, pnt direction, int damage, int radius, char image): Weapon(position, direction, damage, image), radius_(radius){}

private:
    int radius_;
};

class Actor : public MapObject {
public:
    explicit Actor(pnt position, char image) : MapObject(position, image) {
    }

    void collide(MapObject &that) override;

    void collide(Player &that) override;

    void collide(Wall &that) override;

    void collide(Monster &that) override;

    void collide(Healer &that) override;

    void collide(Bullet &that) override {}

    void collide(Bomb &that) override {}

    void collide(Princess &that) override {}
};

class Character : public Actor {
protected:
    int hp_;
    int damage_;
public:
    Character(pnt position, int hp, int damage, char image) : Actor(position, image) {
        position_ = position;
        hp_ = hp;
        damage_ = damage;
    }

    int get_hp() const {
        return hp_;
    }

    void set_hp(int hp) {
        hp_ = hp;
    }

    void heal(int hp) {
        hp_ += hp;
    }

    int get_damage() const {
        return damage_;
    }

    void set_damage(int damage) {
        damage_ = damage;
    }

    void damage(int damage) {
        this->hp_ -= damage;
    }

    string export_obj() const override {
        stringstream ss;
        ss << MapObject::export_obj() << damage_<< " " << hp_;
        return ss.str();
    }

    void collide(MapObject &that) override;

    void collide(Player &that) override;

    void collide(Wall &that) override;

    void collide(Monster &that) override;

    void collide(Healer &that) override;

    void collide(Bullet &that) override {}

    void collide(Bomb &that) override {}

    void collide(Princess &that) override {}

};

class Player : public Character {
public:
    Player(pnt position, int hp, int damage, char image) : Character(position, hp, damage, image) {}

    void collide(MapObject &that) override;

    void collide(Player &that) override;

    void collide(Wall &that) override;

    void collide(Monster &that) override;

    void collide(Healer &that) override;

    void collide(Bullet &that) override {}

    void collide(Bomb &that) override {}

    void collide(Princess &that) override;
};

class Princess : public Character {
public:
    Princess(pnt position, int hp, int damage, char image) : Character(position, hp, damage, image), collided_with_player_(
            false) {}

    bool collided_with_player(){
        return collided_with_player_;
    }
    void collide_with_player(){
        collided_with_player_ = true;
    }

    void collide(MapObject &that) override;

    void collide(Player &that) override;

    void collide(Wall &that) override;

    void collide(Monster &that) override;

    void collide(Healer &that) override;

    void collide(Bullet &that) override {}

    void collide(Bomb &that) override {}

    void collide(Princess &that) override {}

private:
    bool collided_with_player_;
};

class Monster : public Character {
public:
    Monster(pnt position, int hp, int damage, char image) : Character(position, hp, damage, image) {}

    void move(const Map &map, int xoffset = 0, int yoffset = 0) override;

    void collide(MapObject &that) override;

    void collide(Player &that) override;

    void collide(Wall &that) override;

    void collide(Monster &that) override;

    void collide(Healer &that) override;

    void collide(Bullet &that) override;

    void collide(Bomb &that) override {}

    void collide(Princess &that) override {}
};

class Map {
private:
    int sizex_, sizey_;
    vector<shared_ptr<MapObject>> objs_;
    vector<vector<vector<shared_ptr<MapObject>>>> cells;
public:
    shared_ptr<Player> player;
    shared_ptr<Princess> princess;
public:
    explicit Map(const string &filename);

    void recontruct();

    pnt getsize() const {
        return {sizex_, sizey_};
    }

    void setsize(int sizex, int sizey) {
        sizex_ = sizex;
        sizey_ = sizey;
    }

    void read_objects_from_file(const string &filename);

    void add_object(const shared_ptr<MapObject> &obj){
        objs_.push_back(obj);
    }

    vector<vector<vector<shared_ptr<MapObject>>>> &get_map() {
        return cells;
    }

    vector<shared_ptr<MapObject>> &get_objs(){
        return objs_;
    }

    int objs_count(){
        return objs_.size();
    }
};