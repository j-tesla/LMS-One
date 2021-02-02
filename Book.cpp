//
// Created by jsharp on 1/20/21.
//

#include "Book.h"

#include <utility>
#include <fstream>
#include <string>
#include "UI.h"

Book::Book(std::string name, const std::string &directory) : name_(std::move(name)) {
    filePath_ = directory + "/" + name_;
    std::vector<std::string> options = {"novel", "play"};
    int option = ui::getOption("Select the type of the file: " + name_, options);
    type_ = (FileType) option;
    readDetailsFromFile();
}

Book::Book(std::string name, const std::string &directory, const std::string &type, std::string title,
           std::string author, std::string releaseDate, std::string language) : name_(std::move(name)),
                                                                                title_(std::move(title)),
                                                                                author_(std::move(author)),
                                                                                releaseDate_(std::move(releaseDate)),
                                                                                language_(std::move(language)) {
    filePath_ = directory + "/" + name_;
    if (type == "novel") {
        type_ = NOVEL;
    } else if (type == "play") {
        type_ = PLAY;
    } else {
        throw std::runtime_error("Books of type " + type + " are not implemented yet.\n");
    }
}

Book::Book(const Book &other) : name_(other.name_), type_(other.type_), title_(other.title_),
                                author_(other.author_), releaseDate_(other.releaseDate_), language_(other.language_),
                                filePath_(other.filePath_) {}

void Book::readDetailsFromFile() {
    std::ifstream fileStream(filePath_);
    std::string currentLine;
    while (getline(fileStream, currentLine)) {
        currentLine = std::regex_replace(currentLine, std::regex(R"(^[\t\n\r ]+)"), "");
        currentLine = std::regex_replace(currentLine, std::regex(R"([\t\n\r ]+$)"), "");
        if (currentLine.substr(0, 6) == "Title:") {
            title_ = currentLine.substr(7);
            continue;
        }
        if (currentLine.substr(0, 7) == "Author:") {
            author_ = currentLine.substr(8);
            continue;
        }
        if (currentLine.substr(0, 13) == "Release Date:") {
            releaseDate_ = std::regex_replace(currentLine.substr(14), std::regex(R"(\[.*)"), "");
            std::cout << releaseDate_ << std::endl;
            continue;
        }
        if (currentLine.substr(0, 9) == "Language:") {
            language_ = currentLine.substr(10);
            std::cout << language_ << std::endl;
            break;
        }
    }
}

std::string Book::getType() const {
    switch (type_) {
        case NOVEL:
            return "novel";
        case PLAY:
            return "play";
        default:
            return "book";
    }
}

const std::string &Book::getName() const {
    return name_;
}

const std::string &Book::getTitle() const {
    return title_;
}

const std::string &Book::getAuthor() const {
    return author_;
}

const std::string &Book::getReleaseDate() const {
    return releaseDate_;
}

const std::string &Book::getLanguage() const {
    return language_;
}

bool Book::operator<(const Book &rhs) const {
    return std::tie(type_, title_, author_) < std::tie(rhs.type_, rhs.title_, rhs.author_);
}

std::ostream &operator<<(std::ostream &os, const Book &file) {
    os << file.name_ << "  type: " << file.getType() << "  title: " << file.title_ << "  author: " << file.author_
       << "\n   release date: " << file.releaseDate_ << " language: " << file.language_;
    return os;
}

BookView::BookView(const Book &file) : fileStream_(new std::ifstream(file.filePath_)),
                                       empty_(false) {
    std::string startMessage = "*** START OF THIS PROJECT GUTENBERG EBOOK";
    std::string currentLine;
    while (currentLine.substr(0, startMessage.length()) != startMessage) {
        getline(*fileStream_, currentLine);
        currentLine = std::regex_replace(currentLine, std::regex(R"(^[\t\n\r ]+)"), "");
        currentLine = std::regex_replace(currentLine, std::regex(R"([\t\n\r ]+$)"), "");
    }
}

const std::vector<std::string> &BookView::getLines(unsigned int n) {
    lines_.clear();

    std::string input;
    while (n--) {
        if (getline(*fileStream_, input)) {
            lines_.emplace_back(input);
        } else {
            empty_ = true;
            break;
        }
    }

    return lines_;
}

bool BookView::empty() const {
    return empty_;
}

BookView::~BookView() {
    lines_.clear();
    fileStream_->close();
    delete fileStream_;
}
