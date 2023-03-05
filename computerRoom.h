#pragma once
#include<iostream>
#include"my_MySql.h"

using std::cout;
using std::endl;

class computerRoom {
public:
	computerRoom(int roomNum);
	//机房编号
	int _roomNum;
	//机房最大容量
	int _maxNum;
	//机房当前预约状态
	int _week[5][2];

	static const char* _weekName[5];

	static const char* _day[5];

	static const char* _dn[2];

	//输出机房信息
	void showInfo();

	//初始化预约信息
	bool initRsv();
private:
};