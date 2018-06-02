#include "curses.h"
#include "game_manager.h"

int main() {
    GameManager game_manager("level1.txt");

    game_manager.start_game();
    while (game_manager.is_running()) {
        game_manager.make_move();
    }
    game_manager.end_game();
    return 0;
}