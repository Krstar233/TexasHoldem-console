#pragma once

#include <vector>

#include <queue>

#include "Banker.h"

#include "Player.h"

#include "Desk.h"

#include "PokerHeap.h"





using namespace std;



/*

	德州扑克游戏类：

		拥有庄家、玩家、牌局等信息

*/

class TexasHoldemGame

{

private:

	Banker banker;  //庄家

	vector<Player> players;//玩家

	Desk desk; //牌局

	PokerHeap pokerHeap; //扑克牌堆
	
	int personnum;
	
	int outnum;



	void round(queue<Player*> &playersNeedtoBet,bool isRoundOne);



	//第一轮下注

	void firstRound();



	//其他轮下注

	void otherRound();



	//最终牌局判断

	void judgeWin();



public:

	TexasHoldemGame(/* args */);



	//初始化所有信息，开始新的游戏

	void start(int personNum,int AINum);



	//在目前的玩家信息下，继续一轮游戏

	void continueGame();



	//结束游戏

	void endGame();



	~TexasHoldemGame();



	void GameTest(int playernum);

};
