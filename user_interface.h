#pragma once
#include "curses.h"
#include "game_objects.h"
#include "draw_handler.h"
#include "game_manager.h"

class MainMenuController {
public:
    explicit MainMenuController(string mapfilename) : mapfilename_(std::move(mapfilename)) {};

    void run();

protected:
    const string mapfilename_;
};

class GameController {
public:
    explicit GameController(string mapfilename) : mapfilename_(std::move(mapfilename)) {};

    void run();

protected:
    const string mapfilename_;
};

class MapEditorController {
public:
    explicit MapEditorController(string mapfilename) : mapfilename_(std::move(mapfilename)) {};

    void run();

protected:
    const string mapfilename_;
};