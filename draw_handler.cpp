#include "draw_handler.h"
#include "config.h"

void DrawHandler::init_curses() {
    initscr();
    raw();
    noecho();
    curs_set(0);
}

void MainMenuDrawHandler::draw() const {
    clear();
    printw("----%s----\n", menu_.get_header().c_str());
    for (int i = 0; i < menu_.get_labels().size(); ++i) {
        printw("%d. %s\n", i + 1, menu_.get_labels()[i].c_str());
    }
    refresh();
}

void GameDrawHandler::init_curses() {
    DrawHandler::init_curses();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_BLACK, COLOR_RED);
    init_pair(3, COLOR_BLACK, COLOR_GREEN);
}

void GameDrawHandler::draw_ui() {
    string hp = game_config.data["PlayerHP"].dump();
    hp += to_string(map_.player->get_hp());
    char * cstr = new char [hp.length()+1];
    std::strcpy (cstr, hp.c_str());
    mvprintw(LINES - 1, 1, cstr);
}

void GameDrawHandler::draw_defeat() {
    mvprintw(LINES - 1, 1, game_config.data["LoseMessage"].dump().c_str());
}

void GameDrawHandler::draw_victory() {
    mvprintw(LINES - 1, 1, game_config.data["WinMessage"].dump().c_str());
}

void GameDrawHandler::draw_map() {
    clear();
    for (int i = 0; i < map_.get_map().size(); i++) {
        for (int j = 0; j < map_.get_map()[i].size(); j++) {
            addch(static_cast<const chtype>(map_.get_map()[i][j][map_.get_map()[i][j].size() - 1]->get_image()));
        }
        addch('\n');
    }
    mvaddch(map_.player->get_position().y, map_.player->get_position().x,
            static_cast<const chtype>(map_.player->get_image()));
    draw_ui();
    refresh();
}

void MapEditorDrawHandler::draw_ui() {
    attron(COLOR_PAIR(2));
    mvprintw(1, map_.getsize().x + 1, game_config.data["EditorHelp1"].dump().c_str());
    attron(COLOR_PAIR(3));
    mvprintw(2, map_.getsize().x + 1, game_config.data["EditorHelp2"].dump().c_str());
    mvprintw(3, map_.getsize().x + 1, game_config.data["EditorHelp3"].dump().c_str());
    attron(COLOR_PAIR(1));
}
