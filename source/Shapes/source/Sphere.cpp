#include "Shapes/Sphere.hpp"

bool SysCopro::Sphere::IsInside(const SysCopro::Vector3f Dot) const {
    return Dot.Len2() <= this->Radius * this->Radius;
}