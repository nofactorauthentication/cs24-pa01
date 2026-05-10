// card.h
// Author: Wren Hzayen
// All class declarations related to defining a single card go here

#ifndef CARD_H
#define CARD_H

#include <string>
#include <iostream>

using namespace std;

int suitRank(const string& suit);

int valueRank(const string& value);

struct Card {
    string suit;
    string value;

    Card(const string& s, const string& v) : suit(s), value(v) {}

    bool operator<(const Card& other) const;
    bool operator==(const Card& other) const;
};

ostream& operator<<(ostream& os, const Card& c);

#endif
