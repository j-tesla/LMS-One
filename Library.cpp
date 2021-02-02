//
// Created by jsharp on 1/13/21.
//

#include "Library.h"

#include <utility>
#include <dirent.h>
#include <regex>
#include <iostream>

Library::Library(std::string library) : libraryPath_(std::move(library)) {
    this->readIndex();
    this->updateFilesFromDisk();
}

void Library::readIndex() {
    std::ifstream index(this->libraryPath_ + "/index.txt");
    std::string currentLine;
    while (getline(index, currentLine)) {
        currentLine = std::regex_replace(currentLine, std::regex(R"(^[\t\n\r ]+)"), "");
        currentLine = std::regex_replace(currentLine, std::regex(R"([\t\n\r ]+$)"), "");
        std::string fileName = currentLine.substr(0, currentLine.find('\t'));
        currentLine.erase(0, currentLine.find('\t') + 1);
        std::string fileType = currentLine.substr(0, currentLine.find('\t'));
        currentLine.erase(0, currentLine.find('\t') + 1);
        std::string fileTitle = currentLine.substr(0, currentLine.find('\t'));
        currentLine.erase(0, currentLine.find('\t') + 1);
        std::string fileAuthor = currentLine.substr(0, currentLine.find('\t'));
        currentLine.erase(0, currentLine.find('\t') + 1);
        std::string fileReleaseDate = currentLine.substr(0, currentLine.find('\t'));
        currentLine.erase(0, currentLine.find('\t') + 1);
        std::string fileLanguage = currentLine.substr(0, currentLine.find('\t'));
        Book newFile(fileName, libraryPath_, fileType, fileTitle, fileAuthor, fileReleaseDate, fileLanguage);
        files_.insert(newFile);
    }
}

void Library::updateFilesFromDisk() {
    DIR *dr;
    dirent *en;
    dr = opendir(libraryPath_.c_str());
    std::vector<std::string> inDiskNames{};

    if (dr) {
        while ((en = readdir(dr)) != nullptr) {
            std::string filename(en->d_name);
            std::regex regex_filename(".+.txt");

            if (std::regex_match(filename, regex_filename) and filename != "index.txt") {
                inDiskNames.emplace_back(filename);
            }
        }
        closedir(dr);
        // todo
        for (const auto &filename : inDiskNames) {
            bool alreadyPresent = false;
            for (const auto &file: files_) {
                if (file.getName() == filename) {
                    alreadyPresent = true;
                    break;
                }
            }
            if (not alreadyPresent) {
                Book newFile(filename, libraryPath_);
                files_.insert(newFile);
            }
        }

        auto it = files_.begin();
        while (it != files_.end()) {
            bool deleted = true;
            for (const auto &filename : inDiskNames) {
                if (filename == (*it).getName()) {
                    deleted = false;
                    break;
                }
            }
            if (deleted) {
                it = files_.erase(it);
            }

            ++it;
        }

        updateIndex();
    } else {
        throw std::runtime_error("Failed to access directory: " + libraryPath_ + "\n");
    }
}

void Library::updateIndex() {
    std::ofstream indexFile(libraryPath_ + "/index.txt");

    for (const auto &file: files_) {
        indexFile << file.getName() << "\t" << file.getType() << "\t" << file.getTitle() << "\t" << file.getAuthor()
                  << "\t" << file.getReleaseDate() << "\t" << file.getLanguage() << std::endl;
    }
    indexFile.close();
}

std::vector<Book> Library::getFiles() const {
    return std::vector<Book>(files_.begin(), files_.end());
}
