#include "curses.h"
#include "game_objects.h"
#include <vector>
#include <memory>
#include <iostream>

int main() {

    Map map("level1.txt");


    initscr();
    raw();
    noecho();
    curs_set(0);

    while (true) {
        clear();
        refresh();
        map.recontruct();
        vector<vector<vector<shared_ptr<MapObject>>>> &cells = map.get_map();

        for (int i = 0; i < cells.size(); i++) {
            for (int j = 0; j < cells[i].size(); j++) {
                addch(static_cast<const chtype>(cells[i][j][0]->get_image()));
            }
            addch('\n');
        }
        refresh();
        int key;
        while (key = getch()) {
            if (key == 's') {
                map.player->move(map, 0, 1);
                break;
            } else if (key == 'w') {
                map.player->move(map, 0, -1);
                break;
            } else if (key == 'a') {
                map.player->move(map, -1, 0);
                break;
            } else if (key == 'd') {
                map.player->move(map, 1, 0);
                break;
            }
        }
        for (int i = 0; i < cells.size(); i++) {
            for (int j = 0; j < cells[i].size(); j++) {
                for (int z = 0; z < cells[i][j].size(); z++) {
                   cells[i][j][z]->move(*map.player, map);
                }
            }
        }
        map.recontruct();
        for (int i = 0; i < cells.size(); i++) {
            for (int j = 0; j < cells[i].size(); j++) {
                for (int z = 0; z < cells[i][j].size(); z++) {
                    if (z < cells[i][j].size() - 1){
                        cells[i][j][z]->collide(*cells[i][j][z+1]);
                        break;
                    }
                }
            }
        }

    }
    endwin();

    return 0;
}