//����Ա��

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

	//����˺�  
	bool addPerson();

	//�鿴�˺�
	void showPerson();

	//�鿴������Ϣ
	void showComputer();

	//���ԤԼ��¼
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

	//�˵�
	static const char* _menu[];

private:
	//��ѯid��pwd
	static bool login(int id, const char* pwd);

	//��ȡȫ���û�
	bool getPerson();

	//ѧ������
	vector<Person*> _vctr_student;
	//��ʦ����
	vector<Person*> _vctr_teacher;
	//����Ա����
	vector<Person*> _vctr_admin;

	//ȫ���û�����
	vector<Person*> _persons[3] = {
		_vctr_student,
		_vctr_teacher,
		_vctr_admin
	};
};