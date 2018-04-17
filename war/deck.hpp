
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

      // std::cout << c << '\n';
      // if (StandardCard* sc = dynamic_cast<StandardCard*>(c))
      //   push_back(new StandardCard(*sc));
      // else if (JokerCard* jc = dynamic_cast<JokerCard*>(c))
      //   push_back(new JokerCard(*jc));
      // else
      //   throw std::logic_error("unknown card");

      // if (the dynamic type of c is StandardCard)
      //   push_back(new StandardCard(...));
      // if (the dynamic type of c is JokerCard)
      //   push_back(new JokerCard(...));
    }
  }

  ~Deck() {
    for (Card* c : *this)
      delete c;
  }
};

Deck get_deck();

