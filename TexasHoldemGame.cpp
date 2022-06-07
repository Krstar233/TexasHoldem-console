#include "TexasHoldemGame.h"

#include <iostream>

#include<sstream>

#include<string>

using namespace std;



void TexasHoldemGame::round(queue<Player*> &playersNeedtoBet,bool isRoundOne)

{

	int lastBetNum = 0;

	queue<Player*> playerBeted;

	while (!playersNeedtoBet.empty()) {
		
		if (outnum + 1 >= personnum) {
			cout << "��Ϸֻʣһ�ˣ�����������ע" << endl;
			return;
		}

		int cmd;

		Player *player = playersNeedtoBet.front(); playersNeedtoBet.pop();

		cout << "�ֵ���ң�" << player->getName() << endl;



		if(player->getisAI()==false){
			cout << "----------------------" << endl;
			if (desk.getpublicPoker().getSize() != 0) {
				cout << "�����ƣ�";
				desk.getpublicPoker().show();
			}
			cout << "������ƣ�";
			player->handCardShow();
			cout << "ʣ����:$" << player->getMoney() << endl;
			cout << "----------------------" << endl;
		//����֮ǰû����עʱ
		if (desk.getbetMount() == 0) {

			cout << "�����ѡ�� 1.��ע 2.���� 3.���� (���������)��";

			while (cin >> cmd) {

				if (cmd == 1) {

					cout << "��������עֵ: ";

					int bet;

					while (cin >> bet && (bet <= 1 || bet > player->getMoney()))	cout << "��������ȷ��ֵ��";

					player->bet(desk, bet);

					lastBetNum = bet;

					cout << "����ע $" << bet << ", ʣ���ң�$" << player->getMoney() << endl;

					playerBeted.push(player);

					break;

				}

				else if (cmd == 2) {

					playersNeedtoBet.push(player);

					cout << "�����ơ�" << endl;

					break;

				}

				else if (cmd == 3) {

					player->outGame();

					cout << "�����ơ�" << endl;
					
					outnum++;

					break;

				}

				cout << "��������ȷ����ţ�";

			}

			continue;

		}



		//����������ע��

		cout << "�����ѡ�� 1.��ע 2.��ע 3.���� (���������)��";

		while (cin >> cmd) {

			if (cmd == 1) {

				player->followBet(desk, lastBetNum);

				cout << "�Ѹ�ע" << ", ʣ���ң�$" << player->getMoney() << endl;

				playerBeted.push(player);

				break;

			}

			else if (cmd == 2) {

				int num;

				cout << "�������ע���";

				cin >> num;

				player->addBet(desk, lastBetNum, num);

				lastBetNum += num;

				cout << "�Ѽ�ע�� $"<< desk.getbetMount()<<"��ʣ���ң�$" << player->getMoney() << endl;

				while (!playerBeted.empty()) {
					if(playerBeted.front()!=player)
						playersNeedtoBet.push(playerBeted.front());

			//		playersNeedtoBet.push(playerBeted.front());

					playerBeted.pop();

				}
				playerBeted.push(player);


				break;

			}

			else if (cmd == 3) {

				player->outGame();

				cout << "�����ơ�" << endl;
				
				outnum++;

				break;

			}

			cout << "��������ȷ����ţ�";

		}
		
		}
		else{//��AI 
		//����֮ǰû����עʱ
		if (desk.getbetMount()== 0) {

	//		cout << "�����ѡ�� 1.��ע  3.���� (���������)��";

			while (isRoundOne==true?cmd=player->betRoundOne(desk):cmd=player->betRoundOther(desk)) {

				if (cmd == 1) {

				//	cout << "��������עֵ: ";

					int bet=player->getbetHasPut();

				//	while (cin >> bet && (bet <= 0 || bet > player->getMoney()))	cout << "��������ȷ��ֵ" << endl;

				//	player->bet(desk, bet);

					lastBetNum = bet;

					cout << "����ע $" << bet << ", ʣ���ң�$" << player->getMoney() << endl;

					playerBeted.push(player);

					break;

				}

		/*		else if (cmd == 2) {

					playersNeedtoBet.push(player);

					cout << "�����ơ�" << endl;

					break;

				}*/

				else if (cmd == 3) {

					player->outGame();

					cout << "�����ơ�" << endl;

					break;

				}

				cout << "��������ȷ����ţ�";

			}

			continue;

		}



		//����������ע��

	//	cout << "�����ѡ�� 1.��ע 2.��ע 3.���� (���������)��";

		while (isRoundOne==true?cmd=player->betRoundOne(desk):cmd=player->betRoundOther(desk)) {

			if (cmd == 1) {

			//	player->followBet(desk, lastBetNum);

				cout << "�Ѹ�ע" << ", ʣ���ң�$" << player->getMoney() << endl;

				playerBeted.push(player);

				break;

			}

			else if (cmd == 2) {

				int num;

		//		cout << "�������ע���";

		//		cin >> num;

		//		player->addBet(desk, lastBetNum, num);
		

				lastBetNum = player->getbetHasPut();

				cout << "�Ѽ�ע�� $"<<desk.getbetMount()<<"��ʣ���ң�$" << player->getMoney() << endl;

				while (!playerBeted.empty()) {
					if(playerBeted.front()!=player)
						playersNeedtoBet.push(playerBeted.front());
						

					playerBeted.pop();

				}
				
				playerBeted.push(player);

				break;

			}

			else if (cmd == 3) {

				player->outGame();

				cout << "�����ơ�" << endl;
				
				outnum++;

				break;

			}

			cout << "��������ȷ����ţ�";

		}
			
		}
	}

}



void TexasHoldemGame::firstRound()

{

	queue<Player*> q;

	for (int i = 0; i < players.size(); i++) {

		int k = (i + 2) % players.size();

		players[k].initBetHasPut();

		q.push(&players[k]);

	}

	round(q,true);

}



void TexasHoldemGame::otherRound()

{

	queue<Player*> q;

	for (int i = 0; i < players.size(); i++) {

		if (!players[i].isOut()) {

			players[i].initBetHasPut();

			q.push(&players[i]);

		}

	}

	round(q,false);

}



void TexasHoldemGame::judgeWin()

{

	banker.distributeReward(players, desk);

}



TexasHoldemGame::TexasHoldemGame()

{

}



void TexasHoldemGame::start(int personNum,int AINum)

{

	/*

	args:

	personNum,���������
	AINum,AI���� 

	*/

	//��ʼ����Ϸ��Ϣ:

	//banker = Banker();
	int i=0; 
	outnum=0;
	if(personNum>AINum)
		cout << "��������������ǳ�:" << endl;

	for (i = 0; i < personNum-AINum; i++) {

		Player player(false);

		string name;

		cout << "���" << i + 1 << "��";

		cin >> name;

		player.setName(name);

		player.setMoney(10000);

		players.push_back(player);

	}
	
	if(AINum!=0){
	cout << "������AI����ǳ�:" << endl;

	for (; i < personNum; i++) {

		Player player(true);

		string name;

		cout << "���" << i + 1 << "��";

		cin >> name;

		player.setName(name);

		player.setMoney(10000);

		players.push_back(player);

	}
	}
	desk = Desk();
	personnum=personNum;

	continueGame();

}

void TexasHoldemGame::continueGame()

{
	int count,f;
	cout << endl << "-----------------------------------------------------------------"  << endl;
	cout << "��Ϸ��ʼ" << endl;

	desk.initjackPot();

	//�����������
	outnum=0;
	for (int i = 0; i < players.size(); i++)

	{

		players[i].initOut();

		players[i].clearHandCard();

	}



	//��������(�ƾ�)

	desk.init();

	desk.clearPublicPoker();



	//�����ƶ�

	pokerHeap.init();



	//ǿ���´�Сäע

	players[0].bet(desk, 1);

	cout << "��ң�" << players[0].getName() << "����Сäע $1" << endl;

	players[1].bet(desk, 2);

	cout << "��ң�" << players[1].getName() << "���˴�äע $2" << endl;



	//ׯ�Ҹ�ÿ����ҷ���

	banker.licensing(players, pokerHeap);

	cout << "�������." << endl;



	//��ÿ����ҵ���������

	for (int i = 0; i < players.size(); i++) {

		players[i].handCardSort();

	}

	desk.init();


	cout << endl;

	//��һ����ע

	cout << "��һ����ע��" << endl;

	firstRound();
	
	
	count=0;
	for(int i=0;i<personnum;i++){
		if(players[i].isOut()==false){
			count++;f=i;} 
	}
	if(count==1){
		int newmoney=desk.getJackPot();
		newmoney+=players[f].getMoney();
		players[f].setMoney(newmoney);
		cout << "��ֻ��ʤ�������Ϊ�� " << endl;
		cout << "���" << f+1 << "�ţ�" << "����Ϊ��" << players[f].getName()<<endl;
		cout << "���" << f+1 << "�ţ�" << "����Ϊ��" ;players[f].handCardShow();
		goto end;
	}
	


	cout << endl;
	//ׯ�ҷ�3�Ź�����

	cout << "ׯ�ҷ���3�Ź�����" << endl;

	banker.licensingPublicCard(desk, pokerHeap, 3);



	//�����ƶ�����

	desk.publicPokerSort();

	desk.publicPokerShow();


	desk.init();
	//�ڶ�����ע
	cout << endl;
	cout << "�ڶ�����ע��" << endl;

	otherRound();

	count=0;
	for(int i=0;i<personnum;i++){
		if(players[i].isOut()==false){
			count++;f=i;} 
	}
	if(count==1){
		int newmoney=desk.getJackPot();
		newmoney+=players[f].getMoney();
		players[f].setMoney(newmoney);
		cout << "��ֻ��ʤ�������Ϊ�� " << endl;
		cout << "���" << f+1 << "�ţ�" << "����Ϊ��" << players[f].getName()<<endl;
		cout << "���" << f+1 << "�ţ�" << "����Ϊ��" ;players[f].handCardShow();
		goto end;
	}


	//ׯ�ҷ�1�Ź�����
	cout << endl;
	cout << "ׯ�ҷ���1�Ź����ƣ�" << endl;

	banker.licensingPublicCard(desk, pokerHeap, 1);



	//�����ƶ�����

	desk.publicPokerSort();

	desk.publicPokerShow();


	desk.init();
	//��������ע
	cout << endl;
	cout << "��������ע��" << endl;

	otherRound();
	
	count=0;
	for(int i=0;i<personnum;i++){
		if(players[i].isOut()==false){
			count++;f=i;} 
	}
	if(count==1){
		int newmoney=desk.getJackPot();
		newmoney+=players[f].getMoney();
		players[f].setMoney(newmoney);
		cout << "��ֻ��ʤ�������Ϊ�� " << endl;
		cout << "���" << f+1 << "�ţ�" << "����Ϊ��" << players[f].getName()<<endl;
		cout << "���" << f+1 << "�ţ�" << "����Ϊ��" ;players[f].handCardShow();
		goto end;
	}



	//ׯ�ҷ����һ�Ź�����
	cout << endl;
	cout << "ׯ�ҷ������һ�Ź����ƣ�" << endl;

	banker.licensingPublicCard(desk, pokerHeap, 1);



	//�����ƶ�����

	desk.publicPokerSort();

	desk.publicPokerShow();


	desk.init();
	//���һ����ע
	cout << endl;
	cout << "���һ����ע:" << endl;

	otherRound();



	//���ձ����ж���Ӯ����һ�ý���
	cout << endl;
	judgeWin();

	
end:
	// ��Ϸֻʣһ�˵��������
	if (outnum == personnum - 1) {
		for (int i = 0; i < personnum; i++) {
			if (!players[i].isOut()) {
				players[i].setMoney(players[i].getMoney() + desk.getJackPot());
				break;
			}
		}
	}
	cout << "������Ϸ����" << endl;

}



void TexasHoldemGame::GameTest(int playerNum)

{

	for (int i = 0; i < playerNum; i++) {
	//	if(i==0)
			Player player(false);
	//	else
	//		Player player(true);
		string res;
		stringstream ss;
		int r;
		r=i+1;
		ss<<r;
		ss>>res;

		string name = "���" + res;

		player.setName(name);

		player.setMoney(10000);

		players.push_back(player);

	}

	desk = Desk();

	while (true) {

		cout << "��Ϸ��ʼ" << endl;



		//�����������

		for (int i = 0; i < players.size(); i++) {

			players[i].clearHandCard();

			players[i].initOut();

		}

		//��������(�ƾ�)

		desk.init();

		desk.clearPublicPoker();



		//�����ƶ�

		pokerHeap.init();



		//ׯ�Ҹ�ÿ����ҷ���

		banker.licensing(players, pokerHeap);

		cout << "�������." << endl;



		//��ÿ����ҵ���������

		for (int i = 0; i < players.size(); i++) {

			players[i].handCardSort();

		}



		//ׯ�ҷ�3�Ź�����

		cout << "ׯ�ҷ���3�Ź�����" << endl;

		banker.licensingPublicCard(desk, pokerHeap, 3);



		//�����ƶ�����

		desk.publicPokerSort();

		desk.publicPokerShow();



		//ׯ�ҷ�1�Ź�����

		cout << "ׯ�ҷ���1�Ź����ƣ�" << endl;

		banker.licensingPublicCard(desk, pokerHeap, 1);



		//�����ƶ�����

		desk.publicPokerSort();

		desk.publicPokerShow();



		//ׯ�ҷ����һ�Ź�����

		cout << "ׯ�ҷ������һ�Ź����ƣ�" << endl;

		banker.licensingPublicCard(desk, pokerHeap, 1);



		//�����ƶ�����

		desk.publicPokerSort();

		desk.publicPokerShow();



		//���ձ����ж���Ӯ����һ�ý���

		judgeWin();



		cout << "������Ϸ����...���������������.." << endl;

		getchar();

		for (int i = 0; i < 25; i++)

			cout << "-";

		cout << endl;

	}

}



void TexasHoldemGame::endGame()

{

}



TexasHoldemGame::~TexasHoldemGame()

{

}
