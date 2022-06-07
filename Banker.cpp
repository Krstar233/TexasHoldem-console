#include "Banker.h"





Banker::Banker()

{

	Rank = new string [10];

	Rank[0] = "�ʼ�ͬ��˳";

	Rank[1] = "ͬ��˳";

	Rank[2] = "����";

	Rank[3] = "���ò�";

	Rank[4] = "ͬ��";

	Rank[5] = "˳��";

	Rank[6] = "����";

	Rank[7] = "����";

	Rank[8] = "һ��";

	Rank[9] = "���Ŵ���";

	winnernum = 0;

}





Banker::~Banker()

{

	delete [] Rank;

}



void Banker::licensing(std::vector<Player>& players, PokerHeap & pokerHeap)

{

	/*

		args:

			players,������Ϸ�����

			pokerHeap,��Ϸ�е�һ���˿���

	*/

	playernum = players.size();

	pokerHeap.upset();

	for (int i = 0; i < playernum; i++)

	{

		if (players[i].isOut() == false)

		{

			for (int j = 0; j < 2; j++)

			{

				Poker poker = pokerHeap.getHeap().back();

				pokerHeap.getHeap().pop_back();

				players[i].getCard().getHeap().push_back(poker);

			}
			if(players[i].getisAI()==false){
				cout << "���" << i+1 << "�ţ�" << "����Ϊ��" ;players[i].handCardShow();//test
			}

		}

	}

}



void Banker::licensingPublicCard(Desk & desk, PokerHeap & pokerHeap, int num)

{

	/*

	args:

		desk,��Ϸ���棨�������з��ù����ƣ�

		pokerHeap,��Ϸ�е�һ���˿���

		num,�������Ƶ���Ŀ

	*/

	for (int i = 0; i < num; i++)

	{

		Poker poker = pokerHeap.getHeap().back();

		pokerHeap.getHeap().pop_back();

		desk.getCard().getHeap().push_back(poker);

	}

}



void Banker::distributeReward(std::vector<Player>& players, Desk & desk)

{

	/*

	args:

		players,������Ϸ����ң���������

		desk,��Ϸ���棬���й����ƣ��Լ�����

	*/

	finalcards = new PokerHeap [playernum];

	players_cards_type = new string [playernum];

	subset = new vector<Poker> [playernum];

	vector<Player>::iterator i;

	int j = 0;

	for (i = players.begin(),j=0; i < players.end(); i++,j++)

	{

		if ((*i).isOut()==false)

		{

			finalcards[j] = (*i).getHandCard();

			finalcards[j].getHeap().insert(finalcards[j].getHeap().end(), desk.getCard().getHeap().begin(), desk.getCard().getHeap().end());

			//test

			/*cout << "���" << j + 1 << "�ŵ�finalcardsΪ��";

			finalcards[j].show();*/

		}

	}

	identifyCardType(players);

	findAWinnerIndex(players);

	findOtherWinnersIndex(players);

	comparisionBetweenWinners();



	//test

	cout << "������յ����ƣ�5�ţ�Ϊ��" << endl;

	for (j = 0; j < playernum; j++)

	{

		if (players[j].isOut() == false)

		{
			cout<<players[j].getName()<<": ";

			for (int k = 0; k < 5; k++)

			{

				subset[j][k].show();
				if (k != 4)
					cout << " ";

			}
			cout << endl;
		}


	}

	

	int money = desk.getJackPot()/winnernum;

	for (j = 0; j < winnernum; j++)

	{

		players[winners_index[j]].setMoney(players[winners_index[j]].getMoney()+money);

	}

	

	cout << "��ֻ��ʤ�������Ϊ�� " << endl;

	for (j = 0; j < winnernum; j++)

	{

		cout << "���" << winners_index[j]+1 << "�ţ�" << "����Ϊ��" << players[winners_index[j]].getName() << "�� ��/����ӵ�е�����" << players_cards_type[winners_index[j]] << "�� ����Ϊ";

		for (int k = 0; k < 5; k++)
		{

			subset[winners_index[j]][k].show();

			cout << " ";

		}

		cout << endl;

	}

	delete[] finalcards;

	delete[] subset;

	delete[] players_cards_type;

	winners_index.clear();

	winnernum = 0;

}



void Banker::identifyCardType(std::vector<Player>& players)

{

	int i;

	for (i = 0; i < playernum; i++)

	{

		if (players[i].isOut() == false)

		{

			int flag;

			flag = isRoyalFlush(finalcards[i], i);

			if (flag == 1)

			{

				players_cards_type[i] = "�ʼ�ͬ��˳";

				continue;

			}

			flag = isFlush(finalcards[i], i);

			if (flag == 1)

			{

				players_cards_type[i] = "ͬ��˳";

				continue;

			}

			flag = isFourArticle(finalcards[i], i);

			if (flag == 1)

			{

				players_cards_type[i] = "����";

				continue;

			}

			flag = isFullHallOfFame(finalcards[i], i);

			if (flag == 1)

			{

				players_cards_type[i] = "���ò�";

				continue;

			}

			flag = isSameSuit(finalcards[i], i);

			if (flag == 1)

			{

				players_cards_type[i] = "ͬ��";

				continue;

			}

			flag = isStraightDraw(finalcards[i], i);

			if (flag == 1)

			{

				players_cards_type[i] = "˳��";

				continue;

			}

			flag = isThreeArticle(finalcards[i], i);

			if (flag == 1)

			{

				players_cards_type[i] = "����";

				continue;

			}

			flag = isTwoPairs(finalcards[i], i);

			if (flag == 1)

			{

				players_cards_type[i] = "����";

				continue;

			}

			flag = isAPair(finalcards[i], i);

			if (flag == 1)

			{

				players_cards_type[i] = "һ��";

				continue;

			}

			flag = isSingleCard(finalcards[i], i);

			if (flag == 1)

			{

				players_cards_type[i] = "���Ŵ���";

				continue;

			}

		}

	}

	//test

	for (i = 0; i < playernum; i++)

	{

		if (players[i].isOut() == false)

		{

			cout <<"���"<<i+1<<"�ŵ���������Ϊ��"<< players_cards_type[i] << endl;

		}

	}

}



int Banker::isRoyalFlush(PokerHeap playercard, int index)

{

	playercard.sort();

	vector < Poker > temp = playercard.getHeap();

	string samecolor = temp[0].getFlower();

	int start = 0, over = 0, counter = 1;

	int i, j;

	for (i = 1; i < 7; i++)

	{

		if (temp[i].getFlower() != samecolor)

		{

			samecolor = temp[i].getFlower();

			start = i;

			counter = 1;

		}

		else

		{

			counter++;

			if (counter == 5)

				break;

		}

	}

	if (7 - start >= 5)

	{

		counter = 0;

		for (i = start; i < 7; i++)

		{

			if (temp[i].getFlower() == samecolor)

			{

				over = i;

			}

		}

		int royalflush[5] = {10,11,12,13,14};

		for (i = 0; i < 5; i++)

		{

			for (j = start; j <= over; j++)

			{

				if (temp[j].getPointSize() == royalflush[i])

				{

					counter++;

					break;

				}

			}

		}

		if (counter == 5)

		{

			for (i = 0; i < 5; i++)

			{

				subset[index].push_back(*(new Poker(samecolor,royalflush[i])));

			}
			temp.clear();
			return 1;

		}

	}
	temp.clear();

	return 0;

}



int Banker::isFlush(PokerHeap playercard, int index)//�Ѿ��ų�AΪ��������

{

	playercard.sort();

	vector < Poker > temp = playercard.getHeap();

	string samecolor = temp[0].getFlower();

	int start = 0, over = 0, counter = 1;

	int i, j, k;

	for (i = 1; i < 7; i++)

	{

		if (temp[i].getFlower() != samecolor)

		{

			samecolor = temp[i].getFlower();

			start = i;

			counter = 1;

		}

		else

		{

			counter++;

			if (counter == 5)

				break;

		}

	}

	if (7 - start >= 5)

	{

		for (i = start; i < 7; i++)

		{

			if (temp[i].getFlower() == samecolor)

			{

				over = i;

			}

		}

		//���������A,2,3,4,5

		counter = 0;

		int specialCase[5] = {5,4,3,2,14};

		for (i = 0; i < 5; i++)

		{

			for (j = start; j <= over; j++)

			{

				if (temp[j].getPointSize() == specialCase[i])

				{

					counter++;

				}

			}

		}

		if (counter == 5)

		{

			for (i = 0; i<5; i++)

			{

				for (j = start; j <= over; j++)

				{

					if (temp[j].getPointSize() == specialCase[i])

					{

						subset[index].push_back(temp[j]);

					}

				}

			}
			temp.clear();
			return 1;

		}



		counter = 1;

		for (j = over; j >= start + 1; j--)

		{

			if (temp[j].getPointSize() - temp[j - 1].getPointSize() == 1)

			{

				counter++;

				if (counter == 5)

				{

					for (k = j - 1 + 4; k >= j - 1; k--)

					{

						subset[index].push_back(temp[k]);

					}
					temp.clear();
					return 1;

				}

			}

			else

			{

				counter = 1;

			}

		}

		if (counter != 5)
		{
			temp.clear();
			return 0;}

	}

	else{
		temp.clear();
		return 0;}
	temp.clear();
	return 0;

}



int Banker::isFourArticle(PokerHeap playercard, int index)

{

	playercard.sortByNum();

	vector < Poker > temp = playercard.getHeap();

	int i, j,k;

	for (i = 0; i < 7; i++)

	{

		int counter = 1;

		for (j = i + 1; j < 7; j++)

		{

			if (temp[j].getPointSize() == temp[i].getPointSize())

			{

				counter++;

			}

		}

		if (counter == 4)

		{

			for (k = i; k < i + 4; k++)

			{

				subset[index].push_back(temp[k]);

			}

			

			for (k = 0; k <7; k++)

			{

				if (temp[k].getPointSize() != subset[index][0].getPointSize())

				{

					subset[index].push_back(temp[k]);

					break;

				}

			}
			temp.clear();
			return 1;

		}

	}
	temp.clear();
	return 0;

}



int Banker::isFullHallOfFame(PokerHeap playercard, int index)

{

	playercard.sortByNum();

	vector < Poker > temp = playercard.getHeap();

	int i, j, k;

	int counter = 0;

	int mark;

	int flag1 = 0, flag2 = 0;

	for (i = 0; i < 7; i++)

	{

		counter = 0;

		for (j = i + 1; j < 7; j++)

		{

			if (temp[j].getPointSize() == temp[i].getPointSize())

			{

				counter++;

			}

		}

		if (counter == 2)

		{

			mark = i;

			flag1 = 1;

			break;

		}

	}

	if (flag1 == 0){
		temp.clear();
		return 0;}

	for (i = 0; i < 7; i++)

	{

		counter = 0;

		if (temp[mark].getPointSize() != temp[i].getPointSize())

		{

			for (j = i + 1; j < 7; j++)

			{

				if (temp[j].getPointSize() == temp[i].getPointSize())

				{

					counter++;

					flag2 = 1;

					int times = 0;

					for (k = 0; k < 7; k++)

					{

						if (temp[k].getPointSize() == temp[mark].getPointSize())

						{

							subset[index].push_back(temp[k]);

						}

					}

					for (k = 0; k < 7; k++)

					{

						if (temp[k].getPointSize() == temp[i].getPointSize())

						{

							times++;

							subset[index].push_back(temp[k]);

							if (times == 2)

								break;

						}

					}
					temp.clear();
					return 1;

				}

			}

		}

	}
	temp.clear();
	return 0;

}



int Banker::isSameSuit(PokerHeap playercard, int index)

{

	playercard.sort();

	vector < Poker > temp = playercard.getHeap();

	string samecolor = temp[0].getFlower();

	int i, j, counter = 1;

	for (i = 1; i < 7; i++)

	{

		if (temp[i].getFlower() == samecolor)

		{

			counter++;

			if (counter == 5)

			{

				for (j = i; j >= i-4; j--)

				{

					subset[index].push_back(temp[j]);

				}
				temp.clear();
				return 1;

			}

		}

		else

		{

			counter = 1;

			samecolor = temp[i].getFlower();

		}

	}
	temp.clear();
	return 0;

}



int Banker::isStraightDraw(PokerHeap playercard, int index)

{

	playercard.sortByNum();

	vector < Poker > temp = playercard.getHeap();

	int i, j, counter = 0;

	//���������A,2,3,4,5

	int specialCase[5] = {5,4,3,2,14};

	for (i = 0; i < 5; i++)

	{

		for (j = 0; j < 7; j++)

		{

			if (temp[j].getPointSize() == specialCase[i])

			{

				counter++;

				break;

			}

		}

	}

	if (counter == 5)

	{

		for (i = 0; i < 5; i++)

		{

			for (j = 0; j < 7; j++)

			{

				if (temp[j].getPointSize() == specialCase[i])

				{

					subset[index].push_back(temp[j]);

				}

			}

		}
		temp.clear();
		return 1;

	}

	

	counter = 1;

	for (i = 0; i < 7-1; i++)

	{

		if (temp[i].getPointSize() - temp[i + 1].getPointSize() == 1)

		{

			counter++;

			if (counter == 5)

			{

				subset[index].push_back(temp[i+1]);

				int times = 0;

				for (j = i; j >= 0; j--)

				{

					if (temp[j + 1].getPointSize() - temp[j].getPointSize() == -1)

					{

						times++;

						subset[index].push_back(temp[j]);

						if (times == 4)

							break;

					}

				}

				Poker media;

				media = subset[index][0];

				subset[index][0] = subset[index][4];

				subset[index][4] = media;

				media = subset[index][1];

				subset[index][1] = subset[index][3];

				subset[index][3] = media;
				temp.clear();
				return 1;

			}

		}

		else if (temp[i].getPointSize() - temp[i + 1].getPointSize() == 0)

		{

			continue;

		}

		else

		{

			counter = 1;

		}

	}
	temp.clear();
	return 0;

}



int Banker::isThreeArticle(PokerHeap playercard, int index)

{

	int i, j, k;

	int counter = 0;

	playercard.sortByNum();

	vector < Poker > temp = playercard.getHeap();

	for (i = 0; i < 7; i++)

	{

		counter = 0;

		for (j = i + 1; j < 7; j++)

		{

			if (temp[j].getPointSize() == temp[i].getPointSize())

			{

				counter++;

				if (counter == 2)

				{

					for (k = j; k >= j - 2; k--)

					{

						subset[index].push_back(temp[k]);

					}

					int times=0,mark=-1;

					for (k = 0; k < 7; k++)

					{

						if (temp[k].getPointSize() != temp[i].getPointSize() && temp[k].getPointSize() != mark)

						{

							times++;

							mark = temp[k].getPointSize();

							subset[index].push_back(temp[k]);

							if (times == 2)

								break;

						}

					}
					temp.clear();
					return 1;

				}

			}

			else

			{

				counter = 0;

				break;

			}

		}

	}
	temp.clear();
	return 0;

}



int Banker::isTwoPairs(PokerHeap playercard, int index)

{

	int firstpairs_num = -1;

	int secondpairs_num = -1;

	int i, j;

	playercard.sortByNum();



	vector < Poker > temp = playercard.getHeap();

	for (i = 0; i < 7; i++)

	{

		for (j = i + 1; j < 7; j++)

		{

			if (temp[j].getPointSize() == temp[i].getPointSize())

			{

				firstpairs_num = temp[j].getPointSize();

				break;

			}

		}

		if (firstpairs_num != -1){
			break;}

	}

	if (firstpairs_num == -1){
		temp.clear();
		return 0;}

	for (i = 0; i < 7; i++)

	{

		if (temp[i].getPointSize() != firstpairs_num)

		{

			for (j = i + 1; j < 7; j++)

			{

				if (temp[j].getPointSize() == temp[i].getPointSize())

				{

					secondpairs_num = temp[j].getPointSize();

					break;

				}

			}

		}

	}

	if (firstpairs_num != -1 && secondpairs_num != -1)

	{

		for (i = 0; i < 7; i++)

		{

			if (temp[i].getPointSize() == firstpairs_num)

			{

				subset[index].push_back(temp[i]);

			}

		}

		for (i = 0; i < 7; i++)

		{

			if (temp[i].getPointSize() == secondpairs_num)

			{

				subset[index].push_back(temp[i]);

			}

		}

		for (i = 0; i < 7; i++)

		{

			if (temp[i].getPointSize() != firstpairs_num && temp[i].getPointSize() != secondpairs_num)

			{

				subset[index].push_back(temp[i]);

				break;

			}

		}
		temp.clear();
		return 1;

	}

	else
		temp.clear();
		return 0;

}



int Banker::isAPair(PokerHeap playercard, int index)

{

	playercard.sortByNum();

	int i, j, k;

	vector < Poker > temp = playercard.getHeap();

	for (i = 0; i < 7; i++)

	{

		for (j = i + 1; j < 7; j++)

		{

			if (temp[j].getPointSize() == temp[i].getPointSize())

			{

				subset[index].push_back(temp[i]);

				subset[index].push_back(temp[j]);

				int times=0;

				for (k = 0; k < 7; k++)

				{

					if (temp[k].getPointSize() != temp[j].getPointSize())

					{

						times++;

						subset[index].push_back(temp[k]);

						if (times == 3)

							break;

					}

				}
				temp.clear();
				return 1;

			}

		}

	}
	temp.clear();
	return 0;

}



int Banker::isSingleCard(PokerHeap playercard, int index)

{

	playercard.sortByNum();

	vector < Poker > temp = playercard.getHeap();

	for (int i = 0; i < 5; i++)

	{

		subset[index].push_back(temp[i]);

	}
	temp.clear();
	return 1;

}



void Banker::findAWinnerIndex(std::vector<Player>& players)

{

	int i, j;

	int minrankindex = 11;

	int index = 0, rankindex = 0;



	for (i = 0; i < playernum; i++)

	{

		if (players[i].isOut() == false)

		{

			for (j = 0; j < 10; j++)

			{

				if (players_cards_type[i] == Rank[j])

				{

					rankindex = j;

					break;

				}

			}

			if (rankindex < minrankindex)

			{

				minrankindex = rankindex;

				index = i;

			}

		}

	}

	winners_index.push_back(index);

	winnernum++;

}



void Banker::findOtherWinnersIndex(std::vector<Player>& players)

{

	int i, j = 0;

	for (i = 0; i < playernum; i++)

	{

		if (players[i].isOut() == false)

		{

			if (i != winners_index[0])

			{

				if (players_cards_type[i] == players_cards_type[winners_index[0]])

				{

					winners_index.push_back(i);

					winnernum++;

				}

			}

		}

	}

	

}



void Banker::comparisionBetweenWinners()

{

	int len = winners_index.size();



	if (len == 1)

		return;

	string ranktype = players_cards_type[winners_index[0]];

	if (ranktype == Rank[0])

	{

		comparisionOfRoyalFlush();

	}

	else if (ranktype == Rank[1])

	{

		comparisionOfFlush();

	}

	else if (ranktype == Rank[2])

	{

		comparisionOfFourArticle();

	}

	else if (ranktype == Rank[3])

	{

		comparisionOfFullHallOfFame();

	}

	else if (ranktype == Rank[4])

	{

		comparisionOfSameSuit();

	}

	else if (ranktype == Rank[5])

	{

		comparisionOfStraightDraw();

	}

	else if (ranktype == Rank[6])

	{

		comparisionOfThreeArticle();

	}

	else if (ranktype == Rank[7])

	{

		comparisionOfTwoPairs();

	}

	else if (ranktype == Rank[8])

	{

		comparisionOfAPair();

	}

	else if (ranktype == Rank[9])

	{

		comparisionOfSingleCard();

	}

}



void Banker::comparisionOfRoyalFlush()

{

	winnernum = winners_index.size();

	return;

}



void Banker::comparisionOfFlush()//�Ѿ��ų�AΪ�������

{

	int len = winners_index.size();

	int i, j;

	//���Ƶ�����ѡ���±�ŵ�winners_index�ĵ�һλ��

	for (i = 0; i < len-1; i++)

	{

		for (j = 0; j < 5; j++)

		{

			if (subset[winners_index[i]][j].getPointSize() > subset[winners_index[i + 1]][j].getPointSize())

			{

				int temp = winners_index[i];

				winners_index[i] = winners_index[i + 1];

				winners_index[i + 1] = temp;

				break;

			}

			else if (subset[winners_index[i]][j].getPointSize() < subset[winners_index[i + 1]][j].getPointSize())

			{

				break;

			}

			else

				break;

		}

	}



	//����Ƿ���������±�Ϊwinners_index[len-1]�ȴ����Ƶĺ�ѡ��

	vector<int> temp;

	temp.push_back(winners_index[len-1]);

	for (i = 0; i < len-1; i++)

	{

		for (j = 0; j < 5; j++)

		{

			if (subset[winners_index[len-1]][j].getPointSize() != subset[winners_index[i]][j].getPointSize())

			{

				break;

			}

		}

		if (j == 5)

		{

			temp.push_back(winners_index[i]);

		}

	}

	winners_index.assign(temp.begin(),temp.end());

	winnernum = winners_index.size();
	temp.clear();
	return;

}



void Banker::comparisionOfFourArticle()

{

	int len = winners_index.size();

	int i;

	for (i = 0; i < len-1; i++)

	{

		if (subset[winners_index[i]][0].getPointSize() > subset[winners_index[i + 1]][0].getPointSize())

		{

			int temp = winners_index[i];

			winners_index[i] = winners_index[i + 1];

			winners_index[i + 1] = temp;

		}

		else if (subset[winners_index[i]][0].getPointSize() == subset[winners_index[i + 1]][0].getPointSize())//�п��ܳ�����ͬ��4��ͬ����������ׯ�ҵĹ�������

		{

			if (subset[winners_index[i]][4].getPointSize() > subset[winners_index[i + 1]][4].getPointSize())

			{

				int temp = winners_index[i];

				winners_index[i] = winners_index[i + 1];

				winners_index[i + 1] = temp;

			}

		}

	}



	vector<int> temp;

	temp.push_back(winners_index[len - 1]);

	for (i = 0; i < len - 1; i++)

	{

		if (subset[winners_index[len - 1]][0].getPointSize() == subset[winners_index[i]][0].getPointSize()&& subset[winners_index[len - 1]][4].getPointSize() == subset[winners_index[i]][4].getPointSize())

		{

			temp.push_back(winners_index[i]);

		}

	}

	winners_index.assign(temp.begin(), temp.end());

	winnernum = winners_index.size();
	
	temp.clear();

	return;

}



void Banker::comparisionOfFullHallOfFame()

{

	int len = winners_index.size();

	int i;

	for (i = 0; i < len - 1; i++)

	{

		if (subset[winners_index[i]][0].getPointSize() > subset[winners_index[i + 1]][0].getPointSize())

		{

			int temp = winners_index[i];

			winners_index[i] = winners_index[i + 1];

			winners_index[i + 1] = temp;

		}

		else if (subset[winners_index[i]][0].getPointSize() == subset[winners_index[i + 1]][0].getPointSize())

		{

			if (subset[winners_index[i]][3].getPointSize() > subset[winners_index[i + 1]][3].getPointSize())

			{

				int temp = winners_index[i];

				winners_index[i] = winners_index[i + 1];

				winners_index[i + 1] = temp;

			}

		}

	}

	

	vector<int> temp;

	temp.push_back(winners_index[len - 1]);

	for (i = 0; i < len - 1; i++)

	{

		if (subset[winners_index[len - 1]][0].getPointSize() == subset[winners_index[i]][0].getPointSize() && subset[winners_index[len - 1]][3].getPointSize() == subset[winners_index[i]][3].getPointSize())

		{

			temp.push_back(winners_index[i]);

		}

	}

	winners_index.assign(temp.begin(), temp.end());

	winnernum = winners_index.size();
	temp.clear();
	return;

}



void Banker::comparisionOfSameSuit()

{

	int len = winners_index.size();

	int i,j;

	for (i = 0; i < len - 1; i++)

	{

		for (j = 0; j < 5; j++)

		{

			if (subset[winners_index[i]][j].getPointSize() > subset[winners_index[i + 1]][j].getPointSize())

			{

				int temp = winners_index[i];

				winners_index[i] = winners_index[i + 1];

				winners_index[i + 1] = temp;

				break;

			}

			else if (subset[winners_index[i]][j].getPointSize() < subset[winners_index[i + 1]][j].getPointSize())

			{

				break;

			}

			else

				continue;

		}

	}



	vector<int> temp;

	temp.push_back(winners_index[len-1]);

	for (i = 0; i < len-1; i++)

	{

		for (j = 0; j < 5; j++)

		{

			if (subset[winners_index[len-1]][j].getPointSize() != subset[winners_index[i]][j].getPointSize())

			{

				break;

			}

		}

		if (j == 5)

		{

			temp.push_back(winners_index[i]);

		}

	}

	winners_index.assign(temp.begin(), temp.end());

	winnernum = winners_index.size();
	temp.clear();
	return;

}



void Banker::comparisionOfStraightDraw()

{

	int len = winners_index.size();

	int i, j;

	for (i = 0; i < len - 1; i++)

	{

		for (j = 0; j < 5; j++)

		{

			if (subset[winners_index[i]][j].getPointSize() > subset[winners_index[i + 1]][j].getPointSize() || subset[winners_index[i+1]][4].getPointSize() == 14)

			{

				int temp = winners_index[i];

				winners_index[i] = winners_index[i + 1];

				winners_index[i + 1] = temp;

				break;

			}

			else if (subset[winners_index[i]][j].getPointSize() < subset[winners_index[i + 1]][j].getPointSize())

			{

				break;

			}

			else

				continue;

		}

	}

	vector<int> temp;

	temp.push_back(winners_index[len - 1]);

	for (i = 0; i < len - 1; i++)

	{

		for (j = 0; j < 5; j++)

		{

			if (subset[winners_index[len - 1]][j].getPointSize() != subset[winners_index[i]][j].getPointSize())

			{

				break;

			}

		}

		if (j == 5)

		{

			temp.push_back(winners_index[i]);

		}

	}

	winners_index.assign(temp.begin(), temp.end());

	winnernum = winners_index.size();
	temp.clear();
	
	return;

}



void Banker::comparisionOfThreeArticle()

{

	int len = winners_index.size();

	int i,j;

	for (i = 0; i < len - 1; i++)

	{

		if (subset[winners_index[i]][0].getPointSize() > subset[winners_index[i + 1]][0].getPointSize())

		{

			int temp = winners_index[i];

			winners_index[i] = winners_index[i + 1];

			winners_index[i + 1] = temp;

		}

		else if (subset[winners_index[i]][0].getPointSize() == subset[winners_index[i + 1]][0].getPointSize())

		{

			for (j = 3; j <= 4; j++)

			{

				if (subset[winners_index[i]][j].getPointSize() > subset[winners_index[i + 1]][j].getPointSize())

				{

					int temp = winners_index[i];

					winners_index[i] = winners_index[i + 1];

					winners_index[i + 1] = temp;

				}

			}

		}

	}

	

	vector<int> temp;

	temp.push_back(winners_index[len - 1]);

	for (i = 0; i < len - 1; i++)

	{

		if (subset[winners_index[len - 1]][0].getPointSize() == subset[winners_index[i]][0].getPointSize() && subset[winners_index[len - 1]][3].getPointSize() == subset[winners_index[i]][3].getPointSize()&& subset[winners_index[len - 1]][4].getPointSize() == subset[winners_index[i]][4].getPointSize())

		{

			temp.push_back(winners_index[i]);

		}

	}

	winners_index.assign(temp.begin(), temp.end());

	winnernum = winners_index.size();
	temp.clear();
	return;

}



void Banker::comparisionOfTwoPairs()

{

	int len = winners_index.size();

	int i,j;

	for (i = 0; i < len - 1; i++)

	{

		for (j = 0; j < 5; j++)

		{

			if (subset[winners_index[i]][j].getPointSize() > subset[winners_index[i + 1]][j].getPointSize())

			{

				int temp = winners_index[i];

				winners_index[i] = winners_index[i + 1];

				winners_index[i + 1] = temp;

				break;

			}

			else if (subset[winners_index[i]][j].getPointSize() < subset[winners_index[i + 1]][j].getPointSize())

			{

				break;

			}

			else

				continue;

		}

	}



	vector<int> temp;

	temp.push_back(winners_index[len - 1]);

	for (i = 0; i < len - 1; i++)

	{

		for (j = 0; j < 5; j++)

		{

			if (subset[winners_index[len - 1]][j].getPointSize() != subset[winners_index[i]][j].getPointSize())

			{

				break;

			}

		}

		if (j == 5)

		{

			temp.push_back(winners_index[i]);

		}

	}

	winners_index.assign(temp.begin(), temp.end());

	winnernum = winners_index.size();
	temp.clear();
	return;

}



void Banker::comparisionOfAPair()

{

	int len = winners_index.size();

	int i, j;

	for (i = 0; i < len - 1; i++)

	{

		for (j = 0; j < 5; j++)

		{

			if (subset[winners_index[i]][j].getPointSize() > subset[winners_index[i + 1]][j].getPointSize())

			{

				int temp = winners_index[i];

				winners_index[i] = winners_index[i + 1];

				winners_index[i + 1] = temp;

				break;

			}

			else if (subset[winners_index[i]][j].getPointSize() < subset[winners_index[i + 1]][j].getPointSize())

			{

				break;

			}

			else

				continue;

		}

	}

	vector<int> temp;

	temp.push_back(winners_index[len - 1]);

	for (i = 0; i < len - 1; i++)

	{

		for (j = 0; j < 5; j++)

		{

			if (subset[winners_index[len - 1]][j].getPointSize() != subset[winners_index[i]][j].getPointSize())

			{

				break;

			}

		}

		if (j == 5)

		{

			temp.push_back(winners_index[i]);

		}

	}

	winners_index.assign(temp.begin(), temp.end());

	winnernum = winners_index.size();
	temp.clear();
	return;

}



void Banker::comparisionOfSingleCard()

{

	int len = winners_index.size();

	int i, j;

	for (i = 0; i < len - 1; i++)

	{

		for (j = 0; j < 5; j++)

		{

			if (subset[winners_index[i]][j].getPointSize() > subset[winners_index[i + 1]][j].getPointSize())

			{

				int temp = winners_index[i];

				winners_index[i] = winners_index[i + 1];

				winners_index[i + 1] = temp;

				break;

			}

			else if (subset[winners_index[i]][j].getPointSize() < subset[winners_index[i + 1]][j].getPointSize())

			{

				break;

			}

			else

				continue;

		}

	}



	vector<int> temp;

	temp.push_back(winners_index[len - 1]);

	for (i = 0; i < len - 1; i++)

	{

		for (j = 0; j < 5; j++)

		{

			if (subset[winners_index[len - 1]][j].getPointSize() != subset[winners_index[i]][j].getPointSize())

			{

				break;

			}

		}

		if (j == 5)

		{

			temp.push_back(winners_index[i]);

		}

	}

	winners_index.assign(temp.begin(), temp.end());

	winnernum = winners_index.size();
	temp.clear();
	return;

}
