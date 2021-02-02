//

//
// Created by jsharp on 1/27/21.


#include <utility>
#include <regex>
#include <iostream>

#include "NovelStats.h"

NovelStats::NovelStats(const Book &book, std::string word, unsigned n) : book_(book), word_(std::move(word)),
                                                                         n_(n) {
    generateStats();
}

void NovelStats::generateStats() {
    std::ifstream fileStream(book_.filePath_);

    std::string startMessage = "*** START OF THIS PROJECT GUTENBERG EBOOK";
    std::string currentLine;
    while (currentLine.substr(0, startMessage.length()) != startMessage) {
        getline(fileStream, currentLine);
        currentLine = std::regex_replace(currentLine, std::regex(R"(^[\t\n\r ]+)"), "");
        currentLine = std::regex_replace(currentLine, std::regex(R"([\t\n\r ]+$)"), "");
    }

    std::vector<std::string> currentParagraph;
    std::vector<Paragraph> currentChapter;

    while (getline(fileStream, currentLine)) {
        currentLine = std::regex_replace(currentLine, std::regex(R"(^[\t\n\r ]+)"), "");
        currentLine = std::regex_replace(currentLine, std::regex(R"([\t\n\r ]+$)"), "");
        if (currentLine.empty() and not currentParagraph.empty()) {
            Paragraph para(currentParagraph, word_);
            addParagraph(para);
            currentChapter.emplace_back(para);
            currentParagraph.clear();
        } else if (std::regex_match(currentLine, std::regex(R"(^[Cc][Hh][Aa][Pp][Tt][Ee][Rr].*)"))) {
            addChapter(Chapter(currentChapter, word_));
            currentChapter.clear();
            currentParagraph.emplace_back(currentLine);
        } else if (not currentLine.empty()) {
            currentParagraph.emplace_back(currentLine);
        }
    }
    Paragraph para(currentParagraph, word_);
    addParagraph(para);
    currentChapter.emplace_back(para);
    currentParagraph.clear();
    addChapter(Chapter(currentChapter, word_));
    currentChapter.clear();
}

void NovelStats::addParagraph(const Paragraph &paragraph) {
    topParagraphs_.emplace(paragraph);
    if (topParagraphs_.size() > n_) {
        topParagraphs_.pop();
    }
}

void NovelStats::addChapter(const Chapter &chapter) {
    topChapters_.emplace(chapter);
    if (topChapters_.size() > n_) {
        topChapters_.pop();
    }

}

std::vector<Paragraph> NovelStats::getTopParagraphs() {
    std::vector<Paragraph> temp;
    auto topParagraphs = topParagraphs_;
    while (not topParagraphs.empty()) {
        if (topParagraphs.top().getWordCount() > 0)
            temp.insert(temp.begin(), topParagraphs.top());
        topParagraphs.pop();
    }
    return temp;
}

std::vector<Chapter> NovelStats::getTopChapters() {
    std::vector<Chapter> temp;
    auto topChapters = topChapters_;
    while (not topChapters.empty()) {
        if (topChapters.top().getWordCount() > 0)
            temp.insert(temp.begin(), topChapters.top());
        topChapters.pop();
    }
    return temp;
}

Paragraph::Paragraph(std::vector<std::string> lines, std::string word) : lines_(std::move(lines)),
                                                                         word_(std::move(word)), word_count(0) {
    for (const std::string &line : lines_) {
        std::stringstream lineStream(line);
        std::string currentWord;


        for (char &c: word_) {
            if (c <= 'z' and c >= 'a') {
                c += 'A' - 'a';
            }
        }
        while (lineStream >> currentWord) {
            for (char &c: currentWord) {
                if (c <= 'z' and c >= 'a') {
                    c += 'A' - 'a';
                }
            }
            if (std::regex_match(currentWord, std::regex(R"([^a-zA-Z]*)" + word_ + R"([^a-zA-Z]*)"))) {
                ++word_count;
            }
        }
    }
}

Paragraph::Paragraph(const Paragraph &paragraph) : lines_(paragraph.lines_), word_(paragraph.word_),
                                                   word_count(paragraph.word_count) {}

const std::vector<std::string> &Paragraph::getLines() const {
    return lines_;
}


Chapter::Chapter(std::vector<Paragraph> paragraphs, std::string word) : paragraphs_(std::move(paragraphs)),
                                                                        word_(std::move(word)), word_count(0) {
    for (const Paragraph &paragraph: paragraphs_) {
        word_count += paragraph.getWordCount();
    }
}

bool Paragraph::operator<(const Paragraph &rhs) const {
    return word_count < rhs.word_count;
}

bool Paragraph::operator>(const Paragraph &rhs) const {
    return rhs < *this;
}

bool Paragraph::operator<=(const Paragraph &rhs) const {
    return !(rhs < *this);
}

bool Paragraph::operator>=(const Paragraph &rhs) const {
    return !(*this < rhs);
}

const std::string &Paragraph::getWord() const {
    return word_;
}

unsigned int Paragraph::getWordCount() const {
    return word_count;
}

std::ostream &operator<<(std::ostream &os, const Paragraph &paragraph) {
    os << paragraph.lines_[0].substr(0, 30) << " ... " << "(" << paragraph.word_count << " occurrence(s) of "
       << paragraph.word_ << ")";
    return os;
}

Chapter::Chapter(const Chapter &chapter) : paragraphs_(chapter.paragraphs_), word_(chapter.word_),
                                           word_count(chapter.word_count) {}

const std::string &Chapter::getWord() const {
    return word_;
}

unsigned int Chapter::getWordCount() const {
    return word_count;
}

const std::vector<Paragraph> &Chapter::getParagraphs() const {
    return paragraphs_;
}

bool Chapter::operator<(const Chapter &rhs) const {
    return word_count < rhs.word_count;
}

bool Chapter::operator>(const Chapter &rhs) const {
    return rhs < *this;
}

bool Chapter::operator<=(const Chapter &rhs) const {
    return !(rhs < *this);
}

bool Chapter::operator>=(const Chapter &rhs) const {
    return !(*this < rhs);
}

std::ostream &operator<<(std::ostream &os, const Chapter &chapter) {
    os << chapter.paragraphs_[0].getLines()[0]  << "(" << chapter.word_count << " occurrence(s) of " << chapter.word_ << ")" ;
    return os;
}

std::vector<std::string> Chapter::getLines() const {
    std::vector<std::string> lines;
    for (const Paragraph &para : paragraphs_) {
        auto paraLines = para.getLines();
        lines.reserve(lines.size() + paraLines.size());
        lines.insert(lines.end(), paraLines.begin(), paraLines.end());
    }

    return lines;
}

//Novel::Novel(const Book &other) : Book(other) {
////    stats = NovelStats(*this)
//}
