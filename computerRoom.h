#pragma once
#include<iostream>
#include"my_MySql.h"

using std::cout;
using std::endl;

class computerRoom {
public:
	computerRoom(int roomNum);
	//�������
	int _roomNum;
	//�����������
	int _maxNum;
	//������ǰԤԼ״̬
	int _week[5][2];

	static const char* _weekName[5];

	static const char* _day[5];

	static const char* _dn[2];

	//���������Ϣ
	void showInfo();

	//��ʼ��ԤԼ��Ϣ
	bool initRsv();
private:
};