//
// Created by jsharp on 1/25/21.
//

#include "UI.h"

#include <iostream>

void ui::welcome() {
    std::cout << "\033[1;4;30;44m" << "Welcome to LMS-One, the lightest Library Management System.\n" << "\033[0m"
              << std::endl;
}

std::string ui::getText(const std::string &text, const std::regex &validPattern) {

    std::cout << "\033[35m" << text << "\n" << "\033[0m";

    std::string input;

    getline(std::cin, input);
    input = std::regex_replace(input, std::regex(R"(^[\t\n\r ]+)"), "");
    input = std::regex_replace(input, std::regex(R"([\t\n\r ]+$)"), "");
    while (!std::regex_match(input, validPattern)) {
        std::cout << "\033[1m" << "Enter valid text\n" << "\033[0m";
        getline(std::cin, input);
        input = std::regex_replace(input, std::regex(R"(^[\t\n\r ]+)"), "");
        input = std::regex_replace(input, std::regex(R"([\t\n\r ]+$)"), "");
    }
    return input;
}

void ui::showBook(const Book &file) {
    BookView fileView(file);
    unsigned pageSize = std::stoi(getText("Enter number of lines to view in a page", std::regex(R"(\d+)")));
    while (!fileView.empty()) {
        for (const auto &line: fileView.getLines(pageSize)) {
            std::cout << line << std::endl;
        }
        std::cout << "\033[32m" << "Press enter to print next page, q and enter to close." << "\033[0m" << std::endl;
        std::string input = "not empty lol";
        bool running = true;
        while (true) {
            getline(std::cin, input);
            input = std::regex_replace(input, std::regex(R"(^[\t\n\r ]+)"), "");
            input = std::regex_replace(input, std::regex(R"([\t\n\r ]+$)"), "");

            if (input == "q" or input == "0") {
                running = false;
            }
            break;
        }
        if (not running)
            break;
    }
}
