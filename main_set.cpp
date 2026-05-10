// This file should implement the game using the std::set container class
// Do not include card_list.h in this file
#include <iostream>
#include <fstream>
#include <string>
#include <set>

using namespace std;

// idea: we'll store the set as an integer in, of all things, base 13. the bigger digit is the suit, the smaller one is the card.

// then we'll convert this back to base 10, effectively assigning each card a #. club ace is 0, club king is 12, etc etc. these would be, to borrow from hex, 00 and 0b, which then rolls over to 10 with diamond ace. etc etc!

// encode helpers
int suitDigit(string suit) {
  if (suit == "c") return 0;
  if (suit == "d") return 13;
  if (suit == "s") return 26;
  if (suit == "h") return 39;
  return -1; // are you serious
}

int cardDigit(string value) {
  if (value == "a") return 1;
  if (value == "j") return 11;
  if (value == "q") return 12;
  if (value == "k") return 13;
  return stoi(value); // non-exceptional card
}

// encode - convert full card to int using above system
int encode(string suit, string value) {
  return suitDigit(suit) + cardDigit(value);
}

// decode helpers
string decodeSuit(int n) {
  switch ((n-1)/13) {
    case 0: return "c";
    case 1: return "d";
    case 2: return "s";
    case 3: return "h";
    default: return "N"; // should not happen
  }
}

string decodeValue(int n) {
  int card = (n-1) % 13 + 1;
  if (card == 1)  return "a";
  if (card == 11) return "j";
  if (card == 12) return "q";
  if (card == 13) return "k";
  return to_string(card); // non-exceptional card
}

// decode - print card in console
void printCard(int n) {
  cout << decodeSuit(n) << " " << decodeValue(n);
}

// other helpers
void parseLine(string card, set<int>& hand) {
  if (card.length() < 3) return;
  string suit  = card.substr(0, 1);
  string value = card.substr(2);
  hand.insert(encode(suit, value));
}

bool lookForMatch(set<int>& a, set<int>& b) {
  for (int card:a) {
    if (b.count(card)) return true;
  }
  return false;
}

int main(int argv, char** argc){
  if(argv < 3){
    cout << "Please provide 2 file names" << endl;
    return 1;
  }
  
  ifstream cardFile1 (argc[1]);
  ifstream cardFile2 (argc[2]);
  string line;

  if (cardFile1.fail() || cardFile2.fail() ){
    cout << "Could not open file " << argc[2];
    return 1;
  }

  set<int> hand_A, hand_B;

  //Read each file
  while (getline (cardFile1, line) && (line.length() > 0)){
    parseLine(line, hand_A);
  }
  cardFile1.close();


  while (getline (cardFile2, line) && (line.length() > 0)){
    parseLine(line, hand_B);
  }
  cardFile2.close();
  
  // game time; in main.cpp this should call playGame
  // thankfully we're in main_set

  while (lookForMatch(hand_A, hand_B)) {
    for(set<int>::iterator i = hand_A.begin(); i != hand_A.end(); ++i) {
      if (hand_B.count(*i)) {
        // picked card matches!
        cout << "Alice picked matching card "; printCard(*i); cout << endl;
        hand_B.erase(*i);
        hand_A.erase(*i);
        break;
      }
    }

    // apparently STL has a reverse iterator! i was looking more into how to use sets and found this on one of the cpp docs!
    // https://en.cppreference.com/cpp/iterator/reverse_iterator
    for(set<int>::reverse_iterator ri = hand_B.rbegin(); ri != hand_B.rend(); ++ri) {
      if (hand_A.count(*ri)) {
        // picked card matches!
        cout << "Bob picked matching card "; printCard(*ri); cout << endl;
        hand_A.erase(*ri);
        hand_B.erase(*ri);
        break;
      }
    }
  }

  // print cards
  cout << endl << "Alice's cards:" << endl;
  for (int card:hand_A) {
    printCard(card);
    cout << endl;
  }

  cout << endl << "Bob's cards:" << endl;
  for (int card:hand_B) {
    printCard(card);
    cout << endl;
  }
  
  return 0;
}
