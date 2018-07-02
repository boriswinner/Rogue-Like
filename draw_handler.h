#include "curses.h"
#include "menu.h"
#include "game_objects.h"

class DrawHandler {
public:
    virtual void init_curses();
};

class MainMenuDrawHandler : public DrawHandler {
public:
    explicit MainMenuDrawHandler(Menu &menu) : menu_(menu) {}

    void draw() const;

protected:
    Menu &menu_;
};

class GameDrawHandler : public DrawHandler {
public:
    explicit GameDrawHandler(Map &map) : map_(map) {}

    void init_curses() override;

    virtual void draw_ui();

    virtual void draw_defeat();

    virtual void draw_victory();

    void draw_map();

protected:
    Map &map_;
};

class MapEditorDrawHandler: public GameDrawHandler{
public:
    explicit MapEditorDrawHandler(Map &map) : GameDrawHandler(map) {}

    void draw_ui() override;
};