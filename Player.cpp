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

			desk, ��Ϸ���棬������Ľ��ؼ���ע

			bet, ������Ϸ��������ߵ�ע����Ŀ�����������ע����������������ע����Ӹ���עֵΪbet�Ĵ�С)

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

		desk, ��Ϸ���棬������Ľ��ؼ���ע

		bet, ������Ϸ��������ߵ�ע����Ŀ�����������ע����������������ע����Ӹ���עֵΪbet�Ĵ�С)

		num, �����עbet�Ļ����ϼ�ע������

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
	//����Ӯ�Ƹ���,ȷ��winPro�����ֵ 
	
	double cardMakingPro[11]={0,0.0000323206,0.000278507,0.00168067,0.0259610,0.0302859,0.0479329,0.0482987,0.234955,0.437729,0.172877};
	//���򣺻ʼ�ͬ��˳��ͬ��˳����������«��ͬ����˳�ӣ����������ԣ�һ�ԣ����� 
	//��52�����г�7�ŵĳ��Ƹ��� 
	
	for(int i=1;i<=10;i++){
		double winp=0; 
		for(int j=10;j>i;j--)
			winp+=cardMakingPro[j]; //ֻȷ���˱���������͵Ŀ����� 
		winPro[i]=winp;
	}
	winPro[0]=0;
}

//����Ϊ����ֵ������ 
//1.��ע 2.���� 3.����  (���ֻ�δ������ע�� 
//1.��ע 2.��ע 3.���� ��������������ע�� 
int Player::betRoundOne(Desk & desk)
{
//	countWinPro(); 
	int flag=0;//0.���� 1.һ�� 2.ͬ��˳ 3.���� 4.ͬ�� 5.˳�� 6.�����ƶ�����10 (��ͬ���ִ���ͬ���ͣ� 
	int betMount=desk.getbetMount();
	
	//����
	handCard.sort(); 
	vector<Poker> card=handCard.getHeap(); 
	
	//�ж����� 
	if(card[0].getFlower()==card[1].getFlower())
		flag=4;
	if(card[0].getPointSize()==card[1].getPointSize()+1){
		if(flag==4){
			if(card[0].getPointSize()==13&&card[1].getPointSize()==14)//�˴�����ֱ�ӽ�A��Ϊ14,���½�Ĭ�����
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
	
/*	//�ж��Ƿ������Ϸ 
	if(flag==0){
		outGame(); 
		return 3;
	}
	else{*///��Ϊһ����10~40����������1~10�� �ɸ� 
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
		else{//��ֵ�� 
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

//����Ϊ����ֵ������ 
//1.��ע 2.���� 3.���� (���ֻ�δ������ע�� 
//1.��ע 2.��ע 3.���� ��������������ע��
int Player::betRoundOther(Desk & desk)
{
	int flag=0;//0.��ʼ 1.�ʼ�ͬ��˳ 2.ͬ��˳ 3.���� 4.��« 5.ͬ�� 6.˳�� 7.���� 8.���� 9.һ�� 10.����  (��ͬ���ִ���ͬ���ͣ� 
	int betMount=desk.getbetMount();
	double cardMakingPro[11]={0,0.0000323206,0.000278507,0.00168067,0.0259610,0.0302859,0.0479329,0.0482987,0.234955,0.437729,0.172877};
	
	double  hearOuts[2][21]={{0,0.021,0.043,0.064,0.085,0.106,0.128,0.149,0.17,0.191,0.213,0.234,0.255,0.277,0.298,0.319,0.34,0.362,0.383,0.404,0.426},
	{0,0.022,0.043,0.065,0.087,0.109,0.13,0.152,0.174,0.196,0.217,0.239,0.261,0.283,0.304,0.326,0.348,0.37,0.391,0.413,0.435}};
	//����λ��0Ϊ��λ
	//���ƶ�������turn��riverʱ���Ƹ���
	
	//��ʼ��
	int pokerType[4];//�ں�÷��
	int pokerNum[15];//2��K��A 
	int outsCardType[10];//�ʼ�ͬ��˳��ͬ��˳����������«��ͬ����˳�ӣ����������ԣ�һ��  ����λ��0Ϊ��λ
	for(int i=0;i<4;i++)
		pokerType[i]=0;
	for(int i=0;i<15;i++)
		pokerNum[i]=0;
	for(int i=0;i<10;i++)
		outsCardType[i]=0; 
		
	//���򣨴�С���� 
	vector<Poker> a=handCard.getHeap(),c=desk.publicPoker.getHeap(); 
	vector<Poker> temp(a);
	vector<Poker> temp1(c);
	while(!temp1.empty()){
		temp.push_back(temp1.back());temp1.pop_back();
	}
	PokerHeap temp2(temp);
	temp2.sort();
	vector<Poker> card=temp2.getHeap();//cardΪ���հ������ƺ͹����Ƶ�vector 
	
		
	//���Ƿ�ͬ������ͬ��
	for(int i=0;i<2+desk.getSize();i++){
		if(card[i].getFlower()=="����")	
			pokerType[0]++;
		else if(card[i].getFlower()=="����")
			pokerType[1]++;
		else if(card[i].getFlower()=="÷��")
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
	
	//���Ƿ�˳�ӻ�����ͷ˳
	for(int i=0,j,n,k,m,temp;i<1+desk.getSize();i++){
		n=1;//�����˶����� 
		k=0;//�ϵ�ģʽ��0.�ޣ�1.�У� 
		m=1;//���ܷ����ϵ�˳ 
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
		//���Ƿ�ͬ��˳������ͷͬ��˳
		if(n==5){
			int f=0;//�жϱ�־
			j=temp;
			for(int k=0;k<4;k++){
				if(card[j-k].getPointSize()==card[j-k-1].getPointSize()){
					k--;j--;}
				else if(card[j-k].getFlower()!=card[j-k-1].getFlower()){
					f=1;
					break;
				}
			}
			if(f==0){//��ͬ��˳
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
			int f=0;//�жϱ�־
			j=temp;
			for(int k=0;k<3;k++){
				if(card[j-k].getPointSize()==card[j-k-1].getPointSize()){
					k--;j--;}
				else if(card[j-k].getFlower()!=card[j-k-1].getFlower()){
					f=1;
					break;
				}
			}
			if(f==0){//������ͷͬ��˳ 
				outsCardType[2]+=2; 
			} 
			else
				outsCardType[6]+=8;
		}
		else if(m==4){
			int f=0;//�жϱ�־
			j=temp;
			for(int k=0;k<3;k++){
				if(card[j-k].getPointSize()==card[j-k-1].getPointSize()){
					k--;j--;}
				else if(card[j-k].getFlower()!=card[j-k-1].getFlower()){
					f=1;
					break;
				}
			}
			if(f==0){//�����ϵ�ͬ��˳ 
				outsCardType[2]+=1; 
			} 
			else
				outsCardType[6]+=4;
		}
	}
	
	//���Ƿ���ӻ������� 
	int dui=0;//�ɶԵ���ʲô�� 
	int n=0;//��n��һ�� 
	for(int i=0;i<2+desk.getSize();i++)
		pokerNum[card[i].getPointSize()]++;
	for(int i=2;i<15;i++){
		if(pokerNum[i]==4&&(flag==0||flag>3)){//���Ƿ����� 
			flag=3;
		}
		else if(pokerNum[i]==3&&(flag==0||flag>7)){//���Ƿ�������������
			 flag=7;
			 outsCardType[3]++;
		} 
		else if(pokerNum[i]==2){ 
			if(flag==7)//���Ƿ��« 
				flag=4;
			n++;
			outsCardType[7]+=2; 
			if(n==2&&(flag==0||flag>8)){//���Ƿ������������� 
				if(i>dui)
					dui=i; 
				flag=8; 
				outsCardType[7]+=4; 
			} 
			else if(n==1&&(flag==0||flag>9)){//���Ƿ�һ�� 
				flag=9;dui=i;
				outsCardType[7]+=2;//������ 
				outsCardType[8]+=desk.getSize()*3;//������ 
			}
		}
	}
	
	//������һ��
	if(flag==0) 
		outsCardType[9]+=(2+desk.getSize())*3;
	
	//����Ӯ�Ƹ���
	//���ϳ���ʤ�� (�绹δ�г��ƣ���ù�����Ч��
	double winp=0; 
	winp=winPro[flag];
	//����һ�Ժ����Գ���Ƶ�ʽϸߣ��������ϸ��
	if(flag==9){ 
		winp+=((dui-2)/13.0)*cardMakingPro[9];
	}
	else if(flag==8){
		winp+=((dui-2)/13.0)*cardMakingPro[8];
	} 
	//��������ʤ�� (���������һ�֣� 
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
				if(desk.getSize()==3){//��turn�� 
					if(hearOuts[0][outsCardType[i]]*t>max)
						max=hearOuts[0][outsCardType[i]]*t;
					}
				else if(desk.getSize()==4){//��river�� 
					if(hearOuts[1][outsCardType[i]]*t>max)
						max=hearOuts[1][outsCardType[i]]*t;}
				}
		}
	}
	if(flag==0)
		winp+=max;
	if(winp>0.5)
		winp=winp/2;
	//�ж��Ƿ������Ϸ 
	if(betMount==0){
		if((betMount/desk.getJackPot())*desk.getJackPot()>1)
			bet(desk,int((betMount/desk.getJackPot())*desk.getJackPot()));
		else
			bet(desk,2);
		return 1;
	}
	else{
		if((betMount/desk.getJackPot())<winp&&winp>0.1){//Ӯ�Ƹ�����׳ظ��� 
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
