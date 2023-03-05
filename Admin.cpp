#include"Admin.h"

const char* Admin::_menu[] = {
	{"\t\t-----------------------------------"},
	{"\t\t|                                 |"},
	{"\t\t|          1.添加账号             |"},
	{"\t\t|                                 |"},
	{"\t\t|          2.查看账号             |"},
	{"\t\t|                                 |"},
	{"\t\t|          3.查看机房             |"},
	{"\t\t|                                 |"},
	{"\t\t|          4.清空预约             |"},
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

Admin::Admin() {

}

Admin::Admin(int id, const char* pwd) {
	my_MySql* mysql = new my_MySql();
	mysql->connet(mysql->_host, mysql->_user, mysql->_pwd, mysql->_databaseName, mysql->_port);
	sprintf_s(mysql->_sentence, "select * from admin where id = %d and pwd = %s", id, pwd);
	mysql->quire_res(mysql->_sentence);
	mysql->_row = mysql->getRow();
	this->_num = atoi(mysql->_row[Admin::attr::num]);
	this->_id = atoi(mysql->_row[Admin::attr::id]);
	this->_pwd = mysql->_row[Admin::attr::pwd];
	this->_name = mysql->_row[Admin::attr::name];
}

Admin::Admin(int num, int id, const char* pwd, const char* name) {
	this->_num = num;
	this->_id = id;
	this->_pwd = (char*)pwd;
	this->_name = (char*)name;
}

Admin::~Admin() {

}

//登陆验证
Person* Admin::login() {
	int id;
	char pwd[20];

	cout << "请输入你的ID：";
	cin >> id;
	cout << "请输入密码：";
	cin >> pwd;
	if (!Admin::login(id, pwd))
		return nullptr;
	cout << "登录成功" << endl;
	system("pause");
	return (new Admin(id, pwd));
}

//查询id和pwd
bool Admin::login(int id, const char* pwd) {
	my_MySql* mysql = new my_MySql();
	if (!(mysql->connet(mysql->_host, mysql->_user, mysql->_pwd, mysql->_databaseName, mysql->_port))) {
		delete mysql;
		mysql = nullptr;
		return false;
	}
	sprintf_s(mysql->_sentence, "select * from admin where id = %d and pwd = %s", id, pwd);
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
bool Admin::init(Person*& person) {
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
		sprintf_s(mysql->_sentence, "select * from admin where id = %d", id);
		if (mysql->quire_res(mysql->_sentence)) {
			delete mysql;
			mysql = nullptr;
			cout << "【id】重复" << endl;
			system("pause");
			return false;
		}
	}
	sprintf_s(mysql->_sentence, "update admin set id = %d, pwd = %s, name = '%s' where num = %d", id, pwd, name, _num);
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
	person = new Admin(id, pwd);
	return true;
}

//显示身份信息
void Admin::showIdentity() {
	cout << "num = " << _num << "\tid = " << _id << "\tpwd = " << _pwd << "\tname = " << _name << endl;
}

//显示菜单
void Admin::showMenu(const char* menu[]) {
	for (int i = 0; i < 18; i++) {
		cout << menu[i] << endl;
	}
}

//菜单选择
bool Admin::select(Person*& person) {
	int select = 0;
	cin >> select;
	system("cls");
	switch (select)
	{
	case 1:		//添加账号
	{
		if (!((Admin*)person)->addPerson()) {
			cout << "添加失败，请稍后重试" << endl;
		}
		else {
			cout << "添加成功" << endl;
		}
		system("pause");
		break;
	}
	case 2:		//查看账号
	{
		((Admin*)person)->showPerson();
		break;
	}
	case 3:		//查看机房
	{
		((Admin*)person)->showComputer();
		break;
	}
	case 4:		//清空预约
	{
		if (!((Admin*)person)->cleanFile()) {
			cout << "清空失败，清稍后重试" << endl;
			system("pause");
		}
		else {
			cout << "清空成功" << endl;
			system("pause");
		}
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

//添加账号  
bool Admin::addPerson() {
	int select;
	do {
		cout << "[1]--添加学生" << endl
			<< "[2]--添加教师" << endl
			<< "[0]--取消添加" << endl
			<< "请输入你的选择：" << endl;
		cin >> select;
		switch (select)
		{
		case 0:		//取消添加
			cout << "未添加用户" << endl;
			system("pause");
			return false;
		case 1:	case 2:
		{
			int id;
			char pwd[20];
			char name[20];
			my_MySql* mysql = new my_MySql();
			if (!(mysql->connet(mysql->_host, mysql->_user, mysql->_pwd, mysql->_databaseName, mysql->_port))) {
				delete mysql;
				mysql = nullptr;
				return false;
			}
			if (select == 1) {
				cout << "正在添加学生" << endl;
				mysql->tableName = (char*)"student";
			}
			else {
				cout << "正在添加老师" << endl;
				mysql->tableName = (char*)"teacher";
			}
			cout << "请输入【id】：";
			cin >> id;
			cout << "请输入【pwd】：";
			cin >> pwd;
			cout << "请输入【name】：";
			cin >> name;
			cout << endl << "当前添加的信息为" << endl
				<< "id = " << id << endl
				<< "pwd = " << pwd << endl
				<< "name = " << name << endl << endl;
			cout << "[任意数字]--不添加" << endl
				<< "[1]--添加" << endl
				<< "确认添加吗？";
			int sel;
			cin >> sel;
			if (sel != 1) {
				return false;
			}
			sprintf_s(mysql->_sentence, "insert into %s (id, pwd, name) values (%d, '%s', '%s')", mysql->tableName, id, pwd, name);
			if (!(mysql->quire(mysql->_sentence))) {
				delete mysql;
				mysql = nullptr;
				return false;
			}
			delete mysql;
			mysql = nullptr;
			return true;
		}
		default:
			cout << "输入错误，请重新输入" << endl;
			system("pause");
			break;
		}
	} while (true);
}

//获取用户容器
bool Admin::getPerson() {
	my_MySql* mysql = new my_MySql();
	if (!(mysql->connet(mysql->_host, mysql->_user, mysql->_pwd, mysql->_databaseName, mysql->_port))) {
		delete mysql;
		mysql = nullptr;
		return false;
	}
	for (int i = 0; i < 3; i++) {
		sprintf_s(mysql->_sentence, "select * from %s", user[i]);
		if (!(mysql->quire_res(mysql->_sentence))) {
			delete mysql;
			mysql = nullptr;
			return false;
		}
		mysql->_fieldNum = mysql->getFieldNum();
		mysql->_row = mysql->getRow();
		do {
			switch (i)
			{
			case 0:
				this->_persons[i].push_back(new Student(atoi(mysql->_row[attr::num]), atoi(mysql->_row[attr::id]), mysql->_row[attr::pwd], mysql->_row[attr::name]));
				break;
			case 1:
				this->_persons[i].push_back(new Teacher(atoi(mysql->_row[attr::num]), atoi(mysql->_row[attr::id]), mysql->_row[attr::pwd], mysql->_row[attr::name]));
				break;
			case 2:
				this->_persons[i].push_back(new Admin(atoi(mysql->_row[attr::num]), atoi(mysql->_row[attr::id]), mysql->_row[attr::pwd], mysql->_row[attr::name]));
			}
		} while ((mysql->_row = mysql_fetch_row(mysql->_res)));
	}
	delete mysql;
	mysql = nullptr;
	return true;
}

//查看账号
void Admin::showPerson() {
	//获取全部用户
	getPerson();
	for (int i = 0; i < 3; i++) {
		cout << user[i] << "：" << endl;
		for (vector<Person*>::iterator it = _persons[i].begin(); it != _persons[i].end(); it++) {
			(*it)->showIdentity();
		}
		cout << endl;
	}
	system("pause");
	for (int i = 0; i < 3; i++) {
		vector<Person*>& vctr = _persons[i];
		for (auto person : vctr) {
			delete person;
		}
		vctr.clear();
	}
}

//查看机房信息
void Admin::showComputer() {
	for (int i = 1; i < 4; i++) {
		computerRoom cmproom(i);
		if (!cmproom.initRsv()) {
			cout << "机房数据初始化失败" << endl;
			system("pause");
			return;
		}
		cmproom.showInfo();
		cout << endl;
	}
	system("pause");
}

//清空预约记录
bool Admin::cleanFile() {
	//简单的删除验证
	cout << "确定清空预约？" << endl;
	cout << "请输入你的密码以确认：";
	char pwd[20];
	cin >> pwd;
	if (strcmp(pwd, _pwd) != 0) {
		return false;
	}
	my_MySql* mysql = new my_MySql();
	if (!(mysql->connet(mysql->_host, mysql->_user, mysql->_pwd, mysql->_databaseName, mysql->_port))) {
		delete mysql;
		mysql = nullptr;
		return false;
	}
	sprintf_s(mysql->_sentence, "START TRANSACTION");
	if (!(mysql->quire(mysql->_sentence))) {
		delete mysql;
		mysql = nullptr;
		return false;
	}
	//清空所有预约记录
	sprintf_s(mysql->_sentence, "delete from computerorder");
	if (!(mysql->quire(mysql->_sentence))) {
		delete mysql;
		mysql = nullptr;
		return false;
	}
	//重置每天的预约情况
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 2; j++) {
			sprintf_s(mysql->_sentence, "update computerroom set %s%s = 0", computerRoom::_day[i], computerRoom::_dn[j]);
			if (!(mysql->quire(mysql->_sentence))) {
				delete mysql;
				mysql = nullptr;
				return false;
			}
		}
	}
	sprintf_s(mysql->_sentence, "COMMIT");
	if (!(mysql->quire(mysql->_sentence))) {
		delete mysql;
		mysql = nullptr;
		return false;
	}
	return true;
}