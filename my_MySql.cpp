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
	//判定连接状态，若已经连接，则直接返回true
	if (_connetState) {
		//cout << "数据库已连接" << endl;
		return true;
	}
	//若无连接，则创建一个新的连接
	//_mysqlHeadle = mysql_init(nullptr);
	mysql_init(_mysqlHeadle);
	if (!_mysqlHeadle) {
		//cout << "初始化_mysqlHeadle失败" << endl;
		return false;
	}

	if (!(mysql_real_connect(_mysqlHeadle, host, user, pwd, db, port, NULL, 0))) {
		//cout << "连接数据库失败" << endl;
		return false;
	}
	//cout << "数据库连接成功" << endl;
	_connetState = true;
	return true;
}

//自定义查询语句_获取结果集
bool my_MySql::quire_res(const char* sentence) {
	if (mysql_query(_mysqlHeadle, sentence)) {
		//cout << "查询出错" << endl;
		//system("pause");
		return false;
	}
	_res = mysql_store_result(_mysqlHeadle);
	_rowNum = mysql_num_rows(_res);
	if (!_rowNum) {
		//cout << "未找到该用户" << endl;
		//system("pause");
		return false;
	}
	return true;
}

//仅查询_获取查询是否成功
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