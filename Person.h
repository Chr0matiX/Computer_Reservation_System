//Person������
//��ɣ�����ࡢ�˵���

#pragma once
#include"my_MySql.h"

class Person {
public:
	virtual bool init(Person*& person) = 0;
	//��ʾ�����Ϣ
	virtual void showIdentity() = 0;

	virtual ~Person() {}
protected:
	//id
	int _id;
	//���
	int _num;
	//����
	char* _pwd;
	//����
	char* _name;
};