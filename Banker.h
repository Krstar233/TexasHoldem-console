#pragma once

#include <vector>

#include "Player.h"

#include "PokerHeap.h"

#include "Desk.h"

#include <string>

/*

	ׯ���ࣺ

		�����˿��ƶѣ��������ҷ����Լ���������, 

		�����ܶ����Ľ���ж���Ӯ������ҷַ����ء�

*/



class Banker

{

private:

	int winnernum;

	int playernum;

	string* players_cards_type;//������Ƶ�����

	PokerHeap* finalcards;//�����Ƽ�������

	vector<Poker>* subset;//ɸѡ������������

	vector<int> winners_index;//��¼Ӯ�ҵ��±�

public:

	string* Rank;

	Banker();

	~Banker();



	//��ÿ����ҷ�������

	void licensing(std::vector<Player> &players, PokerHeap &pokerHeap);



	//�������Ź����Ƶ�����

	void licensingPublicCard(Desk &desk, PokerHeap &pokerHeap, int num);



	//������ҵ����ƣ���������ϵĹ����ƣ��ж���Ӯ��������ҷַ�����

	void distributeReward(std::vector<Player>& players, Desk &desk);



	//���ÿ��������Ƶ�����

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
