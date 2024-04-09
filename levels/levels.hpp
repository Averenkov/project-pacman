#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <vector>
#include <string>
#include <iostream>

enum map_symbol {
    pacman = 'C',
    evil = 'E',
    brick = 'A',
    empty = 'B',
    loot = ' '
};


struct Level {
    const int width = 19;
    const int length = 21;
    std::vector<std::string> sheme = {
        "AAAAAAAAAAAAAAAAAAA",
        "A        A        A",
        "A AA AAA A AAA AA A",
        "A        A        A",
        "A AA A AAAAA A AA A",
        "A    A   A   A    A",
        "AAAA AAA A AAA AAAA",
        "BBBA A       A ABBB",
        "AAAA A ABBBA A AAAA",
        "       BEEEB       ",
        "AAAA A ABBBA A AAAA",
        "BBBA A       A ABBB",
        "AAAA A AAAAA A AAAA",
        "A        A        A",
        "A AA AAA A AAA AA A",
        "A  A     C     A  A",
        "AA A A AAAAA A A AA",
        "A    A   A   A    A",
        "A AAAAAA A AAAAAA A",
        "A                 A",
        "AAAAAAAAAAAAAAAAAAA"
    };
};

#endif