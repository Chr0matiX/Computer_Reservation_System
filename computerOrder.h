#pragma once

#include<iostream>
#include"computerRoom.h"

using std::cout;
using std::endl;

class computerOrder {
public:
	computerOrder(int id, int room, int day, int dn, int state);
	~computerOrder();
	//�鿴ԤԼ
	void showOrder();

	int _id;
	int _room;
	int _day;
	int _dn;
	int _state;
};