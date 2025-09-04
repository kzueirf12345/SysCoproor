#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>

#include "Common/ErrorHandle.hpp"
#include "Plot/Plot.hpp"

Common::Error SysCopro::Plot::Print(sf::RenderWindow& Window) {
    sf::RectangleShape BGRect(
        sf::Vector2f(
            this->RightCorner.x - this->LeftCorner.x,
            this->RightCorner.y - this->LeftCorner.y
        )
    );

    BGRect.setPosition(this->LeftCorner);
    BGRect.setFillColor(this->BGColor);
    BGRect.setOutlineColor(sf::Color::Black);

    Window.draw(BGRect);

    sf::VertexArray XAxis(sf::PrimitiveType::Lines, 2);
    sf::VertexArray YAxis(sf::PrimitiveType::Lines, 2);

    XAxis[0].color = XAxis[1].color = sf::Color(255, 255, 255, 200);
    YAxis[0].color = YAxis[1].color = sf::Color(255, 255, 255, 200);

    XAxis[0].position = sf::Vector2f(
        this->LeftCorner.x, 
        this->LeftCorner.y + (this->RightCorner.y - this->LeftCorner.y) / 2
    );

    XAxis[1].position = sf::Vector2f(
        this->RightCorner.x, 
        this->LeftCorner.y + (this->RightCorner.y - this->LeftCorner.y) / 2
    );

    YAxis[0].position = sf::Vector2f(
        this->LeftCorner.x + (this->RightCorner.x - this->LeftCorner.x) / 2, 
        this->LeftCorner.y
    );

    YAxis[1].position = sf::Vector2f(
        this->LeftCorner.x + (this->RightCorner.x - this->LeftCorner.x) / 2, 
        this->RightCorner.y
    );

    Window.draw(XAxis);
    Window.draw(YAxis);

    return Common::Error::SUCCESS;
}