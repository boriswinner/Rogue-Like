#include "game_objects.h"
#include "curses.h"

class GameManager {
public:
    explicit GameManager(const string &map_file_name) : map_(map_file_name), cells_(map_.get_map()), isrunning_(true) {}

    bool is_running() {
        return isrunning_;
    }

    void start_game() {
        map_.recontruct();
    }

    virtual void make_move(int key);

    virtual void check_keys(int key);

    void end_game() {
        isrunning_ = false;
    }

    Map &get_map() {
        return map_;
    }

protected:
    Map map_;
    vector<vector<vector<shared_ptr<MapObject>>>> &cells_;
    bool isrunning_;
};

class MapEditorManager : public GameManager {
public:
    explicit MapEditorManager(const string &mapfilename) : GameManager(mapfilename) {}

    void make_move(int key, int hp = 0, int dmg = 0) {
        map_.recontruct();
        check_keys(key, hp, dmg);
        map_.recontruct();
    }

protected:
    void check_keys(int key, int hp = 0, int dmg = 0) {
        GameManager::check_keys(key);
        if (key == '1') {
            replace_player_cell(
                    make_shared<Wall>(pnt{map_.player->get_position().x, map_.player->get_position().y}, '#'));
        } else if (key == '2') {
            replace_player_cell(
                    make_shared<Monster>(pnt{map_.player->get_position().x, map_.player->get_position().y}, hp, dmg,
                                         '&'));
        } else if (key == '3') {
            replace_player_cell(
                    make_shared<Healer>(pnt{map_.player->get_position().x, map_.player->get_position().y}, hp, '@'));
        } else if (key == '4') {
            clear_player_cell();
        } else if (key == '0'){
            export_to_file();
        }
    }

    void replace_player_cell(const shared_ptr<MapObject> &obj) {
        clear_player_cell();
        map_.add_object(obj);
    }

    void clear_player_cell() {
        for (int i = 0; i < cells_[map_.player->get_position().y][map_.player->get_position().x].size(); ++i) {
            cells_[map_.player->get_position().y][map_.player->get_position().x][i]->remove();
        }
        map_.player->deremove();
        map_.add_object(make_shared<Floor>(pnt{map_.player->get_position().x, map_.player->get_position().y}, '*'));
    }

    void export_to_file() {
        ofstream out;
        out.open("output.txt");
        out << map_.objs_count() << ' ' << map_.getsize().x << ' ' << map_.getsize().y << '\n';
        for (int i = 0; i < map_.get_objs().size(); ++i){
            out << map_.get_objs()[i]->export_obj() << '\n';
        }
        out.close();
    }
};