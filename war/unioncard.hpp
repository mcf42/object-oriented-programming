#pragma once

#include <cassert>
#include <vector>
#include <iosfwd>
#include <iostream>

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

enum Suit {
  Spades,
  Clubs, 
  Diamonds,
  Hearts,
};

enum Color {
  Black, Red
};

class Card
{
public:
  Card(int n)
    : id(n)
  { }

  virtual ~Card() = default;

  virtual Card* clone() = 0;
};

class StandardCard : public Card
{
public:
  StandardCard(int n, Rank r, Suit s)
    : Card(n), rank(r), suit(s)
  { }

  Card* clone() override {
    return new StandardCard(*this);
  }

  Rank get_rank() const { return rank; }
  Suit get_suit() const { return suit; }

  Rank rank;
  Suit suit;
};

class JokerCard : public Card
{
public:
  JokerCard(int n, Color c)
    : Card(n), color(c)
  { }

  Card* clone() override {
    return new JokerCard(*this);
  }

  Color color;
};