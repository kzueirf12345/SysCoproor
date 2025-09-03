#ifndef SYS_COPROOR_SOURCE_PLOT_INCLUDE_PLOT_HPP
#define SYS_COPROOR_SOURCE_PLOT_INCLUDE_PLOT_HPP

#include <SFML/Graphics.hpp>

#include "Common/include/ErrorHandle.hpp"
#include "Vector/include/Vector.hpp"

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

