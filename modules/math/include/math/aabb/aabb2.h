#pragma once

////////////////////////////////////////////////////////////////
// Current target includes.
////////////////////////////////////////////////////////////////

#include "math/aabb/aabb.h"

namespace math
{
    ////////////////////////////////////////////////////////////////
    // Area.
    ////////////////////////////////////////////////////////////////

    template<is_size<2> T>
    [[nodiscard]] typename T::element_type area(const AABB<T>& lhs) noexcept { return reduce_mul(lhs.upper - lhs.lower); }
}