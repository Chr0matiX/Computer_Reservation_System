#include"my_MySql.h"

my_MySql::my_MySql() {
	_mysqlHeadle = new MYSQL();
	_connetState = false;
	_res = nullptr;
}

my_MySql::~my_MySql() {

}

bool my_MySql::connet(
	const char* host,
	const char* user,
	const char* pwd,
	const char* db,
	const unsigned int port) {
	//�ж�����״̬�����Ѿ����ӣ���ֱ�ӷ���true
	if (_connetState) {
		//cout << "���ݿ�������" << endl;
		return true;
	}
	//�������ӣ��򴴽�һ���µ�����
	//_mysqlHeadle = mysql_init(nullptr);
	mysql_init(_mysqlHeadle);
	if (!_mysqlHeadle) {
		//cout << "��ʼ��_mysqlHeadleʧ��" << endl;
		return false;
	}

	if (!(mysql_real_connect(_mysqlHeadle, host, user, pwd, db, port, NULL, 0))) {
		//cout << "�������ݿ�ʧ��" << endl;
		return false;
	}
	//cout << "���ݿ����ӳɹ�" << endl;
	_connetState = true;
	return true;
}

//�Զ����ѯ���_��ȡ�����
bool my_MySql::quire_res(const char* sentence) {
	if (mysql_query(_mysqlHeadle, sentence)) {
		//cout << "��ѯ����" << endl;
		//system("pause");
		return false;
	}
	_res = mysql_store_result(_mysqlHeadle);
	_rowNum = mysql_num_rows(_res);
	if (!_rowNum) {
		//cout << "δ�ҵ����û�" << endl;
		//system("pause");
		return false;
	}
	return true;
}

//����ѯ_��ȡ��ѯ�Ƿ�ɹ�
bool my_MySql::quire(const char* sentence) {
	if (mysql_query(_mysqlHeadle, sentence)) {
		return false;
	}
	return true;
}

MYSQL_ROW my_MySql::getRow() {
	return mysql_fetch_row(_res);
}

int my_MySql::getFieldNum() {
	return mysql_num_fields(_res);
}