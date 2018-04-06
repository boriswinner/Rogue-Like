#include "curses.h"
#include "game_objects.h"
#include <vector>
#include <memory>
#include <iostream>

using namespace std;

int main()
{

    //create objects
    Player player({0,0},1,1);
    vector<shared_ptr<MapObject>> objs;
    objs.push_back(make_shared<Player>(player));
    objs.push_back(make_shared<MapObject>(MapObject(pnt{0,1})));
    objs.push_back(make_shared<MapObject>(MapObject(pnt{1,0})));
    objs.push_back(make_shared<MapObject>(MapObject(pnt{1,1})));

    initscr();
    raw();
    noecho();
    cbreak();
    while(true){
        clear();
        Map map(2,2,objs);
        vector <vector <vector <shared_ptr<MapObject>>>> &cells = map.get_map();

        for (int i = 0; i < cells.size(); i++){
            for (int j = 0; j < cells[i].size(); j++){
                addch(static_cast<const chtype>(cells[i][j][0]->get_image()));
            }
            addch('\n');
        }
        refresh();
        int key;
        while (key = getch()){
            if (key == KEY_DOWN){
                player.move(0,1);
            }
            if ((key == KEY_UP) || (key == KEY_DOWN) || (key == KEY_LEFT) || (key == KEY_RIGHT)){ break;}
        }
    }
    endwin();

    return 0;
}