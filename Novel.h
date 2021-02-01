//
// Created by jsharp on 1/27/21.
//

#ifndef LMS_ONE_NOVEL_H
#define LMS_ONE_NOVEL_H

#include <string>
#include <vector>
#include <set>
#include <queue>

#include "Book.h"

class Paragraph {
private:
    std::vector<std::string> lines_;
    std::string word_;
    unsigned word_count;

public:
    explicit Paragraph(std::vector<std::string> lines, std::string word);

    Paragraph(const Paragraph &paragraph);

    const std::vector<std::string> &getLines() const;

    unsigned int getWordCount() const;

    const std::string &getWord() const;

    bool operator<(const Paragraph &rhs) const;

    bool operator>(const Paragraph &rhs) const;

    bool operator<=(const Paragraph &rhs) const;

    bool operator>=(const Paragraph &rhs) const;

};

class Chapter {
private:
    std::vector<Paragraph> paragraphs_;
    std::string word_;
    unsigned word_count;

public:
    Chapter(std::vector<Paragraph> paragraphs, std::string word);

    const std::vector<Paragraph> &getParagraphs() const;

    Chapter(const Chapter &chapter);

    const std::string &getWord() const;

    unsigned int getWordCount() const;

    bool operator<(const Chapter &rhs) const;

    bool operator>(const Chapter &rhs) const;

    bool operator<=(const Chapter &rhs) const;

    bool operator>=(const Chapter &rhs) const;
};

class NovelStats {
    const Book file_;
    const std::string word_{};
    const unsigned n_{};
    std::priority_queue<Paragraph> topParagraphs_{};
    std::priority_queue<Chapter> topChapters_{};

    void addParagraph(Paragraph paragraph);

    void addChapter(const Chapter &chapter);

    void generateStats();

public:
    explicit NovelStats(const Book &file, std::string word, unsigned n);

};

#endif //LMS_ONE_NOVEL_H
