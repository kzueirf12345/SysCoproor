#include <cmath>

#include <SFML/Config.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>

#include "Common/ErrorHandle.hpp"
#include "Plot/Plot.hpp"

Common::Error SysCopro::Plot::Print(sf::RenderWindow& Window) const {

    Window.draw(this->CreateBG());

    Window.draw(this->CreateAxis(true ));
    Window.draw(this->CreateAxis(false));

    Window.draw(this->CreateGrid(true ));
    Window.draw(this->CreateGrid(false));

    return Common::Error::SUCCESS;
}

sf::RectangleShape SysCopro::Plot::CreateBG() const
{
    sf::RectangleShape BGRect(
        sf::Vector2f(
            this->RightCorner.x - this->LeftCorner.x,
            this->RightCorner.y - this->LeftCorner.y
        )
    );

    BGRect.setPosition(this->LeftCorner);
    BGRect.setFillColor(this->BGColor);
    BGRect.setOutlineColor(sf::Color::Black);

    return BGRect;
}

sf::VertexArray SysCopro::Plot::CreateAxis(const bool isX) const
{
    sf::VertexArray Axis(sf::PrimitiveType::Lines, 2);

    Axis[0].color = Axis[1].color = this->FGColor;

    if (isX) {
        Axis[0].position.x = this->LeftCorner.x;
        Axis[0].position.y = this->OriginOffset.y * ScaleY + this->LeftCorner.y;

        Axis[1].position.x = this->RightCorner.x;
        Axis[1].position.y = this->OriginOffset.y * ScaleY + this->LeftCorner.y;
    } else {
        Axis[0].position.x = this->OriginOffset.x * ScaleX + this->LeftCorner.x; 
        Axis[0].position.y = this->LeftCorner.y;

        Axis[1].position.x = this->OriginOffset.x * ScaleX + this->LeftCorner.x; 
        Axis[1].position.y = this->RightCorner.y;
    }

    return Axis;
}

sf::VertexArray SysCopro::Plot::CreateGrid(const bool isX) const
{
    constexpr sf::Uint8 GridLineOpacity = 25;
    const sf::Color GridLineColor(
        this->FGColor.r, 
        this->FGColor.g, 
        this->FGColor.b, 
        GridLineOpacity
    );

    if (isX) {
        const size_t GridLinesCnt = (this->RightCorner.y - this->LeftCorner.y) / this->ScaleY + 1;

        sf::VertexArray Grid(sf::PrimitiveType::Lines, 2 * GridLinesCnt);

        for (size_t LineNum = 0; LineNum < GridLinesCnt; ++LineNum) {
            Grid[2 * LineNum].color = Grid[2 * LineNum + 1].color = GridLineColor;

            Grid[2 * LineNum]    .position.x = this->LeftCorner .x;
            Grid[2 * LineNum + 1].position.x = this->RightCorner.x;

            Grid[2 * LineNum].position.y = this->LeftCorner.y + ScaleY * LineNum;
            Grid[2 * LineNum + 1].position.y = Grid[2 * LineNum].position.y;
        }

        return Grid;
    } else {
        const size_t GridLinesCnt = (this->RightCorner.x - this->LeftCorner.x) / this->ScaleX + 1;

        sf::VertexArray Grid(sf::PrimitiveType::Lines, 2 * GridLinesCnt);

        for (size_t LineNum = 0; LineNum < GridLinesCnt; ++LineNum) {
            Grid[2 * LineNum].color = Grid[2 * LineNum + 1].color = GridLineColor;

            Grid[2 * LineNum]    .position.y = this->LeftCorner .y;
            Grid[2 * LineNum + 1].position.y = this->RightCorner.y;

            Grid[2 * LineNum].position.x = this->LeftCorner.x + ScaleX * LineNum;
            Grid[2 * LineNum + 1].position.x = Grid[2 * LineNum].position.x;
        }

        return Grid;
    }

}