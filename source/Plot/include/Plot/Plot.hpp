#ifndef SYS_COPROOR_SOURCE_PLOT_INCLUDE_PLOT_PLOT_HPP
#define SYS_COPROOR_SOURCE_PLOT_INCLUDE_PLOT_PLOT_HPP

#include <cstdint>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

#include "Common/ErrorHandle.hpp"
// #include "Vector/Vector.hpp"

namespace SysCopro
{
    
class Plot {
private:
    sf::Vector2f LeftCorner;
    sf::Vector2f RightCorner;
    sf::Color    BGColor;
    uint64_t     Scale;

public:
    Plot(sf::Vector2f LeftCorner, sf::Vector2f RightCorner, sf::Color BGColor, uint64_t Scale)
        : LeftCorner{LeftCorner}, RightCorner{RightCorner}, BGColor{BGColor}, Scale{Scale}
    { }

    Common::Error Print(sf::RenderWindow& Renderer);

    ~Plot() = default;
};

}

#endif /*SYS_COPROOR_SOURCE_PLOT_INCLUDE_PLOT_PLOT_HPP*/

