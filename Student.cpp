#include"Student.h"

const char* Student::_menu[] = {
	{"\t\t-----------------------------------"},
	{"\t\t|                                 |"},
	{"\t\t|          1.申请预约             |"},
	{"\t\t|                                 |"},
	{"\t\t|          2.查看我的预约         |"},
	{"\t\t|                                 |"},
	{"\t\t|          3.查看所有预约         |"},
	{"\t\t|                                 |"},
	{"\t\t|          4.取消预约             |"},
	{"\t\t|                                 |"},
	{"\t\t|          5.查看我的信息         |"},
	{"\t\t|                                 |"},
	{"\t\t|          6.修改我的信息         |"},
	{"\t\t|                                 |"},
	{"\t\t|          0.注销登录             |"},
	{"\t\t|                                 |"},
	{"\t\t-----------------------------------"},
	{"请输入你的选择："}
};

Student::Student() {

}

Student::Student(int id, const char* pwd) {
	my_MySql* mysql = new my_MySql();
	mysql->connet(mysql->_host, mysql->_user, mysql->_pwd, mysql->_databaseName, mysql->_port);
	sprintf_s(mysql->_sentence, "select * from student where id = %d and pwd = '%s'", id, pwd);
	mysql->quire_res(mysql->_sentence);
	mysql->_row = mysql->getRow();
	this->_num = atoi(mysql->_row[Student::attr::num]);
	this->_id = atoi(mysql->_row[Student::attr::id]);
	this->_pwd = mysql->_row[Student::attr::pwd];
	this->_name = mysql->_row[Student::attr::name];
}

Student::Student(int num, int id, const char* pwd, const char* name) {
	this->_num = num;
	this->_id = id;
	this->_pwd = (char*)pwd;
	this->_name = (char*)name;
}

Student::~Student() {

}

//登陆验证
Student* Student::login() {
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


//查询id和pwd
bool Student::login(int id, const char* pwd) {
	my_MySql* mysql = new my_MySql();
	if (!(mysql->connet(mysql->_host, mysql->_user, mysql->_pwd, mysql->_databaseName, mysql->_port))) {
		delete mysql;
		mysql = nullptr;
		return false;
	}
	sprintf_s(mysql->_sentence, "select * from student where id = %d and pwd = '%s'", id, pwd);
	if (!(mysql->quire_res(mysql->_sentence))) {
		delete mysql;
		mysql = nullptr;
		return false;
	}
	delete mysql;
	mysql = nullptr;
	return true;
}

//修改身份数据
bool Student::init(Person*& person) {
	int id;
	char pwd[20];
	char name[20];
	cout << endl
		<< "请按提示输入修改的信息" << endl
		<< "请输入【id】：";
	cin >> id;
	cout << "请输入【pwd】：";
	cin >> pwd;
	cout << "请输入【name】：";
	cin >> name;
	cout << endl
		<< "修改后的信息为："
		<< "id = " << id << endl
		<< "pwd = " << pwd << endl
		<< "name = " << name << endl;
	cout << "[任意数字]--不保存修改" << endl
		<< "[1]--保存修改" << endl
		<< "确认保存修改吗？";
	int select;
	cin >> select;
	if (select != 1) {
		return false;
	}
	my_MySql* mysql = new my_MySql();
	if (!(mysql->connet(mysql->_host, mysql->_user, mysql->_pwd, mysql->_databaseName, mysql->_port))) {
		delete mysql;
		mysql = nullptr;
		return false;
	}
	//判定重复
	if (id != this->_id) {
		sprintf_s(mysql->_sentence, "select * from student where id = %d", id);
		if (mysql->quire_res(mysql->_sentence)) {
			delete mysql;
			mysql = nullptr;
			cout << "【id】重复" << endl;
			system("pause");
			return false;
		}
	}
	sprintf_s(mysql->_sentence, "update student set id = %d, pwd = %s, name = '%s' where num = %d", id, pwd, name, _num);
	if (!(mysql->quire(mysql->_sentence))) {
		delete mysql;
		mysql = nullptr;
		return false;
	}
	delete mysql;
	mysql = nullptr;
	//更新当前对象
	delete person;
	person = nullptr;
	person = new Student(id, pwd);
	return true;
}

//显示身份信息
void Student::showIdentity() {
	cout << "num = " << _num << "\tid = " << _id << "\tpwd = " << _pwd << "\tname = " << _name << endl;
}

//显示菜单
void Student::showMenu(const char* menu[]) {
	for (int i = 0; i < 18; i++) {
		cout << menu[i] << endl;
	}
}

//选择菜单
bool Student::select(Person*& person) {
	int select = 0;
	cin >> select;
	system("cls");
	switch (select)
	{
	case 1:		//申请预约
	{
		if (!((Student*)person)->applyOrder()) {
			cout << "预约失败" << endl;
		}
		else {
			cout << "预约成功" << endl;
		}
		system("pause");
		break;
	}
	case 2:		//查看我的预约
	{
		((Student*)person)->showMyOrder();
		break;
	}
	case 3:		//查看所有预约
	{
		((Student*)person)->showAllOrder();
		break;
	}
	case 4:		//取消预约
	{
		if (!((Student*)person)->cancelOrder()) {
			cout << "取消预约失败" << endl;
		}
		else {
			cout << "取消预约成功" << endl;
		}
		system("pause");
		break;
	}
	case 5:		//查看个人信息
	{
		person->showIdentity();
		system("pause");
		break;
	}
	case 6:		//修改个人信息
	{
		//首先显示个人信息
		person->showIdentity();
		if (!person->init(person)) {
			cout << "未修改个人信息" << endl;
		}
		else {
			cout << "修改成功" << endl;
		}
		system("pause");
		break;
	}
	case 0:		//退出系统
	{
		delete person;
		cout << "退出成功" << endl;
		system("pause");
		return false;
	}
	default:
	{
		cout << "选择有误" << endl;
		system("pause");
		break;
	}
	}
	return true;
}

//申请预约
bool Student::applyOrder() {
	//显示全部机房的信息
	showAllOrder();
	//录入申请
	int room = 0;
	int day = 0;
	int dn = 0;
	cout << "[1]--20容量" << endl
		<< "[2]--50容量" << endl
		<< "[3]--100容量" << endl
		<< "请输入选择的机房：";
	cin >> room;

	cout << "[1]--星期一" << endl
		<< "[2]--星期二" << endl
		<< "··· ···" << endl
		<< "请输入星期的数字：";
	cin >> day;

	cout << "[1]--上午" << endl
		<< "[2]--下午" << endl
		<< "请输入时间段：";
	cin >> dn;
	if (!((room == 1 || room == 2 || room == 3)
		&& (day == 1 || day == 2 || day == 3 || day == 4 || day == 5)
		&& (dn == 1 || dn == 2))) {
		cout << "请输入正确的房间和日期" << endl;
		system("pause");
		return false;
	}
	day--;		//校正输入与参数
	cout << "当前提交的预约为：\t" << computerRoom::_weekName[day] << " " << (dn == 1 ? "上午" : "下午") << endl
		<< "[1]--提交预约" << endl
		<< "[任意数字]--不提交预约" << endl;
	dn--;		//校正输入与参数
	int select;
	cin >> select;
	if (select != 1) {
		return false;
	}
	//连接数据库
	my_MySql* mysql = new my_MySql();
	if (!(mysql->connet(mysql->_host, mysql->_user, mysql->_pwd, mysql->_databaseName, mysql->_port))) {
		delete mysql;
		mysql = nullptr;
		return false;
	}
	//先查一下选择的机房预约人数是不是满了
	sprintf_s(mysql->_sentence, "select max, %s%s  from computerroom where num = %d", computerRoom::_day[day], computerRoom::_dn[dn], room);
	if (!(mysql->quire_res(mysql->_sentence))) {
		delete mysql;
		mysql = nullptr;
		return false;
	}
	mysql->_row = mysql->getRow();
	if ((atoi(mysql->_row[0]) - atoi(mysql->_row[1])) < 1) {
		cout << "当前预约已满，请选择别的时间或者机房" << endl;
		system("pause");
		delete mysql;
		mysql = nullptr;
		return false;
	}
	//是否重复添加预约
	sprintf_s(mysql->_sentence, "select * from computerorder where id = %d and day = %d and dn = %d", _id, day, dn);
	if (mysql->quire_res(mysql->_sentence)) {
		cout << "预约重复，清重新选择" << endl;
		system("pause");
		delete mysql;
		mysql = nullptr;
		return false;
	}
	//提交预约和更改预约人数的事务
	sprintf_s(mysql->_sentence, "START TRANSACTION");
	if (!(mysql->quire(mysql->_sentence))) {
		delete mysql;
		mysql = nullptr;
		return false;
	}
	//机房人数减一
	sprintf_s(mysql->_sentence, "update computerroom SET %s%s = %s%s + 1 WHERE num = %d;", computerRoom::_day[day], computerRoom::_dn[dn], computerRoom::_day[day], computerRoom::_dn[dn], room);
	if (!(mysql->quire(mysql->_sentence))) {
		delete mysql;
		mysql = nullptr;
		return false;
	}
	//提交预约
	mysql->_row = mysql->getRow();
	sprintf_s(mysql->_sentence, "insert into computerorder (id, room, day, dn, state) values (%d, %d, %d, %d, %d)", _id, room, day, dn, 0);
	if (!(mysql->quire(mysql->_sentence))) {
		delete mysql;
		mysql = nullptr;
		return false;
	}
	sprintf_s(mysql->_sentence, "COMMIT");
	if (!(mysql->quire(mysql->_sentence))) {
		delete mysql;
		mysql = nullptr;
		return false;
	}
	delete mysql;
	mysql = nullptr;
	return true;
}

//查看所有预约
void Student::showAllOrder() {
	for (int i = 1; i < 4; i++) {
		computerRoom cmp(i);
		if (!cmp.initRsv()) {
			cout << "机房数据初始化失败" << endl;
			system("pause");
			return;
		}
		cmp.showInfo();
		cout << endl;
	}
	system("pause");
}

//获取自己身预约
bool Student::getMyOrder() {
	//连接数据库
	my_MySql* mysql = new my_MySql();
	if (!(mysql->connet(mysql->_host, mysql->_user, mysql->_pwd, mysql->_databaseName, mysql->_port))) {
		delete mysql;
		mysql = nullptr;
		return false;
	}
	sprintf_s(mysql->_sentence, "select * from computerorder where id = %d", _id);
	if (!(mysql->quire_res(mysql->_sentence))) {
		delete mysql;
		mysql = nullptr;
		return false;
	}
	//获取行
	mysql->_row = mysql->getRow();
	//清空一下容器
	if (!(_vctr_orders.empty())) {
		_vctr_orders.clear();
	}
	do {		//注入_vctr_orders容器中
		_vctr_orders.push_back(computerOrder(atoi(mysql->_row[0]), atoi(mysql->_row[1]), atoi(mysql->_row[2]), atoi(mysql->_row[3]), atoi(mysql->_row[4])));
	} while (((mysql->_row = mysql_fetch_row(mysql->_res))));
	delete mysql;
	mysql = nullptr;
	return true;
}

//查看我的预约
void Student::showMyOrder() {
	//首先获取预约
	getMyOrder();
	int i = 1;
	for (vector<computerOrder>::iterator it = _vctr_orders.begin(); it != _vctr_orders.end(); it++) {
		cout << "[" << i << "]：\t";
		it->showOrder();
		i++;
	}
	system("pause");
}

//取消预约
bool Student::cancelOrder() {
	//首先显示自己的预约
	showMyOrder();
	cout << "想要删除第几号预约？" << endl
		<< "请输入序号：";
	int select;
	cin >> select;
	if (!(select > 0 && select < _vctr_orders.size())) {
		cout << "输入有误，请输入正确的序号" << endl;
		return false;
	}
	my_MySql* mysql = new my_MySql();
	sprintf_s(mysql->_sentence, "delete from computerorder where id = %d and day = %d and dn = %d", _vctr_orders[select - 1]._id, _vctr_orders[select - 1]._day, _vctr_orders[select - 1]._dn);
	cout << "即将删除：" << endl;
	_vctr_orders[select - 1].showOrder();
	cout << "[1]--确认删除" << endl
		<< "[其他数字]--取消删除" << endl
		<< "确认删除吗？";
	cin >> select;
	if (select != 1) {
		return false;
	}
	if (!(mysql->connet(mysql->_host, mysql->_user, mysql->_pwd, mysql->_databaseName, mysql->_port))) {
		delete mysql;
		mysql = nullptr;
		return false;
	}
	if (!(mysql->quire(mysql->_sentence))) {
		delete mysql;
		mysql = nullptr;
		return false;
	}
	return true;
}