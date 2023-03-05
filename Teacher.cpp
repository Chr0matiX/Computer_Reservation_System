#include"Teacher.h"

const char* Teacher::_menu[] = {
	{"\t\t-----------------------------------"},
	{"\t\t|                                 |"},
	{"\t\t|          1.查看所有预约         |"},
	{"\t\t|                                 |"},
	{"\t\t|          2.审核预约             |"},
	{"\t\t|                                 |"},
	{"\t\t|          3.查看我的信息         |"},
	{"\t\t|                                 |"},
	{"\t\t|          4.修改我的信息         |"},
	{"\t\t|                                 |"},
	{"\t\t|          0.注销登录             |"},
	{"\t\t|                                 |"},
	{"\t\t-----------------------------------"},
	{"请输入你的选择："}
};

Teacher::Teacher() {

}

Teacher::Teacher(int id, const char* pwd) {
	my_MySql* mysql = new my_MySql();
	mysql->connet(mysql->_host, mysql->_user, mysql->_pwd, mysql->_databaseName, mysql->_port);
	sprintf_s(mysql->_sentence, "select * from teacher where id = %d and pwd = %s", id, pwd);
	mysql->quire_res(mysql->_sentence);
	mysql->_row = mysql->getRow();
	this->_num = atoi(mysql->_row[Teacher::attr::num]);
	this->_id = atoi(mysql->_row[Teacher::attr::id]);
	this->_pwd = mysql->_row[Teacher::attr::pwd];
	this->_name = mysql->_row[Teacher::attr::name];
}

Teacher::Teacher(int num, int id, const char* pwd, const char* name) {
	this->_num = num;
	this->_id = id;
	this->_pwd = (char*)pwd;
	this->_name = (char*)name;
}

Teacher::~Teacher() {

}

//Person::
//登陆验证
Person* Teacher::login() {
	int id;
	char pwd[20];

	cout << "请输入你的ID：";
	cin >> id;
	cout << "请输入密码：";
	cin >> pwd;
	if (!Teacher::login(id, pwd))
		return nullptr;
	cout << "登录成功" << endl;
	system("pause");
	return (new Teacher(id, pwd));
}

//查询id和pwd
bool Teacher::login(int id, const char* pwd) {
	my_MySql* mysql = new my_MySql();
	if (!(mysql->connet(mysql->_host, mysql->_user, mysql->_pwd, mysql->_databaseName, mysql->_port))) {
		delete mysql;
		mysql = nullptr;
		return false;
	}
	sprintf_s(mysql->_sentence, "select * from teacher where id = %d and pwd = %s", id, pwd);
	if (!(mysql->quire_res(mysql->_sentence))) {
		delete mysql;
		mysql = nullptr;
		return false;
	}
	delete mysql;
	mysql = nullptr;
	return true;
}

//Person::Identity::
//修改身份数据
bool Teacher::init(Person*& person) {
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
		sprintf_s(mysql->_sentence, "select * from teacher where id = %d", id);
		if (mysql->quire_res(mysql->_sentence)) {
			delete mysql;
			mysql = nullptr;
			cout << "【id】重复" << endl;
			system("pause");
			return false;
		}
	}
	sprintf_s(mysql->_sentence, "update teacher set id = %d, pwd = %s, name = '%s' where num = %d", id, pwd, name, _num);
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
	person = new Teacher(id, pwd);
	return true;
}
//显示身份信息
void Teacher::showIdentity() {
	cout << "num = " << _num << "\tid = " << _id << "\tpwd = " << _pwd << "\tname = " << _name << endl;
}

//Person::Menu::
//显示菜单
void Teacher::showMenu(const char* menu[]) {
	for (int i = 0; i < 14; i++) {
		cout << menu[i] << endl;
	}
}

//菜单选择
bool Teacher::select(Person*& person) {
	int select = 0;
	cin >> select;
	system("cls");
	switch (select)
	{
	case 1:		//查看所有预约
	{
		((Teacher*)person)->getAllOrder(1);		//获取全部预约
		((Teacher*)person)->showAllOrder();
		break;
	}
	case 2:		//审核预约
	{
		((Teacher*)person)->getAllOrder(0);		//获取未通过审核的预约
		((Teacher*)person)->showAllOrder();
		if (!((Teacher*)person)->validOrder()) {
			cout << "未完成当前审核" << endl;
		}
		else {
			cout << "完成当前审核" << endl;
		}
		system("pause");
		break;
	}
	case 3:		//查看个人信息
	{
		person->showIdentity();
		system("pause");
		break;
	}
	case 4:		//修改个人信息
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

//获取预约（0为获取未审核预约，1为通过审核的预约）
bool Teacher::getAllOrder(int i) {
	//连接数据库
	my_MySql* mysql = new my_MySql();
	if (!(mysql->connet(mysql->_host, mysql->_user, mysql->_pwd, mysql->_databaseName, mysql->_port))) {
		delete mysql;
		mysql = nullptr;
		return false;
	}
	if (i) {		//查询所有
		sprintf_s(mysql->_sentence, "select * from computerorder");
	}
	else {			//仅仅查询未审核
		sprintf_s(mysql->_sentence, "select * from computerorder where state = 0");
	}
	if (!(mysql->quire_res(mysql->_sentence))) {
		delete mysql;
		mysql = nullptr;
		return false;
	}
	//获取行和列数
	mysql->_fieldNum = mysql->getFieldNum();
	mysql->_row = mysql->getRow();
	//清空一下容器
	if (!(_vctr_AllOrders.empty())) {
		_vctr_AllOrders.clear();
	}
	do {		//注入_vctr_orders容器中
		_vctr_AllOrders.push_back(computerOrder(atoi(mysql->_row[0]), atoi(mysql->_row[1]), atoi(mysql->_row[2]), atoi(mysql->_row[3]), atoi(mysql->_row[4])));
	} while (((mysql->_row = mysql_fetch_row(mysql->_res))));
	delete mysql;
	mysql = nullptr;
	return true;
}

//查看所有预约
void Teacher::showAllOrder() {
	int i = 1;
	for (vector<computerOrder>::iterator it = _vctr_AllOrders.begin(); it != _vctr_AllOrders.end(); it++) {
		cout << "[" << i << "]：\t";
		it->showOrder();
		i++;
	}
	system("pause");
}
//审核预约
bool Teacher::validOrder() {
	cout << "想要审核第几号预约？" << endl
		<< "请输入序号：";
	int select;
	cin >> select;
	if (!(select > 0 && select < _vctr_AllOrders.size())) {
		cout << "输入有误，请输入正确的序号" << endl;
		return false;
	}
	my_MySql* mysql = new my_MySql();
	sprintf_s(mysql->_sentence, "update computerorder set state = 1 where id = %d and day = %d and dn = %d", _vctr_AllOrders[select - 1]._id, _vctr_AllOrders[select - 1]._day, _vctr_AllOrders[select - 1]._dn);
	cout << "审核通过的预约：" << endl;
	_vctr_AllOrders[select - 1].showOrder();
	cout << "[1]--审核通过" << endl
		<< "[其他数字]--取消审核" << endl
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