//管理员类

#pragma once

#include<vector>
#include"Person.h"
#include"Student.h"
#include"Teacher.h"
#include"computerRoom.h"

using std::cout;
using std::cin;
using std::endl;
using std::vector;

class Admin : public Person {
public:
	Admin();
	Admin(int id, const char* pwd);
	Admin(int num, int id, const char* pwd, const char* name);
	~Admin();

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

	//添加账号  
	bool addPerson();

	//查看账号
	void showPerson();

	//查看机房信息
	void showComputer();

	//清空预约记录
	bool cleanFile();

	enum attr {
		num,
		id,
		pwd,
		name
	};

	char* user[3] = {
		(char*)"student",
		(char*)"teacher",
		(char*)"admin"
	};

	//菜单
	static const char* _menu[];

private:
	//查询id和pwd
	static bool login(int id, const char* pwd);

	//获取全部用户
	bool getPerson();

	//学生容器
	vector<Person*> _vctr_student;
	//教师容器
	vector<Person*> _vctr_teacher;
	//管理员容器
	vector<Person*> _vctr_admin;

	//全部用户容器
	vector<Person*> _persons[3] = {
		_vctr_student,
		_vctr_teacher,
		_vctr_admin
	};
};