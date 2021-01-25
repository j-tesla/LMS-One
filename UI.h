//
// Created by jsharp on 1/24/21.
//

#ifndef LMS_ONE_UI_H
#define LMS_ONE_UI_H

#include <string>
#include <vector>

namespace ui {
    void welcome();

    template <typename T>
    int getOption(const std::string &text, const std::vector<T> &options);

    template <typename T>
    void showList(const std::string &text, const std::vector<T> &list);
}


#endif //LMS_ONE_UI_H
