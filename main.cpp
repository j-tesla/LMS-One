#include <iostream>
#include <string>
#include <sys/stat.h>
#include "Library.h"
#include "UI.h"

namespace error_handlers {
    int noLibraryPassed() {
        return 1;
    }
}

inline bool pathExists(const std::string &name);

inline void showMainMenu(const Library& library);


int main(int argc, char *argv[]) {

    if (argc < 2)
        return error_handlers::noLibraryPassed();

    const std::string library_location(argv[1]);
    if (not pathExists(library_location)) {
        return error_handlers::noLibraryPassed();
    }
    ui::welcome();
    Library library(library_location);

    showMainMenu(library);
    return 0;
}

inline void showMainMenu(const Library& library) {
    bool running = true;
    while (running) {
        std::vector<std::string> menuOptions = {"List all the books", "exit"};
        int option = ui::getOption("Main Menu", menuOptions);
        switch (option) {
            case 0:
                ui::showList("List of books available in the library", library.getFiles());
                std::cout << "Books" << std::endl;
                break;
            default:
                running = false;
                break;
        }
        std::cout << std::endl;
    }
}

inline bool pathExists(const std::string &name) {
    struct stat buffer{};
    return (stat(name.c_str(), &buffer) == 0);
}
