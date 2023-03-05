#include"computerRoom.h"

const char* computerRoom::_weekName[5] = {
	"星期一",
	"星期二",
	"星期三",
	"星期四",
	"星期五"
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

//输出机房信息
void computerRoom::showInfo() {
	cout << "机房编号：" << _roomNum << "\t最大容量：" << _maxNum << endl;
	for (int day = 0; day < 5; day++) {
		cout << _weekName[day] << "：";
		for (int dn = 0; dn < 2; dn++) {
			if (!dn) {
				cout << "\t上午已预约：" << _week[day][dn] << "\t还剩：" << _maxNum - _week[day][dn] << "\t";
			}
			else {
				cout << "\t下午已预约：" << _week[day][dn] << "\t还剩：" << _maxNum - _week[day][dn] << "\t";
			}
		}
		cout << endl;
	}
}

//获取当前机房的信息
bool computerRoom::initRsv() {
	//先把数据库连上
	my_MySql* mysql = new my_MySql();
	if (!(mysql->connet(mysql->_host, mysql->_user, mysql->_pwd, mysql->_databaseName, mysql->_port))) {
		delete mysql;
		mysql = nullptr;
		return false;
	}
	//然后找到当前机房的信息
	sprintf_s(mysql->_sentence, "select * from computerroom where num = %d", _roomNum);
	if (!(mysql->quire_res(mysql->_sentence))) {
		delete mysql;
		mysql = nullptr;
		return false;
	}
	//接着获取一下数据行
	mysql->_row = mysql->getRow();
	_maxNum = atoi(mysql->_row[1]);
	int fieldNum = 2;		//从第三个开始获取数据
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