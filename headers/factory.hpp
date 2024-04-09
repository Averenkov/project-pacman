#ifndef FACTORY_HPP
#define FACTORY_HPP
#include "character.hpp"
#include "observe.hpp"
#include <map>
#include <iostream>
#include <utility>

class abstractCharacterFactory {
public:
    virtual character* create(std::pair<int, int> pos, observable* map) const = 0;
};

template<class C>
class characterCreater: public abstractCharacterFactory {
public:
    virtual character* create(std::pair<int, int> pos, observable* map) const;
};

class characterFactory {
protected:
    typedef std::map<int, abstractCharacterFactory*> mapFactory;
    mapFactory m;
public:
    characterFactory() = default;

    template<class C>
    void add(int characterID);

    character* create(int characterID, std::pair<int, int> pos, observable* map);
};

#endif