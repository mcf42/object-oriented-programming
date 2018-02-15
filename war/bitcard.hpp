#pragma once

#include <iosfwd>

#include <vector>

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

enum Suit{
  Hearts,
  Diamonds,
  Clubs,
  Spades,
};

class BitCard{
Public:
  Card() = default;
  Card(Rank r, Suit s)
    : bits((unsigned)s << 4 | (unsigned)r)
  {}

  Rank get_rank() const {
    return (Rank)(0b001111 & bits);
  }

  Suit get_suit() const {
    return (Suit)((0b110000 & bits) >> 4);
  }

  friend bool operator==(BitCard a, BitCard b) const {
    return a.bits == b.bits;
  }

  friend bool operator!=(BitCard a, BitCard b) const {
    return a.bits != b.bits;
  }

  friend bool operator<(BitCard a, BitCard b) {
    return a.bits < b.bits;
  }

  friend bool operator<=(BitCard a, BitCard b) {
    return a.bits <= b.bits;
  }

  friend bool operator>=(BitCard a, BitCard b) {
    return a.bits >= b.bits;
  }

private:
  unsigned char bits;
};
