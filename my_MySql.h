//mysql��
//��������mysql��ѯ��д��Ȳ���

#pragma once
#include<mysql.h>
#include<iostream>

using std::cout;
using std::endl;

//mysql��
class my_MySql {
public:
	my_MySql();
	~my_MySql();
	/// <summary>
	/// ����mysql���ݿ�
	/// </summary>
	/// <param name="headle">sql���</param>
	/// <param name="host">���ݿ��ַ</param>
	/// <param name="user">�û���</param>
	/// <param name="pwd">����</param>
	/// <param name="db">���ݿ���</param>
	/// <param name="port">�˿ں�</param>
	/// <returns></returns>
	bool connet(
		const char* host,
		const char* user,
		const char* pwd,
		const char* db,
		const unsigned int port);
	//�����Զ����ѯ���
	bool quire_res(const char* sentence);
	bool quire(const char* sentence);
	//��ȡ�������
	MYSQL_ROW getRow();
	//��ȡ���������
	int getFieldNum();

	char* tableName;
	char _sentence[150];

	//�����
	MYSQL_ROW _row;
	//���������
	int _fieldNum;
	//���������
	int _rowNum;
	//��ѯ�Ľ����
	MYSQL_RES* _res;
	//sql���
	MYSQL* _mysqlHeadle;
	//����״̬
	bool _connetState;

	//��ַ
	const char* _host = "127.0.0.1";
	//�û���
	const char* _user = "root";
	//����
	const char* _pwd = "root";
	//���ݿ���
	const char* _databaseName = "Computer_rsv_sys";
	//�˿�
	const unsigned int _port = 3306;
};