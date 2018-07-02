#pragma once
#include <algorithm>
#include "game_objects.h"
#include "curses.h"
//#include "config.h"

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

    void make_move(int key, int hp = 0, int dmg = 0);

protected:
    void check_keys(int key, int hp = 0, int dmg = 0);

    void replace_player_cell(const shared_ptr<MapObject> &obj);

    void clear_player_cell();

    void export_to_file();
};