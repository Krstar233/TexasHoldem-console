#include "Poker.h"





void Poker::show()

{

	cout << flower;

	string sizes[] = { "0","A","2","3","4","5","6","7","8","9","10","J","Q","K","A" };

	cout << sizes[size];

}



Poker::Poker()

{

}



Poker::Poker(string flower, int size)

{

	this->flower = flower;

	this->size = size;

}



Poker::Poker(string flower, string size)

{

	string sizes[] = {"0","A","2","3","4","5","6","7","8","9","10","J","Q","K","A"};

	this->flower = flower;

	for (int i = 0; i < 15; i++) {

		if (size == sizes[i]) {

			this->size = i;

			return;

		}

	}

	this->size = 0;

}



int Poker::getFlowerSize() const

{

	string flowers[] ={ "ºÚÌÒ", "ºìÌÒ", "Ã·»¨", "·½¿é" };

	for(int i = 0; i < 4; i++) {

		if (this->flower == flowers[i])

			return 3 - i;

	}

	return -1;

}



int Poker::getPointSize() const

{

	return this->size;

}



string Poker::getFlower() const

{

	return this->flower; 

} 



bool Poker::operator<(const Poker & poker)

{

	if (this->size < poker.size)

		return true;

	if (this->size == poker.size) {

		if (this->getFlowerSize() < poker.getFlowerSize())

			return true;

	}

	return false;

}



bool Poker::operator==(const Poker & poker)

{

	return this->size == poker.size && this->getFlowerSize() == poker.getFlowerSize();

}



bool Poker::operator>(const Poker & poker)

{

	return !(*this < poker || *this == poker);

}



bool Poker::operator>=(const Poker & poker)

{

	return !(*this < poker);

}



bool Poker::operator<=(const Poker & poker)

{

	return !(*this > poker);

}



Poker::~Poker()

{



}
