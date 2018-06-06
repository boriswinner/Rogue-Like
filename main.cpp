#include "curses.h"
#include "game_manager.h"
#include "menu.h"

using namespace std;

int main() {
    Menu main_menu(string("Rogue-Like"),2,string("Play Game"),string("Open Map Editor"));
    int choice = 0;
    while ((choice = main_menu.make_move()) == 0){}
    if (choice == '1'){
        GameManager game_manager("level1.txt");
        game_manager.start_game();
        while (game_manager.is_running()) {
            game_manager.make_move();
        }
        game_manager.end_game();
    } else if (choice == '2'){
        MapEditor map_editor("level1.txt");
        map_editor.start_game();
        while (map_editor.is_running()) {
            map_editor.make_move();
        }
        map_editor.end_game();
    }

    return 0;
}