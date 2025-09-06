#ifndef SYS_COPROOR_SOURCE_SPHERE_INCLUDE_SPHERE_SPHERE_HPP
#define SYS_COPROOR_SOURCE_SPHERE_INCLUDE_SPHERE_SPHERE_HPP

#include <cmath>

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>

#include "Vector/Vector.hpp"
#include "Shapes/Circle.hpp"

namespace SysCopro
{

class Sphere {
private:
public:
    float Radius;
    
    explicit Sphere(const float Radius)              : Radius{Radius} {}
    explicit Sphere(const SysCopro::Circle&  Circle) : Radius{Circle.Radius} {}
    explicit Sphere(const SysCopro::Circle&& Circle) : Radius{Circle.Radius} {}

    [[nodiscard]] bool IsInside(const SysCopro::Vector3f Dot) const;

    ~Sphere() = default;
};

}

#endif /*SYS_COPROOR_SOURCE_SPHERE_INCLUDE_SPHERE_SPHERE_HPP*/