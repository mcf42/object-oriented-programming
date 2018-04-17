/*
this is a rational number class. its only allows the creation of valid
rational numbers. it supports equality operators, ordering operators, basic
arithmetic operators and istream/ostream operations.

Michael Fiander
*/

class Rational {
private:
	int num; // the numerator
	int den; // the denominator

public:
	int getNum() { return num; }
	int getDen() { return den; }
	void setNum(int a) { num = a; }
	void setDen(int a) { 
		if (a == 0)
			{
				den = 1;
			}
		else
			{
			den = a;
			}
	}

	Rational() {
		num = 0;
		den = 1;
	}

	Rational(int a, int b) {
		if(b == 0)
		{
			den = 1;
		}
		else
		{
			num = a;
			den = b;
		}
	}

	bool operator==(const Rational& b) {
		if (num == b->num && den == b->den)
			return true;
		else
			return false;
	}

	bool operator!=(const Rational& b) {
		if (!this == b)
			return true;
		else
			return false;
	}

	bool operator<(const Rational& b) {
		if (den < b->den)
			if (num < b.num)
				return true;
		else
			return false;
	}

	bool operator<=(const Rational& b) {
		if (den <= b->den)
			if (num <= b.num)
				return true;
		else
			return false;
	}

	bool operator>(const Rational& b) {
		if (den > b->den)
			if (num > b.num)
				return true;
		else
			return false;
	}

	bool operator>=(const Rational& b) {
		if (den >= b->den)
			if (num >= b.num)
				return true;
		else
			return false;
	}

	Rational operator+(const Rational& b) {
		Rational rat;
		rat.num = (this->num * b->den) + (b->num * this->den);
		rat.den = (this->den * b->den);
	}

	Rational operator-(const Rational& b) {
		Rational rat;
		rat.num = (this->num * b->den) - (b->num * this->den);
		rat.den = (this->den * b->den);
	}

	Rational operator*(const Rational& b) {
		Rational rat;
		rat.num = this->num * b->num;
		rat.den = this->den * b->den;
	}

	Rational operator/(const Rational& b) {
		Rational rat;
		rat.num = this->num * b->den;
		rat.den = this->den * b->num;
	}

	std::istream& operator>>(istream& is, Rational& a)
	{
		std::string trash;
		is >> a.num;
		is >> trash;
		is >> a.den;
	}

	std::istream& operator<<(istream& is, Rational& a)
	{
		is << a.num;
		is << '/';
		is << a.den;
	}
}