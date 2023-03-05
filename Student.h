#pragma once
#include"computerOrder.h"

#include <iostream>
#include <vector>

#include"Person.h"
#include"computerRoom.h"

using std::cout;
using std::endl;
using std::cin;
using std::vector;

class Student : public Person {
public:
	Student();
	Student(int id, const char* pwd);
	Student(int num, int id, const char* pwd, const char* name);
	~Student();

	//Person::
	//登陆验证
	static Student* login();

	//Person::Identity::
	//修改身份数据
	bool init(Person*& person);
	//显示身份信息
	void showIdentity();

	//Person::Menu::
	//显示菜单
	static void showMenu(const char* menu[]);
	//菜单选择
	static bool select(Person*& person);

	//申请预约
	bool applyOrder();
	//查看我的预约
	void showMyOrder();
	//查看所有预约
	void showAllOrder();
	//取消预约
	bool cancelOrder();

	enum attr {
		num,
		id,
		pwd,
		name
	};

	//菜单
	static const char* _menu[];
private:
	//自身预约的容器
	vector<computerOrder> _vctr_orders;
	//查询id和pwd
	static bool login(int id, const char* pwd);
	//获取自身的预约
	bool getMyOrder();
};

