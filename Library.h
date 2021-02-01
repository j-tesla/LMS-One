//
// Created by jsharp on 1/13/21.
//

#ifndef LMS_ONE_LIBRARY_H
#define LMS_ONE_LIBRARY_H

#include <string>
#include <vector>
#include <unordered_set>
#include <set>
#include "Book.h"

class Library {


private:

    std::string libraryPath_;
    std::set<Book> files_{};
    void updateFilesFromDisk();
    void readIndex();
    void updateIndex();
public:
    explicit Library(std::string library);

    std::vector<Book> getFiles() const;

};


#endif //LMS_ONE_LIBRARY_H
