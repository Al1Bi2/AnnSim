#include "plane.hpp"


class Anneal {
public:
	Plane plane;
	std::vector<int> tour;
	double start_t;
    double temperature;
    double end_t;
public:
	Anneal(Plane plane, double end_t=0.0001, double initialTemp = 1000.0) : plane(plane), end_t(end_t), start_t(initialTemp) {
		for (int i = 0; i < plane.size(); i++) {
			tour.push_back(i);
		}
	}

    void simulate_annealing(long num=10000000000, int closed = 1) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, plane.size() - 1);
        std::uniform_real_distribution<double> prob(0, 1);
        temperature = start_t;
        int last_t = 0;
        for(int k=0;k< num;k++) {

            temperature =temperature*0.99995;

            int i = distrib(gen);
            int j = distrib(gen);
            if (i != j) {
                std::vector<int> new_tour=tour;
                std::reverse(new_tour.begin() + std::min(i, j), new_tour.begin() + std::max(i, j) + 1);
                
                if (cost(closed,tour) > cost(closed, new_tour)) {
                    tour = new_tour;
                    last_t = temperature;
                }
                else {
                    double dE = fabs(cost(closed, tour) - cost(closed, new_tour));
                    double P = exp((-dE) / temperature);
                    if (prob(gen) < P) {
                        tour = new_tour;
                        last_t = temperature;
                    }
                }
            }
            last_t++;
            if (temperature < end_t) {
                std::cout << "!!!";
                break;
           }
            //displayTour();
        }
        std::cout << "Cost - "<< cost(closed, tour) << std::endl;
        //display_tour();
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