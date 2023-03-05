#include<iostream>

#include"cptSystem.h"

using std::cout;
using std::cin;
using std::endl;

int main() {
	Person* person = nullptr;

	do {
		system("cls");
		cptSystem::showMenu(cptSystem::_menu);
	} while (cptSystem::Select(person));

	person = nullptr;
	return 0;
}