#include "game_objects.h"
#include "curses.h"

class GameManager {
public:
    explicit GameManager(const string &mapfilename) : map_(mapfilename), cells_(map_.get_map()), isrunning_(true) {}

    bool is_running() {
        return isrunning_;
    }

    void start_game() {
        init_curses();
    }

    virtual void make_move() {
        map_.recontruct();
        draw_map();
        for (int i = 0; i < cells_.size(); i++) {
            for (int j = 0; j < cells_[i].size(); j++) {
                for (int z = 0; z < cells_[i][j].size(); z++) {
                    cells_[i][j][z]->move(map_, 0, 0);
                }
            }
        }
        int key = getch();
        check_keys(key);
        map_.recontruct();
        for (int i = 0; i < cells_.size(); i++) {
            for (int j = 0; j < cells_[i].size(); j++) {
                for (int z = 0; z < cells_[i][j].size(); z++) {
                    if (z < cells_[i][j].size() - 1) {
                        for (int f = z + 1; f < cells_[i][j].size(); ++f) {
                            cells_[i][j][z]->collide(*cells_[i][j][f]);
                        }
                    }
                }
            }
        }
    }

    virtual void check_keys(int key) {
        if (key == 's') {
            map_.player->move(map_, 0, 1);
        } else if (key == 'w') {
            map_.player->move(map_, 0, -1);
        } else if (key == 'a') {
            map_.player->move(map_, -1, 0);
        } else if (key == 'd') {
            map_.player->move(map_, 1, 0);
        }
    }

    void end_game() {
        endwin();
    }

protected:
    Map map_;
    vector<vector<vector<shared_ptr<MapObject>>>> &cells_;
    bool isrunning_;

    void init_curses() {
        initscr();
        raw();
        noecho();
        curs_set(0);
        start_color();
        init_pair(1, COLOR_WHITE, COLOR_BLACK);
        init_pair(2, COLOR_BLACK, COLOR_RED);
        init_pair(3, COLOR_BLACK, COLOR_GREEN);
    }

    virtual void draw_ui() {
        char player_hp[15] = "Player HP: ";
        itoa(map_.player->get_hp(), player_hp + 11, 10); //11 is player_hp length
        mvprintw(LINES - 1, 1, player_hp);
        if (map_.player->get_hp() <= 0) {
            mvprintw(LINES - 1, 1, "GAME OVER! PRESS R TO RESET");
        }
    }

    virtual void draw_map() {
        clear();
        refresh();
        for (int i = 0; i < cells_.size(); i++) {
            for (int j = 0; j < cells_[i].size(); j++) {
                addch(static_cast<const chtype>(cells_[i][j][0]->get_image()));
            }
            addch('\n');
        }
        draw_ui();
    }
};

class MapEditor: public GameManager{
public:
    explicit MapEditor(const string &mapfilename) : GameManager(mapfilename) {}

    void make_move() override {
        map_.recontruct();
        draw_map();
        int key = getch();
        check_keys(key);
        map_.recontruct();
    }

protected:

    void check_keys(int key) override {
        GameManager::check_keys(key);
        if (key == '1') {
            for (int i = 0; i < cells_[map_.player->get_position().y][map_.player->get_position().x].size(); ++i) {
                cells_[map_.player->get_position().y][map_.player->get_position().x][i]->remove();
            }
            map_.player->deremove();
            map_.add_object(make_shared<Wall>(pnt{map_.player->get_position().x, map_.player->get_position().y}, '#'));
            map_.add_object(make_shared<Floor>(pnt{map_.player->get_position().x, map_.player->get_position().y}, '*'));
        }
    }

    void draw_ui() override {
        attron(COLOR_PAIR(2));
        mvprintw(1, map_.getsize().x + 1, "P is cursor");
        attron(COLOR_PAIR(3));
        mvprintw(2, map_.getsize().x + 1, "1 - wall, 2 - monster, 3 - healer");
        attron(COLOR_PAIR(1));
    }

};