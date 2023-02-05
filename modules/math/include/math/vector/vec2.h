#pragma once

////////////////////////////////////////////////////////////////
// Standard includes.
////////////////////////////////////////////////////////////////

#include <cassert>
#include <concepts>
#include <iostream>

////////////////////////////////////////////////////////////////
// Current target includes.
////////////////////////////////////////////////////////////////

#include "math/vector/vector.h"

namespace math
{
    template<typename T>
    struct vec<T, 2>
    {
        static constexpr size_t size = 2;
        using element_type = T;

        T x, y;

        ////////////////////////////////////////////////////////////////
        // Constructors.
        ////////////////////////////////////////////////////////////////

        // Default.

        [[nodiscard]] vec() noexcept : x(0), y(0) {}

        // From values.

        [[nodiscard]] explicit vec(const T v) noexcept : x(v), y(v) {}

        [[nodiscard]] vec(const T x, const T y) noexcept : x(x), y(y) {}

        // From convertible values.

        template<std::convertible_to<T> U>
        [[nodiscard]] explicit vec(const U v) : x(static_cast<T>(v)), y(static_cast<T>(v)) {}

        template<std::convertible_to<T> U>
        [[nodiscard]] vec(const U x, const U y) : x(static_cast<T>(x)), y(static_cast<T>(y)) {}

        // From pointer.

        [[nodiscard]] explicit vec(const T* ptr) : x(ptr[0]), y(ptr[1]) {}

        // Copy.

        [[nodiscard]] vec(const vec<T, 2>& rhs) noexcept : x(rhs.x), y(rhs.y) {}

        // Move.

        [[nodiscard]] vec(vec<T, 2>&& rhs) noexcept : x(rhs.x), y(rhs.y) {}

        // Copy from convertible.

        template<std::convertible_to<T> U>
        [[nodiscard]] explicit vec(const vec<U, 2>& rhs) : x(static_cast<T>(rhs.x)), y(static_cast<T>(rhs.y)) {}

        // Move from convertible.

        ////////////////////////////////////////////////////////////////
        // Assignment operators.
        ////////////////////////////////////////////////////////////////

        // Copy.

        vec<T, 2>& operator=(const vec<T, 2>& rhs) noexcept { x = rhs.x; y = rhs.y; return *this; }

        // Move.

        vec<T, 2>& operator=(vec<T, 2>&& rhs) noexcept { x = rhs.x; y = rhs.y; return *this; }

        // Assign from value.

        vec<T, 2>& operator=(const T rhs) noexcept { x = rhs; y = rhs; return *this; }

        // Assign from convertible value.

        template<std::convertible_to<T> U>
        vec<T, 2>& operator=(const U rhs) { x = static_cast<T>(rhs); y = static_cast<T>(rhs); return *this; }

        // Assign from convertible.

        template<std::convertible_to<T> U>
        vec<T, 2>& operator=(const vec<U, 2>& rhs) { x = static_cast<T>(rhs.x); y = static_cast<T>(rhs.y); return *this; }

        ////////////////////////////////////////////////////////////////
        // Destructor.
        ////////////////////////////////////////////////////////////////

        ~vec() noexcept = default;

        ////////////////////////////////////////////////////////////////
        // Element access.
        ////////////////////////////////////////////////////////////////

        [[nodiscard]] const T& operator[](const size_t i) const { assert(i < 2); return (&x)[i]; }

        [[nodiscard]] T& operator[](const size_t i) { assert(i < 2); return (&x)[i]; }

        ////////////////////////////////////////////////////////////////
        // Swizzling.
        ////////////////////////////////////////////////////////////////

        [[nodiscard]] vec<T, 2> xx() const noexcept { return vec<T, 2>(x, x); }
        [[nodiscard]] vec<T, 2> xy() const noexcept { return vec<T, 2>(x, y); }
        [[nodiscard]] vec<T, 2> yx() const noexcept { return vec<T, 2>(y, x); }
        [[nodiscard]] vec<T, 2> yy() const noexcept { return vec<T, 2>(y, y); }
    };

    ////////////////////////////////////////////////////////////////
    // Check for special values.
    ////////////////////////////////////////////////////////////////

    template<typename T>
    [[nodiscard]] vec<bool, 2> is_finite(const vec<T, 2>& lhs) noexcept { return vec<bool, 2>(std::isfinite(lhs.x), std::isfinite(lhs.y)); }

    template<typename T>
    [[nodiscard]] vec<bool, 2> is_infinite(const vec<T, 2>& lhs) noexcept { return vec<bool, 2>(std::isinf(lhs.x), std::isinf(lhs.y)); }

    template<typename T>
    [[nodiscard]] vec<bool, 2> is_neg_infinite(const vec<T, 2>& lhs) noexcept { return vec<bool, 2>(lhs.x == -std::numeric_limits<T>::infinite(), lhs.y == -std::numeric_limits<T>::infinite()); }

    template<typename T>
    [[nodiscard]] vec<bool, 2> is_pos_infinite(const vec<T, 2>& lhs) noexcept { return vec<bool, 2>(lhs.x == std::numeric_limits<T>::infinite(), lhs.y == std::numeric_limits<T>::infinite()); }

    template<typename T>
    [[nodiscard]] vec<bool, 2> is_NaN(const vec<T, 2>& lhs) noexcept { return vec<bool, 2>(std::isnan(lhs.x), std::isnan(lhs.y)); }

    template<typename T>
    [[nodiscard]] vec<bool, 2> is_normal(const vec<T, 2>& lhs) noexcept { return vec<bool, 2>(std::isnormal(lhs.x), std::isnormal(lhs.y)); }

    ////////////////////////////////////////////////////////////////
    // Arithmetic operators.
    ////////////////////////////////////////////////////////////////

    template<arithmetic T>
    [[nodiscard]] vec<T, 2> operator+(const vec<T, 2>& lhs, const vec<T, 2>& rhs) noexcept { return vec<T, 2>(lhs.x + rhs.x, lhs.y + rhs.y); }

    template<arithmetic T>
    [[nodiscard]] vec<T, 2> operator+(const vec<T, 2>& lhs, const T rhs) noexcept { return vec<T, 2>(lhs.x + rhs, lhs.y + rhs); }

    template<arithmetic T>
    [[nodiscard]] vec<T, 2> operator+(const T lhs, const vec<T, 2>& rhs) noexcept { return vec<T, 2>(lhs + rhs.x, lhs + rhs.y); }

    template<arithmetic T>
    [[nodiscard]] vec<T, 2> operator-(const vec<T, 2>& lhs, const vec<T, 2>& rhs) noexcept { return vec<T, 2>(lhs.x - rhs.x, lhs.y - rhs.y); }

    template<arithmetic T>
    [[nodiscard]] vec<T, 2> operator-(const vec<T, 2>& lhs, const T rhs) noexcept { return vec<T, 2>(lhs.x - rhs, lhs.y - rhs); }

    template<arithmetic T>
    [[nodiscard]] vec<T, 2> operator-(const T lhs, const vec<T, 2>& rhs) noexcept { return vec<T, 2>(lhs - rhs.x, lhs - rhs.y); }

    template<arithmetic T>
    [[nodiscard]] vec<T, 2> operator-(const vec<T, 2>& lhs) noexcept { return vec<T, 2>(-lhs.x, -lhs.y); }

    template<arithmetic T>
    [[nodiscard]] vec<T, 2> operator*(const vec<T, 2>& lhs, const vec<T, 2>& rhs) noexcept { return vec<T, 2>(lhs.x * rhs.x, lhs.y * rhs.y); }

    template<arithmetic T>
    [[nodiscard]] vec<T, 2> operator*(const vec<T, 2>& lhs, const T rhs) noexcept { return vec<T, 2>(lhs.x * rhs, lhs.y * rhs); }

    template<arithmetic T>
    [[nodiscard]] vec<T, 2> operator*(const T lhs, const vec<T, 2>& rhs) noexcept { return vec<T, 2>(lhs * rhs.x, lhs * rhs.y); }

    template<arithmetic T>
    [[nodiscard]] vec<T, 2> operator/(const vec<T, 2>& lhs, const vec<T, 2>& rhs) noexcept { return vec<T, 2>(lhs.x / rhs.x, lhs.y / rhs.y); }

    template<arithmetic T>
    [[nodiscard]] vec<T, 2> operator/(const vec<T, 2>& lhs, const T rhs) noexcept { return vec<T, 2>(lhs.x / rhs, lhs.y / rhs); }

    template<arithmetic T>
    [[nodiscard]] vec<T, 2> operator/(const T lhs, const vec<T, 2>& rhs) noexcept { return vec<T, 2>(lhs / rhs.x, lhs / rhs.y); }

    ////////////////////////////////////////////////////////////////
    // Comparison operators.
    ////////////////////////////////////////////////////////////////

    template<std::equality_comparable T>
    [[nodiscard]] bool operator==(const vec<T, 2>& lhs, const vec<T, 2>& rhs) noexcept { return lhs.x == rhs.x && lhs.y == rhs.y; }

    template<std::equality_comparable T>
    [[nodiscard]] bool operator!=(const vec<T, 2>& lhs, const vec<T, 2>& rhs) noexcept { return lhs.x != rhs.x || lhs.y != rhs.y; }

    ////////////////////////////////////////////////////////////////
    // Per-element comparisons.
    ////////////////////////////////////////////////////////////////

    template<std::totally_ordered T>
    [[nodiscard]] vec<bool, 2> cmpeq(const vec<T, 2>& lhs, const vec<T, 2>& rhs) noexcept { return vec<bool, 2>(lhs.x == rhs.x, lhs.y == rhs.y); }

    template<std::totally_ordered T>
    [[nodiscard]] vec<bool, 2> cmpeq(const vec<T, 2>& lhs, const T rhs) noexcept { return vec<bool, 2>(lhs.x == rhs, lhs.y == rhs); }

    template<std::totally_ordered T>
    [[nodiscard]] vec<bool, 2> cmpeq(const T lhs, const vec<T, 2>& rhs) noexcept { return vec<bool, 2>(lhs == rhs.x, lhs == rhs.y); }

    template<std::totally_ordered T>
    [[nodiscard]] vec<bool, 2> cmpneq(const vec<T, 2>& lhs, const vec<T, 2>& rhs) noexcept { return vec<bool, 2>(lhs.x != rhs.x, lhs.y != rhs.y); }

    template<std::totally_ordered T>
    [[nodiscard]] vec<bool, 2> cmpneq(const vec<T, 2>& lhs, const T rhs) noexcept { return vec<bool, 2>(lhs.x != rhs, lhs.y != rhs); }

    template<std::totally_ordered T>
    [[nodiscard]] vec<bool, 2> cmpneq(const T lhs, const vec<T, 2>& rhs) noexcept { return vec<bool, 2>(lhs != rhs.x, lhs != rhs.y); }

    template<std::totally_ordered T>
    [[nodiscard]] vec<bool, 2> cmplt(const vec<T, 2>& lhs, const vec<T, 2>& rhs) noexcept { return vec<bool, 2>(lhs.x < rhs.x, lhs.y < rhs.y); }

    template<std::totally_ordered T>
    [[nodiscard]] vec<bool, 2> cmplt(const vec<T, 2>& lhs, const T rhs) noexcept { return vec<bool, 2>(lhs.x < rhs, lhs.y < rhs); }

    template<std::totally_ordered T>
    [[nodiscard]] vec<bool, 2> cmplt(const T lhs, const vec<T, 2>& rhs) noexcept { return vec<bool, 2>(lhs < rhs.x, lhs < rhs.y); }

    template<std::totally_ordered T>
    [[nodiscard]] vec<bool, 2> cmpgt(const vec<T, 2>& lhs, const vec<T, 2>& rhs) noexcept { return vec<bool, 2>(lhs.x > rhs.x, lhs.y > rhs.y); }

    template<std::totally_ordered T>
    [[nodiscard]] vec<bool, 2> cmpgt(const vec<T, 2>& lhs, const T rhs) noexcept { return vec<bool, 2>(lhs.x > rhs, lhs.y > rhs); }

    template<std::totally_ordered T>
    [[nodiscard]] vec<bool, 2> cmpgt(const T lhs, const vec<T, 2>& rhs) noexcept { return vec<bool, 2>(lhs > rhs.x, lhs > rhs.y); }

    template<std::totally_ordered T>
    [[nodiscard]] vec<bool, 2> cmple(const vec<T, 2>& lhs, const vec<T, 2>& rhs) noexcept { return vec<bool, 2>(lhs.x <= rhs.x, lhs.y <= rhs.y); }

    template<std::totally_ordered T>
    [[nodiscard]] vec<bool, 2> cmple(const vec<T, 2>& lhs, const T rhs) noexcept { return vec<bool, 2>(lhs.x <= rhs, lhs.y <= rhs); }

    template<std::totally_ordered T>
    [[nodiscard]] vec<bool, 2> cmple(const T lhs, const vec<T, 2>& rhs) noexcept { return vec<bool, 2>(lhs <= rhs.x, lhs <= rhs.y); }

    template<std::totally_ordered T>
    [[nodiscard]] vec<bool, 2> cmpge(const vec<T, 2>& lhs, const vec<T, 2>& rhs) noexcept { return vec<bool, 2>(lhs.x >= rhs.x, lhs.y >= rhs.y); }

    template<std::totally_ordered T>
    [[nodiscard]] vec<bool, 2> cmpge(const vec<T, 2>& lhs, const T rhs) noexcept { return vec<bool, 2>(lhs.x >= rhs, lhs.y >= rhs); }

    template<std::totally_ordered T>
    [[nodiscard]] vec<bool, 2> cmpge(const T lhs, const vec<T, 2>& rhs) noexcept { return vec<bool, 2>(lhs >= rhs.x, lhs >= rhs.y); }

    ////////////////////////////////////////////////////////////////
    // Dot product etc.
    ////////////////////////////////////////////////////////////////

    template<arithmetic T>
    [[nodiscard]] T dot(const vec<T, 2>& lhs, const vec<T, 2>& rhs) noexcept { return lhs.x * rhs.x + lhs.y * rhs.y; }

    template<arithmetic T>
    [[nodiscard]] vec<T, 2> cross(const vec<T, 2>& lhs) noexcept { return vec<T, 2>(-lhs.y, lhs.x); }

    template<arithmetic T>
    [[nodiscard]] vec<T, 2> lerp(const vec<T, 2>& a, const vec<T, 2>& b, const vec<T, 2>& t) noexcept { return vec<T, 2>(lerp(a.x, b.x, t.x), lerp(a.y, b.y, t.y)); }

    template<arithmetic T>
    [[nodiscard]] vec<T, 2> lerp(const vec<T, 2>& a, const vec<T, 2>& b, const T t) noexcept { return vec<T, 2>(lerp( a.x, b.x, t), lerp(a.y, b.y, t)); }

    ////////////////////////////////////////////////////////////////
    // Trigonometry.
    ////////////////////////////////////////////////////////////////

    template<std::floating_point T>
    [[nodiscard]] vec<T, 2> acos(const vec<T, 2>& lhs) noexcept { return vec<T, 2>(acos(lhs.x), acos(lhs.y)); }

    template<std::floating_point T>
    [[nodiscard]] vec<T, 2> asin(const vec<T, 2>& lhs) noexcept { return vec<T, 2>(asin(lhs.x), asin(lhs.y)); }

    template<std::floating_point T>
    [[nodiscard]] vec<T, 2> atan(const vec<T, 2>& lhs) noexcept { return vec<T, 2>(atan(lhs.x), atan(lhs.y)); }

    template<std::floating_point T>
    [[nodiscard]] vec<T, 2> atan2(const vec<T, 2>& lhs, const vec<T, 2>& rhs) noexcept { return vec<T, 2>(atan2(lhs.x, rhs.x), atan2(lhs.y, rhs.y)); }

    template<std::floating_point T>
    [[nodiscard]] vec<T, 2> cos(const vec<T, 2>& lhs) noexcept { return vec<T, 2>(cos(lhs.x), cos(lhs.y)); }

    template<std::floating_point T>
    [[nodiscard]] vec<T, 2> cosh(const vec<T, 2>& lhs) noexcept { return vec<T, 2>(cosh(lhs.x), cosh(lhs.y)); }

    template<std::floating_point T>
    [[nodiscard]] vec<T, 2> sin(const vec<T, 2>& lhs) noexcept { return vec<T, 2>(sin(lhs.x), sin(lhs.y)); }

    template<std::floating_point T>
    [[nodiscard]] vec<T, 2> sinh(const vec<T, 2>& lhs) noexcept { return vec<T, 2>(sinh(lhs.x), sinh(lhs.y)); }

    template<std::floating_point T>
    [[nodiscard]] vec<T, 2> tan(const vec<T, 2>& lhs) noexcept { return vec<T, 2>(tan(lhs.x), tan(lhs.y)); }

    template<std::floating_point T>
    [[nodiscard]] vec<T, 2> tanh(const vec<T, 2>& lhs) noexcept { return vec<T, 2>(tanh(lhs.x), tanh(lhs.y)); }

    ////////////////////////////////////////////////////////////////
    // Exponential / Logarithmic.
    ////////////////////////////////////////////////////////////////

    template<std::floating_point T>
    [[nodiscard]] vec<T, 2> exp(const vec<T, 2>& lhs) noexcept { return vec<T, 2>(exp(lhs.x), exp(lhs.y)); }

    template<std::floating_point T>
    [[nodiscard]] vec<T, 2> exp2(const vec<T, 2>& lhs) noexcept { return vec<T, 2>(exp2(lhs.x), exp2(lhs.y)); }

    template<std::floating_point T>
    [[nodiscard]] vec<T, 2> log(const vec<T, 2>& lhs) noexcept { return vec<T, 2>(log(lhs.x), log(lhs.y)); }

    template<std::floating_point T>
    [[nodiscard]] vec<T, 2> log2(const vec<T, 2>& lhs) noexcept { return vec<T, 2>(log2(lhs.x), log2(lhs.y)); }

    template<std::floating_point T>
    [[nodiscard]] vec<T, 2> log10(const vec<T, 2>& lhs) noexcept { return vec<T, 2>(log10(lhs.x), log10(lhs.y)); }

    ////////////////////////////////////////////////////////////////
    // Power.
    ////////////////////////////////////////////////////////////////

    template<std::floating_point T>
    [[nodiscard]] vec<T, 2> pow(const vec<T, 2>& lhs, const vec<T, 2>& rhs) noexcept { return vec<T, 2>(pow(lhs.x, rhs.x), pow(lhs.y, rhs.y)); }

    template<std::floating_point T>
    [[nodiscard]] vec<T, 2> pow(const vec<T, 2>& lhs, const T rhs) noexcept { return vec<T, 2>(pow(lhs.x, rhs), pow(lhs.y, rhs)); }

    template<std::floating_point T>
    [[nodiscard]] vec<T, 2> sqrt(const vec<T, 2>& lhs) noexcept { return vec<T, 2>(sqrt(lhs.x), sqrt(lhs.y)); }

    template<std::floating_point T>
    [[nodiscard]] vec<T, 2> rsqrt(const vec<T, 2>& lhs) noexcept { return vec<T, 2>(rsqrt(lhs.x), rsqrt(lhs.y)); }

    ////////////////////////////////////////////////////////////////
    // Min/max, abs and clamp.
    ////////////////////////////////////////////////////////////////

    template<has_min T>
    [[nodiscard]] vec<T, 2> min(const vec<T, 2>& lhs, const vec<T, 2>& rhs) noexcept { return vec<T, 2>(min(lhs.x, rhs.x), min(lhs.y, rhs.y)); }

    template<has_min T>
    [[nodiscard]] vec<T, 2> min(const vec<T, 2>& lhs, const T rhs) noexcept { return vec<T, 2>(min(lhs.x, rhs), min(lhs.y, rhs)); }

    template<has_min T>
    [[nodiscard]] vec<T, 2> min(const T lhs, const vec<T, 2>& rhs) noexcept { return vec<T, 2>(min(lhs, rhs.x), min(lhs, rhs.y)); }

    template<has_max T>
    [[nodiscard]] vec<T, 2> max(const vec<T, 2>& lhs, const vec<T, 2>& rhs) noexcept { return vec<T, 2>(max(lhs.x, rhs.x), max(lhs.y, rhs.y)); }

    template<has_max T>
    [[nodiscard]] vec<T, 2> max(const vec<T, 2>& lhs, const T rhs) noexcept { return vec<T, 2>(max(lhs.x, rhs), max(lhs.y, rhs)); }

    template<has_max T>
    [[nodiscard]] vec<T, 2> max(const T lhs, const vec<T, 2>& rhs) noexcept { return vec<T, 2>(max(lhs, rhs.x), max(lhs, rhs.y)); }

    template<has_clamp T>
    [[nodiscard]] vec<T, 2> clamp(const vec<T, 2>& a, const vec<T, 2>& min, const vec<T, 2>& max) noexcept { return vec<T, 2>(clamp(a.x, min.x, max.x), clamp(a.y, min.y, max.y)); }

    template<has_clamp T>
    [[nodiscard]] vec<T, 2> clamp(const vec<T, 2>& a, const vec<T, 2>& min, const T max) noexcept { return vec<T, 2>(clamp(a.x, min.x, max), clamp(a.y, min.y, max)); }

    template<has_clamp T>
    [[nodiscard]] vec<T, 2> clamp(const vec<T, 2>& a, const T min, const vec<T, 2>& max) noexcept { return vec<T, 2>(clamp(a.x, min, max.x), clamp(a.y, min, max.y)); }

    template<has_clamp T>
    [[nodiscard]] vec<T, 2> clamp(const vec<T, 2>& a, const T min, const T max) noexcept { return vec<T, 2>(clamp(a.x, min, max), clamp(a.y, min, max)); }

    ////////////////////////////////////////////////////////////////
    // Rounding, abs, etc.
    ////////////////////////////////////////////////////////////////

    template<has_abs T>
    [[nodiscard]] vec<T, 2> abs(const vec<T, 2>& lhs) noexcept { return vec<T, 2>(abs(lhs.x), abs(lhs.y)); }

    template<has_ceil T>
    [[nodiscard]] vec<T, 2> ceil(const vec<T, 2>& lhs) noexcept { return vec<T, 2>(ceil(lhs.x), ceil(lhs.y)); }

    template<has_floor T>
    [[nodiscard]] vec<T, 2> floor(const vec<T, 2>& lhs) noexcept { return vec<T, 2>(floor(lhs.x), floor(lhs.y)); }

    template<has_frac T>
    [[nodiscard]] vec<T, 2> frac(const vec<T, 2>& lhs) noexcept { return vec<T, 2>(frac(lhs.x), frac(lhs.y)); }

    template<has_round T>
    [[nodiscard]] vec<T, 2> round(const vec<T, 2>& lhs) noexcept { return vec<T, 2>(round(lhs.x), round(lhs.y)); }

    template<has_trunc T>
    [[nodiscard]] vec<T, 2> trunc(const vec<T, 2>& lhs) noexcept { return vec<T, 2>(trunc(lhs.x), trunc(lhs.y)); }

    // Require integral or modulo operator on T?
    // Implement for all vector sizes.
    // Implement fmod for floating point.
    template<typename T>
    [[nodiscard]] vec<T, 2> operator%(const vec<T, 2>& lhs, const vec<T, 2>& rhs) noexcept { return vec<T, 2>(lhs.x % rhs.x, lhs.y % rhs.y); }

    ////////////////////////////////////////////////////////////////
    // Select.
    ////////////////////////////////////////////////////////////////

    template<typename T>
    [[nodiscard]] vec<T, 2> select(const vec<T, 2>& t, const vec<T, 2>& f, const vec<bool, 2>& b) noexcept { return vec<T, 2>(select(t.x, f.x, b.x), select(t.y, f.y, b.y)); }

    ////////////////////////////////////////////////////////////////
    // Multiply and add.
    ////////////////////////////////////////////////////////////////

    template<arithmetic T>
    [[nodiscard]] vec<T, 2> madd(const vec<T, 2>& a, const vec<T, 2>& b, const vec<T, 2>& c) noexcept { return vec<T, 2>(madd(a.x, b.x, c.x), madd(a.y, b.y, c.y)); }

    template<arithmetic T>
    [[nodiscard]] vec<T, 2> nmadd(const vec<T, 2>& a, const vec<T, 2>& b, const vec<T, 2>& c) noexcept { return vec<T, 2>(nmadd(a.x, b.x, c.x), nmadd(a.y, b.y, c.y)); }

    template<arithmetic T>
    [[nodiscard]] vec<T, 2> msub(const vec<T, 2>& a, const vec<T, 2>& b, const vec<T, 2>& c) noexcept { return vec<T, 2>(msub(a.x, b.x, c.x), msub(a.y, b.y, c.y)); }

    template<arithmetic T>
    [[nodiscard]] vec<T, 2> nmsub(const vec<T, 2>& a, const vec<T, 2>& b, const vec<T, 2>& c) noexcept { return vec<T, 2>(nmsub(a.x, b.x, c.x), nmsub(a.y, b.y, c.y)); }

    ////////////////////////////////////////////////////////////////
    // Reduction.
    ////////////////////////////////////////////////////////////////

    template<arithmetic T>
    [[nodiscard]] T reduce_add(const vec<T, 2>& lhs) noexcept { return lhs.x + lhs.y; }

    template<arithmetic T>
    [[nodiscard]] T reduce_mul(const vec<T, 2>& lhs) noexcept { return lhs.x * lhs.y; }

    template<arithmetic T>
    [[nodiscard]] T reduce_min(const vec<T, 2>& lhs) noexcept { return min(lhs.x, lhs.y); }

    template<arithmetic T>
    [[nodiscard]] T reduce_max(const vec<T, 2>& lhs) noexcept { return max(lhs.x, lhs.y); }

    ////////////////////////////////////////////////////////////////
    // Shift operators.
    ////////////////////////////////////////////////////////////////

    template<std::integral T, std::integral U>
    [[nodiscard]] vec<T, 2> operator<<(const vec<T, 2>& lhs, const vec<U, 2>& rhs) noexcept { return vec<T, 2>(lhs.x << rhs.x, lhs.y << rhs.y); }

    template<std::integral T, std::integral U>
    [[nodiscard]] vec<T, 2> operator<<(const vec<T, 2>& lhs, const U rhs) noexcept { return vec<T, 2>(lhs.x << rhs, lhs.y << rhs); }

    template<std::integral T, std::integral U>
    [[nodiscard]] vec<T, 2> operator<<(const T lhs, const vec<U, 2>& rhs) noexcept { return vec<T, 2>(lhs << rhs.x, lhs << rhs.y); }

    template<std::integral T, std::integral U>
    [[nodiscard]] vec<T, 2> operator>>(const vec<T, 2>& lhs, const vec<U, 2>& rhs) noexcept { return vec<T, 2>(lhs.x >> rhs.x, lhs.y >> rhs.y); }

    template<std::integral T, std::integral U>
    [[nodiscard]] vec<T, 2> operator>>(const vec<T, 2>& lhs, const U rhs) noexcept { return vec<T, 2>(lhs.x >> rhs, lhs.y >> rhs); }

    template<std::integral T, std::integral U>
    [[nodiscard]] vec<T, 2> operator>>(const T lhs, const vec<U, 2>& rhs) noexcept { return vec<T, 2>(lhs >> rhs.x, lhs >> rhs.y); }

    ////////////////////////////////////////////////////////////////
    // Bitwise operators.
    ////////////////////////////////////////////////////////////////

    template<std::integral T>
    [[nodiscard]] vec<T, 2> operator|(const vec<T, 2>& lhs, const vec<T, 2>& rhs) noexcept { return vec<T, 2>(lhs.x | rhs.x, lhs.y | rhs.y); }

    template<std::integral T>
    [[nodiscard]] vec<T, 2> operator|(const vec<T, 2>& lhs, const T rhs) noexcept { return vec<T, 2>(lhs.x | rhs, lhs.y | rhs); }

    template<std::integral T>
    [[nodiscard]] vec<T, 2> operator|(const T lhs, const vec<T, 2>& rhs) noexcept { return vec<T, 2>(lhs | rhs.x, lhs | rhs.y); }

    template<std::integral T>
    [[nodiscard]] vec<T, 2> operator&(const vec<T, 2>& lhs, const vec<T, 2>& rhs) noexcept { return vec<T, 2>(lhs.x & rhs.x, lhs.y & rhs.y); }

    template<std::integral T>
    [[nodiscard]] vec<T, 2> operator&(const vec<T, 2>& lhs, const T rhs) noexcept { return vec<T, 2>(lhs.x & rhs, lhs.y & rhs); }

    template<std::integral T>
    [[nodiscard]] vec<T, 2> operator&(const T lhs, const vec<T, 2>& rhs) noexcept { return vec<T, 2>(lhs & rhs.x, lhs & rhs.y); }

    template<std::integral T>
    [[nodiscard]] vec<T, 2> operator^(const vec<T, 2>& lhs, const vec<T, 2>& rhs) noexcept { return vec<T, 2>(lhs.x ^ rhs.x, lhs.y ^ rhs.y); }

    template<std::integral T>
    [[nodiscard]] vec<T, 2> operator^(const vec<T, 2>& lhs, const T rhs) noexcept { return vec<T, 2>(lhs.x ^ rhs, lhs.y ^ rhs); }

    template<std::integral T>
    [[nodiscard]] vec<T, 2> operator^(const T lhs, const vec<T, 2>& rhs) noexcept { return vec<T, 2>(lhs ^ rhs.x, lhs ^ rhs.y); }

    template<std::integral T>
    [[nodiscard]] vec<T, 2> operator~(const vec<T, 2>& lhs) noexcept { return vec<T, 2>(~lhs.x, ~lhs.y); }

    ////////////////////////////////////////////////////////////////
    // Boolean vector reduction.
    ////////////////////////////////////////////////////////////////

    [[nodiscard]] inline bool all(const vec<bool, 2>& lhs) { return lhs.x & lhs.y; }

    [[nodiscard]] inline bool any(const vec<bool, 2>& lhs) { return lhs.x | lhs.y; }

    ////////////////////////////////////////////////////////////////
    // Output.
    ////////////////////////////////////////////////////////////////

    template<typename T>
    std::ostream& operator<<(std::ostream& out, const vec<T, 2>& v) { return out << "(" << v.x << ", " << v.y << ")"; }
}
