#include "Desk.h"





Desk::Desk()

{

	betMount = jackPot = 0;

}





Desk::~Desk()

{

}



void Desk::init()

{
	betMount=0;

}

void Desk::initjackPot(){
	jackPot=0;
}

void Desk::publicPokerSort()

{

	publicPoker.sort();

}



void Desk::publicPokerShow()

{

	publicPoker.show();

}



int Desk::getSize(){

	return publicPoker.getSize();

}


int Desk::getbetMount(){
	return betMount;
}


int Desk::getJackPot(){

	return jackPot;

}



void Desk::addJackPot(int num) {

	this->jackPot += num;

}

void Desk::setbetMount(int num){
	betMount=num;
}


PokerHeap Desk::getpublicPoker()

{

	return publicPoker;

}



PokerHeap& Desk::getCard()

{

	return publicPoker;

}



void Desk::clearPublicPoker()

{

	publicPoker.clear();

}
