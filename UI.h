//
// Created by jsharp on 1/24/21.
//

#ifndef LMS_ONE_UI_H
#define LMS_ONE_UI_H

#include <string>
#include <vector>
#include <iostream>
#include <regex>
#include <algorithm>

namespace ui {
    void welcome();

    template<typename T>
    int getOption(const std::string &text, const std::vector<T> &options) {
        {
            std::vector<std::string> inputs = {"1", "2", "3", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14",
                                               "15", "16",
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

    }

    template<typename T>
    void showList(const std::string &text, const std::vector<T> &list) {
        {
            std::cout << "\033[35m" << text << "\n" << "\033[0m";
            int i = 1;
            std::cout <<  "\033[34m";
            for (const auto &x: list) {
                std::cout << i++ << ". " << x << std::endl;
            }
            std::cout << "\033[0m";
        }
    }
}


#endif //LMS_ONE_UI_H
