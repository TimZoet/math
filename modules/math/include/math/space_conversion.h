#pragma once

////////////////////////////////////////////////////////////////
// Current target includes.
////////////////////////////////////////////////////////////////

#include "math/vector/vector.h"
#include "math/vector/vec2.h"
#include "math/vector/vec3.h"
#include "math/vector/vec4.h"

namespace math
{
    // TODO: This stuff probably should not be in the math library.
    
    inline void create_tangent_space(math::vec<float, 3>& T, math::vec<float, 3>& B, const math::vec<float, 3>& N) noexcept
    {
        if (math::abs(N.z) > 0.5f)
            T = cross(N, math::vec<float, 3>(1.0f, 0, 0));
        else
            T = cross(N, math::vec<float, 3>(0, 0, 1.0f));
        B = cross(T, N);
    }

    [[nodiscard]] inline math::vec<float, 3> tangent_to_world(const math::vec<float, 3>& v, const math::vec<float, 3>& T, const math::vec<float, 3>& B, const math::vec<float, 3>& N) noexcept
    {
        return normalize(math::vec<float, 3>(
            T.x * v.x + B.x * v.y + N.x * v.z,
            T.y * v.x + B.y * v.y + N.y * v.z,
            T.z * v.x + B.z * v.y + N.z * v.z
            ));
    }

    [[nodiscard]] inline math::vec<float, 3> world_to_tangent(const math::vec<float, 3>& v, const math::vec<float, 3>& T, const math::vec<float, 3>& B, const math::vec<float, 3>& N) noexcept
    {
        return normalize(math::vec<float, 3>(
            T.x * v.x + T.y * v.y + T.z * v.z,
            B.x * v.x + B.y * v.y + B.z * v.z,
            N.x * v.x + N.y * v.y + N.z * v.z
            ));
    }
}
