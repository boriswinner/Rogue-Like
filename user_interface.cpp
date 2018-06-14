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
        MapEditorController map_controller(mapfilename_);
        map_controller.run();
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

void MapEditorController::run() {
    MapEditorManager map_editor_manager(mapfilename_);
    map_editor_manager.start_game();
    MapEditorDrawHandler map_editor_draw_handler(map_editor_manager.get_map());
    while (map_editor_manager.is_running()){
        map_editor_draw_handler.draw_map();
        int key = getch();
        int hp = 0;
        int dmg = 0;
        if (key == '2'){
            echo();
            mvprintw(LINES - 2, 1, "Enter Monster HP:");
            char hp_str[10];
            getstr(hp_str);
            hp = strtol(hp_str, nullptr, 0);
            if (hp == 0L)
                return;
            mvprintw(LINES - 2, 1, "Enter Monster damage:");
            char dmg_str[10];
            getstr(dmg_str);
            dmg = strtol(dmg_str, nullptr, 0);
            if (dmg == 0L)
                return;
            noecho();
        } else if (key == '3'){
            echo();
            mvprintw(LINES - 2, 1, "Enter Healer Heal Value:");
            char hp_str[10];
            getstr(hp_str);
            int hp = strtol(hp_str, nullptr, 0);
            if (hp == 0L)
                return;
            noecho();
        }
        map_editor_manager.make_move(key, hp, dmg);
    }
}
