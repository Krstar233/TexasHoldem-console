#pragma once

#include <vector>

#include "Player.h"

#include "PokerHeap.h"

#include "Desk.h"

#include <string>

/*

	庄家类：

		持有扑克牌堆，负责给玩家发牌以及发公共牌, 

		并且能对最后的结局判断输赢，给玩家分发奖池。

*/



class Banker

{

private:

	int winnernum;

	int playernum;

	string* players_cards_type;//玩家手牌的种类

	PokerHeap* finalcards;//公共牌加上手牌

	vector<Poker>* subset;//筛选出来的五张牌

	vector<int> winners_index;//记录赢家的下标

public:

	string* Rank;

	Banker();

	~Banker();



	//给每名玩家发两张牌

	void licensing(std::vector<Player> &players, PokerHeap &pokerHeap);



	//发若干张公共牌到桌上

	void licensingPublicCard(Desk &desk, PokerHeap &pokerHeap, int num);



	//根据玩家的手牌，结合桌面上的公共牌，判断输赢，并给玩家分发奖池

	void distributeReward(std::vector<Player>& players, Desk &desk);



	//辨别每个玩家手牌的种类

	void identifyCardType(std::vector<Player>& players);



	int isRoyalFlush(PokerHeap playercard,int index);



	int isFlush(PokerHeap playercard, int index);

	

	int isFourArticle(PokerHeap playercard, int index);



	int isFullHallOfFame(PokerHeap playercard, int index);



	int isSameSuit(PokerHeap playercard, int index);



	int isStraightDraw(PokerHeap playercard, int index);



	int isThreeArticle(PokerHeap playercard, int index);



	int isTwoPairs(PokerHeap playercard, int index);



	int isAPair(PokerHeap playercard, int index);



	int isSingleCard(PokerHeap playercard, int index);



	void findAWinnerIndex(std::vector<Player>& players);



	void findOtherWinnersIndex(std::vector<Player>& players);



	void comparisionBetweenWinners();



	void comparisionOfRoyalFlush();



	void comparisionOfFlush();



	void comparisionOfFourArticle();



	void comparisionOfFullHallOfFame();



	void comparisionOfSameSuit();



	void comparisionOfStraightDraw();



	void comparisionOfThreeArticle();

	

	void comparisionOfTwoPairs();



	void comparisionOfAPair();



	void comparisionOfSingleCard();

};
