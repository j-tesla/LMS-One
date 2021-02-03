//
// Created by Jayanth PSY on 1/24/21.
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

        std::vector<std::string> inputs;
        inputs.reserve(options.size());
        for (int i = 0; i < options.size(); ++i) {
            inputs.emplace_back(std::to_string(i + 1));
        }

        std::cout << "\033[35m" << text << "\n" << "\033[0m";

        int optionSelected = options.size();
        while (optionSelected == options.size()) {
            std::cout << "\033[32m" << "To select an option, enter its number.\n" << "\033[0m" << "\033[34m";
            int i = 0;
            for (const auto &option: options) {
                std::cout << ++i << ". " << option << std::endl;
            }
            if (!optionZero.empty())
                std::cout << "0. " << optionZero << std::endl;
            std::cout << "\033[0m";

            std::string input;
            getline(std::cin, input);
            input = std::regex_replace(input, std::regex(R"(^[\t\n\r ]+)"), "");
            input = std::regex_replace(input, std::regex(R"([\t\n\r ]+$)"), "");
            optionSelected = std::find(inputs.begin(), inputs.begin() + options.size(), input) - inputs.begin();
            if (input == "0" and !optionZero.empty())
                optionSelected = -1;
        }
        return optionSelected;


    }

    template<typename T>
    void showList(const std::string &text, const T &list) {
        {
            std::cout << "\033[35m" << text << "\n" << "\033[0m";
            int i = 0;
            std::cout << "\033[34m";
            for (const auto &x: list) {
                std::cout << ++i << ". " << x << std::endl;
            }
            std::cout << "\033[0m";
        }
    }

    template<typename T>
    void showLines(const T &lines) {
        unsigned pageSize = std::stoi(getText("Enter number of lines to view in a page", std::regex(R"(\d+)")));
        unsigned line = 0;
        bool running = true;

        while (line < lines.size()) {
            for (int i = 0; i < pageSize; ++i) {
                if (line >= lines.size()) {
                    running = false;
                    break;
                }
                std::cout << lines[line] << std::endl;
                ++line;
            }
            if (running) {
                std::cout << "\033[32m" << "Press enter to print next page, q and enter to close." << "\033[0m" << std::endl;
                std::string input = "not empty lol";
                while (true) {
                    getline(std::cin, input);
                    input = std::regex_replace(input, std::regex(R"(^[\t\n\r ]+)"), "");
                    input = std::regex_replace(input, std::regex(R"([\t\n\r ]+$)"), "");

                    if (input == "q" or input == "0") {
                        running = false;
                    }
                    break;
                }
                if (not running) {
                    break;
                }
            }
        }
    }

    template<typename T>
    void showLine(const T &line) {
        std::cout << "\033[34m" << line << "\033[0m" << std::endl;
    }

    void showBook(const Book &file);
}


#endif //LMS_ONE_UI_H
