# Computer_reservation_System
两个星期重构了一下当初练手的项目，应用新的特性、新的结构和Mysql数据库。
### 1、应用的技术
使用了STL、MySql、auto、封装、继承、多态、指针、引用
#### 1）常用容器vector
容器的声明：
```
    //学生容器
	vector<Person*> _vctr_student;
    //教师容器
	vector<Person*> _vctr_teacher;
	//管理员容器
	vector<Person*> _vctr_admin;

	//全部用户容器
	vector<Person*> _persons[3] = {
		_vctr_student,
		_vctr_teacher,
		_vctr_admin
	};
```
迭代器的使用：
```
    for (int i = 0; i < 3; i++) {
		cout << user[i] << "：" << endl;
		for (vector<Person*>::iterator it = _persons[i].begin(); it != _persons[i].end(); it++) {
		(*it)->showIdentity();
	    }
	}
```
#### 2）MySql Api
接口中的一些字段
```
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
```
接口的封装
```
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
```
两个封装的查询语句
```
//自定义查询语句_获取结果集
bool my_MySql::quire_res(const char* sentence) {
	if (mysql_query(_mysqlHeadle, sentence)) {
		//cout << "查询出错" << endl;
		//system("pause");
		return false;
	}
	//获取结果集
	_res = mysql_store_result(_mysqlHeadle);
	//结果集的行数
	_rowNum = mysql_num_rows(_res);
	if (!_rowNum) {        //行数不为空证明查询到匹配项
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
```
执行自定义sql语句
```
sprintf_s(mysql->_sentence, "select * from computerorder where id = %d", _id);
	if (!(mysql->quire_res(mysql->_sentence))) {
		delete mysql;
		mysql = nullptr;
		return false;
	}
```
对结果集的处理
```
//获取行
mysql->_row = mysql->getRow();
do {		//注入_vctr_orders容器中
	_vctr_orders.push_back(
	    computerOrder(
	        atoi(mysql->_row[0]), 
    	    atoi(mysql->_row[1]), 
    	    atoi(mysql->_row[2]), 
    	    atoi(mysql->_row[3]), 
	        atoi(mysql->_row[4])));
} while (((mysql->_row = mysql_fetch_row(mysql->_res))));
```
#### 3）新特性auto等
释放动态分配的内存
```
for (int i = 0; i < 3; i++) {
	vector<Person*>& vctr = _persons[i];
	for (auto person : vctr) {
		delete person;
	}
	vctr.clear();
}
```
#### 4）继承
定义抽象类
```
#pragma once
#include"my_MySql.h"

class Person {
public:
    //修改身份信息
	virtual bool init(Person*& person) = 0;
	//显示身份信息
	virtual void showIdentity() = 0;
	//虚析构函数
	virtual ~Person() {}
protected:
	//id
	int _id;
	//编号
	int _num;
	//密码
	char* _pwd;
	//姓名
	char* _name;
};
```
继承抽象类，并实例化纯虚函数

![继承关系](https://user-images.githubusercontent.com/54742361/222948540-d44de5bf-f750-4b5a-9e90-d29551d30668.png)
#### 5）多态
使用父类指针指向子类对象
```
Person* person = nullptr;    //父类指针

person = Student::login();

//登陆验证
Student* Student::login() {        //返回一个子类对象的指针
	int id;
	char pwd[20];

	cout << "请输入你的ID：";
	cin >> id;
	cout << "请输入密码：";
	cin >> pwd;
	if (!Student::login(id, pwd))
		return nullptr;
	cout << "登录成功" << endl;
	system("pause");
	return (new Student(id, pwd));
}
```
#### 6）引用
使用引用，避免拷贝重复申请内存，变量复用性高，使用灵活且方便：
```
//选择
static bool Select(Person*& person);
```
### 2、实现的基本功能
#### 1）学生
1. 申请预约
2. 查看我的预约
3. 查看所有预约
4. 取消预约
5. 查看我的信息
6. 修改我的信息
#### 2）教师
1. 查看所有预约
2. 审核预约
3. 查看我的信息
4. 修改我的信息
#### 3）管理员
1. 添加账号
2. 查看账号
3. 查看机房
4. 清空预约
5. 查看我的信息
6. 修改我的信息


