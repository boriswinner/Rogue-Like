//
// Created by Lenovo on 14.06.2018.
//

#include "user_interface.h"
#include "draw_handler.h"

void MainMenuController::run() {
    Menu main_menu(string("Rogue-Like"), 2, string("Play Game"), string("Open Map Editor"));
    MainMenuDrawHandler menu_draw_handler(main_menu);
    menu_draw_handler.init_curses();
    menu_draw_handler.draw();
    int choice = getch();
    if (choice == '1') {
        GameController game_controller(mapfilename_);
        game_controller.run();
    } else if (choice == '2') {
        /*MapEditor map_editor(mapfilename_);
        map_editor.start_game();
        while (map_editor.is_running()) {
            int key = getch();
            map_editor.make_move(key);
        }
        map_editor.end_game();*/
    }
}

void GameController::run() {
    GameManager game_manager(mapfilename_);
    game_manager.start_game();
    GameDrawHandler game_draw_handler(game_manager.get_map());
    while (game_manager.is_running()) {
        game_draw_handler.draw_map();
        int key = getch();
        game_manager.make_move(key);
    }
    game_manager.end_game();
    endwin();
}
