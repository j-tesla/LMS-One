#include <sys/stat.h>

#include <iostream>
#include <string>

#include "Library.h"
#include "UI.h"
#include "Novel.h"

namespace error_handlers {
    int noLibraryPassed() {
        return 1;
    }
}

inline bool pathExists(const std::string &name);

bool caseInsensitiveFind(std::string text, std::string filter);

void showBookMenu(const Book &book);

void showSearchMenu(const Library &library);

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
                bool running2 = true;
                while (running2) {
                    int bookSelected = ui::getOption("List of books available in the library", library.getFiles(),
                                                     "back");
                    if (bookSelected == -1) {
                        running2 = false;
                    } else {
                        showBookMenu(library.getFiles()[bookSelected]);
                    }
                }
                break;
            }
            case 1: {
                showSearchMenu(library);
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

void showSearchMenu(const Library &library) {
    std::vector<std::string> searchOptions = {"search by filename", "search by title", "search by author name"};
    bool running = true;
    while (running) {
        int optionSelected = ui::getOption("Select filter", searchOptions, "back");
        switch (optionSelected) {
            case 0: {
                std::string filter = ui::getText("Enter filename to search");

                std::vector<Book> filtered;

                std::copy_if(library.getFiles().begin(), library.getFiles().end(), std::back_inserter(filtered),
                             [filter](const Book &file) {
                                 return caseInsensitiveFind(file.getName(), filter);
                             });
                bool running2 = true;
                while (running2) {
                    int bookSelected;
                    if (filtered.empty()) {
                        bookSelected = ui::getOption("No matching book found in the library", filtered, "back");
                    } else {
                        bookSelected = ui::getOption("List of matching books in the library", filtered, "back");
                    }
                    if (bookSelected == -1) {
                        running2 = false;
                    } else {
                        showBookMenu(filtered[bookSelected]);
                    }
                }
                break;
            }
            case 1: {
                std::string filter = ui::getText("Enter title to search");

                std::vector<Book> filtered;

                std::copy_if(library.getFiles().begin(), library.getFiles().end(), std::back_inserter(filtered),
                             [filter](const Book &file) {
                                 return caseInsensitiveFind(file.getTitle(), filter);
                             });
                bool running2 = true;
                while (running2) {
                    int bookSelected;
                    if (filtered.empty()) {
                        bookSelected = ui::getOption("No matching book found in the library", filtered, "back");
                    } else {
                        bookSelected = ui::getOption("List of matching books in the library", filtered, "back");
                    }

                    if (bookSelected == -1) {
                        running2 = false;
                    } else {
                        showBookMenu(filtered[bookSelected]);
                    }
                }
                break;
            }
            case 2: {
                std::string filter = ui::getText("Enter author name to search");

                std::vector<Book> filtered;

                std::copy_if(library.getFiles().begin(), library.getFiles().end(), std::back_inserter(filtered),
                             [filter](const Book &file) {
                                 return caseInsensitiveFind(file.getAuthor(), filter);
                             });
                bool running2 = true;
                while (running2) {
                    int bookSelected;
                    if (filtered.empty()) {
                        bookSelected = ui::getOption("No matching book found in the library", filtered, "back");
                    } else {
                        bookSelected = ui::getOption("List of matching books in the library", filtered, "back");
                    }

                    if (bookSelected == -1) {
                        running2 = false;
                    } else {
                        showBookMenu(filtered[bookSelected]);
                    }
                }
                break;
            }
            default: {
                running = false;
                break;
            }
        }
    }
}

void showBookMenu(const Book &book) {
    std::vector<std::string> bookOptions = {"View book"};
    if (book.getType() == "novel") {
        bookOptions.emplace_back("Show word stats");
    } else {
        bookOptions.emplace_back("Show character stats");
    }

    bool running = true;
    while (running) {
        int optionSelected = ui::getOption("Select filter", bookOptions, "back");
        switch (optionSelected) {
            case 0: {
                ui::showBook(book);
                break;
            }
            case 1: {
                if (book.getType() == "novel") {
                    std::string query = ui::getText(
                            "Enter a word to search for top chapters and to paragraphs by the frequency of the word",
                            std::regex(R"([a-zA-Z]+)"));
                    unsigned statSize = std::stoi(
                            ui::getText("Enter n to get top n chapters and top n paragraphs", std::regex(R"(\d+)")));

                    NovelStats stats(book, query, statSize);
                    bool running2 = true;
                    while (running2) {
                        std::vector<std::string> statOptions = {"Top Paragraphs", "Top Chapters"};
                        int statOption = ui::getOption("Choose to view top paragraphs or chapters", statOptions,
                                                       "back");

                        switch (statOption) {
                            case 0: {
                                // todo print top paras
                                break;
                            }
                            case 1: {
                                // todo print top chapters
                                break;
                            }
                            default:
                                running2 = false;
                                break;
                        }

                    }

                    // TODO novel stats in progress
                } else {
                    // TODO play stats
                }
            }
            default:
                running = false;
                break;
        }
    }
}

bool caseInsensitiveFind(std::string text, std::string filter) {
    std::transform(text.begin(), text.end(), text.begin(), ::toupper);
    std::transform(filter.begin(), filter.end(), filter.begin(), ::toupper);
    return text.find(filter) < text.size() - 1;

}


inline bool pathExists(const std::string &name) {
    struct stat buffer{};
    return (stat(name.c_str(), &buffer) == 0);
}
