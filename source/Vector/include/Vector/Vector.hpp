#ifndef SYS_COPROOR_SOURCE_VECTOR_INCLUDE_VECTOR_VECTOR_HPP
#define SYS_COPROOR_SOURCE_VECTOR_INCLUDE_VECTOR_VECTOR_HPP

#include <cstdint>

namespace SysCopro
{
class Vector {
private:
    uint64_t x;
    uint64_t y;
public:
    Vector(uint64_t x, uint64_t y) 
        : x{x}, y{y} 
    {};

    uint64_t GetX();
    uint64_t GetY();

    ~Vector() = default;
};
}
#endif /*SYS_COPROOR_SOURCE_VECTOR_INCLUDE_VECTOR_VECTOR_HPP*/

