// card_list.cpp
// Author: Wren Hzayen
// Implementation of the classes defined in card_list.h

#include "card_list.h"

CardList::CardList() : root(nullptr) {}

CardList::~CardList() {
  del(root);
}

// priv nav helpers
Node* CardList::min(Node* n) const {
  if(!n) return nullptr;
  while(n->left) n=n->left;
  return n;
}

Node* CardList::max(Node* n) const {
  if(!n) return nullptr;
  while(n->right) n=n->right;
  return n;
}

Node* CardList::next(const Node* n) const{
  if(n->right) return min(n->right);
  Node* p = n->parent;
  while(p&&n == p->right) {
    n=p;
    p=p->parent;
  }
  
  return p;
}

Node* CardList::prev(const Node* n) const {
  if(n->left) return max(n->left);
  Node* p = n->parent;
  while(p&&n == p->left) {
    n=p;
    p=p->parent;
  }
  
  return p;
}

// priv op helpers

void CardList::swap(Node* a, Node* b) {
  if (!a->parent) root = b;
  else if (a==a->parent->left) a->parent->left = b;
  else a->parent->right = b;
  if (b) b->parent = a->parent;
}

void CardList::del(Node* n) {
  if (!n) return;
  del(n->left);
  del(n->right);
  delete n;
}

Node* CardList::search(const Card& card) const {
  Node* current = root;

  // search for the card based off value
  while(current) {
    if (card == current->card) return current;
    else if (card < current->card) current = current->left;
    else current = current->right;
  }
  return nullptr;
}

// iterator op overloads

CardList::iterator& CardList::iterator::operator++() { // dont wanna confuse with std::iterator
  if(current) current = list->next(current);
  return *this;
}

CardList::iterator CardList::iterator::operator++(int) {
  iterator newcard = *this;
  ++(*this);
  return newcard;
}

CardList::iterator& CardList::iterator::operator--() {
  // we need to do this because this is how decrementing through the list works. else we just get a broken hand :c

  if (!current) current = list->max(list->root);
  else current = list->prev(current);
  return *this;
}

CardList::iterator CardList::iterator::operator--(int) {
  iterator newcard = *this;
  --(*this);
  return newcard;
}

// public fxns

void CardList::insert(const Card& card) {
  Node* newCard = new Node(card);
  Node* parent = nullptr;
  Node* current = root;

  while(current) {
    parent = current;

    // search for card currently existing, or candidate parent.
    // if duplicate, delete new card
    if (card < current->card) current = current->left;
    else if (current->card < card) current = current->right; // using > kills this
    else {
      delete newCard;
      return;
    }
  }

  newCard->parent = parent;
  if (!parent) root = newCard;
  else if (card < parent->card) parent->left = newCard;
  else parent->right = newCard;
}

void CardList::remove(iterator it) {
  Node* current = it.current;
  if (!current) return;

  if(!current->left) {
    swap(current, current->right);
  } else if (!current->right) {
    swap(current, current->left);
  } else {
    Node* minimum = min(current->right);
    if(minimum->parent != current) {
      // make sure right child is adopted
      // sorry jimmy your parents adopted you or something i dunno lmao

      swap(minimum, minimum->right);
      minimum->right = current->right;
      minimum->right->parent = minimum;
    }
    // adopt left child as well
    swap(current, minimum);
    minimum->left = current->left;
    minimum->left->parent = minimum;
  }

  delete current; // do the actual deletion
}

CardList::iterator CardList::find(const Card& card) const {
  return iterator(search(card), this);
}

bool CardList::contains(const Card& card) const {
  return (search(card));
}

// fxns to make iterator

CardList::iterator CardList::begin() const {
  return iterator(min(root), this);
}

CardList::iterator CardList::end() const {
  return iterator(nullptr, this);
}

CardList::reverse_iterator CardList::rbegin() const { // dont wanna confuse with std::reverse_iterator
  return reverse_iterator(end());
}

CardList::reverse_iterator CardList::rend() const {
  return reverse_iterator(begin());
}

// playgame & main helpers

void parseLine(string card, CardList& hand) {
  if (card.length() < 3) return;
  string suit  = card.substr(0, 1);
  string value = card.substr(2);
  hand.insert(Card(suit, value));
}

bool lookForMatch(const CardList& a, const CardList& b) {
  for (CardList::iterator i = a.begin(); i != a.end(); ++i) {
    if (b.contains(*i)) return true;
  }
  return false;
}

// playgame (arguably this should be in main but the instructions call for it to be here)

void playGame(CardList& hand_A, CardList& hand_B) {
  while (lookForMatch(hand_A, hand_B)) {
    // process hand A
    for (CardList::iterator i = hand_A.begin(); i != hand_A.end(); ++i) {
      if (hand_B.contains(*i)) {
        Card target = *i;
        cout << "Alice picked matching card " << target << endl;
        hand_A.remove(hand_A.find(target));
        hand_B.remove(hand_B.find(target));
        break;
      }
    }

    if (!lookForMatch(hand_A, hand_B)) break;

    // process hand B
    for (CardList::reverse_iterator ri = hand_B.rbegin(); ri != hand_B.rend(); ++ri) {
      if (hand_A.contains(*ri)) {
        Card target = *ri;
        cout << "Bob picked matching card " << target << endl;
        hand_A.remove(hand_A.find(target));
        hand_B.remove(hand_B.find(target));
        break;
      }
    }
  }

  // print cards
  cout << endl << "Alice's cards:" << endl;
  for (CardList::iterator i = hand_A.begin(); i != hand_A.end(); ++i) {
    cout << *i << endl;
  }

  cout << endl << "Bob's cards:" << endl;
  for (CardList::iterator i = hand_B.begin(); i != hand_B.end(); ++i) {
    cout << *i << endl;
  }
}
