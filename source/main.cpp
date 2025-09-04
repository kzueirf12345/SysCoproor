#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include "Plot/Plot.hpp"
#include "Common/ErrorHandle.hpp"

int main()
{
    SysCopro::Plot plot(sf::Vector2f(100, 100), sf::Vector2f(500, 500), sf::Color::Magenta, 5);

    sf::RenderWindow window(sf::VideoMode(1000, 1000), "System Coproordinations (SysCopro)");

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