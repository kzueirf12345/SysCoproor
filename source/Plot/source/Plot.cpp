#include <SFML/Graphics.hpp>

#include "Common/ErrorHandle.hpp"
#include "Plot/Plot.hpp"

Common::Error SysCopro::Plot::Print(sf::RenderWindow& Renderer) {
    sf::RectangleShape BGRect(
        sf::Vector2f(
            this->RightCorner.x - this->LeftCorner.x,
            this->RightCorner.y - this->LeftCorner.y
        )
    );

    BGRect.setPosition(this->LeftCorner);
    BGRect.setFillColor(this->BGColor);
    BGRect.setOutlineColor(sf::Color::Black);

    Renderer.draw(BGRect);

    return Common::Error::SUCCESS;
}