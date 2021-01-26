//
// Created by jsharp on 1/25/21.
//

#include "UI.h"

#include <iostream>

void ui::welcome() {
    std::cout << "\033[1;4;30;44m" << "Welcome to LMS-One, the lightest Library Management System.\n" << "\033[0m"
              << std::endl;
}

std::string ui::getText(const std::string &text, const std::regex& validPattern) {

    std::cout << "\033[35m" << text << "\n" << "\033[0m";

    std::string input;

    getline(std::cin, input);

    while (!std::regex_match(input, validPattern)){
        std::cout << "\033[1m" << "Enter valid text\n" << "\033[0m";
        getline(std::cin, input);

    }
    return input;
}

