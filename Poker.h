#pragma once

#include <string>

#include <iostream>

using namespace std;

class Poker

{

	string flower;

	int size;

public:

	void show();

	Poker();

	Poker(string flower,int size);

	Poker(string flower, string size);

	int getFlowerSize() const;

	int getPointSize() const;

	string getFlower() const;

	bool operator < (const Poker &poker);

	bool operator == (const Poker &poker);

	bool operator > (const Poker &poker);

	bool operator >= (const Poker &poker);

	bool operator <= (const Poker &poker);

	~Poker();

};


