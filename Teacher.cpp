#include"Teacher.h"

const char* Teacher::_menu[] = {
	{"\t\t-----------------------------------"},
	{"\t\t|                                 |"},
	{"\t\t|          1.�鿴����ԤԼ         |"},
	{"\t\t|                                 |"},
	{"\t\t|          2.���ԤԼ             |"},
	{"\t\t|                                 |"},
	{"\t\t|          3.�鿴�ҵ���Ϣ         |"},
	{"\t\t|                                 |"},
	{"\t\t|          4.�޸��ҵ���Ϣ         |"},
	{"\t\t|                                 |"},
	{"\t\t|          0.ע����¼             |"},
	{"\t\t|                                 |"},
	{"\t\t-----------------------------------"},
	{"���������ѡ��"}
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
//��½��֤
Person* Teacher::login() {
	int id;
	char pwd[20];

	cout << "���������ID��";
	cin >> id;
	cout << "���������룺";
	cin >> pwd;
	if (!Teacher::login(id, pwd))
		return nullptr;
	cout << "��¼�ɹ�" << endl;
	system("pause");
	return (new Teacher(id, pwd));
}

//��ѯid��pwd
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
//�޸��������
bool Teacher::init(Person*& person) {
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
		sprintf_s(mysql->_sentence, "select * from teacher where id = %d", id);
		if (mysql->quire_res(mysql->_sentence)) {
			delete mysql;
			mysql = nullptr;
			cout << "��id���ظ�" << endl;
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
	//���µ�ǰ����
	delete person;
	person = nullptr;
	person = new Teacher(id, pwd);
	return true;
}
//��ʾ�����Ϣ
void Teacher::showIdentity() {
	cout << "num = " << _num << "\tid = " << _id << "\tpwd = " << _pwd << "\tname = " << _name << endl;
}

//Person::Menu::
//��ʾ�˵�
void Teacher::showMenu(const char* menu[]) {
	for (int i = 0; i < 14; i++) {
		cout << menu[i] << endl;
	}
}

//�˵�ѡ��
bool Teacher::select(Person*& person) {
	int select = 0;
	cin >> select;
	system("cls");
	switch (select)
	{
	case 1:		//�鿴����ԤԼ
	{
		((Teacher*)person)->getAllOrder(1);		//��ȡȫ��ԤԼ
		((Teacher*)person)->showAllOrder();
		break;
	}
	case 2:		//���ԤԼ
	{
		((Teacher*)person)->getAllOrder(0);		//��ȡδͨ����˵�ԤԼ
		((Teacher*)person)->showAllOrder();
		if (!((Teacher*)person)->validOrder()) {
			cout << "δ��ɵ�ǰ���" << endl;
		}
		else {
			cout << "��ɵ�ǰ���" << endl;
		}
		system("pause");
		break;
	}
	case 3:		//�鿴������Ϣ
	{
		person->showIdentity();
		system("pause");
		break;
	}
	case 4:		//�޸ĸ�����Ϣ
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

//��ȡԤԼ��0Ϊ��ȡδ���ԤԼ��1Ϊͨ����˵�ԤԼ��
bool Teacher::getAllOrder(int i) {
	//�������ݿ�
	my_MySql* mysql = new my_MySql();
	if (!(mysql->connet(mysql->_host, mysql->_user, mysql->_pwd, mysql->_databaseName, mysql->_port))) {
		delete mysql;
		mysql = nullptr;
		return false;
	}
	if (i) {		//��ѯ����
		sprintf_s(mysql->_sentence, "select * from computerorder");
	}
	else {			//������ѯδ���
		sprintf_s(mysql->_sentence, "select * from computerorder where state = 0");
	}
	if (!(mysql->quire_res(mysql->_sentence))) {
		delete mysql;
		mysql = nullptr;
		return false;
	}
	//��ȡ�к�����
	mysql->_fieldNum = mysql->getFieldNum();
	mysql->_row = mysql->getRow();
	//���һ������
	if (!(_vctr_AllOrders.empty())) {
		_vctr_AllOrders.clear();
	}
	do {		//ע��_vctr_orders������
		_vctr_AllOrders.push_back(computerOrder(atoi(mysql->_row[0]), atoi(mysql->_row[1]), atoi(mysql->_row[2]), atoi(mysql->_row[3]), atoi(mysql->_row[4])));
	} while (((mysql->_row = mysql_fetch_row(mysql->_res))));
	delete mysql;
	mysql = nullptr;
	return true;
}

//�鿴����ԤԼ
void Teacher::showAllOrder() {
	int i = 1;
	for (vector<computerOrder>::iterator it = _vctr_AllOrders.begin(); it != _vctr_AllOrders.end(); it++) {
		cout << "[" << i << "]��\t";
		it->showOrder();
		i++;
	}
	system("pause");
}
//���ԤԼ
bool Teacher::validOrder() {
	cout << "��Ҫ��˵ڼ���ԤԼ��" << endl
		<< "��������ţ�";
	int select;
	cin >> select;
	if (!(select > 0 && select < _vctr_AllOrders.size())) {
		cout << "����������������ȷ�����" << endl;
		return false;
	}
	my_MySql* mysql = new my_MySql();
	sprintf_s(mysql->_sentence, "update computerorder set state = 1 where id = %d and day = %d and dn = %d", _vctr_AllOrders[select - 1]._id, _vctr_AllOrders[select - 1]._day, _vctr_AllOrders[select - 1]._dn);
	cout << "���ͨ����ԤԼ��" << endl;
	_vctr_AllOrders[select - 1].showOrder();
	cout << "[1]--���ͨ��" << endl
		<< "[��������]--ȡ�����" << endl
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