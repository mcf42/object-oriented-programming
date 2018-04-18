
#include <iostream>
#include <iomanip>
#include <map>
#include <vector>

class value {
	virtual void print();
};

class true : value {
	void print() override {}
};

class false : value {
	void print() override {}
};

class null : value {
	void print() override {}
};

class string : value {
	void print() override {}
};

class array : value {
	void print() override {}
};

class object : value {
	void print() override {}
};