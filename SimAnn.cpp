// SimAnn.cpp: определяет точку входа для приложения.
//


#include "anneal.hpp"

using namespace std;
constexpr coordType WindowWidth = 800.0f;
constexpr coordType WindowHeight = 800.0f;
constexpr coordType PointRadius = 0.002f;




int main()
{
	Plane plane;
	plane.fillRnd<double>(5);
	plane.display();
	Anneal anneal(plane);
	anneal.displayTour();
	anneal.simulateAnnealing();
	anneal.displayTour();
	return 0;
}
