#pragma once

////////////////////////////////////////////////////////////////
// Current target includes.
////////////////////////////////////////////////////////////////

#include "math/aabb/aabb.h"
#include "math/matrix/matrix.h"

namespace math
{
    // Transform axis-aligned bounding box using a matrix, 
    // calculating the new AABB of the transformed corners.
    template<is_size<3> T>
    [[nodiscard]] AABB<T> operator*(const AABB<T>& aabb, const matrix<typename T::element_type, 4, 4>& m) noexcept
    {
        // Calculate all 8 transformed corners.
        const T c0 = m * T(aabb.lower.x, aabb.lower.y, aabb.lower.z);
        const T c1 = m * T(aabb.lower.x, aabb.lower.y, aabb.upper.z);
        const T c2 = m * T(aabb.lower.x, aabb.upper.y, aabb.lower.z);
        const T c3 = m * T(aabb.lower.x, aabb.upper.y, aabb.upper.z);
        const T c4 = m * T(aabb.upper.x, aabb.lower.y, aabb.lower.z);
        const T c5 = m * T(aabb.upper.x, aabb.lower.y, aabb.upper.z);
        const T c6 = m * T(aabb.upper.x, aabb.upper.y, aabb.lower.z);
        const T c7 = m * T(aabb.upper.x, aabb.upper.y, aabb.upper.z);

        T lower = pos_infinity<T>();
        T upper = neg_infinity<T>();

        // Lower bound.
        lower = min(lower, c0);
        lower = min(lower, c1);
        lower = min(lower, c2);
        lower = min(lower, c3);
        lower = min(lower, c4);
        lower = min(lower, c5);
        lower = min(lower, c6);
        lower = min(lower, c7);

        // Upper bound.
        upper = max(upper, c0);
        upper = max(upper, c1);
        upper = max(upper, c2);
        upper = max(upper, c3);
        upper = max(upper, c4);
        upper = max(upper, c5);
        upper = max(upper, c6);
        upper = max(upper, c7);

        return AABB<T>(lower, upper);
    }

    template<is_size<3> T>
    [[nodiscard]] AABB<T> operator*(const matrix<typename T::element_type, 4, 4>& m, const AABB<T>& aabb) noexcept
    {
        return aabb * m;
    }

    ////////////////////////////////////////////////////////////////
    // Area.
    ////////////////////////////////////////////////////////////////

    template<is_size<3> T>
    [[nodiscard]] typename T::element_type area(const AABB<T>& lhs) noexcept
    {
        const auto v = lhs.upper - lhs.lower;
        return T::element_type(2) * (v.x * (v.y + v.z) + v.y * v.z);
    }
}