//
// Created by jsharp on 1/20/21.
//

#include "LibraryFile.h"

#include <utility>
#include <fstream>
#include "UI.h"

LibraryFile::LibraryFile(std::string name, const std::string &directory) : name(std::move(name)) {
    this->filePath = directory + "/" + this->name;
    std::vector<std::string> options = {"novel", "play"};
    int option = ui::getOption("Select the type of the file: " + this->name, options);
    this->type = (FileType) option;
    this->readDetailsFromFile();
}

LibraryFile::LibraryFile(std::string name, const std::string &directory, const std::string &type, std::string title,
                         std::string author) : name(
        std::move(name)), title(std::move(title)), author(std::move(author)) {
    this->filePath = directory + "/" + this->name;
    if (type == "novel") {
        this->type = NOVEL;
    } else if (type == "play") {
        this->type = PLAY;
    } else {
        throw;
    }
}

void LibraryFile::readDetailsFromFile() {
    std::ifstream fileStream(this->filePath);
    std::string current_line;
    while (getline(fileStream, current_line)) {
        if (current_line.substr(0, 6) == "Title:") {
            this->title = current_line.substr(7);
        }
        if (current_line.substr(0, 7) == "Author:") {
            this->author = current_line.substr(8);
            break;
        }
    }
}

std::string LibraryFile::getType() const {
    switch (this->type) {
        case NOVEL:
            return "novel";
        case PLAY:
            return "play";
        default:
            return "book";
    }
}

std::ostream &operator<<(std::ostream &os, const LibraryFile &file) {
    os << file.name << " type: " << file.type << " title: " << file.title << " author: " << file.author;
    return os;
}

const std::string &LibraryFile::getName() const {
    return name;
}

const std::string &LibraryFile::getTitle() const {
    return title;
}

const std::string &LibraryFile::getAuthor() const {
    return author;
}

