#include <iostream>

#include <string>



#include "TexasHoldemGame.h"

#include "PokerHeap.h"

using namespace std;



void printStartVeiw();

void game();

void pokerheapTest();

void gameTest();
 

int main() {



	game();



//	gameTest();



	//pokerheapTest();

}





void printStartVeiw() {

	cout << "*****��ӭ���������˿�******" << endl;

	cout << "      �Ƿ�ʼ��Ϸ��" << endl;

	cout << "          (Y/N)" << endl;

	cout << "**************************" << endl;

}

void game() {

	TexasHoldemGame game; //�����˿���Ϸ����

	string cmd; //����ĶԵ����˿���Ϸ����������

	int n; //������ҵ�����
	int m;//AI���� 


	printStartVeiw();

	cin >> cmd;



	if (cmd == "Y" || cmd == "y") {

		cout << "����������ܸ���(3~20��)��";

		while (cin >> n && (n < 3 || n > 20)) cout << "���������룺";
		
		cout<<"������AI������";
		cin>>m; 

		game.start(n,m);

	}

	while (cmd == "Y" || cmd == "y") {

		cout << "������Ϸ��(Y/N):" << endl;

		cin >> cmd;

		if (cmd == "Y" || cmd == "y") {

			cout << endl;
			game.continueGame();

		}

		else

			break;

	}

	cout << "��Ϸ������" << endl;

	game.endGame();

}



void pokerheapTest()

{

	PokerHeap pok;

	pok.init();

	pok.show();

	cout << "�ϼƣ�" << pok.getSize() << "��" << endl;

	cout << "======================================" << endl;

	pok.upset();

	pok.show();

	cout << "�ϼƣ�" << pok.getSize() << "��" << endl;

	cout << "======================================" << endl;

	pok.sort();

	pok.show();

	cout << "�ϼƣ�" << pok.getSize() << "��" << endl;



	Poker poker1("����", "J");

	Poker poker2("����", "Q");

	if (poker1 < poker2) {

		poker1.show(); cout << " < "; poker2.show(); cout << endl;

	}

}



void gameTest()

{

	TexasHoldemGame game;

	game.GameTest(3);

}
