#pragma once

#include <vector>

#include "Poker.h"

using namespace std;

/*

	扑克牌堆类：

		存放若干张扑克牌

*/

class PokerHeap

{

	vector<Poker> heap;

public:

	PokerHeap();

	PokerHeap(vector<Poker> a);

	~PokerHeap();



	//链式基数排序

	void sort();



	//将数据置为一副新扑克牌

	void init();



	//打乱顺序（洗牌）

	void upset();



	//展示牌堆

	void show();



	//返回牌堆张数

	int getSize();



	//返回扑克牌堆

	vector<Poker>& getHeap();

	

	void sortByNum();

	

	//清空牌组

	void clear();

};
