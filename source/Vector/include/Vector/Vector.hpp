#ifndef SYS_COPROOR_SOURCE_VECTOR_INCLUDE_VECTOR_VECTOR_HPP
#define SYS_COPROOR_SOURCE_VECTOR_INCLUDE_VECTOR_VECTOR_HPP

#include <SFML/System/Vector2.hpp>

namespace SysCopro
{
class Vector {
private:
public:
    sf::Vector2f Begin;
    sf::Vector2f End;

    Vector(sf::Vector2f Begin, sf::Vector2f End) 
        : Begin{Begin}, End{End} 
    {};

    ~Vector() = default;
};
}
#endif /*SYS_COPROOR_SOURCE_VECTOR_INCLUDE_VECTOR_VECTOR_HPP*/

