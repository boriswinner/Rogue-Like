#include "curses.h"
#include "game_objects.h"
#include <vector>
#include <memory>
#include <iostream>

using namespace std;

int main()
{

    //vector <MapObject> objects {main_player};
    vector<shared_ptr<MapObject>> objs;
    objs.push_back(make_shared<Player>(Player({1,2},1,1)));
    cout << objs[0]->get_position().x;
    Map map(10,10,objs);
    map.get_map();


    return 0;
}