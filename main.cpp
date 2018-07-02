#include "menu.h"
#include "user_interface.h"
#include "config.h"


Config &game_config = Config::Instance();
using namespace std;

int main() {
    MainMenuController main_menu("level1.txt");
    main_menu.run();
    return 0;
}