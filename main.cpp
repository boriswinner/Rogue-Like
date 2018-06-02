#include "curses.h"
#include "game_manager.h"

int main() {
    GameManager game_manager("level1.txt");

    game_manager.start_game();
    while (true) {
        game_manager.make_move();
    }
    endwin();

    return 0;
}