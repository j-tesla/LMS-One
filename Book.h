//
// Created by jsharp on 1/20/21.
//

#ifndef LMS_ONE_BOOK_H
#define LMS_ONE_BOOK_H


#include <string>
#include <ostream>
#include <fstream>
#include <vector>
//#include "Novel.h"

class Book {
private:
    enum FileType {
        NOVEL, PLAY
    };

    std::string name_;
    FileType type_;
    std::string title_;
    std::string author_;
    std::string filePath_;

    void readDetailsFromFile();

public:
    Book(std::string name, const std::string &directory, const std::string &type, std::string title,
         std::string author);

    explicit Book(std::string name, const std::string &directory);

    Book(const Book &other);

    std::string getType() const;

    const std::string &getName() const;

    const std::string &getTitle() const;

    const std::string &getAuthor() const;

    bool operator<(const Book &rhs) const;

    friend std::ostream &operator<<(std::ostream &os, const Book &file);

    friend class BookView;

    friend class NovelStats;

    friend class PlayStats;
};

class BookView {
private:
    std::ifstream *fileStream_{};
    std::vector<std::string> lines_;
    bool empty_{};

public:
    explicit BookView(const Book &file);

    BookView(const BookView &other) = delete;

    BookView &operator=(const BookView &rhs) = delete;

    const std::vector<std::string> &getLines(unsigned n);

    bool empty() const;

    ~BookView();

};


#endif //LMS_ONE_BOOK_H
