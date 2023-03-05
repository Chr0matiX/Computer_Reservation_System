#include"Student.h"

const char* Student::_menu[] = {
	{"\t\t-----------------------------------"},
	{"\t\t|                                 |"},
	{"\t\t|          1.����ԤԼ             |"},
	{"\t\t|                                 |"},
	{"\t\t|          2.�鿴�ҵ�ԤԼ         |"},
	{"\t\t|                                 |"},
	{"\t\t|          3.�鿴����ԤԼ         |"},
	{"\t\t|                                 |"},
	{"\t\t|          4.ȡ��ԤԼ             |"},
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

//��½��֤
Student* Student::login() {
	int id;
	char pwd[20];

	cout << "���������ID��";
	cin >> id;
	cout << "���������룺";
	cin >> pwd;
	if (!Student::login(id, pwd))
		return nullptr;
	cout << "��¼�ɹ�" << endl;
	system("pause");
	return (new Student(id, pwd));
}


//��ѯid��pwd
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

//�޸��������
bool Student::init(Person*& person) {
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
		sprintf_s(mysql->_sentence, "select * from student where id = %d", id);
		if (mysql->quire_res(mysql->_sentence)) {
			delete mysql;
			mysql = nullptr;
			cout << "��id���ظ�" << endl;
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
	//���µ�ǰ����
	delete person;
	person = nullptr;
	person = new Student(id, pwd);
	return true;
}

//��ʾ�����Ϣ
void Student::showIdentity() {
	cout << "num = " << _num << "\tid = " << _id << "\tpwd = " << _pwd << "\tname = " << _name << endl;
}

//��ʾ�˵�
void Student::showMenu(const char* menu[]) {
	for (int i = 0; i < 18; i++) {
		cout << menu[i] << endl;
	}
}

//ѡ��˵�
bool Student::select(Person*& person) {
	int select = 0;
	cin >> select;
	system("cls");
	switch (select)
	{
	case 1:		//����ԤԼ
	{
		if (!((Student*)person)->applyOrder()) {
			cout << "ԤԼʧ��" << endl;
		}
		else {
			cout << "ԤԼ�ɹ�" << endl;
		}
		system("pause");
		break;
	}
	case 2:		//�鿴�ҵ�ԤԼ
	{
		((Student*)person)->showMyOrder();
		break;
	}
	case 3:		//�鿴����ԤԼ
	{
		((Student*)person)->showAllOrder();
		break;
	}
	case 4:		//ȡ��ԤԼ
	{
		if (!((Student*)person)->cancelOrder()) {
			cout << "ȡ��ԤԼʧ��" << endl;
		}
		else {
			cout << "ȡ��ԤԼ�ɹ�" << endl;
		}
		system("pause");
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

//����ԤԼ
bool Student::applyOrder() {
	//��ʾȫ����������Ϣ
	showAllOrder();
	//¼������
	int room = 0;
	int day = 0;
	int dn = 0;
	cout << "[1]--20����" << endl
		<< "[2]--50����" << endl
		<< "[3]--100����" << endl
		<< "������ѡ��Ļ�����";
	cin >> room;

	cout << "[1]--����һ" << endl
		<< "[2]--���ڶ�" << endl
		<< "������ ������" << endl
		<< "���������ڵ����֣�";
	cin >> day;

	cout << "[1]--����" << endl
		<< "[2]--����" << endl
		<< "������ʱ��Σ�";
	cin >> dn;
	if (!((room == 1 || room == 2 || room == 3)
		&& (day == 1 || day == 2 || day == 3 || day == 4 || day == 5)
		&& (dn == 1 || dn == 2))) {
		cout << "��������ȷ�ķ��������" << endl;
		system("pause");
		return false;
	}
	day--;		//У�����������
	cout << "��ǰ�ύ��ԤԼΪ��\t" << computerRoom::_weekName[day] << " " << (dn == 1 ? "����" : "����") << endl
		<< "[1]--�ύԤԼ" << endl
		<< "[��������]--���ύԤԼ" << endl;
	dn--;		//У�����������
	int select;
	cin >> select;
	if (select != 1) {
		return false;
	}
	//�������ݿ�
	my_MySql* mysql = new my_MySql();
	if (!(mysql->connet(mysql->_host, mysql->_user, mysql->_pwd, mysql->_databaseName, mysql->_port))) {
		delete mysql;
		mysql = nullptr;
		return false;
	}
	//�Ȳ�һ��ѡ��Ļ���ԤԼ�����ǲ�������
	sprintf_s(mysql->_sentence, "select max, %s%s  from computerroom where num = %d", computerRoom::_day[day], computerRoom::_dn[dn], room);
	if (!(mysql->quire_res(mysql->_sentence))) {
		delete mysql;
		mysql = nullptr;
		return false;
	}
	mysql->_row = mysql->getRow();
	if ((atoi(mysql->_row[0]) - atoi(mysql->_row[1])) < 1) {
		cout << "��ǰԤԼ��������ѡ����ʱ����߻���" << endl;
		system("pause");
		delete mysql;
		mysql = nullptr;
		return false;
	}
	//�Ƿ��ظ����ԤԼ
	sprintf_s(mysql->_sentence, "select * from computerorder where id = %d and day = %d and dn = %d", _id, day, dn);
	if (mysql->quire_res(mysql->_sentence)) {
		cout << "ԤԼ�ظ���������ѡ��" << endl;
		system("pause");
		delete mysql;
		mysql = nullptr;
		return false;
	}
	//�ύԤԼ�͸���ԤԼ����������
	sprintf_s(mysql->_sentence, "START TRANSACTION");
	if (!(mysql->quire(mysql->_sentence))) {
		delete mysql;
		mysql = nullptr;
		return false;
	}
	//����������һ
	sprintf_s(mysql->_sentence, "update computerroom SET %s%s = %s%s + 1 WHERE num = %d;", computerRoom::_day[day], computerRoom::_dn[dn], computerRoom::_day[day], computerRoom::_dn[dn], room);
	if (!(mysql->quire(mysql->_sentence))) {
		delete mysql;
		mysql = nullptr;
		return false;
	}
	//�ύԤԼ
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

//�鿴����ԤԼ
void Student::showAllOrder() {
	for (int i = 1; i < 4; i++) {
		computerRoom cmp(i);
		if (!cmp.initRsv()) {
			cout << "�������ݳ�ʼ��ʧ��" << endl;
			system("pause");
			return;
		}
		cmp.showInfo();
		cout << endl;
	}
	system("pause");
}

//��ȡ�Լ���ԤԼ
bool Student::getMyOrder() {
	//�������ݿ�
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
	//��ȡ��
	mysql->_row = mysql->getRow();
	//���һ������
	if (!(_vctr_orders.empty())) {
		_vctr_orders.clear();
	}
	do {		//ע��_vctr_orders������
		_vctr_orders.push_back(computerOrder(atoi(mysql->_row[0]), atoi(mysql->_row[1]), atoi(mysql->_row[2]), atoi(mysql->_row[3]), atoi(mysql->_row[4])));
	} while (((mysql->_row = mysql_fetch_row(mysql->_res))));
	delete mysql;
	mysql = nullptr;
	return true;
}

//�鿴�ҵ�ԤԼ
void Student::showMyOrder() {
	//���Ȼ�ȡԤԼ
	getMyOrder();
	int i = 1;
	for (vector<computerOrder>::iterator it = _vctr_orders.begin(); it != _vctr_orders.end(); it++) {
		cout << "[" << i << "]��\t";
		it->showOrder();
		i++;
	}
	system("pause");
}

//ȡ��ԤԼ
bool Student::cancelOrder() {
	//������ʾ�Լ���ԤԼ
	showMyOrder();
	cout << "��Ҫɾ���ڼ���ԤԼ��" << endl
		<< "��������ţ�";
	int select;
	cin >> select;
	if (!(select > 0 && select < _vctr_orders.size())) {
		cout << "����������������ȷ�����" << endl;
		return false;
	}
	my_MySql* mysql = new my_MySql();
	sprintf_s(mysql->_sentence, "delete from computerorder where id = %d and day = %d and dn = %d", _vctr_orders[select - 1]._id, _vctr_orders[select - 1]._day, _vctr_orders[select - 1]._dn);
	cout << "����ɾ����" << endl;
	_vctr_orders[select - 1].showOrder();
	cout << "[1]--ȷ��ɾ��" << endl
		<< "[��������]--ȡ��ɾ��" << endl
		<< "ȷ��ɾ����";
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