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
	//��½��֤
	static Student* login();

	//Person::Identity::
	//�޸��������
	bool init(Person*& person);
	//��ʾ�����Ϣ
	void showIdentity();

	//Person::Menu::
	//��ʾ�˵�
	static void showMenu(const char* menu[]);
	//�˵�ѡ��
	static bool select(Person*& person);

	//����ԤԼ
	bool applyOrder();
	//�鿴�ҵ�ԤԼ
	void showMyOrder();
	//�鿴����ԤԼ
	void showAllOrder();
	//ȡ��ԤԼ
	bool cancelOrder();

	enum attr {
		num,
		id,
		pwd,
		name
	};

	//�˵�
	static const char* _menu[];
private:
	//����ԤԼ������
	vector<computerOrder> _vctr_orders;
	//��ѯid��pwd
	static bool login(int id, const char* pwd);
	//��ȡ�����ԤԼ
	bool getMyOrder();
};

