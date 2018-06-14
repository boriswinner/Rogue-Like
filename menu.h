#pragma once
#include <string>
#include <vector>
#include <cstdarg>

using std::string;
using std::vector;

class Menu{
public:
    explicit Menu(const string& header, int num_of_labels, const string& label,...){
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

    string& get_header(){
        return header_;
    }

    vector <string>& get_labels(){
        return labels_;
    }

protected:
    string header_;
    vector <string> labels_;
};