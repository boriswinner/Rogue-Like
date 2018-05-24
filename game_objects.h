#include <vector>
#include <memory>
#include <cstdlib>
#include <fstream>

#pragma once
#define SGN(x) (((x) > 0) - ((x) < 0))


typedef struct Point {
    int x, y;

    bool operator==(const Point& that){
        return (this->x == that.x && this->y == that.y);
    }
} pnt;

using namespace std;

class Map;
class Player;
class Wall;
class Monster;

class MapObject {
protected:
    pnt position_;
    pnt previous_position_;
    const char image_;
public:
    explicit MapObject(pnt position, char image = '*') : image_(image), position_(position), previous_position_(pnt{0,0}) {
    }

    pnt get_position() const {
        return position_;
    }

    void set_position(pnt position) {
        position_ = position;
    }

    char get_image() const {
        return image_;
    }

    virtual void move(Map &map, int xoffset = 0, int yoffset = 0);
    virtual void move(Player &player, Map &map, int xoffset = 0, int yoffset = 0){};

    void move_back(){
        position_ = previous_position_;
    }

    virtual void collide(MapObject& that){
        return;
    }
    virtual void collide(Player& that){
        return;
    }
    virtual void collide(Wall& that){
        return;
    }
    virtual void collide(Monster& that){
        return;
    }
};

class Obstacle : public MapObject {
public:
    explicit Obstacle(pnt position, char image = '*') : MapObject(position, image) {
    }
};

class Wall : public Obstacle{
public:
    explicit Wall(pnt position, char image = '&') : Obstacle(position, image) {
    }

    void collide(Player& that) override;
};

class Actor : public MapObject {
public:
    explicit Actor(pnt position, char image = '*') : MapObject(position, image) {
    }
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

    int get_damage() const {
        return damage_;
    }

    void set_damage(int damage) {
        damage_ = damage;
    }
};

class Player : public Character {
public:
    Player(pnt position, int hp, int damage) : Character(position, hp, damage, 'P') {}

    void collide(Wall& that) override;
};

class Princess : public Character {
public:
    Princess(pnt position, int hp, int damage) : Character(position, hp, damage, '&') {}
};

class Monster : public Character {
public:
    Monster(pnt position, int hp, int damage) : Character(position, hp, damage, '#') {}

    void move(Player &player, Map &map, int xoffset = 0, int yoffset = 0) override;
};

class Map {
private:
    int sizex_, sizey_;
    vector<shared_ptr<MapObject>> objs;
    vector<vector<vector<shared_ptr<MapObject>>>> cells;
public:
    shared_ptr<Player> player;
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

    void add_to_cell(int x, int y, MapObject *object) {
        //cells[x][y].erase(cells[x][y].begin(),cells[x][y].end());
        //cells[x][y].push_back(object);
    }

    vector<vector<vector<shared_ptr<MapObject>>>> &get_map() {
        return cells;
    }
};