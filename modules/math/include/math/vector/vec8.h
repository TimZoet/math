#pragma once

////////////////////////////////////////////////////////////////
// Standard includes.
////////////////////////////////////////////////////////////////

#include <cassert>
#include <iostream>

////////////////////////////////////////////////////////////////
// Current target includes.
////////////////////////////////////////////////////////////////

#include "math/vector/vector.h"
#include "math/vector/vec2.h"
#include "math/vector/vec3.h"
#include "math/vector/vec4.h"

namespace math
{
    template<typename T>
    struct vec<T, 8>
    {
        static constexpr size_t size = 8;
        using element_type = T;

        T a, b, c, d, e, f, g, h;

        ////////////////////////////////////////////////////////////////
        // Constructors.
        ////////////////////////////////////////////////////////////////

        // Default.

        [[nodiscard]] vec() noexcept : a(0), b(0), c(0), d(0), e(0), f(0), g(0), h(0) {}

        // From values.

        [[nodiscard]] explicit vec(const T v) noexcept : a(v), b(v), c(v), d(v), e(v), f(v), g(v), h(v) {}

        [[nodiscard]] vec(const T a, const T b, const T c, const T d, const T e, const T f, const T g, const T h) noexcept : a(a), b(b), c(c), d(d), e(e), f(f), g(g), h(h) {}

        // From convertible values.

        template<std::convertible_to<T> U>
        [[nodiscard]] explicit vec(const U rhs) :
            a(static_cast<T>(rhs)), b(static_cast<T>(rhs)), c(static_cast<T>(rhs)), d(static_cast<T>(rhs)),
            e(static_cast<T>(rhs)), f(static_cast<T>(rhs)), g(static_cast<T>(rhs)), h(static_cast<T>(rhs))
        {}

        template<std::convertible_to<T> U>
        [[nodiscard]] vec(const U a, const U b, const U c, const U d, const U e, const U f, const U g, const U h) :
            a(static_cast<T>(a)), b(static_cast<T>(b)), c(static_cast<T>(c)), d(static_cast<T>(d)),
            e(static_cast<T>(e)), f(static_cast<T>(f)), g(static_cast<T>(g)), h(static_cast<T>(h))
        {}

        // From pointer.

        [[nodiscard]] explicit vec(const T* ptr) : a(ptr[0]), b(ptr[1]), c(ptr[2]), d(ptr[3]), e(ptr[4]), f(ptr[5]), g(ptr[6]), h(ptr[7]) {}

        // Copy.

        [[nodiscard]] vec(const vec<T, 8>& rhs) noexcept : a(rhs.a), b(rhs.b), c(rhs.c), d(rhs.d), e(rhs.e), f(rhs.f), g(rhs.g), h(rhs.h) {}

        // Move.

        [[nodiscard]] vec(vec<T, 8>&& rhs) noexcept : a(rhs.a), b(rhs.b), c(rhs.c), d(rhs.d), e(rhs.e), f(rhs.f), g(rhs.g), h(rhs.h) {}

        // Copy from convertible.

        template<std::convertible_to<T> U>
        [[nodiscard]] explicit vec(const vec<U, 8>& rhs) :
            a(static_cast<T>(rhs.a)), b(static_cast<T>(rhs.b)), c(static_cast<T>(rhs.c)), d(static_cast<T>(rhs.d)),
            e(static_cast<T>(rhs.e)), f(static_cast<T>(rhs.f)), g(static_cast<T>(rhs.g)), h(static_cast<T>(rhs.h))
        {}

        // Move from convertible.
        
        template<std::convertible_to<T> U>
        [[nodiscard]] vec(vec<U, 8>&& rhs) :
            a(static_cast<T>(rhs.a)), b(static_cast<T>(rhs.b)), c(static_cast<T>(rhs.c)), d(static_cast<T>(rhs.d)),
            e(static_cast<T>(rhs.e)), f(static_cast<T>(rhs.f)), g(static_cast<T>(rhs.g)), h(static_cast<T>(rhs.h))
        {}

        ////////////////////////////////////////////////////////////////
        // Assignment operators.
        ////////////////////////////////////////////////////////////////

        // Copy.

        vec<T, 8>& operator=(const vec<T, 8>& rhs) noexcept
        {
            a = rhs.a; b = rhs.b; c = rhs.c; d = rhs.d;
            e = rhs.e; f = rhs.f; g = rhs.g; h = rhs.h;
            return *this;
        }

        // Move.

        vec<T, 8>& operator=(vec<T, 8>&& rhs) noexcept
        {
            a = rhs.a; b = rhs.b; c = rhs.c; d = rhs.d;
            e = rhs.e; f = rhs.f; g = rhs.g; h = rhs.h;
            return *this;
        }

        // Assign from value.

        vec<T, 8>& operator=(const T rhs) noexcept
        {
            a = rhs; b = rhs; c = rhs; d = rhs;
            e = rhs; f = rhs; g = rhs; h = rhs;
            return *this;
        }

        // Assign from convertible value.

        template<std::convertible_to<T> U>
        vec<T, 8>& operator=(const U rhs)
        {
            a = static_cast<T>(rhs); b = static_cast<T>(rhs); c = static_cast<T>(rhs); d = static_cast<T>(rhs);
            e = static_cast<T>(rhs); f = static_cast<T>(rhs); g = static_cast<T>(rhs); h = static_cast<T>(rhs);
            return *this;
        }

        // Assign from convertible.

        template<std::convertible_to<T> U>
        vec<T, 8>& operator=(const vec<U, 8>& rhs)
        {
            a = static_cast<T>(rhs.a); b = static_cast<T>(rhs.b); c = static_cast<T>(rhs.c); d = static_cast<T>(rhs.d);
            e = static_cast<T>(rhs.e); f = static_cast<T>(rhs.f); g = static_cast<T>(rhs.g); h = static_cast<T>(rhs.h);
            return *this;
        }

        ////////////////////////////////////////////////////////////////
        // Defaulted constructors and operators.
        ////////////////////////////////////////////////////////////////

        ~vec() noexcept = default;

        ////////////////////////////////////////////////////////////////
        // Element access.
        ////////////////////////////////////////////////////////////////

        [[nodiscard]] const T& operator[](const size_t i) const { assert(i < 8); return (&a)[i]; }

        [[nodiscard]] T& operator[](const size_t i) { assert(i < 8); return (&a)[i]; }
    };

    ////////////////////////////////////////////////////////////////
    // Check for special values.
    ////////////////////////////////////////////////////////////////

    template<typename T>
    [[nodiscard]] vec<bool, 8> is_finite(const vec<T, 8>& lhs) noexcept
    {
        return vec<bool, 8>(
            std::isfinite(lhs.a), std::isfinite(lhs.b), std::isfinite(lhs.c), std::isfinite(lhs.d),
            std::isfinite(lhs.e), std::isfinite(lhs.f), std::isfinite(lhs.g), std::isfinite(lhs.h)
            ); 
    }

    template<typename T>
    [[nodiscard]] vec<bool, 8> is_infinite(const vec<T, 8>& lhs) noexcept
    {
        return vec<bool, 8>(
            std::isinf(lhs.a), std::isinf(lhs.b), std::isinf(lhs.c), std::isinf(lhs.d),
            std::isinf(lhs.e), std::isinf(lhs.f), std::isinf(lhs.g), std::isinf(lhs.h)
            );
    }

    template<typename T>
    [[nodiscard]] vec<bool, 8> is_neg_infinite(const vec<T, 8>& lhs) noexcept
    {
        return vec<bool, 8>(
            lhs.a == -std::numeric_limits<T>::infinite(), lhs.b == -std::numeric_limits<T>::infinite(), lhs.c == -std::numeric_limits<T>::infinite(), lhs.d == -std::numeric_limits<T>::infinite(),
            lhs.e == -std::numeric_limits<T>::infinite(), lhs.f == -std::numeric_limits<T>::infinite(), lhs.g == -std::numeric_limits<T>::infinite(), lhs.h == -std::numeric_limits<T>::infinite()
            );
    }

    template<typename T>
    [[nodiscard]] vec<bool, 8> is_pos_infinite(const vec<T, 8>& lhs) noexcept
    {
        return vec<bool, 8>(
            lhs.a == std::numeric_limits<T>::infinite(), lhs.b == std::numeric_limits<T>::infinite(), lhs.c == std::numeric_limits<T>::infinite(), lhs.d == std::numeric_limits<T>::infinite(),
            lhs.e == std::numeric_limits<T>::infinite(), lhs.f == std::numeric_limits<T>::infinite(), lhs.g == std::numeric_limits<T>::infinite(), lhs.h == std::numeric_limits<T>::infinite()
            );
    }

    template<typename T>
    [[nodiscard]] vec<bool, 8> is_NaN(const vec<T, 8>& lhs) noexcept
    {
        return vec<bool, 8>(
            std::isnan(lhs.a), std::isnan(lhs.b), std::isnan(lhs.c), std::isnan(lhs.d),
            std::isnan(lhs.e), std::isnan(lhs.f), std::isnan(lhs.g), std::isnan(lhs.h)
            );
    }

    template<typename T>
    [[nodiscard]] vec<bool, 8> is_normal(const vec<T, 8>& lhs) noexcept
    {
        return vec<bool, 8>(
            std::isnormal(lhs.a), std::isnormal(lhs.b), std::isnormal(lhs.c), std::isnormal(lhs.d),
            std::isnormal(lhs.e), std::isnormal(lhs.f), std::isnormal(lhs.g), std::isnormal(lhs.h)
            );
    }

    ////////////////////////////////////////////////////////////////
    // Arithmetic operators.
    ////////////////////////////////////////////////////////////////

    template<arithmetic T>
    [[nodiscard]] vec<T, 8> operator+(const vec<T, 8>& lhs, const vec<T, 8>& rhs) noexcept
    {
        return vec<T, 8>(
            lhs.a + rhs.a, lhs.b + rhs.b, lhs.c + rhs.c, lhs.d + rhs.d,
            lhs.e + rhs.e, lhs.f + rhs.f, lhs.g + rhs.g, lhs.h + rhs.h
            );
    }

    template<arithmetic T>
    [[nodiscard]] vec<T, 8> operator+(const vec<T, 8>& lhs, const T rhs) noexcept
    {
        return vec<T, 8>(
            lhs.a + rhs, lhs.b + rhs, lhs.c + rhs, lhs.d + rhs,
            lhs.e + rhs, lhs.f + rhs, lhs.g + rhs, lhs.h + rhs
            );
    }

    template<arithmetic T>
    [[nodiscard]] vec<T, 8> operator+(const T lhs, const vec<T, 8>& rhs) noexcept
    {
        return vec<T, 8>(
            lhs + rhs.a, lhs + rhs.b, lhs + rhs.c, lhs + rhs.d,
            lhs + rhs.e, lhs + rhs.f, lhs + rhs.g, lhs + rhs.h
            );
    }

    template<arithmetic T>
    [[nodiscard]] vec<T, 8> operator-(const vec<T, 8>& lhs, const vec<T, 8>& rhs) noexcept
    {
        return vec<T, 8>(
            lhs.a - rhs.a, lhs.b - rhs.b, lhs.c - rhs.c, lhs.d - rhs.d,
            lhs.e - rhs.e, lhs.f - rhs.f, lhs.g - rhs.g, lhs.h - rhs.h
            );
    }

    template<arithmetic T>
    [[nodiscard]] vec<T, 8> operator-(const vec<T, 8>& lhs, const T rhs) noexcept
    {
        return vec<T, 8>(
            lhs.a - rhs, lhs.b - rhs, lhs.c - rhs, lhs.d - rhs,
            lhs.e - rhs, lhs.f - rhs, lhs.g - rhs, lhs.h - rhs
            );
    }

    template<arithmetic T>
    [[nodiscard]] vec<T, 8> operator-(const T lhs, const vec<T, 8>& rhs) noexcept
    {
        return vec<T, 8>(
            lhs - rhs.a, lhs - rhs.b, lhs - rhs.c, lhs - rhs.d,
            lhs - rhs.e, lhs - rhs.f, lhs - rhs.g, lhs - rhs.h
            );
    }

    template<arithmetic T>
    [[nodiscard]] vec<T, 8> operator-(const vec<T, 8>& lhs) noexcept
    {
        return vec<T, 8>(
            -lhs.a, -lhs.b, -lhs.c, -lhs.d,
            -lhs.e, -lhs.f, -lhs.g, -lhs.h
            );
    }

    template<arithmetic T>
    [[nodiscard]] vec<T, 8> operator*(const vec<T, 8>& lhs, const vec<T, 8>& rhs) noexcept
    {
        return vec<T, 8>(
            lhs.a * rhs.a, lhs.b * rhs.b, lhs.c * rhs.c, lhs.d * rhs.d,
            lhs.e * rhs.e, lhs.f * rhs.f, lhs.g * rhs.g, lhs.h * rhs.h
            );
    }

    template<arithmetic T>
    [[nodiscard]] vec<T, 8> operator*(const vec<T, 8>& lhs, const T rhs) noexcept
    {
        return vec<T, 8>(
            lhs.a * rhs, lhs.b * rhs, lhs.c * rhs, lhs.d * rhs,
            lhs.e * rhs, lhs.f * rhs, lhs.g * rhs, lhs.h * rhs
            );
    }

    template<arithmetic T>
    [[nodiscard]] vec<T, 8> operator*(const T lhs, const vec<T, 8>& rhs) noexcept
    {
        return vec<T, 8>(
            lhs * rhs.a, lhs * rhs.b, lhs * rhs.c, lhs * rhs.d,
            lhs * rhs.e, lhs * rhs.f, lhs * rhs.g, lhs * rhs.h
            );
    }

    template<arithmetic T>
    [[nodiscard]] vec<T, 8> operator/(const vec<T, 8>& lhs, const vec<T, 8>& rhs) noexcept
    {
        return vec<T, 8>(
            lhs.a / rhs.a, lhs.b / rhs.b, lhs.c / rhs.c, lhs.d / rhs.d,
            lhs.e / rhs.e, lhs.f / rhs.f, lhs.g / rhs.g, lhs.h / rhs.h
            );
    }

    template<arithmetic T>
    [[nodiscard]] vec<T, 8> operator/(const vec<T, 8>& lhs, const T rhs) noexcept
    {
        const T inv = T(1) / rhs;
        return vec<T, 8>(
            lhs.a * inv, lhs.b * inv, lhs.c * inv, lhs.d * inv,
            lhs.e * inv, lhs.f * inv, lhs.g * inv, lhs.h * inv
            );
    }

    template<arithmetic T>
    [[nodiscard]] vec<T, 8> operator/(const T lhs, const vec<T, 8>& rhs) noexcept
    {
        return vec<T, 8>(
            lhs / rhs.a, lhs / rhs.b, lhs / rhs.c, lhs / rhs.d,
            lhs / rhs.e, lhs / rhs.f, lhs / rhs.g, lhs / rhs.h
            );
    }

    ////////////////////////////////////////////////////////////////
    // Comparison operators.
    ////////////////////////////////////////////////////////////////

    template<std::equality_comparable T>
    [[nodiscard]] bool operator==(const vec<T, 8>& lhs, const vec<T, 8>& rhs) noexcept
    {
        return lhs.a == rhs.a && lhs.b == rhs.b && lhs.c == rhs.c && lhs.d == rhs.d && 
            lhs.e == rhs.e && lhs.f == rhs.f && lhs.g == rhs.g && lhs.h == rhs.h;
    }

    template<std::equality_comparable T>
    [[nodiscard]] bool operator!=(const vec<T, 8>& lhs, const vec<T, 8>& rhs) noexcept
    {
        return lhs.a == rhs.a || lhs.b == rhs.b || lhs.c == rhs.c || lhs.d == rhs.d || 
            lhs.e == rhs.e || lhs.f == rhs.f || lhs.g == rhs.g || lhs.h == rhs.h;
    }

    ////////////////////////////////////////////////////////////////
    // Per-element comparisons.
    ////////////////////////////////////////////////////////////////

    template<std::totally_ordered T>
    [[nodiscard]] vec<bool, 8> cmpeq(const vec<T, 4>& lhs, const vec<T, 4>& rhs) noexcept
    {
        return vec<bool, 8>(
            lhs.a == rhs.a, lhs.b == rhs.b, lhs.c == rhs.c, lhs.d == rhs.d,
            lhs.e == rhs.e, lhs.f == rhs.f, lhs.g == rhs.g, lhs.h == rhs.h
            );
    }

    template<std::totally_ordered T>
    [[nodiscard]] vec<bool, 8> cmpeq(const vec<T, 4>& lhs, const T rhs) noexcept
    {
        return vec<T, 8>(
            lhs.a == rhs, lhs.b == rhs, lhs.c == rhs, lhs.d == rhs,
            lhs.e == rhs, lhs.f == rhs, lhs.g == rhs, lhs.h == rhs
            );
    }

    template<std::totally_ordered T>
    [[nodiscard]] vec<bool, 8> cmpeq(const T lhs, const vec<T, 4>& rhs) noexcept
    {
        return vec<T, 8>(
            lhs == rhs.a, lhs == rhs.b, lhs == rhs.c, lhs == rhs.d,
            lhs == rhs.e, lhs == rhs.f, lhs == rhs.g, lhs == rhs.h
            );
    }

    template<std::totally_ordered T>
    [[nodiscard]] vec<bool, 8> cmpneq(const vec<T, 4>& lhs, const vec<T, 4>& rhs) noexcept
    {
        return vec<bool, 8>(
            lhs.a != rhs.a, lhs.b != rhs.b, lhs.c != rhs.c, lhs.d != rhs.d,
            lhs.e != rhs.e, lhs.f != rhs.f, lhs.g != rhs.g, lhs.h != rhs.h
            );
    }

    template<std::totally_ordered T>
    [[nodiscard]] vec<bool, 8> cmpneq(const vec<T, 4>& lhs, const T rhs) noexcept
    {
        return vec<T, 8>(
            lhs.a != rhs, lhs.b != rhs, lhs.c != rhs, lhs.d != rhs,
            lhs.e != rhs, lhs.f != rhs, lhs.g != rhs, lhs.h != rhs
            );
    }

    template<std::totally_ordered T>
    [[nodiscard]] vec<bool, 8> cmpneq(const T lhs, const vec<T, 4>& rhs) noexcept
    {
        return vec<T, 8>(
            lhs != rhs.a, lhs != rhs.b, lhs != rhs.c, lhs != rhs.d,
            lhs != rhs.e, lhs != rhs.f, lhs != rhs.g, lhs != rhs.h
            );
    }

    template<std::totally_ordered T>
    [[nodiscard]] vec<bool, 8> cmplt(const vec<T, 4>& lhs, const vec<T, 4>& rhs) noexcept
    {
        return vec<bool, 8>(
            lhs.a < rhs.a, lhs.b < rhs.b, lhs.c < rhs.c, lhs.d < rhs.d,
            lhs.e < rhs.e, lhs.f < rhs.f, lhs.g < rhs.g, lhs.h < rhs.h
            );
    }

    template<std::totally_ordered T>
    [[nodiscard]] vec<bool, 8> cmplt(const vec<T, 4>& lhs, const T rhs) noexcept
    {
        return vec<T, 8>(
            lhs.a < rhs, lhs.b < rhs, lhs.c < rhs, lhs.d < rhs,
            lhs.e < rhs, lhs.f < rhs, lhs.g < rhs, lhs.h < rhs
            );
    }

    template<std::totally_ordered T>
    [[nodiscard]] vec<bool, 8> cmplt(const T lhs, const vec<T, 4>& rhs) noexcept
    {
        return vec<T, 8>(
            lhs < rhs.a, lhs < rhs.b, lhs < rhs.c, lhs < rhs.d,
            lhs < rhs.e, lhs < rhs.f, lhs < rhs.g, lhs < rhs.h
            );
    }

    template<std::totally_ordered T>
    [[nodiscard]] vec<bool, 8> cmpgt(const vec<T, 4>& lhs, const vec<T, 4>& rhs) noexcept
    {
        return vec<bool, 8>(
            lhs.a > rhs.a, lhs.b > rhs.b, lhs.c > rhs.c, lhs.d > rhs.d,
            lhs.e > rhs.e, lhs.f > rhs.f, lhs.g > rhs.g, lhs.h > rhs.h
            );
    }

    template<std::totally_ordered T>
    [[nodiscard]] vec<bool, 8> cmpgt(const vec<T, 4>& lhs, const T rhs) noexcept
    {
        return vec<T, 8>(
            lhs.a > rhs, lhs.b > rhs, lhs.c > rhs, lhs.d > rhs,
            lhs.e > rhs, lhs.f > rhs, lhs.g > rhs, lhs.h > rhs
            );
    }

    template<std::totally_ordered T>
    [[nodiscard]] vec<bool, 8> cmpgt(const T lhs, const vec<T, 4>& rhs) noexcept
    {
        return vec<T, 8>(
            lhs > rhs.a, lhs > rhs.b, lhs > rhs.c, lhs > rhs.d,
            lhs > rhs.e, lhs > rhs.f, lhs > rhs.g, lhs > rhs.h
            );
    }

    template<std::totally_ordered T>
    [[nodiscard]] vec<bool, 8> cmple(const vec<T, 4>& lhs, const vec<T, 4>& rhs) noexcept
    {
        return vec<bool, 8>(
            lhs.a <= rhs.a, lhs.b <= rhs.b, lhs.c <= rhs.c, lhs.d <= rhs.d,
            lhs.e <= rhs.e, lhs.f <= rhs.f, lhs.g <= rhs.g, lhs.h <= rhs.h
            );
    }

    template<std::totally_ordered T>
    [[nodiscard]] vec<bool, 8> cmple(const vec<T, 4>& lhs, const T rhs) noexcept
    {
        return vec<T, 8>(
            lhs.a <= rhs, lhs.b <= rhs, lhs.c <= rhs, lhs.d <= rhs,
            lhs.e <= rhs, lhs.f <= rhs, lhs.g <= rhs, lhs.h <= rhs
            );
    }

    template<std::totally_ordered T>
    [[nodiscard]] vec<bool, 8> cmple(const T lhs, const vec<T, 4>& rhs) noexcept
    {
        return vec<T, 8>(
            lhs <= rhs.a, lhs <= rhs.b, lhs <= rhs.c, lhs <= rhs.d,
            lhs <= rhs.e, lhs <= rhs.f, lhs <= rhs.g, lhs <= rhs.h
            );
    }

    template<std::totally_ordered T>
    [[nodiscard]] vec<bool, 8> cmpge(const vec<T, 4>& lhs, const vec<T, 4>& rhs) noexcept
    {
        return vec<bool, 8>(
            lhs.a >= rhs.a, lhs.b >= rhs.b, lhs.c >= rhs.c, lhs.d >= rhs.d,
            lhs.e >= rhs.e, lhs.f >= rhs.f, lhs.g >= rhs.g, lhs.h >= rhs.h
            );
    }

    template<std::totally_ordered T>
    [[nodiscard]] vec<bool, 8> cmpge(const vec<T, 4>& lhs, const T rhs) noexcept
    {
        return vec<T, 8>(
            lhs.a >= rhs, lhs.b >= rhs, lhs.c >= rhs, lhs.d >= rhs,
            lhs.e >= rhs, lhs.f >= rhs, lhs.g >= rhs, lhs.h >= rhs
            );
    }

    template<std::totally_ordered T>
    [[nodiscard]] vec<bool, 8> cmpge(const T lhs, const vec<T, 4>& rhs) noexcept
    {
        return vec<T, 8>(
            lhs >= rhs.a, lhs >= rhs.b, lhs >= rhs.c, lhs >= rhs.d,
            lhs >= rhs.e, lhs >= rhs.f, lhs >= rhs.g, lhs >= rhs.h
            );
    }

    ////////////////////////////////////////////////////////////////
    // Dot product etc.
    ////////////////////////////////////////////////////////////////

    template<arithmetic T>
    [[nodiscard]] T dot(const vec<T, 8>& lhs, const vec<T, 8>& rhs) noexcept
    {
        return lhs.a * rhs.a + lhs.b * rhs.b + lhs.c * rhs.c + lhs.d * rhs.d +
            lhs.e * rhs.e + lhs.f * rhs.f + lhs.g * rhs.g + lhs.h * rhs.h;
    }

    template<arithmetic T>
    [[nodiscard]] vec<T, 8> lerp(const vec<T, 8>& a, const vec<T, 8>& b, const vec<T, 8>& t) noexcept
    {
        return vec<T, 8>(
            lerp(a.a, b.a, t.a), lerp(a.b, b.b, t.b), lerp(a.c, b.c, t.c), lerp(a.d, b.d, t.d),
            lerp(a.e, b.e, t.e), lerp(a.f, b.f, t.f), lerp(a.g, b.g, t.g), lerp(a.h, b.h, t.h)
            );
    }

    template<arithmetic T>
    [[nodiscard]] vec<T, 8> lerp(const vec<T, 8>& a, const vec<T, 8>& b, const T t) noexcept
    {
        return vec<T, 8>(
            lerp(a.a, b.a, t), lerp(a.b, b.b, t), lerp(a.c, b.c, t), lerp(a.d, b.d, t),
            lerp(a.e, b.e, t), lerp(a.f, b.f, t), lerp(a.g, b.g, t), lerp(a.h, b.h, t)
            );
    }

    ////////////////////////////////////////////////////////////////
    // Trigonometry.
    ////////////////////////////////////////////////////////////////

    template<std::floating_point T>
    [[nodiscard]] vec<T, 8> acos(const vec<T, 8>& lhs) noexcept
    {
        return vec<T, 8>(
            acos(lhs.a), acos(lhs.b), acos(lhs.c), acos(lhs.d),
            acos(lhs.e), acos(lhs.f), acos(lhs.g), acos(lhs.h)
            );
    }

    template<std::floating_point T>
    [[nodiscard]] vec<T, 8> asin(const vec<T, 8>& lhs) noexcept
    {
        return vec<T, 8>(
            asin(lhs.a), asin(lhs.b), asin(lhs.c), asin(lhs.d),
            asin(lhs.e), asin(lhs.f), asin(lhs.g), asin(lhs.h)
            );
    }

    template<std::floating_point T>
    [[nodiscard]] vec<T, 8> atan(const vec<T, 8>& lhs) noexcept
    {
        return vec<T, 8>(
            atan(lhs.a), atan(lhs.b), atan(lhs.c), atan(lhs.d),
            atan(lhs.e), atan(lhs.f), atan(lhs.g), atan(lhs.h)
            );
    }

    template<std::floating_point T>
    [[nodiscard]] vec<T, 8> atan2(const vec<T, 8>& lhs, const vec<T, 8>& rhs) noexcept
    {
        return vec<T, 8>(
            atan2(lhs.a, rhs.a), atan2(lhs.b, rhs.b), atan2(lhs.c, rhs.c), atan2(lhs.d, rhs.d),
            atan2(lhs.e, rhs.e), atan2(lhs.f, rhs.f), atan2(lhs.g, rhs.g), atan2(lhs.h, rhs.h)
            );
    }

    template<std::floating_point T>
    [[nodiscard]] vec<T, 8> cos(const vec<T, 8>& lhs) noexcept
    {
        return vec<T, 8>(
            cos(lhs.a), cos(lhs.b), cos(lhs.c), cos(lhs.d),
            cos(lhs.e), cos(lhs.f), cos(lhs.g), cos(lhs.h)
            );
    }

    template<std::floating_point T>
    [[nodiscard]] vec<T, 8> cosh(const vec<T, 8>& lhs) noexcept
    {
        return vec<T, 8>(
            cosh(lhs.a), cosh(lhs.b), cosh(lhs.c), cosh(lhs.d),
            cosh(lhs.e), cosh(lhs.f), cosh(lhs.g), cosh(lhs.h)
            );
    }

    template<std::floating_point T>
    [[nodiscard]] vec<T, 8> sin(const vec<T, 8>& lhs) noexcept
    {
        return vec<T, 8>(
            sin(lhs.a), sin(lhs.b), sin(lhs.c), sin(lhs.d),
            sin(lhs.e), sin(lhs.f), sin(lhs.g), sin(lhs.h)
            );
    }

    template<std::floating_point T>
    [[nodiscard]] vec<T, 8> sinh(const vec<T, 8>& lhs) noexcept
    {
        return vec<T, 8>(
            sinh(lhs.a), sinh(lhs.b), sinh(lhs.c), sinh(lhs.d),
            sinh(lhs.e), sinh(lhs.f), sinh(lhs.g), sinh(lhs.h)
            );
    }

    template<std::floating_point T>
    [[nodiscard]] vec<T, 8> tan(const vec<T, 8>& lhs) noexcept
    {
        return vec<T, 8>(
            tan(lhs.a), tan(lhs.b), tan(lhs.c), tan(lhs.d),
            tan(lhs.e), tan(lhs.f), tan(lhs.g), tan(lhs.h)
            );
    }

    template<std::floating_point T>
    [[nodiscard]] vec<T, 8> tanh(const vec<T, 8>& lhs) noexcept
    {
        return vec<T, 8>(
            tanh(lhs.a), tanh(lhs.b), tanh(lhs.c), tanh(lhs.d),
            tanh(lhs.e), tanh(lhs.f), tanh(lhs.g), tanh(lhs.h)
            );
    }

    ////////////////////////////////////////////////////////////////
    // Exponential / Logarithmic.
    ////////////////////////////////////////////////////////////////

    template<std::floating_point T>
    [[nodiscard]] vec<T, 8> exp(const vec<T, 8>& lhs) noexcept
    {
        return vec<T, 8>(
            exp(lhs.a), exp(lhs.b), exp(lhs.c), exp(lhs.d),
            exp(lhs.e), exp(lhs.f), exp(lhs.g), exp(lhs.h)
            );
    }

    template<std::floating_point T>
    [[nodiscard]] vec<T, 8> exp2(const vec<T, 8>& lhs) noexcept
    {
        return vec<T, 8>(
            exp2(lhs.a), exp2(lhs.b), exp2(lhs.c), exp2(lhs.d),
            exp2(lhs.e), exp2(lhs.f), exp2(lhs.g), exp2(lhs.h)
            );
    }

    template<std::floating_point T>
    [[nodiscard]] vec<T, 8> log(const vec<T, 8>& lhs) noexcept
    {
        return vec<T, 8>(
            log(lhs.a), log(lhs.b), log(lhs.c), log(lhs.d),
            log(lhs.e), log(lhs.f), log(lhs.g), log(lhs.h)
            );
    }

    template<std::floating_point T>
    [[nodiscard]] vec<T, 8> log2(const vec<T, 8>& lhs) noexcept
    {
        return vec<T, 8>(
            log2(lhs.a), log2(lhs.b), log2(lhs.c), log2(lhs.d),
            log2(lhs.e), log2(lhs.f), log2(lhs.g), log2(lhs.h)
            );
    }

    template<std::floating_point T>
    [[nodiscard]] vec<T, 8> log10(const vec<T, 8>& lhs) noexcept
    {
        return vec<T, 8>(
            log10(lhs.a), log10(lhs.b), log10(lhs.c), log10(lhs.d),
            log10(lhs.e), log10(lhs.f), log10(lhs.g), log10(lhs.h)
            );
    }

    ////////////////////////////////////////////////////////////////
    // Power.
    ////////////////////////////////////////////////////////////////

    template<std::floating_point T>
    [[nodiscard]] vec<T, 8> pow(const vec<T, 8>& lhs, const vec<T, 8>& rhs) noexcept
    {
        return vec<T, 8>(
            pow(lhs.a, rhs.a), pow(lhs.b, rhs.b), pow(lhs.c, rhs.c), pow(lhs.d, rhs.d),
            pow(lhs.e, rhs.e), pow(lhs.f, rhs.f), pow(lhs.g, rhs.g), pow(lhs.h, rhs.h)
            );
    }

    template<std::floating_point T>
    [[nodiscard]] vec<T, 8> pow(const vec<T, 8>& lhs, const T rhs) noexcept
    {
        return vec<T, 8>(
            pow(lhs.a, rhs), pow(lhs.b, rhs), pow(lhs.c, rhs), pow(lhs.d, rhs),
            pow(lhs.e, rhs), pow(lhs.f, rhs), pow(lhs.g, rhs), pow(lhs.h, rhs)
            );
    }

    template<std::floating_point T>
    [[nodiscard]] vec<T, 8> sqrt(const vec<T, 8>& lhs) noexcept
    {
        return vec<T, 8>(
            sqrt(lhs.a), sqrt(lhs.b), sqrt(lhs.c), sqrt(lhs.d),
            sqrt(lhs.e), sqrt(lhs.f), sqrt(lhs.g), sqrt(lhs.h)
            );
    }

    template<std::floating_point T>
    [[nodiscard]] vec<T, 8> rsqrt(const vec<T, 8>& lhs) noexcept
    {
        return vec<T, 8>(
            rsqrt(lhs.a), rsqrt(lhs.b), rsqrt(lhs.c), rsqrt(lhs.d),
            rsqrt(lhs.e), rsqrt(lhs.f), rsqrt(lhs.g), rsqrt(lhs.h)
            );
    }

    ////////////////////////////////////////////////////////////////
    // Min/max, abs and clamp.
    ////////////////////////////////////////////////////////////////

    template<has_min T>
    [[nodiscard]] vec<T, 8> min(const vec<T, 8>& lhs, const vec<T, 8>& rhs) noexcept
    {
        return vec<T, 8>(
            min(lhs.a, rhs.a), min(lhs.b, rhs.b), min(lhs.c, rhs.c), min(lhs.d, rhs.d),
            min(lhs.e, rhs.e), min(lhs.f, rhs.f), min(lhs.g, rhs.g), min(lhs.h, rhs.h)
            );
    }

    template<has_min T>
    [[nodiscard]] vec<T, 8> min(const vec<T, 8>& lhs, const T rhs) noexcept
    {
        return vec<T, 8>(
            min(lhs.a, rhs), min(lhs.b, rhs), min(lhs.c, rhs), min(lhs.d, rhs),
            min(lhs.e, rhs), min(lhs.f, rhs), min(lhs.g, rhs), min(lhs.h, rhs)
            );
    }

    template<has_min T>
    [[nodiscard]] vec<T, 8> min(const T lhs, const vec<T, 8>& rhs) noexcept
    {
        return vec<T, 8>(
            min(lhs, rhs.a), min(lhs, rhs.b), min(lhs, rhs.c), min(lhs, rhs.d),
            min(lhs, rhs.e), min(lhs, rhs.f), min(lhs, rhs.g), min(lhs, rhs.h)
            );
    }

    template<has_max T>
    [[nodiscard]] vec<T, 8> max(const vec<T, 8>& lhs, const vec<T, 8>& rhs) noexcept
    {
        return vec<T, 8>(
            max(lhs.a, rhs.a), max(lhs.b, rhs.b), max(lhs.c, rhs.c), max(lhs.d, rhs.d),
            max(lhs.e, rhs.e), max(lhs.f, rhs.f), max(lhs.g, rhs.g), max(lhs.h, rhs.h)
            );
    }

    template<has_max T>
    [[nodiscard]] vec<T, 8> max(const vec<T, 8>& lhs, const T rhs) noexcept
    {
        return vec<T, 8>(
            max(lhs.a, rhs), max(lhs.b, rhs), max(lhs.c, rhs), max(lhs.d, rhs),
            max(lhs.e, rhs), max(lhs.f, rhs), max(lhs.g, rhs), max(lhs.h, rhs)
            );
    }

    template<has_max T>
    [[nodiscard]] vec<T, 8> max(const T lhs, const vec<T, 8>& rhs) noexcept
    {
        return vec<T, 8>(
            max(lhs, rhs.a), max(lhs, rhs.b), max(lhs, rhs.c), max(lhs, rhs.d),
            max(lhs, rhs.e), max(lhs, rhs.f), max(lhs, rhs.g), max(lhs, rhs.h)
            );
    }

    template<has_clamp T>
    [[nodiscard]] vec<T, 8> clamp(const vec<T, 8>& a, const vec<T, 8>& min, const vec<T, 8>& max) noexcept
    {
        return vec<T, 8>(
            clamp(a.a, min.a, max.a), clamp(a.b, min.b, max.b), clamp(a.c, min.c, max.c), clamp(a.d, min.d, max.d),
            clamp(a.e, min.e, max.e), clamp(a.f, min.f, max.f), clamp(a.g, min.g, max.g), clamp(a.h, min.h, max.h)
            );
    }

    template<has_clamp T>
    [[nodiscard]] vec<T, 8> clamp(const vec<T, 8>& a, const vec<T, 8>& min, const T max) noexcept
    {
        return vec<T, 8>(
            clamp(a.a, min.a, max), clamp(a.b, min.b, max), clamp(a.c, min.c, max), clamp(a.d, min.d, max),
            clamp(a.e, min.e, max), clamp(a.f, min.f, max), clamp(a.g, min.g, max), clamp(a.h, min.h, max)
            );
    }

    template<has_clamp T>
    [[nodiscard]] vec<T, 8> clamp(const vec<T, 8>& a, const T min, const vec<T, 8>& max) noexcept
    {
        return vec<T, 8>(
            clamp(a.a, min, max.a), clamp(a.b, min, max.b), clamp(a.c, min, max.c), clamp(a.d, min, max.d),
            clamp(a.e, min, max.e), clamp(a.f, min, max.f), clamp(a.g, min, max.g), clamp(a.h, min, max.h)
            );
    }

    template<has_clamp T>
    [[nodiscard]] vec<T, 8> clamp(const vec<T, 8>& a, const T min, const T max) noexcept
    {
        return vec<T, 8>(
            clamp(a.a, min, max), clamp(a.b, min, max), clamp(a.c, min, max), clamp(a.d, min, max),
            clamp(a.e, min, max), clamp(a.f, min, max), clamp(a.g, min, max), clamp(a.h, min, max)
            );
    }

    ////////////////////////////////////////////////////////////////
    // Rounding, abs, etc.
    ////////////////////////////////////////////////////////////////

    template<has_abs T>
    [[nodiscard]] vec<T, 8> abs(const vec<T, 8>& lhs) noexcept
    {
        return vec<T, 8>(
            abs(lhs.a), abs(lhs.b), abs(lhs.c), abs(lhs.d),
            abs(lhs.e), abs(lhs.f), abs(lhs.g), abs(lhs.h)
            );
    }

    template<has_ceil T>
    [[nodiscard]] vec<T, 8> ceil(const vec<T, 8>& lhs) noexcept
    {
        return vec<T, 8>(
            ceil(lhs.a), ceil(lhs.b), ceil(lhs.c), ceil(lhs.d),
            ceil(lhs.e), ceil(lhs.f), ceil(lhs.g), ceil(lhs.h)
            );
    }

    template<has_floor T>
    [[nodiscard]] vec<T, 8> floor(const vec<T, 8>& lhs) noexcept
    {
        return vec<T, 8>(
            floor(lhs.a), floor(lhs.b), floor(lhs.c), floor(lhs.d),
            floor(lhs.e), floor(lhs.f), floor(lhs.g), floor(lhs.h)
            );
    }

    template<has_frac T>
    [[nodiscard]] vec<T, 8> frac(const vec<T, 8>& lhs) noexcept
    {
        return vec<T, 8>(
            frac(lhs.a), frac(lhs.b), frac(lhs.c), frac(lhs.d),
            frac(lhs.e), frac(lhs.f), frac(lhs.g), frac(lhs.h)
            );
    }

    template<has_round T>
    [[nodiscard]] vec<T, 8> round(const vec<T, 8>& lhs) noexcept
    {
        return vec<T, 8>(
            round(lhs.a), round(lhs.b), round(lhs.c), round(lhs.d),
            round(lhs.e), round(lhs.f), round(lhs.g), round(lhs.h)
            );
    }

    template<has_trunc T>
    [[nodiscard]] vec<T, 8> trunc(const vec<T, 8>& lhs) noexcept
    {
        return vec<T, 8>(
            trunc(lhs.a), trunc(lhs.b), trunc(lhs.c), trunc(lhs.d),
            trunc(lhs.e), trunc(lhs.f), trunc(lhs.g), trunc(lhs.h)
            );
    }

    ////////////////////////////////////////////////////////////////
    // Select.
    ////////////////////////////////////////////////////////////////

    template<typename T>
    [[nodiscard]] vec<T, 8> select(const vec<T, 8>& t, const vec<T, 8>& f, const vec<bool, 8>& b) noexcept
    {
        return vec<T, 8>(
            select(t.a, f.a, b.a), select(t.b, f.b, b.b), select(t.c, f.c, b.c), select(t.d, f.d, b.d),
            select(t.e, f.e, b.e), select(t.f, f.f, b.f), select(t.g, f.g, b.g), select(t.h, f.h, b.h)
            );
    }

    ////////////////////////////////////////////////////////////////
    // Multiply and add.
    ////////////////////////////////////////////////////////////////

    template<arithmetic T>
    [[nodiscard]] vec<T, 8> madd(const vec<T, 8>& a, const vec<T, 8>& b, const vec<T, 8>& c) noexcept
    {
        return vec<T, 8>(
            madd(a.a, b.a, c.a), madd(a.b, b.b, c.b), madd(a.c, b.c, c.c), madd(a.d, b.d, c.d),
            madd(a.e, b.e, c.e), madd(a.f, b.f, c.f), madd(a.g, b.g, c.g), madd(a.h, b.h, c.h)
            );
    }

    template<arithmetic T>
    [[nodiscard]] vec<T, 8> nmadd(const vec<T, 8>& a, const vec<T, 8>& b, const vec<T, 8>& c) noexcept
    {
        return vec<T, 8>(
            nmadd(a.a, b.a, c.a), nmadd(a.b, b.b, c.b), nmadd(a.c, b.c, c.c), nmadd(a.d, b.d, c.d),
            nmadd(a.e, b.e, c.e), nmadd(a.f, b.f, c.f), nmadd(a.g, b.g, c.g), nmadd(a.h, b.h, c.h)
            );
    }

    template<arithmetic T>
    [[nodiscard]] vec<T, 8> msub(const vec<T, 8>& a, const vec<T, 8>& b, const vec<T, 8>& c) noexcept
    {
        return vec<T, 8>(
            msub(a.a, b.a, c.a), msub(a.b, b.b, c.b), msub(a.c, b.c, c.c), msub(a.d, b.d, c.d),
            msub(a.e, b.e, c.e), msub(a.f, b.f, c.f), msub(a.g, b.g, c.g), msub(a.h, b.h, c.h)
            );
    }

    template<arithmetic T>
    [[nodiscard]] vec<T, 8> nmsub(const vec<T, 8>& a, const vec<T, 8>& b, const vec<T, 8>& c) noexcept
    {
        return vec<T, 8>(
            nmsub(a.a, b.a, c.a), nmsub(a.b, b.b, c.b), nmsub(a.c, b.c, c.c), nmsub(a.d, b.d, c.d),
            nmsub(a.e, b.e, c.e), nmsub(a.f, b.f, c.f), nmsub(a.g, b.g, c.g), nmsub(a.h, b.h, c.h)
            );
    }

    ////////////////////////////////////////////////////////////////
    // Reduction.
    ////////////////////////////////////////////////////////////////

    template<arithmetic T>
    [[nodiscard]] T reduce_add(const vec<T, 8>& lhs) noexcept { return lhs.a + lhs.b + lhs.c + lhs.d + lhs.e + lhs.f + lhs.g + lhs.h; }

    template<arithmetic T>
    [[nodiscard]] T reduce_mul(const vec<T, 8>& lhs) noexcept { return lhs.a * lhs.b * lhs.c * lhs.d * lhs.e * lhs.f * lhs.g * lhs.h; }

    template<arithmetic T>
    [[nodiscard]] T reduce_min(const vec<T, 8>& lhs) noexcept { return min(lhs.a, lhs.b, lhs.c, lhs.d, lhs.e, lhs.f, lhs.g, lhs.h); }

    template<arithmetic T>
    [[nodiscard]] T reduce_max(const vec<T, 8>& lhs) noexcept { return max(lhs.a, lhs.b, lhs.c, lhs.d, lhs.e, lhs.f, lhs.g, lhs.h); }

    ////////////////////////////////////////////////////////////////
    // Shift operators.
    ////////////////////////////////////////////////////////////////

    template<std::integral T, std::integral U>
    [[nodiscard]] vec<T, 8> operator<<(const vec<T, 8>& lhs, const vec<U, 8>& rhs) noexcept
    {
        return vec<T, 8>(
            lhs.a << rhs.a, lhs.b << rhs.b, lhs.c << rhs.c, lhs.d << rhs.d,
            lhs.e << rhs.e, lhs.f << rhs.f, lhs.g << rhs.g, lhs.h << rhs.h
            );
    }

    template<std::integral T, std::integral U>
    [[nodiscard]] vec<T, 8> operator<<(const vec<T, 8>& lhs, const U rhs) noexcept
    {
        return vec<T, 8>(
            lhs.a << rhs, lhs.b << rhs, lhs.c << rhs, lhs.d << rhs,
            lhs.e << rhs, lhs.f << rhs, lhs.g << rhs, lhs.h << rhs
            );
    }

    template<std::integral T, std::integral U>
    [[nodiscard]] vec<T, 8> operator<<(const T lhs, const vec<U, 8>& rhs) noexcept
    {
        return vec<T, 8>(
            lhs << rhs.a, lhs << rhs.b, lhs << rhs.c, lhs << rhs.d,
            lhs << rhs.e, lhs << rhs.f, lhs << rhs.g, lhs << rhs.h
            );
    }

    template<std::integral T, std::integral U>
    [[nodiscard]] vec<T, 8> operator>>(const vec<T, 8>& lhs, const vec<U, 8>& rhs) noexcept
    {
        return vec<T, 8>(
            lhs.a >> rhs.a, lhs.b >> rhs.b, lhs.c >> rhs.c, lhs.d >> rhs.d,
            lhs.e >> rhs.e, lhs.f >> rhs.f, lhs.g >> rhs.g, lhs.h >> rhs.h
            );
    }

    template<std::integral T, std::integral U>
    [[nodiscard]] vec<T, 8> operator>>(const vec<T, 8>& lhs, const U rhs) noexcept
    {
        return vec<T, 8>(
            lhs.a >> rhs, lhs.b >> rhs, lhs.c >> rhs, lhs.d >> rhs,
            lhs.e >> rhs, lhs.f >> rhs, lhs.g >> rhs, lhs.h >> rhs
            );
    }

    template<std::integral T, std::integral U>
    [[nodiscard]] vec<T, 8> operator>>(const T lhs, const vec<U, 8>& rhs) noexcept
    {
        return vec<T, 8>(
            lhs >> rhs.a, lhs >> rhs.b, lhs >> rhs.c, lhs >> rhs.d,
            lhs >> rhs.e, lhs >> rhs.f, lhs >> rhs.g, lhs >> rhs.h
            );
    }

    ////////////////////////////////////////////////////////////////
    // Bitwise operators.
    ////////////////////////////////////////////////////////////////

    template<std::integral T>
    [[nodiscard]] vec<T, 8> operator|(const vec<T, 8>& lhs, const vec<T, 8>& rhs) noexcept
    {
        return vec<T, 8>(
            lhs.a | rhs.a, lhs.b | rhs.b, lhs.c | rhs.c, lhs.d | rhs.d,
            lhs.e | rhs.e, lhs.f | rhs.f, lhs.g | rhs.g, lhs.h | rhs.h
            );
    }

    template<std::integral T>
    [[nodiscard]] vec<T, 8> operator|(const vec<T, 8>& lhs, const T rhs) noexcept
    {
        return vec<T, 8>(
            lhs.a | rhs, lhs.b | rhs, lhs.c | rhs, lhs.d | rhs,
            lhs.e | rhs, lhs.f | rhs, lhs.g | rhs, lhs.h | rhs
            );
    }

    template<std::integral T>
    [[nodiscard]] vec<T, 8> operator|(const T lhs, const vec<T, 8>& rhs) noexcept
    {
        return vec<T, 8>(
            lhs | rhs.a, lhs | rhs.b, lhs | rhs.c, lhs | rhs.d,
            lhs | rhs.e, lhs | rhs.f, lhs | rhs.g, lhs | rhs.h
            );
    }

    template<std::integral T>
    [[nodiscard]] vec<T, 8> operator&(const vec<T, 8>& lhs, const vec<T, 8>& rhs) noexcept
    {
        return vec<T, 8>(
            lhs.a & rhs.a, lhs.b & rhs.b, lhs.c & rhs.c, lhs.d & rhs.d,
            lhs.e & rhs.e, lhs.f & rhs.f, lhs.g & rhs.g, lhs.h & rhs.h
            );
    }

    template<std::integral T>
    [[nodiscard]] vec<T, 8> operator&(const vec<T, 8>& lhs, const T rhs) noexcept
    {
        return vec<T, 8>(
            lhs.a & rhs, lhs.b & rhs, lhs.c & rhs, lhs.d & rhs,
            lhs.e & rhs, lhs.f & rhs, lhs.g & rhs, lhs.h & rhs
            );
    }

    template<std::integral T>
    [[nodiscard]] vec<T, 8> operator&(const T lhs, const vec<T, 8>& rhs) noexcept
    {
        return vec<T, 8>(
            lhs & rhs.a, lhs & rhs.b, lhs & rhs.c, lhs & rhs.d,
            lhs & rhs.e, lhs & rhs.f, lhs & rhs.g, lhs & rhs.h
            );
    }

    template<std::integral T>
    [[nodiscard]] vec<T, 8> operator^(const vec<T, 8>& lhs, const vec<T, 8>& rhs) noexcept
    {
        return vec<T, 8>(
            lhs.a ^ rhs.a, lhs.b ^ rhs.b, lhs.c ^ rhs.c, lhs.d ^ rhs.d,
            lhs.e ^ rhs.e, lhs.f ^ rhs.f, lhs.g ^ rhs.g, lhs.h ^ rhs.h
            );
    }

    template<std::integral T>
    [[nodiscard]] vec<T, 8> operator^(const vec<T, 8>& lhs, const T rhs) noexcept
    {
        return vec<T, 8>(
            lhs.a ^ rhs, lhs.b ^ rhs, lhs.c ^ rhs, lhs.d ^ rhs,
            lhs.e ^ rhs, lhs.f ^ rhs, lhs.g ^ rhs, lhs.h ^ rhs
            );
    }

    template<std::integral T>
    [[nodiscard]] vec<T, 8> operator^(const T lhs, const vec<T, 8>& rhs) noexcept
    {
        return vec<T, 8>(
            lhs ^ rhs.a, lhs ^ rhs.b, lhs ^ rhs.c, lhs ^ rhs.d,
            lhs ^ rhs.e, lhs ^ rhs.f, lhs ^ rhs.g, lhs ^ rhs.h
            );
    }

    template<std::integral T>
    [[nodiscard]] vec<T, 8> operator~(const vec<T, 8>& lhs) noexcept { return vec<T, 8>(~lhs.a, ~lhs.b, ~lhs.c, ~lhs.d, ~lhs.e, ~lhs.f, ~lhs.g, ~lhs.h); }

    ////////////////////////////////////////////////////////////////
    // Boolean vector reduction.
    ////////////////////////////////////////////////////////////////

    [[nodiscard]] inline bool all(const vec<bool, 8>& lhs) noexcept { return lhs.a & lhs.b & lhs.c & lhs.d & lhs.e & lhs.f & lhs.g & lhs.h; }

    [[nodiscard]] inline bool any(const vec<bool, 8>& lhs) noexcept { return lhs.a | lhs.b | lhs.c | lhs.d | lhs.e | lhs.f | lhs.g | lhs.h; }

    ////////////////////////////////////////////////////////////////
    // Output.
    ////////////////////////////////////////////////////////////////

    template<typename T>
    std::ostream& operator<<(std::ostream& out, const vec<T, 8>& v)
    {
        return out << "(" << v.a << ", " << v.b << ", " << v.c << ", " << v.d << ", " << v.e << ", " << v.f << ", " << v.g << ", " << v.h << ")";
    }
}
