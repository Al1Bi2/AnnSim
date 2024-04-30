#include <stdint.h>
#define coordType double
class Point {
private:
	coordType x;
	coordType y;
public:
	Point(coordType x, coordType y) {
		this->x = x;
		this->y = y;
	}
	Point() {};
	coordType get_x()const {
		return x;
	}

	coordType get_y()const {
		return y;
	}

	void set_x(coordType x) {
		this->x = x;
	}

	void set_y(coordType y) {
		this->y = y;
	}


};
