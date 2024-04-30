#include "plane.hpp"


class Anneal {
public:
	Plane plane;
	std::vector<int> tour;
	double temperature;
public:
	Anneal(Plane plane, double initialTemp = 1000.0) : plane(plane), temperature(initialTemp) {
		for (int i = 0; i < plane.size(); i++) {
			tour.push_back(i);
		}
	}
    void simulate_annealing(double cooling_rate = 0.99, int closed = 1) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, plane.size() - 1);

        while (temperature > 1) {
            int i = distrib(gen);
            int j = distrib(gen);
            if (i != j) {
                std::vector<int> new_tour=tour;
                std::swap(new_tour[i], new_tour[j]);
                if (cost(closed,tour) > cost(closed, new_tour)) {
                    std::swap(tour[i], tour[j]); // отмена изменений, если хуже
                }
            }
            temperature *= cooling_rate;
            //displayTour();
        }

        display_tour();
    }

    double cost(int closed, std::vector<int> atour) {
        double total_distance = 0.0;
        int size = atour.size();
        for (int k = 0; k < size - 1; ++k) {
            total_distance += plane.distance(atour[k], atour[k + 1]);
        }
        if (closed) {
            total_distance += plane.distance(atour.back(), atour.front());
        }
        return total_distance;
    }

    void display_tour() {
        for (int index : tour) {
            std::cout << index << " -> ";
        }
        std::cout << "End" << std::endl;
    }
	Anneal() ;
};