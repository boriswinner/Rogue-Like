#include <vector>
#include <memory>
#ifndef ROG_GAMEOBJECTS_H
#define ROG_GAMEOBJECTS_H
#endif //ROG_GAMEOBJECTS_H

typedef struct Point {
    int x, y;
} pnt;

using namespace std;

class Map;

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
};

class Character: public MapObject{
protected:
    int hp_;
    int damage_;

public:
    Character(pnt position, int hp, int damage, char image) : MapObject(position,image) {
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

    void move(const int xoffset, const int yoffset);
};

class Player: public Character{
public:
    Player(pnt position, int hp, int damage) : Character(position, hp, damage, 'P'){}
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