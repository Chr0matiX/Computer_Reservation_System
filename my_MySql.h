//mysql类
//用来处理mysql查询、写入等操作

#pragma once
#include<mysql.h>
#include<iostream>

using std::cout;
using std::endl;

//mysql类
class my_MySql {
public:
	my_MySql();
	~my_MySql();
	/// <summary>
	/// 连接mysql数据库
	/// </summary>
	/// <param name="headle">sql句柄</param>
	/// <param name="host">数据库地址</param>
	/// <param name="user">用户名</param>
	/// <param name="pwd">密码</param>
	/// <param name="db">数据库名</param>
	/// <param name="port">端口号</param>
	/// <returns></returns>
	bool connet(
		const char* host,
		const char* user,
		const char* pwd,
		const char* db,
		const unsigned int port);
	//运行自定义查询语句
	bool quire_res(const char* sentence);
	bool quire(const char* sentence);
	//获取结果的行
	MYSQL_ROW getRow();
	//获取结果的列数
	int getFieldNum();

	char* tableName;
	char _sentence[150];

	//结果行
	MYSQL_ROW _row;
	//结果的列数
	int _fieldNum;
	//结果的行数
	int _rowNum;
	//查询的结果集
	MYSQL_RES* _res;
	//sql句柄
	MYSQL* _mysqlHeadle;
	//连接状态
	bool _connetState;

	//地址
	const char* _host = "127.0.0.1";
	//用户名
	const char* _user = "root";
	//密码
	const char* _pwd = "root";
	//数据库名
	const char* _databaseName = "Computer_rsv_sys";
	//端口
	const unsigned int _port = 3306;
};