#include"computerRoom.h"

const char* computerRoom::_weekName[5] = {
	"����һ",
	"���ڶ�",
	"������",
	"������",
	"������"
};

const char* computerRoom::_day[5] = {
	"mon",
	"tue",
	"wed",
	"thu",
	"fri"
};

const char* computerRoom::_dn[2] = {
	"_d",
	"_n"
};

computerRoom::computerRoom(int roomNum) {
	_roomNum = roomNum;
}

//���������Ϣ
void computerRoom::showInfo() {
	cout << "������ţ�" << _roomNum << "\t���������" << _maxNum << endl;
	for (int day = 0; day < 5; day++) {
		cout << _weekName[day] << "��";
		for (int dn = 0; dn < 2; dn++) {
			if (!dn) {
				cout << "\t������ԤԼ��" << _week[day][dn] << "\t��ʣ��" << _maxNum - _week[day][dn] << "\t";
			}
			else {
				cout << "\t������ԤԼ��" << _week[day][dn] << "\t��ʣ��" << _maxNum - _week[day][dn] << "\t";
			}
		}
		cout << endl;
	}
}

//��ȡ��ǰ��������Ϣ
bool computerRoom::initRsv() {
	//�Ȱ����ݿ�����
	my_MySql* mysql = new my_MySql();
	if (!(mysql->connet(mysql->_host, mysql->_user, mysql->_pwd, mysql->_databaseName, mysql->_port))) {
		delete mysql;
		mysql = nullptr;
		return false;
	}
	//Ȼ���ҵ���ǰ��������Ϣ
	sprintf_s(mysql->_sentence, "select * from computerroom where num = %d", _roomNum);
	if (!(mysql->quire_res(mysql->_sentence))) {
		delete mysql;
		mysql = nullptr;
		return false;
	}
	//���Ż�ȡһ��������
	mysql->_row = mysql->getRow();
	_maxNum = atoi(mysql->_row[1]);
	int fieldNum = 2;		//�ӵ�������ʼ��ȡ����
	for (int day = 0; day < 5; day++) {
		for (int dn = 0; dn < 2; dn++) {
			_week[day][dn] = atoi(mysql->_row[fieldNum]);
			fieldNum++;
		}
	}
	delete mysql;
	mysql = nullptr;
	return true;
}