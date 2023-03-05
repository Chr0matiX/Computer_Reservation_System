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
	//��½��֤
	static Person* login();

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

	//�鿴����ԤԼ
	void showAllOrder();
	//���ԤԼ
	bool validOrder();

	enum attr {
		num,
		id,
		pwd,
		name
	};

	//�˵�
	static const char* _menu[];

private:
	//��ѯid��pwd
	static bool login(int id, const char* pwd);
	//����ԤԼ������
	vector<computerOrder> _vctr_AllOrders;
	//��ȡȫ��ԤԼ
	bool getAllOrder(int i);
};