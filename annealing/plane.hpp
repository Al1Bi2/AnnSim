#include "point.hpp"

#include <iostream>
#include <type_traits>

#include <random>
#include <vector>

class Plane {
public:
	std::vector<Point> points;
	coordType xmin = -180 ;
	coordType xmax = 180 ;
	coordType ymin = -90 ;
	coordType ymax = 90;
	coordType exp = 100000;

	void addPoint(coordType x, coordType y) {
		points.push_back(Point(x, y));
	}
	void clear() {
		points.clear();
	}
	template<typename T>
	void fillRnd(int16_t quantity) {
		std::random_device rd;
		std::mt19937 gen(rd());
		
	
	std::uniform_real_distribution<T> x_distr(xmin, xmax);
	std::uniform_real_distribution<T> y_distr(ymin, ymax);
	for (int i = 0; i < quantity; i++) {
		addPoint(x_distr(gen), y_distr(gen));
	}
	
	}
	coordType distance(int i, int j) const {
		const Point& p1 = points[i];
		const Point& p2 = points[j];
		return std::hypot(p1.get_x() - p2.get_x(), p1.get_y() - p2.get_y());
	}

	int size() const { return points.size(); }

	Point& getPoint(int index) { return points[index]; }
	void display() {
		for (Point point : points) {
			std::cout << "X:" << point.get_x()<< " Y:" << point.get_y()<<std::endl;
		}
		std::cout << "End" << std::endl;
	}
};