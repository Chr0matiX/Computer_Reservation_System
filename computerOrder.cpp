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

//�鿴ԤԼ
void computerOrder::showOrder() {
	cout << "[" << _room << "]�Ż���\t" << computerRoom::_weekName[_day] << " " << (_dn == 0 ? "����" : "����") << "\t" << (_state == 0 ? "���δͨ��" : "���ͨ��") << endl;
}