#include "game_objects.h"
#include "curses.h"

class GameManager{
public:
    explicit GameManager(const string &mapfilename): map_(mapfilename), cells_(map_.get_map()){}

    void start_game(){
        init_curses();
    }

    void make_move(){
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
        if (key == 's') {
            map_.player->move(map_, 0, 1);
        } else if (key == 'w') {
            map_.player->move(map_, 0, -1);
        } else if (key == 'a') {
            map_.player->move(map_, -1, 0);
        } else if (key == 'd') {
            map_.player->move(map_, 1, 0);
        }
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

    void start_mapeditor(){

    }
protected:
    Map map_;
    vector<vector<vector<shared_ptr<MapObject>>>> &cells_;

    void init_curses(){
        initscr();
        raw();
        noecho();
        curs_set(0);
    }

    void draw_hp(){
        char player_hp[15] = "Player HP: ";
        itoa(map_.player->get_hp(), player_hp + 11, 10); //11 is player_hp length
        mvprintw(LINES - 1, 1, player_hp);
        if (map_.player->get_hp() <= 0) {
            mvprintw(LINES - 1, 1, "GAME OVER! PRESS R TO RESET");
        }
    }

    void get_input(){

    }
    void draw_map(){
        clear();
        refresh();
        vector<vector<vector<shared_ptr<MapObject>>>> &cells = map_.get_map();
        for (int i = 0; i < cells.size(); i++) {
            for (int j = 0; j < cells[i].size(); j++) {
                addch(static_cast<const chtype>(cells[i][j][0]->get_image()));
            }
            addch('\n');
        }
        draw_hp();
    }
};