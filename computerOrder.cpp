#include"computerOrder.h"

computerOrder::computerOrder(int id, int room, int day, int dn, int state) {
	_id = id;
	_room = room;
	_day = day;
	_dn = dn;
	_state = state;
}

computerOrder::~computerOrder() {

}

//查看预约
void computerOrder::showOrder() {
	cout << "[" << _room << "]号机房\t" << computerRoom::_weekName[_day] << " " << (_dn == 0 ? "上午" : "下午") << "\t" << (_state == 0 ? "审核未通过" : "审核通过") << endl;
}