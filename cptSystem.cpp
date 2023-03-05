#include"cptSystem.h"

const char* cptSystem::_menu[] = {
	{"====================  ��ӭ��������ԤԼϵͳ  =================="},
	{"��ѡ���������"},
	{"\t\t -------------------------------"},
	{"\t\t|                               |"},
	{"\t\t|          1.ѧ������           |"},
	{"\t\t|                               |"},
	{"\t\t|          2.��    ʦ           |"},
	{"\t\t|                               |"},
	{"\t\t|          3.�� �� Ա           |"},
	{"\t\t|                               |"},
	{"\t\t|          0.��    ��           |"},
	{"\t\t|                               |"},
	{"\t\t -------------------------------"},
	{"���������ѡ��"}
};

cptSystem::cptSystem() {

}

cptSystem::~cptSystem() {

}

//��ʾ���˵�
void cptSystem::showMenu(const char* menu[]) {
	for (int i = 0; i < 14; i++) {
		cout << menu[i] << endl;
	}
}

bool cptSystem::Select(Person*& person) {
	int slct = 0;
	cin >> slct;
	system("cls");
	switch (slct)
	{
	case 1:			//ѧ��
	{
		//��¼��֤
		person = Student::login();
		if (!person) {
			cout << "��½ʧ�ܣ�������" << endl;
			system("pause");
			break;
		}
		//����˵�ѭ��
		do {
			system("cls");
			Student::showMenu(Student::_menu);
		} while (Student::select(person));
		break;
	}
	case 2:			//��ʦ
	{
		person = Teacher::login();
		if (!person) {
			cout << "��½ʧ�ܣ�������" << endl;
			system("pause");
			break;
		}
		do {
			system("cls");
			Teacher::showMenu(Teacher::_menu);
		} while (Teacher::select(person));
		break;
	}
	case 3:			//����Ա
	{
		person = Admin::login();
		if (!person) {
			cout << "��½ʧ�ܣ�������" << endl;
			system("pause");
			break;
		}
		do {
			system("cls");
			Admin::showMenu(Admin::_menu);
		} while (Admin::select(person));
		break;
	}
	case 0:			//�˳�
	{
		cout << "��ӭ�´�ʹ��" << endl;
		system("pause");
		return false;
	}
	default: {
		cout << "��������������ѡ��" << endl;
		system("pause");
		break;
	}
	}
	return true;
}