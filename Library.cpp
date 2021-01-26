//
// Created by jsharp on 1/13/21.
//

#include "Library.h"

#include <utility>
#include <dirent.h>
#include <fstream>
#include <regex>
#include <iostream>

Library::Library(std::string library) : libraryPath_(std::move(library)) {
    this->readIndex();
    this->updateFilesFromDisk();
}

void Library::readIndex() {
    std::ifstream index(this->libraryPath_ + "/index.txt");
    std::string current_line;
    while (getline(index, current_line)) {
        current_line = std::regex_replace(current_line, std::regex(R"(^[\t\n ]+)"), "");
        current_line = std::regex_replace(current_line, std::regex(R"([\t\n ]+$)"), "");
        std::string fileName = current_line.substr(0, current_line.find('\t'));
        current_line.erase(0, current_line.find('\t') + 1);
        std::string fileType = current_line.substr(0, current_line.find('\t'));
        current_line.erase(0, current_line.find('\t') + 1);
        std::string fileTitle = current_line.substr(0, current_line.find('\t'));
        current_line.erase(0, current_line.find('\t') + 1);
        std::string fileAuthor = current_line.substr(0, current_line.find('\t'));

        LibraryFile newFile(fileName, this->libraryPath_, fileType, fileTitle, fileAuthor);
        this->files_.emplace_back(newFile);
    }
}


void Library::updateFilesFromDisk() {
    DIR *dr;
    dirent *en;
    dr = opendir(this->libraryPath_.c_str());
    if (dr) {
        while ((en = readdir(dr)) != nullptr) {
            std::string filename(en->d_name);
            std::regex regex_filename(".+.txt");

            if (std::regex_match(filename, regex_filename) and filename != "index.txt") {
                bool already_present = false;
                for (const auto &file: this->files_) {
                    if (file.getName() == filename) {
                        already_present = true;
                        break;
                    }
                }
                if (not already_present) {
                    LibraryFile newFile(filename, this->libraryPath_);
                    this->files_.emplace_back(newFile);
                }
            }
        }
        closedir(dr);
        this->updateIndex();
    } else {
        std::cout << "dir absent" << std::endl;
    }
}

void Library::updateIndex() {
    std::ofstream indexFile(this->libraryPath_ + "/index.txt");

    for (const auto &file: this->files_) {
        indexFile << file.getName() << "\t" << file.getType() << "\t" << file.getTitle() << "\t" << file.getAuthor() << std::endl;
    }
    indexFile.close();
}

const std::string &Library::getLibraryPath() const {
    return libraryPath_;
}

const std::vector<LibraryFile> & Library::getFiles() const {
    return files_;
}
