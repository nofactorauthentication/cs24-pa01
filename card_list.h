// card_list.h
// Author: Wren Hzayen
// All class declarations related to defining a BST that represents a player's hand

#ifndef CARD_LIST_H
#define CARD_LIST_H

#include "card.h"
#include <iterator>

using namespace std;

struct Node {
  Card card;
  Node* left;
  Node* right;
  Node* parent;

  Node(const Card& c): card(c), left(nullptr), right(nullptr), parent(nullptr) {}
};

class CardList {
private:
  Node* root;

  // Nav helpers
  Node* min(Node* n) const;
  Node* max(Node* n) const;
  Node* next(const Node* n) const;
  Node* prev(const Node* n) const;

  void swap(Node* a, Node* b);
  void del(Node* n);
  Node* search(const Card& card) const;


public:
  // iterator & reverse
  class iterator {
  private: 
    Node* current;
    const CardList* list;
    friend class CardList; 

  public:
    // i had to google how iterators are declared for this to work. *this included usage of the google ai summary for iterator_category and difference_type*, despite my best efforts to avoid it.
    using iterator_category = bidirectional_iterator_tag;
    using value_type = Card;
    using difference_type = ptrdiff_t;
    using pointer = const Card*;
    using reference = const Card&;

    // constructors
    iterator() : current(nullptr), list(nullptr) {}
    iterator(Node* n, const CardList* list) : current(n), list(list) {}

    // ref/deref
    const Card& operator*() const { return current->card;}
    const Card* operator->() const { return &current->card;}

    // increment
    iterator& operator++();
    iterator operator++(int);

    // decrement
    iterator& operator--();
    iterator operator--(int);

    // equality
    bool operator==(const iterator& i) const {return current == i.current;}
    bool operator!=(const iterator& i) const {return current != i.current;}
  };

  using reverse_iterator = std::reverse_iterator<iterator>;

  CardList();
  ~CardList();

  void insert(const Card& card);
  void remove(iterator it);
  iterator find(const Card& card) const;
  bool contains(const Card& card) const;
  
  iterator begin() const;
  iterator end() const;
  reverse_iterator rbegin() const;
  reverse_iterator rend() const;

};

void parseLine(string card, CardList& hand);
bool lookForMatch(const CardList& a, const CardList& b);
void playGame(CardList& hand_A, CardList& hand_B);

#endif
