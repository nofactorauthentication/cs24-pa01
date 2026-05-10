// This file should implement the game using a custom implementation of a BST (based on your earlier BST implementation)
#include <iostream>
#include <fstream>
#include <string>
#include "card_list.h"

using namespace std;

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
  
  return 0;
}
