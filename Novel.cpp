//

//
// Created by jsharp on 1/27/21.


#include <utility>
#include <sstream>
#include <regex>

#include "Novel.h"

NovelStats::NovelStats(const Book &file, std::string word, unsigned n) : file_(file), word_(std::move(word)),
                                                                         n_(n) {
//    topChapters_ = std::priority_queue<Paragraph>();
}

void NovelStats::generateStats() {

    std::ifstream fileStream(file_.filePath_);

    std::string startMessage = "*** START OF THIS PROJECT GUTENBERG EBOOK";
    std::string currentLine;
    while (currentLine.substr(0, startMessage.length()) != startMessage) {
        getline(fileStream, currentLine);
        currentLine = std::regex_replace(currentLine, std::regex(R"(^[\t\n ]+)"), "");
        currentLine = std::regex_replace(currentLine, std::regex(R"([\t\n ]+$)"), "");
    }

    std::vector<std::string> currentParagraph;
    std::vector<Paragraph> currentChapter;

    // todo parse novel to generate tasks
    while (getline(fileStream, currentLine)) {
        currentLine = std::regex_replace(currentLine, std::regex(R"(^[\t\n ]+)"), "");
        currentLine = std::regex_replace(currentLine, std::regex(R"([\t\n ]+$)"), "");
        if (currentLine.empty() and not currentParagraph.empty()){
            Paragraph para(currentParagraph, word_);
            addParagraph(para);
            currentChapter.emplace_back(para);
            currentParagraph.clear();
        } else if (std::regex_match(currentLine, std::regex(R"(^[Cc][Hh][Aa][Pp][Tt][Ee][Rr].*)"))) {
            addChapter(Chapter(currentChapter, word_));
            currentChapter.clear();
            currentParagraph.emplace_back(currentLine);
        } else {
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

void NovelStats::addParagraph( Paragraph paragraph) {
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

Paragraph::Paragraph(std::vector<std::string> lines, std::string word) : lines_(std::move(lines)),
                                                                         word_(std::move(word)), word_count(0) {
    for (const std::string &line : lines_) {
        std::stringstream lineStream(line);
        std::string currentWord;
        while (lineStream >> currentWord) {
            if (std::regex_match(currentWord, std::regex(R"([^a-zA-Z]*)" + word + R"([^a-zA-Z]*)"))) {
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
