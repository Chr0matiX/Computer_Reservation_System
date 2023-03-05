#pragma once
#include<iostream>
#include"Student.h"
#include"Teacher.h"
#include"Admin.h"

using std::cout;
using std::endl;
using std::cin;

class cptSystem {
public:
	cptSystem();
	~cptSystem();
	//显示主菜单
	static void showMenu(const char* menu[]);
	//选择
	static bool Select(Person*& person);
	//菜单
	static const char* _menu[];

	Person* person;
};