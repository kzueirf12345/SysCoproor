#ifndef SYS_COPROOR_SOURCE_PLOT_INCLUDE_PLOT_HPP
#define SYS_COPROOR_SOURCE_PLOT_INCLUDE_PLOT_HPP

#include <SFML/Graphics.hpp>

#include "Common/ErrorHandle.hpp"
#include "Vector/Vector.hpp"

namespace SysCopro
{
    
class Plot
{
private:
    SysCopro::Vector LeftCorner;
    SysCopro::Vector RightCorner;

public:
    Plot(SysCopro::Vector LeftCorner, SysCopro::Vector RightCorner)
        : LeftCorner{LeftCorner}, RightCorner{RightCorner}
    { }

    Common::Error Print(sf::RenderWindow& Renderer);

    ~Plot() = default;
};

}

#endif /*SYS_COPROOR_SOURCE_PLOT_INCLUDE_PLOT_HPP*/

