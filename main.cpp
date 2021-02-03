//
// Created by Jayanth PSY on 1/13/21.
//

#include <sys/stat.h>

#include <iostream>
#include <string>

#include "Library.h"
#include "UI.h"
#include "NovelStats.h"
#include "PlayStats.h"


inline bool pathExists(const std::string &name);

bool caseInsensitiveFind(std::string text, std::string filter);

void showBookMenu(const Book &book);

void showSearchMenu(const Library &library);

void showMainMenu(const std::string &library_location);

int main(int argc, char *argv[]) {

    if (argc < 2) {
        throw std::runtime_error("Path to library is expected as an argument.\n");
    }

    const std::string library_location(argv[1]);
    if (not pathExists(library_location)) {
        throw std::runtime_error("Failed to access the directory: " + library_location + "\n");
    }
    ui::welcome();


    showMainMenu(library_location);
    return 0;
}

void showMainMenu(const std::string &library_location) {
    Library library(library_location);
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

                auto libraryFiles = library.getFiles();
                std::vector<Book> filtered{};

                std::copy_if(libraryFiles.begin(), libraryFiles.end(), std::back_inserter(filtered),
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

                auto libraryFiles = library.getFiles();
                std::vector<Book> filtered{};

                std::copy_if(libraryFiles.begin(), libraryFiles.end(), std::back_inserter(filtered),
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

                auto libraryFiles = library.getFiles();
                std::vector<Book> filtered{};

                std::copy_if(libraryFiles.begin(), libraryFiles.end(), std::back_inserter(filtered),
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
                            "Enter a word to search for top chapters and top paragraphs by the frequency of the word",
                            std::regex(R"([a-zA-Z]+)"));
                    unsigned statSize = std::stoi(
                            ui::getText("Enter n to get top n chapters and top n paragraphs", std::regex(R"(\d+)")));

                    ui::showLine("Please be patient. It takes a few moments to process the book.");
                    NovelStats stats(book, query, statSize);
                    bool running2 = true;
                    while (running2) {
                        std::vector<std::string> statOptions = {"Top Paragraphs", "Top Chapters"};
                        int statOption = ui::getOption("Choose to view top paragraphs or chapters", statOptions,
                                                       "back");

                        switch (statOption) {
                            case 0: {
                                bool running3 = true;
                                auto topParagraphs = stats.getTopParagraphs();
                                while (running3) {
                                    unsigned chosenPara = ui::getOption("Top paragraphs:", topParagraphs, "back");
                                    if (chosenPara == -1) {
                                        running3 = false;
                                    } else {
                                        ui::showLines(topParagraphs[chosenPara].getLines());
                                    }
                                }
                                break;
                            }
                            case 1: {
                                bool running3 = true;
                                auto topChapters = stats.getTopChapters();
                                while (running3) {
                                    unsigned chosenChapter = ui::getOption("Top paragraphs:", topChapters, "back");
                                    if (chosenChapter == -1) {
                                        running3 = false;
                                    } else {
                                        ui::showLines(topChapters[chosenChapter].getLines());
                                    }
                                }
                                break;
                            }
                            default:
                                running2 = false;
                                break;
                        }
                    }
                } else if (book.getType() == "play") {
                    ui::showLine("Please be patient. It takes a few moments to process the book.");
                    PlayStats stats(book);

                    bool running2 = true;
                    while (running2) {
                        int characterSelected = ui::getOption(
                                "Select a character to view his/her co-characters.",
                                stats.getCharacters(), "back");

                        if (characterSelected == -1) {
                            running2 = false;
                        } else {
                            ui::showList("Characters who acted in at least one scene with " +
                                         stats.getCharacter(characterSelected) + ":",
                                         stats.getCoCharacters(characterSelected));
                            ui::getText("Press enter to continue.", std::regex(".*"));
                        }
                    }
                } else {
                    ui::showLine("Books of type " + book.getType() + " are not supported yet.");
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

bool caseInsensitiveFind(std::string text, std::string filter) {
    for (char &c: text) {
        if (c >= 'a' and c <= 'z') {
            c += 'A' - 'a';
        }
    }
    for (char &c: filter) {
        if (c >= 'a' and c <= 'z') {
            c += 'A' - 'a';
        }
    }
    return text.find(filter) < text.size() - 1;

}


inline bool pathExists(const std::string &name) {
    struct stat buffer{};
    return (stat(name.c_str(), &buffer) == 0);
}
