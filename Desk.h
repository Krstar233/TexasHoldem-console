#pragma once

#include "PokerHeap.h"

/*

	�ƾ֣����棩�ࣺ

		ӵ�й����ƣ����ص���Ϣ��ׯ���ܹ�������ַ�������

*/

class Desk

{

	
	int betMount;//������Ͷע 

	int jackPot;//���� 

public:	
	PokerHeap publicPoker; //������
	Desk();

	~Desk();

	void init(); //��ʼ��

	void publicPokerSort(); //����������

	void publicPokerShow(); //���������
	
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
