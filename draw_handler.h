#include "curses.h"
#include "menu.h"
#include "game_objects.h"

class DrawHandler {
public:
    virtual void init_curses() {
        initscr();
        raw();
        noecho();
        curs_set(0);
    }
};

class MainMenuDrawHandler : public DrawHandler {
public:
    explicit MainMenuDrawHandler(Menu &menu) : menu_(menu) {}

    void draw() const {
        clear();
        printw("----%s----\n", menu_.get_header().c_str());
        for (int i = 0; i < menu_.get_labels().size(); ++i) {
            printw("%d. %s\n", i + 1, menu_.get_labels()[i].c_str());
        }
        refresh();
    }

protected:
    Menu &menu_;
};

class GameDrawHandler : public DrawHandler {
public:
    explicit GameDrawHandler(Map &map) : map_(map) {}

    void init_curses() override {
        DrawHandler::init_curses();
        start_color();
        init_pair(1, COLOR_WHITE, COLOR_BLACK);
        init_pair(2, COLOR_BLACK, COLOR_RED);
        init_pair(3, COLOR_BLACK, COLOR_GREEN);
    }

    virtual void draw_ui() {
        char player_hp[15] = "Player HP: ";
        itoa(map_.player->get_hp(), player_hp + 11, 10); //11 is player_hp length
        mvprintw(LINES - 1, 1, player_hp);
        if (map_.player->get_hp() <= 0) {
            mvprintw(LINES - 1, 1, "GAME OVER! PRESS R TO RESET");
        }
    }

    void draw_map() {
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

protected:
    Map &map_;
};

class MapEditorDrawHandler: public GameDrawHandler{
public:
    explicit MapEditorDrawHandler(Map &map) : GameDrawHandler(map) {}

    void draw_ui() override {
        attron(COLOR_PAIR(2));
        mvprintw(1, map_.getsize().x + 1, "P is cursor");
        attron(COLOR_PAIR(3));
        mvprintw(2, map_.getsize().x + 1, "1 - wall, 2 - monster, 3 - healer, 4- clear, 0 - save");
        attron(COLOR_PAIR(1));
    }
};