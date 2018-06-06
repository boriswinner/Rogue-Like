#pragma once
#include <string>

class Menu{
public:
    explicit Menu(const string& header, int num_of_labels, const string& label,...){
        init_curses();
        header_ = header;
        va_list args;
        va_start(args, label);
        add_item(label);
        for (int i = 1; i < num_of_labels; ++i){
            string s = va_arg(args,string);
            add_item(s);
        }
        va_end(args);
    }

    void add_item(const string& name){
        labels_.push_back(name);
    }

    int make_move(){
        draw();
        int key = getch();
        for (int i = 1; i < 10; ++i){
            if (key == i){
                return i;
            }
        }
    }

    void draw(){
        clear();
        refresh();
        printw("----%s----\n",header_.c_str());
        for (int i = 0; i < labels_.size(); ++i){
            printw("%d. %s\n",i+1,labels_[i].c_str());
        }
    }

protected:
    void init_curses() {
        initscr();
        raw();
        noecho();
        curs_set(0);
    }

    string header_;
    vector <string> labels_;
};