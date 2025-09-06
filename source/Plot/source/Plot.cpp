#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/VertexBuffer.hpp>
#include <cmath>

#include <SFML/Config.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstddef>

#include "Common/ErrorHandle.hpp"
#include "Shapes/Circle.hpp"
#include "Vector/Vector.hpp"
#include "Plot/Plot.hpp"

Common::Error SysCopro::Plot::PrintSysCopro(sf::RenderWindow& Window) const {

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
    constexpr sf::Uint8 GRID_LINE_OPACITY = 25;
    const sf::Color GridLineColor(
        this->GridColor.r, 
        this->GridColor.g, 
        this->GridColor.b, 
        GRID_LINE_OPACITY
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

Common::Error SysCopro::Plot::PrintPlot(sf::RenderWindow& Window, 
                                        float (* const Func)(const float X),
                                        sf::Color Color) const {
    constexpr size_t DOTS_CNT = 1000;

    sf::VertexArray Line(sf::PrimitiveType::LinesStrip);

    const float Step = (Pix2Seg(RightCorner).x - Pix2Seg(LeftCorner).x) / DOTS_CNT;
    const float MinSegX = Pix2Seg(LeftCorner).x;
    const float MaxSegX = Pix2Seg(RightCorner).x;

    for (size_t DotNum = 0; DotNum < DOTS_CNT; ++DotNum) {
        const float CurSegX = MinSegX + DotNum * Step;
        const float CurSegY = Func(CurSegX);
        const sf::Vector2f CurPixDot = Seg2Pix(sf::Vector2f(CurSegX, CurSegY));

        if (this->LeftCorner.y <= CurPixDot.y && CurPixDot.y <= this->RightCorner.y) {
            Line.append(sf::Vertex(CurPixDot, Color));
        } else {
            Window.draw(Line);
            Line.clear();
        }
    }
    Window.draw(Line);

    return Common::Error::SUCCESS;
}

sf::Vector2f SysCopro::Plot::Seg2Pix(const sf::Vector2f SegDot) const
{
    return sf::Vector2f(this->LeftCorner.x + this->ScaleX * (this->OriginOffset.x + SegDot.x),
                        this->LeftCorner.y + this->ScaleY * (this->OriginOffset.y - SegDot.y));
}

sf::Vector2f SysCopro::Plot::Pix2Seg(const sf::Vector2f PixDot) const
{
    return sf::Vector2f(( PixDot.x - this->LeftCorner.x) / this->ScaleX - this->OriginOffset.x,
                        (-PixDot.y + this->LeftCorner.y) / this->ScaleY + this->OriginOffset.y);
}

Common::Error SysCopro::Plot::PrintVector(sf::RenderWindow& Window, const sf::Vector2f& Vector,
                                          sf::Color Color) const {

    sf::VertexArray Line(sf::PrimitiveType::LinesStrip, 2);
    sf::VertexArray Tip (sf::PrimitiveType::LinesStrip, 3);

    Line[0].color = Line[1].color                = Color;
    Tip[0].color  = Tip[1].color  = Tip[2].color = Color;

    Line[0].position = Seg2Pix(sf::Vector2f(0, 0));
    Line[1].position = Seg2Pix(Vector);
    Tip[1].position  = Line[1].position;

    constexpr float TIP_ANGLE_DEGREES = 20;
    constexpr float TIP_ANGLE_RADIANS = TIP_ANGLE_DEGREES * M_PI / 180.0;
    constexpr float TIP_SCALE         = 0.3;

    const sf::Vector2f ScaledTendril = -Vector * TIP_SCALE;


    Tip[0].position.x = Vector.x 
                      + ScaledTendril.x * std::cos( TIP_ANGLE_RADIANS) 
                      - ScaledTendril.y * std::sin( TIP_ANGLE_RADIANS);
    Tip[0].position.y = Vector.y 
                      + ScaledTendril.x * std::sin( TIP_ANGLE_RADIANS) 
                      + ScaledTendril.y * std::cos( TIP_ANGLE_RADIANS);
    
    Tip[2].position.x = Vector.x 
                      + ScaledTendril.x * std::cos( TIP_ANGLE_RADIANS) 
                      - ScaledTendril.y * std::sin(-TIP_ANGLE_RADIANS);
    Tip[2].position.y = Vector.y 
                      + ScaledTendril.x * std::sin(-TIP_ANGLE_RADIANS) 
                      + ScaledTendril.y * std::cos( TIP_ANGLE_RADIANS);

    Tip[0].position = Seg2Pix(Tip[0].position);
    Tip[2].position = Seg2Pix(Tip[2].position);

    Window.draw(Line);
    Window.draw(Tip);
    
    return Common::Error::SUCCESS;
}

Common::Error SysCopro::TransformVector(sf::Vector2f& Vector, const SysCopro::Transform Transform) {
    constexpr float DELTA_ANGLE_RADIANS = 0.01;
    float RotateAngleRadians = NAN;

    switch (Transform) {
        case SysCopro::Transform::ROTATE_CLKWISE:  RotateAngleRadians =  DELTA_ANGLE_RADIANS; break;
        case SysCopro::Transform::ROTATE_CCLKWISE: RotateAngleRadians = -DELTA_ANGLE_RADIANS; break;
        case SysCopro::Transform::NONE:            RotateAngleRadians = 0;                    break;
        
        default:
            break;
    }

    Vector = sf::Vector2f(
        Vector.x * std::cos(RotateAngleRadians) - Vector.y * std::sin(RotateAngleRadians),
        Vector.x * std::sin(RotateAngleRadians) + Vector.y * std::cos(RotateAngleRadians)
    );

    return Common::Error::SUCCESS;
}

Common::Error SysCopro::Plot::PrintCircle(sf::RenderWindow& Window, 
                                          const SysCopro::Circle& Circle) const {

    const sf::Color BGHandledColor (16, 16, 16);
    const sf::Color BaseCircleColor(36, 36, 36);

    const unsigned int WindowWidth  = this->RightCorner.x - this->LeftCorner.x;
    const unsigned int WindowHeight = this->RightCorner.y - this->LeftCorner.y;

    sf::VertexArray Screen(sf::PrimitiveType::Points /*WindowWidth * WindowHeight*/ );

    for (unsigned int y = 0; y < WindowHeight; ++y) {
        for (unsigned int x = 0; x < WindowWidth; ++x) {
            const size_t CurInd = y * WindowWidth + x;
            const SysCopro::Vector2f CurPix(this->LeftCorner.x + x, this->LeftCorner.y + y);
            const SysCopro::Vector2f CurSeg(Pix2Seg(CurPix));

            
            // Screen[CurInd].position = LeftCorner + sf::Vector2f(x, y);
            
            if (Circle.IsInside(CurSeg)) {
                Screen.append(sf::Vertex(LeftCorner + sf::Vector2f(x, y), BaseCircleColor));
                // Screen[CurInd].color = BaseCircleColor;
            } else {
                // Screen[CurInd].color = BGHandledColor;
            }
        }
    }

    Window.draw(Screen);

    return Common::Error::SUCCESS;
}