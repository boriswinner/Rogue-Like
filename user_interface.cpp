#include <ratio>
#include <chrono>
#include <unistd.h>
#include <winuser.h>
#include "user_interface.h"
#include "config.h"
#include "thread"
#include "mingw.thread.h"

void MainMenuController::run() {
    Menu main_menu(string("Rogue-Like"), 3, string("Play Game"), string("Open Map Editor"), string("Exit"));
    MainMenuDrawHandler menu_draw_handler(main_menu);
    menu_draw_handler.init_curses();
    while (true){
        menu_draw_handler.draw();
        int choice = getch();
        if (choice == game_config.data["Choice1"]) {
            GameController game_controller(mapfilename_);
            game_controller.run();
        } else if (choice == game_config.data["Choice2"]) {
            MapEditorController map_controller(mapfilename_);
            map_controller.run();
        } else if (choice == game_config.data["Choice3"]) {
            return;
        }
    }
}

void GameController::run() {
    GameManager game_manager(mapfilename_);
    game_manager.start_game();
    GameDrawHandler game_draw_handler(game_manager.get_map());
    std::chrono::duration<long, std::ratio<5, 25>> frame_ratio{ 1 };
    nodelay(stdscr, TRUE);
    while (game_manager.game_status() == isrunning) {
        game_draw_handler.draw_map();
        while (true) {
            if (GetAsyncKeyState(VK_LEFT)) {
                game_manager.make_move(game_config.data["ButtonLeft"]);
            } else if (GetAsyncKeyState(VK_RIGHT)){
                game_manager.make_move(game_config.data["ButtonRight"]);
            } else if (GetAsyncKeyState(VK_DOWN)){
                game_manager.make_move(game_config.data["ButtonDown"]);
            } else if (GetAsyncKeyState(VK_UP)){
                game_manager.make_move(game_config.data["ButtonUp"]);
            } else {
                game_manager.make_move(game_config.data["NotUsedKey"]);
            }
            game_draw_handler.draw_map();
            std::this_thread::sleep_for(100ms);
            }
        while(int key = getch()){
            auto frame_start = std::chrono::steady_clock::now();
            if (key > 0){
                game_manager.make_move(key);
            } else{
                game_manager.make_move(game_config.data["NotUsedKey"]);
            }
            game_draw_handler.draw_map();
            auto frame_end = std::chrono::steady_clock::now();
            auto delay = frame_ratio - (frame_end - frame_start);
            std::this_thread::sleep_for(delay);
            //flushinp();
        }

    }
    if (game_manager.game_status() == defeat){
        game_draw_handler.draw_defeat();
    } else if (game_manager.game_status() == victory){
        game_draw_handler.draw_victory();
    }
    while (true){
        int key = getch();
        if (key == game_config.data["ReturnKey"]){
            return;
        }
    }

    endwin();
}

void MapEditorController::run() {
    MapEditorManager map_editor_manager(mapfilename_);
    map_editor_manager.start_game();
    MapEditorDrawHandler map_editor_draw_handler(map_editor_manager.get_map());
    map_editor_draw_handler.init_curses();
    while (map_editor_manager.game_status() == isrunning) {
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
            hp = strtol(hp_str, nullptr, 0);
            if (hp == 0L)
                return;
            noecho();
        }
        map_editor_manager.make_move(key, hp, dmg);
    }
}
