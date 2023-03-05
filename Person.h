//Person抽象类
//组成：身份类、菜单类

#pragma once
#include"my_MySql.h"

class Person {
public:
	virtual bool init(Person*& person) = 0;
	//显示身份信息
	virtual void showIdentity() = 0;

	virtual ~Person() {}
protected:
	//id
	int _id;
	//编号
	int _num;
	//密码
	char* _pwd;
	//姓名
	char* _name;
};