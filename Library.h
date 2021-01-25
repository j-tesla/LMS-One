//
// Created by jsharp on 1/13/21.
//

#ifndef LMS_ONE_LIBRARY_H
#define LMS_ONE_LIBRARY_H

#include <string>
#include <vector>
#include "LibraryFile.h"

class Library {


private:

    std::string libraryPath;
    std::vector<LibraryFile> files;
    void updateFilesFromDisk();
    void readIndex();
    void updateIndex();
public:
    explicit Library(std::string library);

    const std::string &getLibraryPath() const;

    const std::vector<LibraryFile> &getFiles() const;

};


#endif //LMS_ONE_LIBRARY_H
