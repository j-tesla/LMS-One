//
// Created by Jayanth PSY on 1/27/21.
//

#ifndef LMS_ONE_NOVELSTATS_H
#define LMS_ONE_NOVELSTATS_H

#include <string>
#include <vector>
#include <set>
#include <queue>
#include <ostream>

#include "Book.h"


class Paragraph;

class Chapter;

class NovelStats {
    const Book book_;
    const std::string word_{};
    const unsigned n_{};
    std::priority_queue<Paragraph, std::vector<Paragraph>, std::greater<>> topParagraphs_{};
    std::priority_queue<Chapter, std::vector<Chapter>, std::greater<>> topChapters_{};

    void addParagraph(const Paragraph &paragraph);

    void addChapter(const Chapter &chapter);

    void generateStats();

public:
    explicit NovelStats(const Book &book, std::string word, unsigned n);

    std::vector<Paragraph> getTopParagraphs();

    std::vector<Chapter> getTopChapters();

};

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

    bool operator<(const Paragraph &rhs) const;

    bool operator>(const Paragraph &rhs) const;

    bool operator<=(const Paragraph &rhs) const;

    bool operator>=(const Paragraph &rhs) const;

    friend std::ostream &operator<<(std::ostream &os, const Paragraph &paragraph);
};

class Chapter {
private:
    std::vector<Paragraph> paragraphs_{};
    std::string word_{};
    unsigned word_count{};

public:
    Chapter(std::vector<Paragraph> paragraphs, std::string word);

    std::vector<std::string> getLines() const;

    Chapter(const Chapter &chapter);

    unsigned int getWordCount() const;

    bool operator<(const Chapter &rhs) const;

    bool operator>(const Chapter &rhs) const;

    bool operator<=(const Chapter &rhs) const;

    bool operator>=(const Chapter &rhs) const;

    friend std::ostream &operator<<(std::ostream &os, const Chapter &chapter);
};


#endif //LMS_ONE_NOVELSTATS_H
