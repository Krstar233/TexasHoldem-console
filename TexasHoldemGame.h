#pragma once

#include <vector>

#include <queue>

#include "Banker.h"

#include "Player.h"

#include "Desk.h"

#include "PokerHeap.h"





using namespace std;



/*

	�����˿���Ϸ�ࣺ

		ӵ��ׯ�ҡ���ҡ��ƾֵ���Ϣ

*/

class TexasHoldemGame

{

private:

	Banker banker;  //ׯ��

	vector<Player> players;//���

	Desk desk; //�ƾ�

	PokerHeap pokerHeap; //�˿��ƶ�
	
	int personnum;
	
	int outnum;



	void round(queue<Player*> &playersNeedtoBet,bool isRoundOne);



	//��һ����ע

	void firstRound();



	//��������ע

	void otherRound();



	//�����ƾ��ж�

	void judgeWin();



public:

	TexasHoldemGame(/* args */);



	//��ʼ��������Ϣ����ʼ�µ���Ϸ

	void start(int personNum,int AINum);



	//��Ŀǰ�������Ϣ�£�����һ����Ϸ

	void continueGame();



	//������Ϸ

	void endGame();



	~TexasHoldemGame();



	void GameTest(int playernum);

};
