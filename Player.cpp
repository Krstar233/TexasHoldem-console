#include "Player.h"

#include <iostream>

using namespace std;




Player::Player(bool is)

{
	isAI=is;

	betHasPut = 0;
	
	hasAdd=false;

	money = 0;

	out = false;
	if(is==true)
		countWinPro(); 

}

void Player::followBet(Desk& desk, int bet)

{

	/*

		args:

			desk, 游戏桌面，可向其的奖池加入注

			bet, 当轮游戏中已下最高的注的数目，即所需跟的注数，（若本轮已下注，则加跟到注值为bet的大小)

	*/

	int addNum = bet - betHasPut;

	desk.addJackPot(addNum);
	desk.setbetMount(bet);

	this->money -= addNum;

	this->betHasPut = bet;

}



void Player::addBet(Desk& desk, int bet, int num)

{

	/*

	args:

		desk, 游戏桌面，可向其的奖池加入注

		bet, 当轮游戏中已下最高的注的数目，即所需跟的注数，（若本轮已下注，则加跟到注值为bet的大小)

		num, 在最高注bet的基础上加注的数额

	*/

	int addNum = bet - betHasPut + num;

	desk.addJackPot(addNum);
	desk.setbetMount(bet+num);

	this->money -= addNum;

	this->betHasPut = bet+num;

}


bool Player::getisAI(){
	return isAI;
}

int Player::getbetHasPut(){
	return betHasPut;
} 

void Player::bet(Desk& desk, int num)

{

//	cout<<num<<endl;
	desk.addJackPot(num);
	desk.setbetMount(num);

	this->money -= num;
	this->betHasPut = num;

}

void Player::countWinPro(){
	//计算赢牌概率,确定winPro数组的值 
	
	double cardMakingPro[11]={0,0.0000323206,0.000278507,0.00168067,0.0259610,0.0302859,0.0479329,0.0482987,0.234955,0.437729,0.172877};
	//次序：皇家同花顺，同花顺，四条，葫芦，同花，顺子，三条，两对，一对，高牌 
	//从52张牌中抽7张的成牌概率 
	
	for(int i=1;i<=10;i++){
		double winp=0; 
		for(int j=10;j>i;j--)
			winp+=cardMakingPro[j]; //只确定了比你更低牌型的可能性 
		winPro[i]=winp;
	}
	winPro[0]=0;
}

//以下为返回值代表含义 
//1.下注 2.让牌 3.弃牌  (本轮还未有人下注） 
//1.跟注 2.加注 3.弃牌 （本轮已有人下注） 
int Player::betRoundOne(Desk & desk)
{
//	countWinPro(); 
	int flag=0;//0.其他 1.一档 2.同花顺 3.对子 4.同花 5.顺子 6.两张牌都大于10 (不同数字代表不同牌型） 
	int betMount=desk.getbetMount();
	
	//排序
	handCard.sort(); 
	vector<Poker> card=handCard.getHeap(); 
	
	//判断牌型 
	if(card[0].getFlower()==card[1].getFlower())
		flag=4;
	if(card[0].getPointSize()==card[1].getPointSize()+1){
		if(flag==4){
			if(card[0].getPointSize()==13&&card[1].getPointSize()==14)//此处建议直接将A设为14,以下皆默认如此
				flag=1;
			else 
				flag=2;
		}
		else
			flag=5;
	}
	if(card[0].getPointSize()==card[1].getPointSize()){
		if(card[0].getPointSize()>10)
			flag=1;
		else 
			flag=3;
	}
	if(flag==0&&(card[0].getPointSize()>10&&card[1].getPointSize()>10))
		flag=6;
	
/*	//判断是否继续游戏 
	if(flag==0){
		outGame(); 
		return 3;
	}
	else{*///如为一档（10~40），其他（1~10） 可改 
		if(betMount==0){
			if(flag!=0){
				if(flag==1)
					bet(desk,40);
				else
					bet(desk,10);
			} 
		//		bet(desk,10);
			else
				bet(desk,2);
			return 1;
		}
		else{//不值得 
			if(flag!=0&&betMount<40){
		 		followBet(desk,betMount);
		//		addBet(desk,betMount,40-betMount);
		//		return 2;
			}
			else if(betMount<=10)
				followBet(desk,betMount);
			else
				return 3;
			return 1;
		}
//	}

}

//以下为返回值代表含义 
//1.下注 2.让牌 3.弃牌 (本轮还未有人下注） 
//1.跟注 2.加注 3.弃牌 （本轮已有人下注）
int Player::betRoundOther(Desk & desk)
{
	int flag=0;//0.初始 1.皇家同花顺 2.同花顺 3.四条 4.葫芦 5.同花 6.顺子 7.三条 8.两对 9.一对 10.高牌  (不同数字代表不同牌型） 
	int betMount=desk.getbetMount();
	double cardMakingPro[11]={0,0.0000323206,0.000278507,0.00168067,0.0259610,0.0302859,0.0479329,0.0482987,0.234955,0.437729,0.172877};
	
	double  hearOuts[2][21]={{0,0.021,0.043,0.064,0.085,0.106,0.128,0.149,0.17,0.191,0.213,0.234,0.255,0.277,0.298,0.319,0.34,0.362,0.383,0.404,0.426},
	{0,0.022,0.043,0.065,0.087,0.109,0.13,0.152,0.174,0.196,0.217,0.239,0.261,0.283,0.304,0.326,0.348,0.37,0.391,0.413,0.435}};
	//数组位置0为空位
	//听牌多少张在turn和river时成牌概率
	
	//初始化
	int pokerType[4];//黑红梅方
	int pokerNum[15];//2到K到A 
	int outsCardType[10];//皇家同花顺，同花顺，四条，葫芦，同花，顺子，三条，两对，一对  数组位置0为空位
	for(int i=0;i<4;i++)
		pokerType[i]=0;
	for(int i=0;i<15;i++)
		pokerNum[i]=0;
	for(int i=0;i<10;i++)
		outsCardType[i]=0; 
		
	//排序（从小到大） 
	vector<Poker> a=handCard.getHeap(),c=desk.publicPoker.getHeap(); 
	vector<Poker> temp(a);
	vector<Poker> temp1(c);
	while(!temp1.empty()){
		temp.push_back(temp1.back());temp1.pop_back();
	}
	PokerHeap temp2(temp);
	temp2.sort();
	vector<Poker> card=temp2.getHeap();//card为最终包含手牌和公共牌的vector 
	
		
	//看是否同花或听同花
	for(int i=0;i<2+desk.getSize();i++){
		if(card[i].getFlower()=="黑桃")	
			pokerType[0]++;
		else if(card[i].getFlower()=="红桃")
			pokerType[1]++;
		else if(card[i].getFlower()=="梅花")
			pokerType[2]++;
		else
			pokerType[3]++;
	} 
	for(int i=0;i<4;i++){
		if(pokerType[i]==5&&(flag==0||flag>5))
			flag=5;
		else if(pokerType[i]==4)
			outsCardType[5]+=9;
	}
	
	//看是否顺子或听两头顺
	for(int i=0,j,n,k,m,temp;i<1+desk.getSize();i++){
		n=1;//连续了多少张 
		k=0;//断点模式（0.无，1.有） 
		m=1;//看能否听断点顺 
		for(j=i;j<1+desk.getSize();j++){
			if(card[j].getPointSize()+1==card[j+1].getPointSize()){
				if(k==0)
					n++;
				m++;
			}
			else if(card[j].getPointSize()!=card[j+1].getPointSize())
				if(card[j].getPointSize()+2==card[j+1].getPointSize()&&k==0){
					m++;k=1;
				}
				else
					break;
		}
		temp=j;
		//看是否同花顺或听两头同花顺
		if(n==5){
			int f=0;//判断标志
			j=temp;
			for(int k=0;k<4;k++){
				if(card[j-k].getPointSize()==card[j-k-1].getPointSize()){
					k--;j--;}
				else if(card[j-k].getFlower()!=card[j-k-1].getFlower()){
					f=1;
					break;
				}
			}
			if(f==0){//是同花顺
				j=temp;
				if(card[j].getPointSize()==14)
					flag==1;
				else
					flag=2;
			} 
			else if(flag==0||flag>6)
				flag=6;
		} 
		else if(n==4){
			int f=0;//判断标志
			j=temp;
			for(int k=0;k<3;k++){
				if(card[j-k].getPointSize()==card[j-k-1].getPointSize()){
					k--;j--;}
				else if(card[j-k].getFlower()!=card[j-k-1].getFlower()){
					f=1;
					break;
				}
			}
			if(f==0){//是听两头同花顺 
				outsCardType[2]+=2; 
			} 
			else
				outsCardType[6]+=8;
		}
		else if(m==4){
			int f=0;//判断标志
			j=temp;
			for(int k=0;k<3;k++){
				if(card[j-k].getPointSize()==card[j-k-1].getPointSize()){
					k--;j--;}
				else if(card[j-k].getFlower()!=card[j-k-1].getFlower()){
					f=1;
					break;
				}
			}
			if(f==0){//是听断点同花顺 
				outsCardType[2]+=1; 
			} 
			else
				outsCardType[6]+=4;
		}
	}
	
	//看是否对子或听对子 
	int dui=0;//成对的是什么数 
	int n=0;//有n个一对 
	for(int i=0;i<2+desk.getSize();i++)
		pokerNum[card[i].getPointSize()]++;
	for(int i=2;i<15;i++){
		if(pokerNum[i]==4&&(flag==0||flag>3)){//看是否四条 
			flag=3;
		}
		else if(pokerNum[i]==3&&(flag==0||flag>7)){//看是否三条且听四条
			 flag=7;
			 outsCardType[3]++;
		} 
		else if(pokerNum[i]==2){ 
			if(flag==7)//看是否葫芦 
				flag=4;
			n++;
			outsCardType[7]+=2; 
			if(n==2&&(flag==0||flag>8)){//看是否两对且听三条 
				if(i>dui)
					dui=i; 
				flag=8; 
				outsCardType[7]+=4; 
			} 
			else if(n==1&&(flag==0||flag>9)){//看是否一对 
				flag=9;dui=i;
				outsCardType[7]+=2;//听三条 
				outsCardType[8]+=desk.getSize()*3;//听两对 
			}
		}
	}
	
	//单张听一对
	if(flag==0) 
		outsCardType[9]+=(2+desk.getSize())*3;
	
	//计算赢牌概率
	//加上成牌胜率 (如还未有成牌，则该过程无效）
	double winp=0; 
	winp=winPro[flag];
	//由于一对和两对出现频率较高，对其进行细化
	if(flag==9){ 
		winp+=((dui-2)/13.0)*cardMakingPro[9];
	}
	else if(flag==8){
		winp+=((dui-2)/13.0)*cardMakingPro[8];
	} 
	//加上听牌胜率 (不参与最后一轮） 
	double t=0,max=0;
	for(int i=1;i<10;i++){
		if(i!=flag){
			t=winPro[i];
			if(i==9){ 
				t+=((dui-2)/13.0)*cardMakingPro[9];
			}
			else if(i==8){
				t+=((dui-2)/13.0)*cardMakingPro[8];
			}
			if(outsCardType[i]<=10){
				if(desk.getSize()==3){//听turn牌 
					if(hearOuts[0][outsCardType[i]]*t>max)
						max=hearOuts[0][outsCardType[i]]*t;
					}
				else if(desk.getSize()==4){//听river牌 
					if(hearOuts[1][outsCardType[i]]*t>max)
						max=hearOuts[1][outsCardType[i]]*t;}
				}
		}
	}
	if(flag==0)
		winp+=max;
	if(winp>0.5)
		winp=winp/2;
	//判断是否继续游戏 
	if(betMount==0){
		if((betMount/desk.getJackPot())*desk.getJackPot()>1)
			bet(desk,int((betMount/desk.getJackPot())*desk.getJackPot()));
		else
			bet(desk,2);
		return 1;
	}
	else{
		if((betMount/desk.getJackPot())<winp&&winp>0.1){//赢牌概率与底池概率 
		//	cout<<"*"<<winp<<"/"<<betMount<<endl;
			if((betMount/desk.getJackPot())<(winp/2)&&hasAdd==false&&int(winp*desk.getJackPot())>betMount){
		//		cout<<"*"<<winp<<endl;
				addBet(desk,betMount,int(winp*desk.getJackPot())-betMount);
				hasAdd=true;
				return 2;}
			else{
				followBet(desk,betMount);
				return 1;
				}
		}
		else{
			outGame();
			return 3;
		}
	}
}

Player::~Player()

{

}



void Player::setName(string name)

{

	this->Name = name;

}



string Player::getName()

{

	return this->Name;

}



void Player::setMoney(int money)

{

	this->money = money;

}



int Player::getMoney()

{

	return this->money;

}



void Player::initOut()

{

	out = false;

}



void Player::outGame()

{

	out = true;

}



bool Player::isOut()

{

	return out;

}



void Player::initBetHasPut()

{

	betHasPut = 0;
	hasAdd=false;
}



void Player::handCardSort()

{

	handCard.sort();

}



void Player::handCardShow()

{

	handCard.show();

}



PokerHeap Player::getHandCard()

{

	return handCard;

}



PokerHeap& Player::getCard()

{

	return handCard;

}



void Player::clearHandCard()

{

	handCard.clear();

}
