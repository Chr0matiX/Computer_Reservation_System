#include"cptSystem.h"

const char* cptSystem::_menu[] = {
	{"====================  欢迎来到机房预约系统  =================="},
	{"请选择您的身份"},
	{"\t\t -------------------------------"},
	{"\t\t|                               |"},
	{"\t\t|          1.学生代表           |"},
	{"\t\t|                               |"},
	{"\t\t|          2.老    师           |"},
	{"\t\t|                               |"},
	{"\t\t|          3.管 理 员           |"},
	{"\t\t|                               |"},
	{"\t\t|          0.退    出           |"},
	{"\t\t|                               |"},
	{"\t\t -------------------------------"},
	{"请输入你的选择："}
};

cptSystem::cptSystem() {

}

cptSystem::~cptSystem() {

}

//显示主菜单
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
	case 1:			//学生
	{
		//登录验证
		person = Student::login();
		if (!person) {
			cout << "登陆失败，请重试" << endl;
			system("pause");
			break;
		}
		//进入菜单循环
		do {
			system("cls");
			Student::showMenu(Student::_menu);
		} while (Student::select(person));
		break;
	}
	case 2:			//老师
	{
		person = Teacher::login();
		if (!person) {
			cout << "登陆失败，请重试" << endl;
			system("pause");
			break;
		}
		do {
			system("cls");
			Teacher::showMenu(Teacher::_menu);
		} while (Teacher::select(person));
		break;
	}
	case 3:			//管理员
	{
		person = Admin::login();
		if (!person) {
			cout << "登陆失败，请重试" << endl;
			system("pause");
			break;
		}
		do {
			system("cls");
			Admin::showMenu(Admin::_menu);
		} while (Admin::select(person));
		break;
	}
	case 0:			//退出
	{
		cout << "欢迎下次使用" << endl;
		system("pause");
		return false;
	}
	default: {
		cout << "输入有误，请重新选择！" << endl;
		system("pause");
		break;
	}
	}
	return true;
}