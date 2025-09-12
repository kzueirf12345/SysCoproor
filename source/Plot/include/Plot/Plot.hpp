#ifndef SYS_COPROOR_SOURCE_PLOT_INCLUDE_PLOT_PLOT_HPP
#define SYS_COPROOR_SOURCE_PLOT_INCLUDE_PLOT_PLOT_HPP

#include <cmath>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

#include "Common/ErrorHandle.hpp"
#include "Shapes/Sphere.hpp"
#include "Vector/Vector.hpp"

namespace SysCopro
{
    
class Plot {
private:
    sf::Vector2f    LeftCorner;
    sf::Vector2f    RightCorner;
    sf::Color       BGColor;
    sf::Color       GridColor;
    unsigned int    ScaleX;
    unsigned int    ScaleY;
    sf::Vector2f    OriginOffset;

    sf::RectangleShape              CreateBG      ()                          const ;
    sf::VertexArray                 CreateAxis    (const bool IsX)            const ;
    sf::VertexArray                 CreateGrid    (const bool IsX)            const ;

    sf::Vector2f                    Seg2Pix       (const sf::Vector2f SegDot) const;
    sf::Vector2f                    Pix2Seg       (const sf::Vector2f PixDot) const;

public:
    Plot(sf::Vector2f LeftCorner, sf::Vector2f RightCorner, sf::Color BGColor, sf::Color GridColor, 
         unsigned int ScaleX, unsigned int ScaleY, sf::Vector2f OriginOffset)
       : LeftCorner{LeftCorner}, RightCorner{RightCorner}, BGColor{BGColor}, GridColor{GridColor}, 
         OriginOffset{OriginOffset}
    { 
        this->ScaleX = (RightCorner.x - LeftCorner.x) / ScaleX;
        this->ScaleY = (RightCorner.y - LeftCorner.y) / ScaleY;
    }

    [[nodiscard]]       sf::Vector2f& GetOriginOffset()       noexcept {return this->OriginOffset;}
    [[nodiscard]] const sf::Vector2f& GetOriginOffset() const noexcept {return this->OriginOffset;}
    [[nodiscard]]       unsigned int& GetScaleX()             noexcept {return this->ScaleX;}
    [[nodiscard]] const unsigned int& GetScaleX()       const noexcept {return this->ScaleX;}
    [[nodiscard]]       unsigned int& GetScaleY()             noexcept {return this->ScaleY;}
    [[nodiscard]] const unsigned int& GetScaleY()       const noexcept {return this->ScaleY;}

    Common::Error MoveLeft      () noexcept;
    Common::Error MoveRight     () noexcept;
    Common::Error MoveUp        () noexcept;
    Common::Error MoveDown      () noexcept;

    Common::Error PrintSysCopro (sf::RenderWindow& Window) const;
    Common::Error PrintPlot     (sf::RenderWindow& Window, float (* const Func)(const float X), 
                                 sf::Color Color) const;
    Common::Error PrintVector   (sf::RenderWindow& Window, const sf::Vector2f& Vector,
                                 sf::Color Color) const;

    Common::Error PrintSphere   (sf::RenderWindow& Window, 
                                 const SysCopro::Sphere& Sphere,
                                 const SysCopro::Vector3f& LightSource,
                                 const SysCopro::Vector3f& Viewer) const;

    ~Plot() = default;
};

}

#endif /*SYS_COPROOR_SOURCE_PLOT_INCLUDE_PLOT_PLOT_HPP*/

