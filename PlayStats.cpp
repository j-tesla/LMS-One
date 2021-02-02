//
// Created by jsharp on 2/1/21.
//

#include <regex>
#include <utility>

#include "PlayStats.h"

PlayStats::PlayStats(const Book &book) : book_(book) {
    generateScenes();
    generateCharacters();
}

void PlayStats::generateScenes() {
    std::ifstream fileStream(book_.filePath_);

    std::string startMessage = "*** START OF THIS PROJECT GUTENBERG EBOOK";
    std::string currentLine;
    while (currentLine.substr(0, startMessage.length()) != startMessage) {
        getline(fileStream, currentLine);
        currentLine = std::regex_replace(currentLine, std::regex(R"(^[\t\n\r ]+)"), "");
        currentLine = std::regex_replace(currentLine, std::regex(R"([\t\n\r ]+$)"), "");
    }

    while (getline(fileStream, currentLine)) {
        currentLine = std::regex_replace(currentLine, std::regex(R"(^[\t\n\r ]+)"), "");
        currentLine = std::regex_replace(currentLine, std::regex(R"([\t\n\r ]+$)"), "");

        if (std::regex_match(currentLine, std::regex(R"(^SCENE.*)"))) {
            scenes_.emplace_back(Scene(currentLine));
        } else {
            if (not scenes_.empty()) {
                scenes_.back().addLine(currentLine);
            }
        }
    }
}

void PlayStats::generateCharacters() {
    for (const auto &scene : scenes_) {
        for (const auto &character : scene.getCharacters()) {
            characters_.emplace(character);
        }
    }
}

const std::set<std::string> &PlayStats::getCharacters() const {
    return characters_;
}

const std::string &PlayStats::getCharacter(int index) const {
    auto it = characters_.begin();
    for (int i = 0; i < index; ++i) {
        it++;
    }
    return  *it;

}

std::set<std::string> PlayStats::getCoCharacters(int index) const {
    std::set<std::string> coCharacters{};

    std::string lead = getCharacter(index);

    for (const auto &scene : scenes_) {
        if (scene.getCharacters().find(lead) != scene.getCharacters().end()) {
            for (const auto &character: scene.getCharacters()) {
                if (character != lead) {
                    coCharacters.emplace(character);
                }
            }
        }
    }

    return coCharacters;
}

Scene::Scene(std::string name) : name_(std::move(name)) {}

void Scene::addLine(const std::string &line) {
    if (std::regex_match(line, std::regex(R"(^[A-Z]+\..*)"))) {
        std::string character = line.substr(0, line.find('.'));
        if (character != "ACT" and character != "SCENE") {
            characters_.emplace(character);
        }
    }
}

const std::set<std::string> &Scene::getCharacters() const {
    return characters_;
}
