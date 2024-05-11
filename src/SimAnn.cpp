// SimAnn.cpp: определяет точку входа для приложения.
//


#include "anneal.hpp"
#include "SFML/Graphics.hpp"
#include <sstream>
using namespace std;

constexpr coordType PointRadius = 3.0f;
sf::RenderTexture bgTex;

void drawPoint(sf::RenderTexture& tex , Point point, sf::Color color)
{
    auto shape = sf::CircleShape(PointRadius);
    shape.setPosition(sf::Vector2f(point.get_x() - PointRadius, 1.0 + point.get_y() - PointRadius));
    shape.setFillColor(color);
    tex.draw(shape);
}

void drawPoints(sf::RenderTexture& tex, const Plane& plane)
{sf::VertexArray edges(sf::Lines);
    for (const auto& point : plane.points) {
        drawPoint(tex, point, sf::Color(100, 250, 50));

    }

}
void drawEdge( Point origin, Point destination, sf::Color color,sf::VertexArray& path)
{
    path.append(sf::Vertex(sf::Vector2f(origin.get_x(),  origin.get_y()), color));
    path.append(sf::Vertex(sf::Vector2f(destination.get_x(),  destination.get_y()), color));
 

}

void drawPath(sf::RenderTexture& tex, const Anneal& anneal)
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
    tex.draw(path);
    path.clear();
}
int main()
{
    Plane plane;
    plane.fillRnd<coordType>(200);
    Anneal anneal(plane,0.00001, 3000);
    float fps;
    sf::Clock clock = sf::Clock::Clock();
    sf::Time previousTime = clock.getElapsedTime();
    sf::Time currentTime;
    auto window = sf::RenderWindow{ { 1920u, 1080u }, "CMake SFML Project" };
    
    bgTex.create(1920u, 1080u);
    window.setFramerateLimit(1000);
    
    window.clear(sf::Color::Black);
    drawPath(bgTex, anneal);
    drawPoints(bgTex,anneal.plane);

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
                    sf::Time previousTime = clock.getElapsedTime();
                   
                    anneal.simulate_annealing(10000000000);
                    sf::Time currentTime = clock.getElapsedTime();
                    cout << (currentTime.asSeconds() - previousTime.asSeconds())<<"S" << endl;

                }
                if (event.key.code == sf::Keyboard::Key::N)
                {
                    plane.clear();
                    plane.fillRnd<coordType>(200);
                    //plane.display();
                    anneal = Anneal(plane, 0.000001, 3000);
                    //anneal.display_tour();
                    bgTex.clear();
                    drawPath(bgTex, anneal);
                    drawPoints(bgTex, anneal.plane);
                    bgTex.display(); // important !
                    sf::Sprite background(bgTex.getTexture());
                    window.clear(sf::Color::Black);
                    window.draw(background);

 
                }
            }
        }

        
        
        bgTex.clear();
        drawPath(bgTex, anneal);
        drawPoints(bgTex, anneal.plane);
        bgTex.display(); // important !
        sf::Sprite background(bgTex.getTexture());
        window.clear(sf::Color::Black);
        window.draw(background);

        currentTime = clock.getElapsedTime();
        fps = 1.0f / (currentTime.asSeconds() - previousTime.asSeconds()); 
        previousTime = currentTime;
        std::ostringstream ss;
        ss << fps;

        window.setTitle(ss.str());
        window.display();
        
    }
}
