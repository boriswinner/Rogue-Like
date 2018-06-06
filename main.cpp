#include "curses.h"
#include "game_manager.h"

int main() {
    GameManager game_manager("level1.txt");

    game_manager.start_mapeditor();
    while (game_manager.is_running()) {
        game_manager.makemove_mapeditor();
    }
    game_manager.end_game();
    return 0;
}