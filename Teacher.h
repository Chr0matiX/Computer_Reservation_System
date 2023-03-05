#pragma once
#include<vector>
#include"Person.h"
#include"computerOrder.h"
using std::cin;
using std::cout;
using std::endl;
using std::vector;

class Teacher : public Person {
public:
	Teacher();
	Teacher(int id, const char* pwd);
	Teacher(int num, int id, const char* pwd, const char* name);
	~Teacher();

	//Person::
	//登陆验证
	static Person* login();

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

	//查看所有预约
	void showAllOrder();
	//审核预约
	bool validOrder();

	enum attr {
		num,
		id,
		pwd,
		name
	};

	//菜单
	static const char* _menu[];

private:
	//查询id和pwd
	static bool login(int id, const char* pwd);
	//所有预约的容器
	vector<computerOrder> _vctr_AllOrders;
	//获取全部预约
	bool getAllOrder(int i);
};