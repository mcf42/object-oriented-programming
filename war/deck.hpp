#pragma once

#include <cassert>
#include <vector>
#include <iosfwd>
#include <iostream>

class Deck : public std::vector<Card*>
{
public:
  Deck(std::initializer_list<Card*> list)
    : std::vector<Card*>(list)
  { }

  Deck(const Deck& d)
  {
    for (Card* c : d) {
      push_back(c->clone());
    }
  }

  ~Deck() {
    for (Card* c : *this)
      delete c;
  }
};

Deck get_deck();