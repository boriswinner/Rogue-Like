#include "curses.h"
#include "game_objects.h"

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
        char player_hp[15] = "Player HP: ";
        itoa(map.player->get_hp(), player_hp + 11, 10); //11 is player_hp length
        mvprintw(LINES - 1, 1, player_hp);
        if (map.player->get_hp() <= 0) {
            mvprintw(LINES - 1, 1, "GAME OVER! PRESS R TO RESET");
        }
        refresh();
        int key = getch();
        if (key == 's') {
            map.player->move(map, 0, 1);
        } else if (key == 'w') {
            map.player->move(map, 0, -1);
        } else if (key == 'a') {
            map.player->move(map, -1, 0);
        } else if (key == 'd') {
            map.player->move(map, 1, 0);
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
                    if (z < cells[i][j].size() - 1) {
                        for (int f = z + 1; f < cells[i][j].size(); ++f) {
                            cells[i][j][z]->collide(*cells[i][j][f]);
                        }
                    }
                }
            }
        }
    }
    endwin();

    return 0;
}