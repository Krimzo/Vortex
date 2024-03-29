#pragma once

// Helper
#include "math/helper/constants.h"

// Imaginary
#include "math/imaginary/complex.h"
#include "math/imaginary/quaternion.h"

// Vector
#include "math/vector/int2.h"
#include "math/vector/float2.h"
#include "math/vector/float3.h"
#include "math/vector/float4.h"

// Matrix
#include "math/matrix/float2x2.h"
#include "math/matrix/float3x3.h"
#include "math/matrix/float4x4.h"

// Triangle
#include "math/triangle/vertex.h"
#include "math/triangle/triangle.h"

// Ray
#include "math/ray/plane.h"
#include "math/ray/sphere.h"
#include "math/ray/ray.h"


namespace kl {
    // Deg trig
    float sin_deg(float angle_in_deg);
    float cos_deg(float angle_in_deg);
    float tan_deg(float angle_in_deg);

    float asin_deg(float value);
    float acos_deg(float value);
    float atan_deg(float value);

    // Lines
    float line_x(const float2& a, const float2& b, float y);
    float line_y(const float2& a, const float2& b, float x);

    // Normalization
    float normalize(float value, float lower, float upper);
    float interpolate(float value, float lower, float upper);

    // Rotation
    quaternion to_quaternion(const float3& euler);
    float3 to_euler(const quaternion& quaternion);

    // Complex
    complex abs(const complex& num);
    complex normalize(const complex& num);
    complex inverse(const complex& num);

    // Quaternion
    quaternion abs(const quaternion& num);
    quaternion normalize(const quaternion& num);
    quaternion inverse(const quaternion& num);

    // Int2 operations
    int2 abs(const int2& vec);

    // Float2 operations
    float2 abs(const float2& vec);
    float2 normalize(const float2& vec);
    float dot(const float2& first, const float2& second);
    float angle(const float2& first, const float2& second, bool full);
    float2 rotate(const float2& vec, float angle);
    float2 reflect(const float2& vec, const float2& point);

    // Float3 operations
    float3 abs(const float3& vec);
    float3 normalize(const float3& vec);
    float dot(const float3& first, const float3& second);
    float angle(const float3& first, const float3& second);
    float3 rotate(const float3& vec, const float3& axis, float angle);
    float3 reflect(const float3& first, float3 normal);
    float3 cross(const float3& first, const float3& second);

    // Float4 operations
    float4 abs(const float4& vec);
    float4 normalize(const float4& vec);
    float dot(const float4& first, const float4& second);
    float angle(const float4& first, const float4& second);

    // Float2x2
    float2x2 abs(const float2x2& mat);
    float2x2 inverse(const float2x2& mat);
    float2x2 transpose(const float2x2& mat);

    // Float3x3
    float3x3 abs(const float3x3& mat);
    float3x3 inverse(const float3x3& mat);
    float3x3 transpose(const float3x3& mat);

    // Float4x4
    float4x4 abs(const float4x4& mat);
    float4x4 inverse(const float4x4& mat);
    float4x4 transpose(const float4x4& mat);
}
