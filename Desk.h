#pragma once

#include "PokerHeap.h"

/*

	牌局（桌面）类：

		拥有公共牌，奖池等信息，庄家能够往上面分发公共牌

*/

class Desk

{

	
	int betMount;//本轮需投注 

	int jackPot;//奖池 

public:	
	PokerHeap publicPoker; //公共牌
	Desk();

	~Desk();

	void init(); //初始化

	void publicPokerSort(); //公共牌排序

	void publicPokerShow(); //公共牌输出
	
	PokerHeap getpublicPoker();
	
	void setbetMount(int num);
	
	void initjackPot();

	int getSize();

	int getJackPot(); 
	
	int getbetMount();

	void addJackPot(int num);


	PokerHeap& getCard();

	void clearPublicPoker();

};
