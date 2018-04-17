
#pragma once

#include <cassert>
#include <vector>
#include <iosfwd>
#include <iostream>

// Defines a new type (user-defined type). Sometimes called
// a kind of type constructor (ignore that).
enum Rank {
  Ace,
  Two,
  Three,
  Four,
  Five,
  Six,
  Seven,
  Eight,
  Nine,
  Ten,
  Jack,
  Queen,
  King,
};

// Represents the suits of a card.
enum Suit {
  Spades,
  Clubs, 
  Diamonds,
  Hearts,
};

enum Color {
  Black, Red
};


// Declares the base class. This class
// abstractly represents the set of all
// cards. There is no object that is not
// one of the derived classes.
class Card
{
public:
  // Just a regular constructor...
  Card(int n)
    : id(n)
  { }

  // Ignore me...
  virtual ~Card() = default;

  // Goal: somebody calls clone and gets a new
  // Card of the same dynamic type and having
  // the same value.
  //
  // This is a virtual function. Calling a virtual
  // function actually calls an overridden version
  // of this function. Which override? The one
  // in the dynamic type of the object on which
  // the function is called.
  //
  // This actually called "virtual constructor".
  // virtual Card* clone() { throw std::logic_error("oops"); }

  // This is called a *pure virtual function*.
  // Pure virtual functions *must* be overridden in
  // a derived class.
  virtual Card* clone() = 0;


  int get_id() const { return id; }

  // Just for fun... uniquely number
  // each card in the deck.
  int id;
};

// Declares a derived class. We often say
// that Standard IS-A Card.
class StandardCard : public Card
{
public:
  // We "inherit" the members of the base
  // class (almost as if) they were declared
  // here.
  // int id;

  // Just a regular constructor... but.
  // You can call a base class constructor
  // explicitly in the member initializer
  // list.
  StandardCard(int n, Rank r, Suit s)
    : Card(n), rank(r), suit(s)
  { }

  // This is an *override* of clone.
  Card* clone() override {
    return new StandardCard(*this);
  }

  Rank get_rank() const { return rank; }
  Suit get_suit() const { return suit; }

  Rank rank;
  Suit suit;
};

// Declares another derived class.
class JokerCard : public Card
{
public:
  JokerCard(int n, Color c)
    : Card(n), color(c)
  { }

  // An *override* of Card::clone.
  Card* clone() override {
    return new JokerCard(*this);
  }

  Color color;
};



// The deck is THE OWNER of the cards it is
// initialized with. To own an object means to
// control its lifetime (i.e., this class
// deletes the owned objects).
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
