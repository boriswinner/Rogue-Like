#include "game_objects.h"
#include "curses.h"

class GameManager {
public:
    explicit GameManager(const string &map_file_name) : map_(map_file_name), cells_(map_.get_map()), isrunning_(true) {}

    bool is_running() {
        return isrunning_;
    }

    void start_game() {
        map_.recontruct();
    }

    virtual void make_move(int key);

    virtual void check_keys(int key);

    void end_game() {
        isrunning_ = false;
    }

    Map &get_map() {
        return map_;
    }

protected:
    Map map_;
    vector<vector<vector<shared_ptr<MapObject>>>> &cells_;
    bool isrunning_;
};

/*class MapEditor : public GameManager {
public:
    explicit MapEditor(const string &mapfilename) : GameManager(mapfilename) {}

    void make_move(int key) override {
        map_.recontruct();
        //draw_map();
        //int key = getch();
        check_keys(key);
        map_.recontruct();
    }

protected:

    void check_keys(int key) override {
        //GameManager::check_keys(key);
        if (key == '1') {
            replace_player_cell(
                    make_shared<Wall>(pnt{map_.player->get_position().x, map_.player->get_position().y}, '#'));
        } else if (key == '2') {
            echo();
            mvprintw(LINES - 2, 1, "Enter Monster HP:");
            char hp_str[10];
            getstr(hp_str);
            int hp = strtol(hp_str, nullptr, 0);
            if (hp == 0L)
                return;
            mvprintw(LINES - 2, 1, "Enter Monster damage:");
            char dmg_str[10];
            getstr(dmg_str);
            int dmg = strtol(dmg_str, nullptr, 0);
            if (dmg == 0L)
                return;
            noecho();
            replace_player_cell(
                    make_shared<Monster>(pnt{map_.player->get_position().x, map_.player->get_position().y}, hp, dmg,
                                         '&'));
        } else if (key == '3') {
            echo();
            mvprintw(LINES - 2, 1, "Enter Healer Heal Value:");
            char hp_str[10];
            getstr(hp_str);
            int hp = strtol(hp_str, nullptr, 0);
            if (hp == 0L)
                return;
            replace_player_cell(
                    make_shared<Healer>(pnt{map_.player->get_position().x, map_.player->get_position().y}, hp, '@'));
            noecho();
        } else if (key == '4') {
            clear_player_cell();
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
        map_.add_object(make_shared<Floor>(pnt{map_.player->get_position().x, map_.player->get_position().y}, '*'));
    }

    /*void draw_ui() override {
        attron(COLOR_PAIR(2));
        mvprintw(1, map_.getsize().x + 1, "P is cursor");
        attron(COLOR_PAIR(3));
        mvprintw(2, map_.getsize().x + 1, "1 - wall, 2 - monster, 3 - healer, 4- clear");
        attron(COLOR_PAIR(1));
    }*/

/* void export_to_file() {
     ofstream out;
     echo();
     mvprintw(LINES - 2, 1, "Enter File Name:");
     char hp_str[100];
     getstr(hp_str);
     noecho();
     out.open(hp_str);
     out << map_.objs_count() << ' ' << map_.getsize().x << ' ' << map_.getsize().y << '\n';

 }
};*/