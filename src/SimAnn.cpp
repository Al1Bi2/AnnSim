// SimAnn.cpp: определяет точку входа для приложения.
//


#include "anneal.hpp"
#include "SFML/Graphics.hpp"
using namespace std;

constexpr coordType PointRadius = 3.0f;

void drawPoint(sf::RenderWindow& window, Point point, sf::Color color)
{
    auto shape = sf::CircleShape(PointRadius);
    shape.setPosition(sf::Vector2f(point.get_x() - PointRadius, 1.0 + point.get_y() - PointRadius));
    shape.setFillColor(color);
    window.draw(shape);
}

void drawPoints(sf::RenderWindow& window, const Plane& plane)
{sf::VertexArray edges(sf::Lines);
    for (const auto& point : plane.points) {
        drawPoint(window, point, sf::Color(100, 250, 50));

    }

}
void drawEdge( Point origin, Point destination, sf::Color color,sf::VertexArray& path)
{
    path.append(sf::Vertex(sf::Vector2f(origin.get_x(),  origin.get_y()), color));
    path.append(sf::Vertex(sf::Vector2f(destination.get_x(),  destination.get_y()), color));
 

}

void drawPath(sf::RenderWindow& window, const Anneal& anneal)
{
    sf::VertexArray path(sf::Lines);
    for (int i=0;i<anneal.tour.size();i++)
    {
        if(i != anneal.tour.size() - 1) {
            drawEdge(anneal.plane.points[anneal.tour[i]], anneal.plane.points[anneal.tour[i+1]], sf::Color(255, 0, 0), path);
        }
        else {
            drawEdge(anneal.plane.points[anneal.tour[i]], anneal.plane.points[anneal.tour[0]], sf::Color(255, 0, 0), path);
        }
    }
    window.draw(path);
    path.clear();
}
int main()
{
    Plane plane;
    plane.fillRnd<coordType>(200);
    Anneal anneal(plane,0.00001,10);
 
    auto window = sf::RenderWindow{ { 1920u, 1080u }, "CMake SFML Project" };
    window.setFramerateLimit(60);

    window.clear(sf::Color::Black);
    drawPath(window, anneal);
    drawPoints(window,anneal.plane);
    sf::CircleShape shape(0.003);
    shape.setFillColor(sf::Color::Green);
    window.draw(shape);
    window.display();

    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Key::S)
                {

                    anneal.simulate_annealing(100000);


                }
                if (event.key.code == sf::Keyboard::Key::N)
                {
                    plane.clear();
                    plane.fillRnd<coordType>(200);
                    plane.display();
                    anneal = Anneal(plane, 0.00001, 20);
                    anneal.display_tour();

 
                }
            }
        }

        
        window.clear(sf::Color::Black);

        drawPath(window, anneal);
        drawPoints(window, anneal.plane);

        sf::CircleShape shape(10);
        shape.setFillColor(sf::Color::Red);
        window.draw(shape);
        window.display();
    }
}
