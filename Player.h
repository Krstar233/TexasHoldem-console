#pragma once

#include "Desk.h"

#include "PokerHeap.h"

#include <string>

using namespace std;

/*

	玩家类：

		拥有手牌，能够下注，跟注，加注，让牌，弃牌

*/

/*
	AI类：
		拥有手牌，能够自主下注，跟注，加注，让牌，弃牌
*/


class Player

{

	

	int betHasPut; //在一轮下注中，已经下的注的数目

	int money; //玩家拥有的注的数目

	bool out;

	PokerHeap handCard; //玩家手牌

	string Name;

	double winPro[11];//各牌型赢牌概率 
	
	bool isAI;//是否AI 
	
	bool hasAdd;

public:

	Player(bool is);

	~Player();

	//计算各牌型赢牌概率
	void countWinPro(); 
	//第一轮判断
	int betRoundOne(Desk & desk);
	//其他轮判断
	int betRoundOther(Desk & desk); 
	//获取玩家身份
	bool getisAI(); 
	int getbetHasPut();

	//下注

	void bet(Desk &desk, int num);



	//跟注

	void followBet(Desk &desk, int bet);



	//加注

	void addBet(Desk &desk, int bet, int num);



	//设置玩家名字

	void setName(string name);



	//获取玩家名字

	string getName();



	void setMoney(int money);



	//获取自己剩余的注(钱)

	int getMoney();



	//重置out

	void initOut();



	//弃牌(退出当局游戏)

	void outGame();



	//返回是否以及弃牌

	bool isOut();



	//重置betHasPut

	void initBetHasPut();



	//将手中的牌排序

	void handCardSort();



	//将手牌展示（输出到控制台）

	void handCardShow();



	//返回手牌

	PokerHeap getHandCard();



	//返回手牌的引用

	PokerHeap& getCard();
 
 

	//清空手牌

	void clearHandCard();

};


