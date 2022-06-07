#include "PokerHeap.h"

#include <cstdlib>

#include <ctime>

#include <list>



PokerHeap::PokerHeap()

{

}



PokerHeap::PokerHeap(vector<Poker> a)

{

	this->heap=a;

}



PokerHeap::~PokerHeap()

{



}



void PokerHeap::sort()

{

	vector<list<Poker> > ranklist(4);

	for (vector<Poker>::iterator it = heap.begin(); it != heap.end(); it++) {

		ranklist.at(it->getFlowerSize()).push_back(*it);

	}

	vector<list<Poker> > suitlist(13);

	for (vector<list<Poker> >::iterator it = ranklist.begin(); it != ranklist.end(); it++) {

		for (list<Poker>::iterator it2 = it->begin(); it2 != it->end(); it2++) {

			suitlist.at(it2->getPointSize() - 2).push_back(*it2);

		}

	}

	heap.clear();

	for (vector<list<Poker> >::iterator it = suitlist.begin(); it != suitlist.end(); it++) {

		for (list<Poker>::iterator it2 = it->begin(); it2 != it->end(); it2++) {

			heap.push_back(*it2);

		}

	}

}



void PokerHeap::init()

{

	heap.clear();

	string flowers[] = { "ºÚÌÒ", "ºìÌÒ", "Ã·»¨", "·½¿é" };

	for (int i = 2; i < 15; i++) {

		for (int j = 0; j < 4; j++) {

			heap.push_back(Poker(flowers[j], i));

		}

	}

}



void PokerHeap::upset()

{

	vector<Poker> n_heap;

	srand(time(0));

	while (!heap.empty()) {

		int i = rand() % heap.size();

		n_heap.push_back(heap[i]);

		heap.erase(heap.begin() + i);

	}

	heap = n_heap;

}



void PokerHeap::show()

{

	for (vector<Poker>::iterator it = heap.begin(); it != heap.end(); it++) {

		it->show();

		cout << " ";

	}cout << endl;

}



int PokerHeap::getSize()

{

	return heap.size();

}



vector<Poker>& PokerHeap::getHeap()

{

	return this->heap;

}



void PokerHeap::sortByNum()

{

	int len = heap.size();

	int i, j;

	for (i = 0; i < len- 1; i++)

	{

		for (j = 0; j < len- 1 - i; j++)

		{

			if (heap[j].getPointSize() < heap[j + 1].getPointSize())

			{

				Poker temp;

				temp = heap[j];

				heap[j] = heap[j + 1];

				heap[j + 1] = temp;

			}

		}

	}

}



void PokerHeap::clear()

{

	heap.clear();

}
