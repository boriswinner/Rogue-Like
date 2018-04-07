#include "curses.h"
#include "game_objects.h"
#include <vector>
#include <memory>
#include <iostream>

using namespace std;

int main()
{

    //create objects
    shared_ptr<Player> player = make_shared<Player>(pnt{0,0},10,2);

    vector<shared_ptr<MapObject>> objs;
    objs.push_back(player);
    objs.push_back(make_shared<Monster>(Monster(pnt{2,1},1,1)));

    objs.push_back(make_shared<MapObject>(MapObject(pnt{0,0})));
    objs.push_back(make_shared<MapObject>(MapObject(pnt{0,1})));
    objs.push_back(make_shared<MapObject>(MapObject(pnt{0,2})));
    objs.push_back(make_shared<MapObject>(MapObject(pnt{1,0})));
    objs.push_back(make_shared<MapObject>(MapObject(pnt{1,1})));
    objs.push_back(make_shared<MapObject>(MapObject(pnt{1,2})));
    objs.push_back(make_shared<MapObject>(MapObject(pnt{2,0})));
    objs.push_back(make_shared<MapObject>(MapObject(pnt{2,1})));
    objs.push_back(make_shared<MapObject>(MapObject(pnt{2,2})));

    initscr();
    raw();
    noecho();

    while(true){
        clear();
        refresh();
        Map map(3,3,objs);
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
            if (key == 's'){
                player->move(0,1);
                break;
            } else if (key == 'w'){
                player->move(0,-1);
                break;
            } else if (key == 'a'){
                player->move(-1,0);
                break;
            } else if (key == 'd'){
                player->move(1,0);
                break;
            }
        }
        for (int i = 0; i < cells.size(); i++){
            for (int j = 0; j < cells[i].size(); j++){
                for (int z = 0; z < cells[i][j].size(); z++){
                    cells[i][j][z]->move(*player);
                }
            }
        }

    }
    endwin();

    return 0;
}