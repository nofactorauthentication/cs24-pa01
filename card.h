// card.h
// Author: Wren Hzayen
// All class declarations related to defining a single card go here

#ifndef CARD_H
#define CARD_H

#include <string>
#include <iostream>

int suitRank(const std::string& suit);

int valueRank(const std::string& value);

struct Card {
    std::string suit;
    std::string value;

    Card(std::string& s, std::string& v) : suit(s), value(v) {}

    bool operator<(const Card& other) const;
    bool operator==(const Card& other) const;
};

std::ostream& operator<<(std::ostream& os, Card& c);

#endif
