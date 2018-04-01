#include <vector>
#ifndef ROG_GAMEOBJECTS_H
#define ROG_GAMEOBJECTS_H
#endif //ROG_GAMEOBJECTS_H

typedef struct Point {
    int x, y;
} pnt;

using namespace std;

class MapObject{
protected:
    pnt position_;
    const char image_;
public:
    pnt get_position() const{
        return position_;
    }

    void set_position(pnt position){
        position_ = position;
    }
};

class Character: public MapObject{
private:
    pnt position_;
    int hp_;
    int damage_;

public:
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

    char get_image() const{
        return image_;
    }

    void move(Map& map, const int xoffset, const int yoffset){
        vector <vector <vector <MapObject*>>> &cells = map.get_map();
        for (int i = 0; i < cells[position_.x][position_.y].size(); ++i){
            if (cells[position_.x][position_.y][i] == this){
                cells[position_.x][position_.y].erase(cells[position_.x][position_.y].begin() + i);
            }
        }
        position_.x += xoffset;
        position_.y += yoffset;
        map.add_to_cell(position_.x,position_.y,this);
    }
};

class Player: public Character{
    const char image_ = '*';
};

class Map{
private:
    const int sizex_,sizey_;
    vector <vector <vector <MapObject*>>> cells;
public:
    Map(const unsigned int sizex, const unsigned int sizey, vector <MapObject> &objects): sizex_(sizex), sizey_(sizey){
        vector <vector <vector <MapObject*>>> cells = vector <vector <vector <MapObject*>>>(sizex);
        for (int i = 0; i < sizex; ++i){
            cells[i].reserve(sizey);
        }
        for (int i = 0; i <= objects.size(); ++i){
            pnt pos = objects[i].get_position();
            cells[pos.x][pos.y].push_back(&objects[i]);
        }
    }

    void add_to_cell(int x, int y, MapObject* object){
        //cells[x][y].erase(cells[x][y].begin(),cells[x][y].end());
        cells[x][y].push_back(object);
    }

    vector <vector <vector <MapObject*>>> &get_map(){
        return cells;
    }
};