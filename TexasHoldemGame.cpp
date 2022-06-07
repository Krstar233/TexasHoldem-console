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
			cout << "游戏只剩一人，跳过本轮下注" << endl;
			return;
		}

		int cmd;

		Player *player = playersNeedtoBet.front(); playersNeedtoBet.pop();

		cout << "轮到玩家：" << player->getName() << endl;



		if(player->getisAI()==false){
			cout << "----------------------" << endl;
			if (desk.getpublicPoker().getSize() != 0) {
				cout << "公共牌：";
				desk.getpublicPoker().show();
			}
			cout << "你的手牌：";
			player->handCardShow();
			cout << "剩余金币:$" << player->getMoney() << endl;
			cout << "----------------------" << endl;
		//本轮之前没人下注时
		if (desk.getbetMount() == 0) {

			cout << "你可以选择 1.下注 2.让牌 3.弃牌 (请输入序号)：";

			while (cin >> cmd) {

				if (cmd == 1) {

					cout << "请输入下注值: ";

					int bet;

					while (cin >> bet && (bet <= 1 || bet > player->getMoney()))	cout << "请输入正确的值：";

					player->bet(desk, bet);

					lastBetNum = bet;

					cout << "已下注 $" << bet << ", 剩余金币：$" << player->getMoney() << endl;

					playerBeted.push(player);

					break;

				}

				else if (cmd == 2) {

					playersNeedtoBet.push(player);

					cout << "已让牌。" << endl;

					break;

				}

				else if (cmd == 3) {

					player->outGame();

					cout << "已弃牌。" << endl;
					
					outnum++;

					break;

				}

				cout << "请输入正确的序号：";

			}

			continue;

		}



		//本轮有人下注后

		cout << "你可以选择 1.跟注 2.加注 3.弃牌 (请输入序号)：";

		while (cin >> cmd) {

			if (cmd == 1) {

				player->followBet(desk, lastBetNum);

				cout << "已跟注" << ", 剩余金币：$" << player->getMoney() << endl;

				playerBeted.push(player);

				break;

			}

			else if (cmd == 2) {

				int num;

				cout << "请输入加注数额：";

				cin >> num;

				player->addBet(desk, lastBetNum, num);

				lastBetNum += num;

				cout << "已加注至 $"<< desk.getbetMount()<<"，剩余金币：$" << player->getMoney() << endl;

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

				cout << "已弃牌。" << endl;
				
				outnum++;

				break;

			}

			cout << "请输入正确的序号：";

		}
		
		}
		else{//是AI 
		//本轮之前没人下注时
		if (desk.getbetMount()== 0) {

	//		cout << "你可以选择 1.下注  3.弃牌 (请输入序号)：";

			while (isRoundOne==true?cmd=player->betRoundOne(desk):cmd=player->betRoundOther(desk)) {

				if (cmd == 1) {

				//	cout << "请输入下注值: ";

					int bet=player->getbetHasPut();

				//	while (cin >> bet && (bet <= 0 || bet > player->getMoney()))	cout << "请输入正确的值" << endl;

				//	player->bet(desk, bet);

					lastBetNum = bet;

					cout << "已下注 $" << bet << ", 剩余金币：$" << player->getMoney() << endl;

					playerBeted.push(player);

					break;

				}

		/*		else if (cmd == 2) {

					playersNeedtoBet.push(player);

					cout << "已让牌。" << endl;

					break;

				}*/

				else if (cmd == 3) {

					player->outGame();

					cout << "已弃牌。" << endl;

					break;

				}

				cout << "请输入正确的序号：";

			}

			continue;

		}



		//本轮有人下注后

	//	cout << "你可以选择 1.跟注 2.加注 3.弃牌 (请输入序号)：";

		while (isRoundOne==true?cmd=player->betRoundOne(desk):cmd=player->betRoundOther(desk)) {

			if (cmd == 1) {

			//	player->followBet(desk, lastBetNum);

				cout << "已跟注" << ", 剩余金币：$" << player->getMoney() << endl;

				playerBeted.push(player);

				break;

			}

			else if (cmd == 2) {

				int num;

		//		cout << "请输入加注数额：";

		//		cin >> num;

		//		player->addBet(desk, lastBetNum, num);
		

				lastBetNum = player->getbetHasPut();

				cout << "已加注至 $"<<desk.getbetMount()<<"，剩余金币：$" << player->getMoney() << endl;

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

				cout << "已弃牌。" << endl;
				
				outnum++;

				break;

			}

			cout << "请输入正确的序号：";

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

	personNum,玩家总人数
	AINum,AI人数 

	*/

	//初始化游戏信息:

	//banker = Banker();
	int i=0; 
	outnum=0;
	if(personNum>AINum)
		cout << "请输入人类玩家昵称:" << endl;

	for (i = 0; i < personNum-AINum; i++) {

		Player player(false);

		string name;

		cout << "玩家" << i + 1 << "：";

		cin >> name;

		player.setName(name);

		player.setMoney(10000);

		players.push_back(player);

	}
	
	if(AINum!=0){
	cout << "请输入AI玩家昵称:" << endl;

	for (; i < personNum; i++) {

		Player player(true);

		string name;

		cout << "玩家" << i + 1 << "：";

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
	cout << "游戏开始" << endl;

	desk.initjackPot();

	//重置弃牌玩家
	outnum=0;
	for (int i = 0; i < players.size(); i++)

	{

		players[i].initOut();

		players[i].clearHandCard();

	}



	//重载桌面(牌局)

	desk.init();

	desk.clearPublicPoker();



	//重置牌堆

	pokerHeap.init();



	//强制下大小盲注

	players[0].bet(desk, 1);

	cout << "玩家：" << players[0].getName() << "下了小盲注 $1" << endl;

	players[1].bet(desk, 2);

	cout << "玩家：" << players[1].getName() << "下了大盲注 $2" << endl;



	//庄家给每名玩家发牌

	banker.licensing(players, pokerHeap);

	cout << "发牌完毕." << endl;



	//把每名玩家的手牌排序

	for (int i = 0; i < players.size(); i++) {

		players[i].handCardSort();

	}

	desk.init();


	cout << endl;

	//第一轮下注

	cout << "第一轮下注：" << endl;

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
		cout << "这局获得胜利的玩家为： " << endl;
		cout << "玩家" << f+1 << "号，" << "名字为：" << players[f].getName()<<endl;
		cout << "玩家" << f+1 << "号，" << "手牌为：" ;players[f].handCardShow();
		goto end;
	}
	


	cout << endl;
	//庄家发3张公共牌

	cout << "庄家发了3张公共牌" << endl;

	banker.licensingPublicCard(desk, pokerHeap, 3);



	//公共牌堆排序

	desk.publicPokerSort();

	desk.publicPokerShow();


	desk.init();
	//第二轮下注
	cout << endl;
	cout << "第二轮下注：" << endl;

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
		cout << "这局获得胜利的玩家为： " << endl;
		cout << "玩家" << f+1 << "号，" << "名字为：" << players[f].getName()<<endl;
		cout << "玩家" << f+1 << "号，" << "手牌为：" ;players[f].handCardShow();
		goto end;
	}


	//庄家发1张公共牌
	cout << endl;
	cout << "庄家发了1张公共牌：" << endl;

	banker.licensingPublicCard(desk, pokerHeap, 1);



	//公共牌堆排序

	desk.publicPokerSort();

	desk.publicPokerShow();


	desk.init();
	//第三轮下注
	cout << endl;
	cout << "第三轮下注：" << endl;

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
		cout << "这局获得胜利的玩家为： " << endl;
		cout << "玩家" << f+1 << "号，" << "名字为：" << players[f].getName()<<endl;
		cout << "玩家" << f+1 << "号，" << "手牌为：" ;players[f].handCardShow();
		goto end;
	}



	//庄家发最后一张公共牌
	cout << endl;
	cout << "庄家发了最后一张公共牌：" << endl;

	banker.licensingPublicCard(desk, pokerHeap, 1);



	//公共牌堆排序

	desk.publicPokerSort();

	desk.publicPokerShow();


	desk.init();
	//最后一轮下注
	cout << endl;
	cout << "最后一轮下注:" << endl;

	otherRound();



	//最终比牌判断输赢，玩家获得奖池
	cout << endl;
	judgeWin();

	
end:
	// 游戏只剩一人的特殊情况
	if (outnum == personnum - 1) {
		for (int i = 0; i < personnum; i++) {
			if (!players[i].isOut()) {
				players[i].setMoney(players[i].getMoney() + desk.getJackPot());
				break;
			}
		}
	}
	cout << "本回游戏结束" << endl;

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

		string name = "玩家" + res;

		player.setName(name);

		player.setMoney(10000);

		players.push_back(player);

	}

	desk = Desk();

	while (true) {

		cout << "游戏开始" << endl;



		//重置弃牌玩家

		for (int i = 0; i < players.size(); i++) {

			players[i].clearHandCard();

			players[i].initOut();

		}

		//重载桌面(牌局)

		desk.init();

		desk.clearPublicPoker();



		//重置牌堆

		pokerHeap.init();



		//庄家给每名玩家发牌

		banker.licensing(players, pokerHeap);

		cout << "发牌完毕." << endl;



		//把每名玩家的手牌排序

		for (int i = 0; i < players.size(); i++) {

			players[i].handCardSort();

		}



		//庄家发3张公共牌

		cout << "庄家发了3张公共牌" << endl;

		banker.licensingPublicCard(desk, pokerHeap, 3);



		//公共牌堆排序

		desk.publicPokerSort();

		desk.publicPokerShow();



		//庄家发1张公共牌

		cout << "庄家发了1张公共牌：" << endl;

		banker.licensingPublicCard(desk, pokerHeap, 1);



		//公共牌堆排序

		desk.publicPokerSort();

		desk.publicPokerShow();



		//庄家发最后一张公共牌

		cout << "庄家发了最后一张公共牌：" << endl;

		banker.licensingPublicCard(desk, pokerHeap, 1);



		//公共牌堆排序

		desk.publicPokerSort();

		desk.publicPokerShow();



		//最终比牌判断输赢，玩家获得奖池

		judgeWin();



		cout << "本回游戏结束...按任意键继续测试.." << endl;

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
