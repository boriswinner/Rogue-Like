#include <vector>
#include <memory>
#include <cstdlib>
#include <fstream>

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
    virtual void move(Player& player, Map& map, const int xoffset = 0, const int yoffset = 0);
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
    virtual void move(Player& player, Map& map, const int xoffset = 0, const int yoffset = 0) override {
        (rand() > RAND_MAX/2) ?
                position_.x -= SGN(position_.x - player.get_position().x) :
                position_.y -= SGN(position_.y - player.get_position().y);
    };
};

class Map{
private:
    unsigned int sizex_,sizey_;
    vector<shared_ptr<MapObject>> objs;
    vector <vector <vector <shared_ptr<MapObject>>>> cells;
public:
    shared_ptr<Player> player;
public:
    Map(const string &filename){
        read_objects_from_file(filename);
        cells.resize(sizey_);
        for (int i = 0; i < sizey_; ++i){
            cells[i].resize(sizex_);
        }
        recontruct();
    }

    void recontruct() {
        for (int i = 0; i < sizey_; ++i){
            for (int j = 0; j < sizex_; ++j){
                cells[i][j].clear();
            }
        }
        for (int i = 0; i < objs.size(); ++i) {
            pnt pos = objs[i]->get_position();
            cells[pos.y][pos.x].push_back(objs[i]);
        }
    }

    pnt getsize(){
        return {sizex_,sizey_};
    }

    pnt setsize(unsigned int sizex, unsigned int sizey){
        sizex_ = sizex;
        sizey_ = sizey;
    }

    void read_objects_from_file(const string &filename){
        ifstream map_file;
        map_file.open(filename);
        unsigned int size, mapsize_x, mapsize_y;
        map_file >> size >> mapsize_x >> mapsize_y;
        objs.reserve(size);
        setsize(mapsize_x,mapsize_y);
        char symbol = '*';
        int damage, hp, x = 0, y = 0;
        for (int i = 0; i < size; ++i){
            map_file >> symbol >> x >> y >> damage >> hp;
            if (symbol == '*'){
                objs.push_back(make_shared<MapObject>(MapObject(pnt{x,y})));
            } else if (symbol == 'P'){
                player = make_shared<Player>(pnt{x,y},hp,damage);
                objs.push_back(player);
            } else if (symbol == '#'){
                objs.push_back(make_shared<Monster>(pnt{x,y},hp,damage));
            }
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