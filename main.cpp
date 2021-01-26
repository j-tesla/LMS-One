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

bool caseInsensitiveFind(std::string text, std::string filter);

void showBook(const LibraryFile &book);

void searchMenu(const Library &library);

void showMainMenu(const Library &library);

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

void showMainMenu(const Library &library) {
    bool running = true;
    while (running) {
        std::vector<std::string> menuOptions = {"List all the books", "Search for a book"};
        int option = ui::getOption("Main Menu", menuOptions, "exit");
        switch (option) {
            case 0: {
                bool running = true;
                while (running) {
                    int bookSelected = ui::getOption("List of books available in the library", library.getFiles(),
                                                     "back");
                    if (bookSelected == -1) {
                        running = false;
                    } else {
                        showBook(library.getFiles()[bookSelected]);
                    }
                }
                break;
            }
            case 1: {
                searchMenu(library);
                break;
            }
            default: {
                running = false;
                break;
            }
        }
        std::cout << std::endl;
    }
}

void searchMenu(const Library &library) {
    std::vector<std::string> searchOptions = {"search by filename", "search by title", "search by author name"};
    int optionSelected = ui::getOption("Select filter", searchOptions, "back");
    switch (optionSelected) {
        case 0: {
            std::string filter = ui::getText("Enter filename to search");

            std::vector<LibraryFile> filtered;

            std::copy_if(library.getFiles().begin(), library.getFiles().end(), std::back_inserter(filtered),
                         [filter](const LibraryFile &file) {
                             return caseInsensitiveFind(file.getName(), filter);
                         });
            bool running = true;
            while (running) {
                int bookSelected = ui::getOption("List of matching books in the library", filtered,
                                                 "back");
                if (bookSelected == -1) {
                    running = false;
                } else {
                    showBook(library.getFiles()[bookSelected]);
                }
            }
            break;
        }
        case 1: {
            std::string filter = ui::getText("Enter title to search");

            std::vector<LibraryFile> filtered;

            std::copy_if(library.getFiles().begin(), library.getFiles().end(), std::back_inserter(filtered),
                         [filter](const LibraryFile &file) {
                             return caseInsensitiveFind(file.getTitle(), filter);
                         });
            bool running = true;
            while (running) {
                int bookSelected = ui::getOption("List of matching books in the library", filtered,
                                                 "back");
                if (bookSelected == -1) {
                    running = false;
                } else {
                    showBook(library.getFiles()[bookSelected]);
                }
            }
            break;
        }
        case 2: {
            std::string filter = ui::getText("Enter author name to search");

            std::vector<LibraryFile> filtered;

            std::copy_if(library.getFiles().begin(), library.getFiles().end(), std::back_inserter(filtered),
                         [filter](const LibraryFile &file) {
                             return caseInsensitiveFind(file.getAuthor(), filter);
                         });
            bool running = true;
            while (running) {
                int bookSelected = ui::getOption("List of books available in the library", filtered,
                                                 "back");
                if (bookSelected == -1) {
                    running = false;
                } else {
                    showBook(library.getFiles()[bookSelected]);
                }
            }
            break;
        }
    }
}

void showBook(const LibraryFile &book) {
    // TODO implement viewing book
}

bool caseInsensitiveFind(std::string text, std::string filter) {
    std::transform(text.begin(), text.end(), text.begin(), ::toupper);
    std::transform(filter.begin(), filter.end(), filter.begin(), ::toupper);
    std::cout << text.size() << " " << text.find(filter)  << " " << text.size() - 1 << std::endl;
    return text.find(filter) < text.size() - 1;

}


inline bool pathExists(const std::string &name) {
    struct stat buffer{};
    return (stat(name.c_str(), &buffer) == 0);
}
