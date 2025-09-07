#include <Vector/Vector.hpp>

Common::Error SysCopro::TransformVector(SysCopro::Vector2f& Vector, const SysCopro::Transform Transform) {
    constexpr float DELTA_ANGLE_RADIANS = 0.01;
    float RotateAngleRadians = NAN;

    switch (Transform) {
        case SysCopro::Transform::ROTATE_CLKWISE:  RotateAngleRadians =  DELTA_ANGLE_RADIANS; break;
        case SysCopro::Transform::ROTATE_CCLKWISE: RotateAngleRadians = -DELTA_ANGLE_RADIANS; break;
        case SysCopro::Transform::NONE:            return Common::Error::SUCCESS;
        default:                                   return Common::Error::UNKNOWN_ENUM_ARG;
    }

    float cosA = std::cos(RotateAngleRadians);
    float sinA = std::sin(RotateAngleRadians);

    Vector = SysCopro::Vector2f(
        Vector.x * cosA - Vector.y * sinA,
        Vector.x * sinA + Vector.y * cosA
    );

    return Common::Error::SUCCESS;
}

Common::Error SysCopro::TransformVector(SysCopro::Vector3f& Vector, const SysCopro::Transform Transform, 
                                        SysCopro::Axis Axis) {
    constexpr float DELTA_ANGLE_RADIANS = 0.01f;
    float RotateAngleRadians = NAN;

    switch (Transform) {
        case SysCopro::Transform::ROTATE_CLKWISE:  RotateAngleRadians =  DELTA_ANGLE_RADIANS; break;
        case SysCopro::Transform::ROTATE_CCLKWISE: RotateAngleRadians = -DELTA_ANGLE_RADIANS; break;
        case SysCopro::Transform::NONE:            return Common::Error::SUCCESS;
        default:                                   return Common::Error::UNKNOWN_ENUM_ARG;
    }

    float cosA = std::cos(RotateAngleRadians);
    float sinA = std::sin(RotateAngleRadians);
    float x = Vector.x, y = Vector.y, z = Vector.z;

    switch (Axis) {
        case SysCopro::Axis::X:
            Vector = SysCopro::Vector3f(
                x,
                y * cosA - z * sinA,
                y * sinA + z * cosA
            );
            break;

        case SysCopro::Axis::Y:
            Vector = SysCopro::Vector3f(
                x * cosA + z * sinA,
                y,
                -x * sinA + z * cosA
            );
            break;

        case SysCopro::Axis::Z:
            Vector = SysCopro::Vector3f(
                x * cosA - y * sinA,
                x * sinA + y * cosA,
                z
            );
            break;

        default:
            return Common::Error::UNKNOWN_ENUM_ARG;
    }

    return Common::Error::SUCCESS;
}