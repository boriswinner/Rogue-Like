#include <algorithm>
#include "game_objects.h"
#include "curses.h"
enum game_statuses{victory=2,defeat=1,isrunning=0};

class GameManager {
public:
    explicit GameManager(const string &map_file_name) : map_(map_file_name), cells_(map_.get_map()), game_status_(isrunning) {}

    int game_status() {
        return game_status_;
    }

    void start_game() {
        map_.recontruct();
    }

    virtual void make_move(int key);

    virtual void check_keys(int key);

    void win_game() {
        game_status_ = victory;
    }

    void lose_game(){
        game_status_ = defeat;
    }

    Map &get_map() {
        return map_;
    }

protected:
    Map map_;
    vector<vector<vector<shared_ptr<MapObject>>>> &cells_;
    int game_status_;
};

class MapEditorManager : public GameManager {
public:
    explicit MapEditorManager(const string &mapfilename) : GameManager(mapfilename) {}

    void make_move(int key, int hp = 0, int dmg = 0) {
//        map_.recontruct();
        check_keys(key, hp, dmg);
        map_.recontruct();
    }

protected:
    void check_keys(int key, int hp = 0, int dmg = 0) {
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

    void replace_player_cell(const shared_ptr<MapObject> &obj) {
        clear_player_cell();
        map_.add_object(obj);
    }

    void clear_player_cell() {
        for (int i = 0; i < cells_[map_.player->get_position().y][map_.player->get_position().x].size(); ++i) {
            cells_[map_.player->get_position().y][map_.player->get_position().x][i]->remove();
        }
        map_.player->deremove();
        map_.add_object(make_shared<Floor>(pnt{map_.player->get_position().x, map_.player->get_position().y}, ' '));
    }

    void export_to_file() {
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
};