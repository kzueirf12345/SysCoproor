#include <iostream>

#include <SFML/Graphics.hpp>

#include "Plot/include/Plot.hpp"
#include "Common/include/ErrorHandle.hpp"

int main()
{
    SysCopro::Plot plot(SysCopro::Vector(100, 100), SysCopro::Vector(500, 500));

    std::cout << SysCopro::Vector(500, 500).GetY() << std::endl;

    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");
    // sf::CircleShape shape(100.f);
    // shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        ERROR_HANDLE(plot.Print(window));

        window.display();
    }

    return 0;
}