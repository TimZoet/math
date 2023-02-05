#pragma once

#include "math/compilation_info.h"
#include "math/constants.h"
#include "math/math_functions.h"
#include "math/space_conversion.h"

#include "math/aabb/aabb.h"
#include "math/aabb/aabb2.h"
#include "math/aabb/aabb3.h"

#include "math/matrix/matrix.h"
#include "math/matrix/mat4x4.h"
//#include "math/matrix/simd/mat4x4fa.h"

#include "math/vector/vector.h"
#include "math/vector/vec2.h"
#include "math/vector/vec3.h"
#include "math/vector/vec4.h"
#include "math/vector/vec8.h"
#include "math/vector/vector_type_traits.h"

#include "math/vector/simd/vec3ba.h"
#include "math/vector/simd/vec3fa.h"
#include "math/vector/simd/vec3ia.h"
#include "math/vector/simd/vec4ba.h"
#include "math/vector/simd/vec4fa.h"
#include "math/vector/simd/vec4ia.h"
#include "math/vector/simd/vec8ba.h"
#include "math/vector/simd/vec8fa.h"
#include "math/vector/simd/vec8ia.h"

namespace math
{
    // TODO: naming of the integer types, could that be better?
    // Once that is done, ctrl+f on all normal usages of math::vec and replace them by these ones.
    using float2 = vec<float, 2>;
    using float3 = vec<float, 3>;
    using float4 = vec<float, 4>;

    using double2 = vec<double, 2>;
    using double3 = vec<double, 3>;
    using double4 = vec<double, 4>;

    using sbyte2 = vec<int8_t, 2>;
    using sbyte3 = vec<int8_t, 3>;
    using sbyte4 = vec<int8_t, 4>;
    using ubyte2 = vec<uint8_t, 2>;
    using ubyte3 = vec<uint8_t, 3>;
    using ubyte4 = vec<uint8_t, 4>;

    using short2 = vec<int16_t, 2>;
    using short3 = vec<int16_t, 3>;
    using short4 = vec<int16_t, 4>;
    using ushort2 = vec<uint16_t, 2>;
    using ushort3 = vec<uint16_t, 3>;
    using ushort4 = vec<uint16_t, 4>;

    using int2 = vec<int32_t, 2>;
    using int3 = vec<int32_t, 3>;
    using int4 = vec<int32_t, 4>;
    using uint2 = vec<uint32_t, 2>;
    using uint3 = vec<uint32_t, 3>;
    using uint4 = vec<uint32_t, 4>;

    using long2 = vec<int64_t, 2>;
    using long3 = vec<int64_t, 3>;
    using long4 = vec<int64_t, 4>;
    using ulong2 = vec<uint64_t, 2>;
    using ulong3 = vec<uint64_t, 3>;
    using ulong4 = vec<uint64_t, 4>;

    using mat3x3f = matrix<float, 3, 3>;
    using mat4x4f = matrix<float, 4, 4>;

    using quaternion = float4;

    template<size_t N>
    using floatN = vec<float, N>;

    template<size_t N>
    using doubleN = vec<double, N>;

    template<size_t N>
    using sbyteN = vec<int8_t, N>;
    template<size_t N>
    using ubyteN = vec<uint8_t, N>;

    template<size_t N>
    using shortN = vec<int16_t, N>;
    template<size_t N>
    using ushortN = vec<uint16_t, N>;

    template<size_t N>
    using intN = vec<int32_t, N>;
    template<size_t N>
    using uintN = vec<uint32_t, N>;

    template<size_t N>
    using longN = vec<int64_t, N>;
    template<size_t N>
    using ulongN = vec<uint64_t, N>;
}