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
	//��ʾ���˵�
	static void showMenu(const char* menu[]);
	//ѡ��
	static bool Select(Person*& person);
	//�˵�
	static const char* _menu[];

	Person* person;
};