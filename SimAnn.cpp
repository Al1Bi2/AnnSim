// SimAnn.cpp: определяет точку входа для приложения.
//


#include "anneal.hpp"

using namespace std;
constexpr coordType WindowWidth = 800.0f;
constexpr coordType WindowHeight = 800.0f;
constexpr coordType PointRadius = 0.002f;




int main()
{
	int closed = 1;
	Plane plane;
	plane.fillRnd<double>(50);
	plane.display();
	Anneal anneal(plane,1000);
	anneal.display_tour();
	anneal.simulate_annealing(0.99, closed);
	cout <<"!" << closed << endl;

	cout << "----------------------------------------------------" << closed << endl;
	
	return 0;
}
