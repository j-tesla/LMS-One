//
// Created by jsharp on 2/1/21.
//

#ifndef LMS_ONE_PLAYSTATS_H
#define LMS_ONE_PLAYSTATS_H

#include <set>

#include "Book.h"

class Scene;

class PlayStats {
private:
    const Book book_;
    std::vector<Scene> scenes_{};
    std::set<std::string> characters_;

    void generateScenes();

    void generateCharacters();

public:
    explicit PlayStats(const Book &book);

    const std::set<std::string> &getCharacters() const;

    const std::string &getCharacter(int index) const;

    std::set<std::string> getCoCharacters(int index) const;
};

class Scene {
private:
    const std::string name_;
    std::set<std::string> characters_{};

public:
    explicit Scene(std::string name);

    void addLine(const std::string &line);

    const std::set<std::string> &getCharacters() const;

};


#endif //LMS_ONE_PLAYSTATS_H
