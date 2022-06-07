#pragma once

#include "Desk.h"

#include "PokerHeap.h"

#include <string>

using namespace std;

/*

	����ࣺ

		ӵ�����ƣ��ܹ���ע����ע����ע�����ƣ�����

*/

/*
	AI�ࣺ
		ӵ�����ƣ��ܹ�������ע����ע����ע�����ƣ�����
*/


class Player

{

	

	int betHasPut; //��һ����ע�У��Ѿ��µ�ע����Ŀ

	int money; //���ӵ�е�ע����Ŀ

	bool out;

	PokerHeap handCard; //�������

	string Name;

	double winPro[11];//������Ӯ�Ƹ��� 
	
	bool isAI;//�Ƿ�AI 
	
	bool hasAdd;

public:

	Player(bool is);

	~Player();

	//���������Ӯ�Ƹ���
	void countWinPro(); 
	//��һ���ж�
	int betRoundOne(Desk & desk);
	//�������ж�
	int betRoundOther(Desk & desk); 
	//��ȡ������
	bool getisAI(); 
	int getbetHasPut();

	//��ע

	void bet(Desk &desk, int num);



	//��ע

	void followBet(Desk &desk, int bet);



	//��ע

	void addBet(Desk &desk, int bet, int num);



	//�����������

	void setName(string name);



	//��ȡ�������

	string getName();



	void setMoney(int money);



	//��ȡ�Լ�ʣ���ע(Ǯ)

	int getMoney();



	//����out

	void initOut();



	//����(�˳�������Ϸ)

	void outGame();



	//�����Ƿ��Լ�����

	bool isOut();



	//����betHasPut

	void initBetHasPut();



	//�����е�������

	void handCardSort();



	//������չʾ�����������̨��

	void handCardShow();



	//��������

	PokerHeap getHandCard();



	//�������Ƶ�����

	PokerHeap& getCard();
 
 

	//�������

	void clearHandCard();

};


