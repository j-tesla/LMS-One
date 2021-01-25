//
// Created by jsharp on 1/25/21.
//

#include "UI.h"

#include <iostream>
#include <regex>
#include <algorithm>


void ui::welcome() {
    std::cout << "\033[1;4;30;44m" << "Welcome to LMS-One, the lightest Library Management System.\n" << "\033[0m"
              << std::endl;
}

template<typename T>
int ui::getOption(const std::string &text, const std::vector<T> &options) {
    std::vector<std::string> inputs = {"1", "2", "3", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16",
                                       "17", "18", "19", "20"};

    std::cout << "\033[35m" << text << "\n" << "\033[0m";

    int option = options.size();
    while (option == options.size()) {
        std::cout << "\033[1m" << "To select an option, enter its number.\n" << "\033[0m" << "\033[34m";
        for (int i = 0; i < options.size(); ++i) {
            std::cout << inputs[i] << ". " << options[i] << std::endl;
        }
        std::cout << "\033[0m";

        std::string input;
        getline(std::cin, input);
        input = std::regex_replace(input, std::regex(R"(^[\t\n ]+)"), "");
        input = std::regex_replace(input, std::regex(R"([\t\n ]+$)"), "");
        option = std::find(inputs.begin(), inputs.begin() + options.size(), input) - inputs.begin();
    }
    return option;
}


template<typename T>
void ui::showList(const std::string &text, const std::vector<T> &list) {
    std::cout << "\033[35m" << text << "\n" << "\033[0m";
    int i = 1;
    for (const auto &x: list) {
        std::cout << i++ << ". " << x << std::endl;
    }
}

template void ui::showList<std::string>(const std::string &text, const std::vector<std::string> &list);

template int ui::getOption<std::string>(const std::string &text, const std::vector<std::string> &options);