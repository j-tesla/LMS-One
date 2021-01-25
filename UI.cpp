//
// Created by jsharp on 1/25/21.
//

#include "UI.h"

#include <iostream>

void ui::welcome() {
    std::cout << "\033[1;4;30;44m" << "Welcome to LMS-One, the lightest Library Management System.\n" << "\033[0m"
              << std::endl;
}
