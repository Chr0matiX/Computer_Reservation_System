#include"Admin.h"

const char* Admin::_menu[] = {
	{"\t\t-----------------------------------"},
	{"\t\t|                                 |"},
	{"\t\t|          1.����˺�             |"},
	{"\t\t|                                 |"},
	{"\t\t|          2.�鿴�˺�             |"},
	{"\t\t|                                 |"},
	{"\t\t|          3.�鿴����             |"},
	{"\t\t|                                 |"},
	{"\t\t|          4.���ԤԼ             |"},
	{"\t\t|                                 |"},
	{"\t\t|          5.�鿴�ҵ���Ϣ         |"},
	{"\t\t|                                 |"},
	{"\t\t|          6.�޸��ҵ���Ϣ         |"},
	{"\t\t|                                 |"},
	{"\t\t|          0.ע����¼             |"},
	{"\t\t|                                 |"},
	{"\t\t-----------------------------------"},
	{"���������ѡ��"}
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

//��½��֤
Person* Admin::login() {
	int id;
	char pwd[20];

	cout << "���������ID��";
	cin >> id;
	cout << "���������룺";
	cin >> pwd;
	if (!Admin::login(id, pwd))
		return nullptr;
	cout << "��¼�ɹ�" << endl;
	system("pause");
	return (new Admin(id, pwd));
}

//��ѯid��pwd
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

//�޸��������
bool Admin::init(Person*& person) {
	int id;
	char pwd[20];
	char name[20];
	cout << endl
		<< "�밴��ʾ�����޸ĵ���Ϣ" << endl
		<< "�����롾id����";
	cin >> id;
	cout << "�����롾pwd����";
	cin >> pwd;
	cout << "�����롾name����";
	cin >> name;
	cout << endl
		<< "�޸ĺ����ϢΪ��"
		<< "id = " << id << endl
		<< "pwd = " << pwd << endl
		<< "name = " << name << endl;
	cout << "[��������]--�������޸�" << endl
		<< "[1]--�����޸�" << endl
		<< "ȷ�ϱ����޸���";
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
	//�ж��ظ�
	if (id != this->_id) {
		sprintf_s(mysql->_sentence, "select * from admin where id = %d", id);
		if (mysql->quire_res(mysql->_sentence)) {
			delete mysql;
			mysql = nullptr;
			cout << "��id���ظ�" << endl;
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
	//���µ�ǰ����
	delete person;
	person = nullptr;
	person = new Admin(id, pwd);
	return true;
}

//��ʾ�����Ϣ
void Admin::showIdentity() {
	cout << "num = " << _num << "\tid = " << _id << "\tpwd = " << _pwd << "\tname = " << _name << endl;
}

//��ʾ�˵�
void Admin::showMenu(const char* menu[]) {
	for (int i = 0; i < 18; i++) {
		cout << menu[i] << endl;
	}
}

//�˵�ѡ��
bool Admin::select(Person*& person) {
	int select = 0;
	cin >> select;
	system("cls");
	switch (select)
	{
	case 1:		//����˺�
	{
		if (!((Admin*)person)->addPerson()) {
			cout << "���ʧ�ܣ����Ժ�����" << endl;
		}
		else {
			cout << "��ӳɹ�" << endl;
		}
		system("pause");
		break;
	}
	case 2:		//�鿴�˺�
	{
		((Admin*)person)->showPerson();
		break;
	}
	case 3:		//�鿴����
	{
		((Admin*)person)->showComputer();
		break;
	}
	case 4:		//���ԤԼ
	{
		if (!((Admin*)person)->cleanFile()) {
			cout << "���ʧ�ܣ����Ժ�����" << endl;
			system("pause");
		}
		else {
			cout << "��ճɹ�" << endl;
			system("pause");
		}
		break;
	}
	case 5:		//�鿴������Ϣ
	{
		person->showIdentity();
		system("pause");
		break;
	}
	case 6:		//�޸ĸ�����Ϣ
	{
		//������ʾ������Ϣ
		person->showIdentity();
		if (!person->init(person)) {
			cout << "δ�޸ĸ�����Ϣ" << endl;
		}
		else {
			cout << "�޸ĳɹ�" << endl;
		}
		system("pause");
		break;
	}
	case 0:		//�˳�ϵͳ
	{
		delete person;
		cout << "�˳��ɹ�" << endl;
		system("pause");
		return false;
	}
	default:
	{
		cout << "ѡ������" << endl;
		system("pause");
		break;
	}
	}
	return true;
}

//����˺�  
bool Admin::addPerson() {
	int select;
	do {
		cout << "[1]--���ѧ��" << endl
			<< "[2]--��ӽ�ʦ" << endl
			<< "[0]--ȡ�����" << endl
			<< "���������ѡ��" << endl;
		cin >> select;
		switch (select)
		{
		case 0:		//ȡ�����
			cout << "δ����û�" << endl;
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
				cout << "�������ѧ��" << endl;
				mysql->tableName = (char*)"student";
			}
			else {
				cout << "���������ʦ" << endl;
				mysql->tableName = (char*)"teacher";
			}
			cout << "�����롾id����";
			cin >> id;
			cout << "�����롾pwd����";
			cin >> pwd;
			cout << "�����롾name����";
			cin >> name;
			cout << endl << "��ǰ��ӵ���ϢΪ" << endl
				<< "id = " << id << endl
				<< "pwd = " << pwd << endl
				<< "name = " << name << endl << endl;
			cout << "[��������]--�����" << endl
				<< "[1]--���" << endl
				<< "ȷ�������";
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
			cout << "�����������������" << endl;
			system("pause");
			break;
		}
	} while (true);
}

//��ȡ�û�����
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

//�鿴�˺�
void Admin::showPerson() {
	//��ȡȫ���û�
	getPerson();
	for (int i = 0; i < 3; i++) {
		cout << user[i] << "��" << endl;
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

//�鿴������Ϣ
void Admin::showComputer() {
	for (int i = 1; i < 4; i++) {
		computerRoom cmproom(i);
		if (!cmproom.initRsv()) {
			cout << "�������ݳ�ʼ��ʧ��" << endl;
			system("pause");
			return;
		}
		cmproom.showInfo();
		cout << endl;
	}
	system("pause");
}

//���ԤԼ��¼
bool Admin::cleanFile() {
	//�򵥵�ɾ����֤
	cout << "ȷ�����ԤԼ��" << endl;
	cout << "���������������ȷ�ϣ�";
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
	//�������ԤԼ��¼
	sprintf_s(mysql->_sentence, "delete from computerorder");
	if (!(mysql->quire(mysql->_sentence))) {
		delete mysql;
		mysql = nullptr;
		return false;
	}
	//����ÿ���ԤԼ���
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