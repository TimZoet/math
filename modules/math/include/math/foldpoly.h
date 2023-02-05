#pragma once

namespace math
{
    template<typename V, typename T>
    V foldpoly(const V& x, const T c0) noexcept
    {
        return V(c0);
    }

    template<typename V, typename T, typename ...Ts>
    V foldpoly(const V& x, const T c0, const Ts... cn) noexcept
    {
        return (x * foldpoly(x, cn...)) + c0;
    }
}
