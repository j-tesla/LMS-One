//
// Created by jsharp on 1/20/21.
//

#ifndef LMS_ONE_LIBRARYFILE_H
#define LMS_ONE_LIBRARYFILE_H


#include <string>
#include <ostream>

enum FileType {
    NOVEL, PLAY
};

class LibraryFile {
private:
    std::string name;
    FileType type;
    std::string title;
    std::string author;
    std::string filePath;

    void readDetailsFromFile();

public:
    LibraryFile(std::string name, const std::string &directory, const std::string& type, std::string title, std::string author);

    explicit LibraryFile(std::string name, const std::string &directory);


    std::string getType() const;

    const std::string &getName() const;

    const std::string &getTitle() const;

    const std::string &getAuthor() const;

    friend std::ostream &operator<<(std::ostream &os, const LibraryFile &file);

};



#endif //LMS_ONE_LIBRARYFILE_H