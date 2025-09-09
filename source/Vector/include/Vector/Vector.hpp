#ifndef SYS_COPROOR_SOURCE_VECTOR_INCLUDE_VECTOR_VECTOR_HPP
#define SYS_COPROOR_SOURCE_VECTOR_INCLUDE_VECTOR_VECTOR_HPP

#include <cmath>

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>

#include "Common/ErrorHandle.hpp"

namespace SysCopro
{

enum class Axis {
    X = 0,
    Y = 1,
    Z = 2
};

enum Transform {
    NONE            = 0,
    ROTATE_CLKWISE  = 1,
    ROTATE_CCLKWISE = 2,
};

//--------------------------------------------------------------------------------------------------

template <typename T>
class Vector2: public sf::Vector2<T> {
    private:
    public:
        Vector2() : sf::Vector2<T>() {}
        Vector2(T X, T Y) : sf::Vector2<T>(X, Y) {}
        template <typename U>
        explicit Vector2(const sf::Vector2<T>& vector)  : sf::Vector2<T>(vector) {}
        explicit Vector2(const sf::Vector2<T>&& vector) : sf::Vector2<T>(vector) {}

        [[nodiscard]] T Len2() const;
        [[nodiscard]] T Len()  const;
};

typedef SysCopro::Vector2<float> Vector2f;
typedef SysCopro::Vector2<int>   Vector2i;

template <typename T>
T operator ^(const SysCopro::Vector2<T>& left, const SysCopro::Vector2<T>& right) {
    return left.x * right.x + left.y * right.y;
}

template <typename T>
SysCopro::Vector2<T> operator !(const SysCopro::Vector2<T>& right) {
    return SysCopro::Vector2<T>(right / right.Len());
}

template <typename T>
T SysCopro::Vector2<T>::Len2() const {
    return (*this) ^ (*this);
}

template <typename T>
T SysCopro::Vector2<T>::Len() const {
    return std::sqrt(this->Len2());
}

Common::Error TransformVector(SysCopro::Vector2f& Vector, const SysCopro::Transform Transform, 
                              const float AngleRadians = 0.01);

//--------------------------------------------------------------------------------------------------

template <typename T>
class Vector3: public sf::Vector3<T> {
    private:
    public:
        Vector3() : sf::Vector3<T>() {}
        Vector3(T X, T Y, T Z) : sf::Vector3<T>(X, Y, Z) {};
        template <typename U>
        explicit Vector3(const sf::Vector3<T>&  vector) : sf::Vector3<T>(vector) {}
        explicit Vector3(const sf::Vector3<T>&& vector) : sf::Vector3<T>(vector) {}
        
        [[nodiscard]] T Len2() const;
        [[nodiscard]] T Len()  const;
};

typedef SysCopro::Vector3<float> Vector3f;
typedef SysCopro::Vector3<int>   Vector3i;

template <typename T>
T operator ^(const SysCopro::Vector3<T>& left, const SysCopro::Vector3<T>& right) {
    return left.x * right.x + left.y * right.y + left.z * right.z;
}

template <typename T>
SysCopro::Vector3<T> operator !(const SysCopro::Vector3<T>& right) {
    return SysCopro::Vector3<T>(right / right.Len());
}

template <typename T>
T SysCopro::Vector3<T>::Len2() const {
    return (*this) ^ (*this);
}

template <typename T>
T SysCopro::Vector3<T>::Len() const {
    return std::sqrt(this->Len2());
}

Common::Error TransformVector(SysCopro::Vector3f& Vector, const SysCopro::Transform Transform, 
                              SysCopro::Axis Axis, const float AngleRadians = 0.01);

}

#endif /*SYS_COPROOR_SOURCE_VECTOR_INCLUDE_VECTOR_VECTOR_HPP*/

