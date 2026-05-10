// card.cpp
// Author: Wren Hzayen
// Implementation of the classes defined in card.h

#include "card.h"

using namespace std;

int suitRank(const string& suit) {
    if (suit == "c") return 0;
    if (suit == "d") return 1;
    if (suit == "s") return 2;
    if (suit == "h") return 3;
    return -1;
}

int valueRank(const string& value) {
    if (value == "a")  return 0;
    if (value == "j")  return 10;
    if (value == "q")  return 11;
    if (value == "k")  return 12;
    int n = stoi(value);
    return n - 1;
}

// comparison operator
bool Card::operator<(const Card& other) const {
    int sr = suitRank(suit);
    int sr2 = suitRank(other.suit);
    if (sr != sr2) return sr < sr2;
    return valueRank(value) < valueRank(other.value);
}

// equality operator
bool Card::operator==(const Card& other) const {
    return suit == other.suit && value == other.value;
}

// wait if stdout is just ostream, can't we modify the << operator to print a specific way when we use an ostream?
ostream& operator<<(ostream& os, const Card& c) {
    os << c.suit << " " << c.value;
    return os;
}
