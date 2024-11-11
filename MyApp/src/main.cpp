#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::RectangleShape shape(sf::Vector2f(100.f, 100.f)); // Квадрат со стороной 100
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(50.f, 50.f); // Поместим квадрат по центру окна

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}
