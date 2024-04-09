#include "factory.hpp"

template<class C>
character* characterCreater<C>::create(std::pair<int, int> pos, observable* map) const {
    return new C(pos, map);
}

template<class C>
void characterFactory::add(int characterID) {
    characterFactory::mapFactory::iterator it = characterFactory::m.find(characterID);
    if (it == characterFactory::m.end()) {
        characterFactory::m[characterID] = new characterCreater<C>();
    }
}

character* characterFactory::create(int characterID, std::pair<int, int> pos, observable* map) {
    characterFactory::mapFactory::iterator it = characterFactory::m.find(characterID);
    if (it != characterFactory::m.end()) {
        return it->second->create(pos, map);
    }
    return 0;
}