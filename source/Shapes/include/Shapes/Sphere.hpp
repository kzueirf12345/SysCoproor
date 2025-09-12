#ifndef SYS_COPROOR_SOURCE_SPHERE_INCLUDE_SPHERE_SPHERE_HPP
#define SYS_COPROOR_SOURCE_SPHERE_INCLUDE_SPHERE_SPHERE_HPP

#include <cmath>

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>

#include "Vector/Vector.hpp"
// #include "Shapes/Circle.hpp"

namespace SysCopro
{

class Sphere {
private:
    sf::Color Color;
public:
    float Radius;
    
    explicit Sphere(const float Radius, sf::Color Color = {0, 0, 0, 255}) 
        : Radius{Radius}, Color(Color) 
    {}
    // explicit Sphere(const SysCopro::Sphere&  Sphere) : Radius{Sphere.Radius}, Color{Sphere.Color} {}
    // explicit Sphere(const SysCopro::Sphere&& Sphere) : Radius{Sphere.Radius}, Color{Sphere.Color} {}

    [[nodiscard]] bool IsInside(const SysCopro::Vector3f Dot) const;

    ~Sphere() = default;
};

}

#endif /*SYS_COPROOR_SOURCE_SPHERE_INCLUDE_SPHERE_SPHERE_HPP*/