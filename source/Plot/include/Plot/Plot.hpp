#ifndef SYS_COPROOR_SOURCE_PLOT_INCLUDE_PLOT_PLOT_HPP
#define SYS_COPROOR_SOURCE_PLOT_INCLUDE_PLOT_PLOT_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

#include "Common/ErrorHandle.hpp"
// #include "Vector/Vector.hpp"

namespace SysCopro
{
    
class Plot {
private:
    sf::Vector2f    LeftCorner;
    sf::Vector2f    RightCorner;
    sf::Color       BGColor;
    sf::Color       FGColor;
    unsigned int    ScaleX;
    unsigned int    ScaleY;
    sf::Vector2f    OriginOffset;
    float (* const Func)(const float X);

    sf::RectangleShape CreateBG      ()                          const ;
    sf::VertexArray    CreateAxis    (const bool IsX)            const ;
    sf::VertexArray    CreateGrid    (const bool IsX)            const ;
    sf::VertexArray    CreateFuncPlot(const size_t DotsCnt)      const ;

    sf::Vector2f       Seg2Pix       (const sf::Vector2f SegDot) const;
    sf::Vector2f       Pix2Seg       (const sf::Vector2f PixDot) const;

public:
    Plot(sf::Vector2f LeftCorner, sf::Vector2f RightCorner, sf::Color BGColor, sf::Color FGColor, 
         unsigned int ScaleX, unsigned int ScaleY, sf::Vector2f OriginOffset, 
         float (* const Func)(const float X))
       : LeftCorner{LeftCorner}, RightCorner{RightCorner}, BGColor{BGColor}, FGColor{FGColor}, 
         OriginOffset{OriginOffset}, Func(Func)
    { 
        this->ScaleX = (RightCorner.x - LeftCorner.x) / ScaleX;
        this->ScaleY = (RightCorner.y - LeftCorner.y) / ScaleY;
    }

    Common::Error Print(sf::RenderWindow& Renderer) const;

    ~Plot() = default;
};

}

#endif /*SYS_COPROOR_SOURCE_PLOT_INCLUDE_PLOT_PLOT_HPP*/

