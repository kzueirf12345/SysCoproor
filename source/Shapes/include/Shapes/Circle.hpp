#ifndef SYS_COPROOR_SOURCE_CIRCLE_INCLUDE_CIRCLE_CIRCLE_HPP
#define SYS_COPROOR_SOURCE_CIRCLE_INCLUDE_CIRCLE_CIRCLE_HPP

#include <cmath>

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>

#include "Vector/Vector.hpp"

namespace SysCopro
{

class Circle {
private:
public:
    float Radius;
    
    explicit Circle(const float Radius) 
        : Radius{Radius}
    { }

    [[nodiscard]] bool IsInside(const SysCopro::Vector2f Dot) const;

    ~Circle() = default;
};

}

#endif /*SYS_COPROOR_SOURCE_CIRCLE_INCLUDE_CIRCLE_CIRCLE_HPP*/

