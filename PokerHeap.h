#pragma once

#include <vector>

#include "Poker.h"

using namespace std;

/*

	�˿��ƶ��ࣺ

		����������˿���

*/

class PokerHeap

{

	vector<Poker> heap;

public:

	PokerHeap();

	PokerHeap(vector<Poker> a);

	~PokerHeap();



	//��ʽ��������

	void sort();



	//��������Ϊһ�����˿���

	void init();



	//����˳��ϴ�ƣ�

	void upset();



	//չʾ�ƶ�

	void show();



	//�����ƶ�����

	int getSize();



	//�����˿��ƶ�

	vector<Poker>& getHeap();

	

	void sortByNum();

	

	//�������

	void clear();

};
