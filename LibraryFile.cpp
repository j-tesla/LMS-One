//
// Created by jsharp on 1/20/21.
//

#include "LibraryFile.h"

#include <utility>
#include <fstream>
#include "UI.h"

LibraryFile::LibraryFile(std::string name, const std::string &directory) : name_(std::move(name)) {
    this->filePath_ = directory + "/" + this->name_;
    std::vector<std::string> options = {"novel", "play"};
    int option = ui::getOption("Select the type_ of the file: " + this->name_, options);
    this->type_ = (FileType) option;
    this->readDetailsFromFile();
}

LibraryFile::LibraryFile(std::string name, const std::string &directory, const std::string &type, std::string title,
                         std::string author) : name_(
        std::move(name)), title_(std::move(title)), author_(std::move(author)) {
    this->filePath_ = directory + "/" + this->name_;
    if (type == "novel") {
        this->type_ = NOVEL;
    } else if (type == "play") {
        this->type_ = PLAY;
    } else {
        throw;
    }
}

LibraryFile::LibraryFile(const LibraryFile &other): name_(other.name_), type_(other.type_), title_(other.title_), author_(other.title_), filePath_(other.filePath_) {
}

void LibraryFile::readDetailsFromFile() {
    std::ifstream fileStream(this->filePath_);
    std::string current_line;
    while (getline(fileStream, current_line)) {
        if (current_line.substr(0, 6) == "Title:") {
            this->title_ = current_line.substr(7);
        }
        if (current_line.substr(0, 7) == "Author:") {
            this->author_ = current_line.substr(8);
            break;
        }
    }
}

std::string LibraryFile::getType() const {
    switch (this->type_) {
        case NOVEL:
            return "novel";
        case PLAY:
            return "play";
        default:
            return "book";
    }
}

std::ostream &operator<<(std::ostream &os, const LibraryFile &file) {
    os << file.name_ << "  type: " << file.getType() << "  title: " << file.title_ << "  author: " << file.author_;
    return os;
}

const std::string &LibraryFile::getName() const {
    return name_;
}

const std::string &LibraryFile::getTitle() const {
    return title_;
}

const std::string &LibraryFile::getAuthor() const {
    return author_;
}

