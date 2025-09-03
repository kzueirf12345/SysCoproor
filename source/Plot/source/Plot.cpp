#include <iostream>

#include <SFML/Graphics.hpp>

#include "Common/include/ErrorHandle.hpp"
#include "Plot/include/Plot.hpp"

Common::Error SysCopro::Plot::Print(sf::RenderWindow& Renderer) {
    sf::RectangleShape Rect(
        sf::Vector2f(
            this->RightCorner.GetX() - this->LeftCorner.GetX(),
            this->RightCorner.GetY() - this->LeftCorner.GetY()
        )
    );

    Rect.setPosition(sf::Vector2f(this->LeftCorner.GetX(), this->LeftCorner.GetY()));

    Renderer.draw(Rect);

    return Common::Error::SUCCESS;
}