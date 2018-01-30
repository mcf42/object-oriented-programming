#pragma once

//card class for war
//Michael Fiander

enum Rank
{
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

enum Suit
{
	Hearts,
	Diamonds,
	Clubs,
	Spades,
};

class Card
{
	Card(Rank r, Suit s) : rank(r), suit(s) {}

	private:
		Rank rank;
		Suit suit;
};
