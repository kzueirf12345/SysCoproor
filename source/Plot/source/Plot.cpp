#include <cmath>
#include <vector>

#include <SFML/Config.hpp>
#include <SFML/Graphics/Vertex.hpp>
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

    constexpr size_t DotsCnt = 2048;
    
    for (auto Line : this->CreateFuncPlot(DotsCnt)) {
        Window.draw(Line);
    }

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

sf::VertexArray SysCopro::Plot::CreateAxis(const bool IsX) const
{
    sf::VertexArray Axis(sf::PrimitiveType::Lines, 2);

    Axis[0].color = Axis[1].color = this->GridColor;

    if (IsX) {
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

sf::VertexArray SysCopro::Plot::CreateGrid(const bool IsX) const
{
    constexpr sf::Uint8 GridLineOpacity = 25;
    const sf::Color GridLineColor(
        this->GridColor.r, 
        this->GridColor.g, 
        this->GridColor.b, 
        GridLineOpacity
    );

    if (IsX) {
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

std::vector<sf::VertexArray> SysCopro::Plot::CreateFuncPlot(const size_t DotsCnt) const
{
    std::vector<sf::VertexArray> Lines;

    const float Step = (Pix2Seg(RightCorner).x - Pix2Seg(LeftCorner).x) / DotsCnt;
    const float MinSegX = Pix2Seg(LeftCorner).x;
    const float MaxSegX = Pix2Seg(RightCorner).x;

    bool IsNewLine = true;

    for (size_t DotNum = 0; DotNum < DotsCnt; ++DotNum) {
        const float CurSegX = MinSegX + DotNum * Step;
        const float CurSegY = this->Func(CurSegX);
        const sf::Vector2f CurPixDot = Seg2Pix(sf::Vector2f(CurSegX, -this->Func(CurSegX)));

        if (this->LeftCorner.y <= CurPixDot.y && CurPixDot.y <= this->RightCorner.y) {
            if (IsNewLine) {
                Lines.push_back(sf::VertexArray(sf::PrimitiveType::LinesStrip));
            }
            Lines.back().append(sf::Vertex(CurPixDot, this->PlotColor));
            IsNewLine = false;
        } else {
            IsNewLine = true;
        }
    }

    return Lines;
}

sf::Vector2f SysCopro::Plot::Seg2Pix(const sf::Vector2f SegDot) const
{
    return sf::Vector2f(this->LeftCorner.x + this->ScaleX * (this->OriginOffset.x + SegDot.x),
                        this->LeftCorner.y + this->ScaleY * (this->OriginOffset.y + SegDot.y));
}

sf::Vector2f SysCopro::Plot::Pix2Seg(const sf::Vector2f PixDot) const
{
    return sf::Vector2f((PixDot.x - this->LeftCorner.x) / this->ScaleX - this->OriginOffset.x,
                        (PixDot.y - this->LeftCorner.y) / this->ScaleY - this->OriginOffset.y);
}