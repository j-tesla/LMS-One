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
#include "Book.h"

namespace ui {
    void welcome();

    std::string getText(const std::string &text, const std::regex &validPattern = std::regex(".*"));

    template<typename T>
    int getOption(const std::string &text, const T &options, const std::string &optionZero = "") {
        {
            std::vector<std::string> inputs;
            inputs.reserve(options.size());
            for (int i = 0; i < options.size(); ++i) {
                inputs.emplace_back(std::to_string(i + 1));
            }

            std::cout << "\033[35m" << text << "\n" << "\033[0m";

            int option = options.size();
            while (option == options.size()) {
                std::cout << "\033[1m" << "To select an option, enter its number.\n" << "\033[0m" << "\033[34m";
                for (int i = 0; i < options.size(); ++i) {
                    std::cout << inputs[i] << ". " << options[i] << std::endl;
                }
                if (!optionZero.empty())
                    std::cout << "0. " << optionZero << std::endl;
                std::cout << "\033[0m";

                std::string input;
                getline(std::cin, input);
                input = std::regex_replace(input, std::regex(R"(^[\t\n ]+)"), "");
                input = std::regex_replace(input, std::regex(R"([\t\n ]+$)"), "");
                option = std::find(inputs.begin(), inputs.begin() + options.size(), input) - inputs.begin();
                if (input == "0" and !optionZero.empty())
                    option = -1;
            }
            return option;
        }

    }

    template<typename T>
    void showList(const std::string &text, const T &list) {
        {
            std::cout << "\033[35m" << text << "\n" << "\033[0m";
            int i = 1;
            std::cout << "\033[34m";
            for (const auto &x: list) {
                std::cout << i++ << ". " << x << std::endl;
            }
            std::cout << "\033[0m";
        }
    }

    void showBook(const Book &file);
}


#endif //LMS_ONE_UI_H
