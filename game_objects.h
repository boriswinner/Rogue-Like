#include <vector>
#include <memory>
#include <cstdlib>

#ifndef ROG_GAMEOBJECTS_H
#define ROG_GAMEOBJECTS_H
#endif //ROG_GAMEOBJECTS_H
#define SGN(x) ((x > 0) - (x < 0))


typedef struct Point {
    int x, y;
} pnt;

using namespace std;

class Map;
class Player;

class MapObject{
protected:
    pnt position_;
    const char image_;
public:
    explicit MapObject( pnt position, char image = '*'):image_(image),position_(position){
    }

    pnt get_position() const{
        return position_;
    }

    void set_position(pnt position){
        position_ = position;
    }

    char get_image() const{
        return image_;
    }
    virtual void move(const int xoffset, const int yoffset);
    virtual void move(Player& player){};
};

class Obstacle: public MapObject{
public:
    explicit Obstacle( pnt position, char image = '*'): MapObject(position,image){
    }
};

class Actor: public MapObject{
public:
    explicit Actor( pnt position, char image = '*'): MapObject(position,image){
    }
};

class Character: public Actor{
protected:
    int hp_;
    int damage_;
public:
    Character(pnt position, int hp, int damage, char image) : Actor(position,image) {
        position_ = position;
        hp_ = hp;
        damage_ = damage;
    }

    int get_hp() const{
        return hp_;
    }

    void set_hp(int hp){
        hp_ = hp;
    }

    int get_damage() const{
        return damage_;
    }

    void set_damage(int damage){
        damage_ = damage;
    }
};

class Player: public Character{
public:
    Player(pnt position, int hp, int damage) : Character(position, hp, damage, 'P'){}
};

class Princess: public Character{
public:
    Princess(pnt position, int hp, int damage) : Character(position, hp, damage, '&'){}
};

class Monster: public Character{
public:
    Monster(pnt position, int hp, int damage) : Character(position, hp, damage, '#'){}
    virtual void move(Player& player) override {
        (rand() > RAND_MAX/2) ?
                position_.x -= SGN(position_.x - player.get_position().x) :
                position_.y -= SGN(position_.y - player.get_position().y);
    };
};

class Map{
private:
    const int sizex_,sizey_;
    vector<shared_ptr<MapObject>> objs;
    vector <vector <vector <shared_ptr<MapObject>>>> cells;
public:
    Map(const unsigned int sizex, const unsigned int sizey, vector<shared_ptr<MapObject>> &objects): sizex_(sizex), sizey_(sizey){
        cells.resize(sizey);
        //vector <vector <vector <shared_ptr<MapObject>>>> cells = vector <vector <vector <shared_ptr<MapObject>>>>(sizex);
        for (int i = 0; i < sizey; ++i){
            cells[i].resize(sizex);
        }
        for (int i = 0; i < objects.size(); ++i){
            pnt pos = objects[i]->get_position();
            cells[pos.y][pos.x].push_back(objects[i]);
        }
    }

    void add_to_cell(int x, int y, MapObject* object){
        //cells[x][y].erase(cells[x][y].begin(),cells[x][y].end());
        //cells[x][y].push_back(object);
    }

    vector <vector <vector <shared_ptr<MapObject>>>> &get_map(){
        return cells;
    }
};