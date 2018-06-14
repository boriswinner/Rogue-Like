#pragma once

#include <utility>
#include "menu.h"
#include "game_objects.h"
#include "game_manager.h"
#include "curses.h"

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