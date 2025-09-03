#ifndef SYS_COPROOR_SOURCE_VECTOR_INCLUDE_VECTOR_HPP
#define SYS_COPROOR_SOURCE_VECTOR_INCLUDE_VECTOR_HPP

#include <cstdint>

namespace SysCopro
{
class Vector {
private:
    std::uint64_t x;
    std::uint64_t y;
public:
    Vector(std::uint64_t x, std::uint64_t y) 
        : x{x}, y{y} 
    {};

    std::uint64_t GetX();
    std::uint64_t GetY();

    ~Vector() = default;
};
}
#endif /*SYS_COPROOR_SOURCE_VECTOR_INCLUDE_VECTOR_HPP*/

