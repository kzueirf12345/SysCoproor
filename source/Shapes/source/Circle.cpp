#include "Shapes/Circle.hpp"

bool SysCopro::Circle::IsInside(const SysCopro::Vector2f Dot) const {
    return Dot.Len2() <= this->Radius * this->Radius;
}