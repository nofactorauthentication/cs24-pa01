// tests.cpp
// Author: Wren Hzayen

#include <iostream>
#include <fstream>
#include <string>
#include "card.h"
#include "card_list.h"

bool handEquality(const CardList& a, const CardList& b) {
    CardList::iterator itA = a.begin();
    CardList::iterator itB = b.begin();

    while (itA != a.end() && itB != b.end()) {
        if (!(*itA == *itB)) {
            return false;
        }

        ++itA;
        ++itB;
    }

    return (itA == a.end() && itB == b.end());
}

int main(int argv, char** argc) {
    cout << "Begin testing." << endl;

    CardList hand_test;
    Card club("c", "10");
    Card diamond("d", "3");
    Card spade("s", "2");
    Card fake("h", "9");


    if(hand_test.contains(club)) {cout << "container fail"; return -1;}
    if((hand_test.begin() != hand_test.end())) {cout << "begin fail"; return -1;}
    if((hand_test.rbegin() != hand_test.rend())) {cout << "rend 1 fail"; return -1;}

    hand_test.insert(club);

    if(!(hand_test.contains(club))) {cout << "insert fail"; return -1;}
    if(!(hand_test.begin() != hand_test.end())) {cout << "begin=end fail single"; return -1;}
    if(!((*hand_test.begin()).suit == "c") || !((*hand_test.begin()).value == "10")) {cout << "c10 fail";  return -1;}

    hand_test.insert(diamond);
    hand_test.insert(spade);

    CardList::iterator it = hand_test.begin();

    it++; // also an increment up check
    if(!((*it).suit == "d") || !((*it).value == "3")) {cout << "d3 or increment fail"; return -1;}
    it++;
    if(!((*it).suit == "s") || !((*it).value == "2")) {cout << "s2 fail"; return -1;}

    it++;
    if(!(it == hand_test.end())) {cout << "end fail"; return -1;}

    it++; // safe end behavior check
    if(!(it == hand_test.end())) {cout << "end safe fail"; return -1;}

    if(hand_test.contains(fake)) {cout << "container fail hearts"; return -1;}

    hand_test.insert(club);

    it = hand_test.begin();
    it++;
    if(!((*it).suit == "d") || !((*it).value == "3")) {cout << "duplicate fail"; return -1;}

    it = hand_test.end();
    --it;
    --it;
    if(!((*it).suit == "d") || !((*it).value == "3")) {cout << "decrement fail"; return -1;}

    CardList::reverse_iterator rit = hand_test.rend();

    --rit;
    if(!((*rit).suit == "c") || !((*rit).value == "10")) {cout << "reverse iterator increment fail"; return -1;}

    CardList::iterator it2 = hand_test.begin();
    it = hand_test.end();

    if(it == it2) {cout << "comparison fail; unequality"; return -1;}

    --it;
    --it;
    it2++;

    if(it != it2) {cout << "comparison fail; equality"; return -1;}

    // game testing; DO NOT CHANGE ALICE OR BOB OR I DIE

    CardList expectedAlice;
    expectedAlice.insert(Card("c", "a"));
    expectedAlice.insert(Card("s", "5"));
    expectedAlice.insert(Card("h", "3"));

    CardList expectedBob;
    expectedBob.insert(Card("c", "2"));
    expectedBob.insert(Card("d", "j"));
    expectedBob.insert(Card("h", "a"));

    // ripped from main

    ifstream cardFile1 (argc[1]);
    ifstream cardFile2 (argc[2]);
    string line;

    if (cardFile1.fail() || cardFile2.fail() ){
        cout << "Could not open file " << argc[2];
        return 1;
    }

    CardList hand_A, hand_B;

    //Read each file
    while (getline (cardFile1, line) && (line.length() > 0)){
        parseLine(line, hand_A);
    }
    cardFile1.close();


    while (getline (cardFile2, line) && (line.length() > 0)){
        parseLine(line, hand_B);
    }
    cardFile2.close();

    playGame(hand_A, hand_B);

    if(!handEquality(hand_A, expectedAlice)) {cout << "alice fail"; return -1;}
    if(!handEquality(hand_B, expectedBob)) {cout << "bob fail"; return -1;}

    // check if no common card does nothing

    playGame(hand_A, hand_B);

    if(!handEquality(hand_A, expectedAlice)) {cout << "alice fail ncc"; return -1;}
    if(!handEquality(hand_B, expectedBob)) {cout << "bob fail ncc"; return -1;}

    CardList blankHand;

    playGame(hand_A, blankHand);

    if(!handEquality(hand_A, expectedAlice)) {cout << "alice fail on blank"; return -1;}
    if(!handEquality(blankHand, blankHand)) {cout << "blank fail"; return -1;}

    cout << "i did a good code";

    return 0;
}
