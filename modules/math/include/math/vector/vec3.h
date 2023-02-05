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
#include "math/vector/vec2.h"

namespace math
{
    template<typename T>
    struct vec<T, 3>
    {
        static constexpr size_t size = 3;
        using element_type = T;

        T x, y, z;

        ////////////////////////////////////////////////////////////////
        // Constructors.
        ////////////////////////////////////////////////////////////////

        // Default.

        [[nodiscard]] vec() noexcept : x(0), y(0), z(0) {}

        // From values.

        [[nodiscard]] explicit vec(const T v) noexcept : x(v), y(v), z(v) {}

        [[nodiscard]] vec(const T x, const T y) noexcept : x(x), y(y), z(0) {}

        [[nodiscard]] vec(const T x, const T y, const T z) noexcept : x(x), y(y), z(z) {}

        // From convertible values.

        template<std::convertible_to<T> U>
        [[nodiscard]] explicit vec(const U v) : x(static_cast<T>(v)), y(static_cast<T>(v)), z(static_cast<T>(v)) {}

        template<std::convertible_to<T> U>
        [[nodiscard]] vec(const U x, const U y) : x(static_cast<T>(x)), y(static_cast<T>(y)), z(0) {}

        template<std::convertible_to<T> U>
        [[nodiscard]] vec(const U x, const U y, const U z) : x(static_cast<T>(x)), y(static_cast<T>(y)), z(static_cast<T>(z)) {}

        // From larger vector.

        // TODO: These methods must also be implemented for all other vector specializations. Also consider using convertible_to.

        template<size_t N2> requires (N2 > 3)
        [[nodiscard]] vec(const vec<T, N2>& rhs) noexcept : x(rhs[0]), y(rhs[1]), z(rhs[2]) {}

        // From pointer.

        [[nodiscard]] explicit vec(const T* ptr) : x(ptr[0]), y(ptr[1]), z(ptr[2]) {}

        // Copy.

        [[nodiscard]] vec(const vec<T, 2>& rhs) noexcept : x(rhs.x), y(rhs.y), z(0) {}

        [[nodiscard]] vec(const vec<T, 3>& rhs) noexcept : x(rhs.x), y(rhs.y), z(rhs.z) {}

        // Move.

        [[nodiscard]] vec(vec<T, 2>&& rhs) noexcept : x(rhs.x), y(rhs.y), z(0) {}

        [[nodiscard]] vec(vec<T, 3>&& rhs) noexcept : x(rhs.x), y(rhs.y), z(rhs.z) {}

        // Copy from convertible.

        template<std::convertible_to<T> U>
        [[nodiscard]] explicit vec(const vec<U, 2>& rhs) : x(static_cast<T>(rhs.x)), y(static_cast<T>(rhs.y)), z(0) {}

        template<std::convertible_to<T> U>
        [[nodiscard]] explicit vec(const vec<U, 3>& rhs) : x(static_cast<T>(rhs.x)), y(static_cast<T>(rhs.y)), z(static_cast<T>(rhs.z)) {}
        
        // Move from convertible.

        // TODO: Implement for these and other specializations.
        
        ////////////////////////////////////////////////////////////////
        // Assignment operators.
        ////////////////////////////////////////////////////////////////

        // Copy.

        vec<T, 3>& operator=(const vec<T, 2>& rhs) noexcept { x = rhs.x; y = rhs.y; z = 0; return *this; }

        vec<T, 3>& operator=(const vec<T, 3>& rhs) noexcept { x = rhs.x; y = rhs.y; z = rhs.z; return *this; }

        // Move.

        vec<T, 3>& operator=(vec<T, 2>&& rhs) noexcept { x = rhs.x; y = rhs.y; z = 0; return *this; }

        vec<T, 3>& operator=(vec<T, 3>&& rhs) noexcept { x = rhs.x; y = rhs.y; z = rhs.z; return *this; }

        // Assign from value.

        vec<T, 3>& operator=(const T rhs) noexcept { x = rhs; y = rhs; z = rhs; return *this; }

        // Assign from convertible value.

        template<std::convertible_to<T> U>
        vec<T, 3>& operator=(const U rhs) { x = static_cast<T>(rhs); y = static_cast<T>(rhs); z = static_cast<T>(rhs); return *this; }

        // Assign from convertible.

        template<std::convertible_to<T> U>
        vec<T, 3>& operator=(const vec<U, 2>& rhs) { x = static_cast<T>(rhs.x); y = static_cast<T>(rhs.y); z = 0; return *this; }

        template<std::convertible_to<T> U>
        vec<T, 3>& operator=(const vec<U, 3>& rhs) { x = static_cast<T>(rhs.x); y = static_cast<T>(rhs.y); z = static_cast<T>(rhs.z); return *this; }

        ////////////////////////////////////////////////////////////////
        // Destructor.
        ////////////////////////////////////////////////////////////////

        ~vec() noexcept = default;

        ////////////////////////////////////////////////////////////////
        // Element access.
        ////////////////////////////////////////////////////////////////

        [[nodiscard]] const T& operator[](const size_t i) const { assert(i < 3); return (&x)[i]; }

        [[nodiscard]] T& operator[](const size_t i) { assert(i < 3); return (&x)[i]; }

        ////////////////////////////////////////////////////////////////
        // Swizzling.
        ////////////////////////////////////////////////////////////////
        
        [[nodiscard]] vec<T, 2> xx() const noexcept { return vec<T, 2>(x, x); }
        [[nodiscard]] vec<T, 2> xy() const noexcept { return vec<T, 2>(x, y); }
        [[nodiscard]] vec<T, 2> xz() const noexcept { return vec<T, 2>(x, z); }
        [[nodiscard]] vec<T, 2> yx() const noexcept { return vec<T, 2>(y, x); }
        [[nodiscard]] vec<T, 2> yy() const noexcept { return vec<T, 2>(y, y); }
        [[nodiscard]] vec<T, 2> yz() const noexcept { return vec<T, 2>(y, z); }
        [[nodiscard]] vec<T, 2> zx() const noexcept { return vec<T, 2>(z, x); }
        [[nodiscard]] vec<T, 2> zy() const noexcept { return vec<T, 2>(z, y); }
        [[nodiscard]] vec<T, 2> zz() const noexcept { return vec<T, 2>(z, z); }

        [[nodiscard]] vec<T, 3> xxx() const noexcept { return vec<T, 3>(x, x, x); }
        [[nodiscard]] vec<T, 3> xxy() const noexcept { return vec<T, 3>(x, x, y); }
        [[nodiscard]] vec<T, 3> xxz() const noexcept { return vec<T, 3>(x, x, z); }
        [[nodiscard]] vec<T, 3> xyx() const noexcept { return vec<T, 3>(x, y, x); }
        [[nodiscard]] vec<T, 3> xyy() const noexcept { return vec<T, 3>(x, y, y); }
        [[nodiscard]] vec<T, 3> xyz() const noexcept { return vec<T, 3>(x, y, z); }
        [[nodiscard]] vec<T, 3> xzx() const noexcept { return vec<T, 3>(x, z, x); }
        [[nodiscard]] vec<T, 3> xzy() const noexcept { return vec<T, 3>(x, z, y); }
        [[nodiscard]] vec<T, 3> xzz() const noexcept { return vec<T, 3>(x, z, z); }
        [[nodiscard]] vec<T, 3> yxx() const noexcept { return vec<T, 3>(y, x, x); }
        [[nodiscard]] vec<T, 3> yxy() const noexcept { return vec<T, 3>(y, x, y); }
        [[nodiscard]] vec<T, 3> yxz() const noexcept { return vec<T, 3>(y, x, z); }
        [[nodiscard]] vec<T, 3> yyx() const noexcept { return vec<T, 3>(y, y, x); }
        [[nodiscard]] vec<T, 3> yyy() const noexcept { return vec<T, 3>(y, y, y); }
        [[nodiscard]] vec<T, 3> yyz() const noexcept { return vec<T, 3>(y, y, z); }
        [[nodiscard]] vec<T, 3> yzx() const noexcept { return vec<T, 3>(y, z, x); }
        [[nodiscard]] vec<T, 3> yzy() const noexcept { return vec<T, 3>(y, z, y); }
        [[nodiscard]] vec<T, 3> yzz() const noexcept { return vec<T, 3>(y, z, z); }
        [[nodiscard]] vec<T, 3> zxx() const noexcept { return vec<T, 3>(z, x, x); }
        [[nodiscard]] vec<T, 3> zxy() const noexcept { return vec<T, 3>(z, x, y); }
        [[nodiscard]] vec<T, 3> zxz() const noexcept { return vec<T, 3>(z, x, z); }
        [[nodiscard]] vec<T, 3> zyx() const noexcept { return vec<T, 3>(z, y, x); }
        [[nodiscard]] vec<T, 3> zyy() const noexcept { return vec<T, 3>(z, y, y); }
        [[nodiscard]] vec<T, 3> zyz() const noexcept { return vec<T, 3>(z, y, z); }
        [[nodiscard]] vec<T, 3> zzx() const noexcept { return vec<T, 3>(z, z, x); }
        [[nodiscard]] vec<T, 3> zzy() const noexcept { return vec<T, 3>(z, z, y); }
        [[nodiscard]] vec<T, 3> zzz() const noexcept { return vec<T, 3>(z, z, z); }
    };

    ////////////////////////////////////////////////////////////////
    // Check for special values.
    ////////////////////////////////////////////////////////////////

    template<typename T>
    [[nodiscard]] vec<bool, 3> is_finite(const vec<T, 3>& lhs) noexcept { return vec<bool, 3>(std::isfinite(lhs.x), std::isfinite(lhs.y), std::isfinite(lhs.z)); }

    template<typename T>
    [[nodiscard]] vec<bool, 3> is_infinite(const vec<T, 3>& lhs) noexcept { return vec<bool, 3>(std::isinf(lhs.x), std::isinf(lhs.y), std::isinf(lhs.z)); }

    template<typename T>
    [[nodiscard]] vec<bool, 3> is_neg_infinite(const vec<T, 3>& lhs) noexcept { return vec<bool, 3>(lhs.x == -std::numeric_limits<T>::infinite(), lhs.y == -std::numeric_limits<T>::infinite(), lhs.z == -std::numeric_limits<T>::infinite()); }

    template<typename T>
    [[nodiscard]] vec<bool, 3> is_pos_infinite(const vec<T, 3>& lhs) noexcept { return vec<bool, 3>(lhs.x == std::numeric_limits<T>::infinite(), lhs.y == std::numeric_limits<T>::infinite(), lhs.z == std::numeric_limits<T>::infinite()); }

    template<typename T>
    [[nodiscard]] vec<bool, 3> is_NaN(const vec<T, 3>& lhs) noexcept { return vec<bool, 3>(std::isnan(lhs.x), std::isnan(lhs.y), std::isnan(lhs.z)); }

    template<typename T>
    [[nodiscard]] vec<bool, 3> is_normal(const vec<T, 3>& lhs) noexcept { return vec<bool, 3>(std::isnormal(lhs.x), std::isnormal(lhs.y), std::isnormal(lhs.z)); }

    ////////////////////////////////////////////////////////////////
    // Arithmetic operators.
    ////////////////////////////////////////////////////////////////

    template<arithmetic T>
    [[nodiscard]] vec<T, 3> operator+(const vec<T, 3>& lhs, const vec<T, 3>& rhs) noexcept { return vec<T, 3>(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z); }

    template<arithmetic T>
    [[nodiscard]] vec<T, 3> operator+(const vec<T, 3>& lhs, const T rhs) noexcept { return vec<T, 3>(lhs.x + rhs, lhs.y + rhs, lhs.z + rhs); }

    template<arithmetic T>
    [[nodiscard]] vec<T, 3> operator+(const T lhs, const vec<T, 3>& rhs) noexcept { return vec<T, 3>(lhs + rhs.x, lhs + rhs.y, lhs + rhs.z); }

    template<arithmetic T>
    [[nodiscard]] vec<T, 3> operator-(const vec<T, 3>& lhs, const vec<T, 3>& rhs) noexcept { return vec<T, 3>(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z); }

    template<arithmetic T>
    [[nodiscard]] vec<T, 3> operator-(const vec<T, 3>& lhs, const T rhs) noexcept { return vec<T, 3>(lhs.x - rhs, lhs.y - rhs, lhs.z - rhs); }

    template<arithmetic T>
    [[nodiscard]] vec<T, 3> operator-(const T lhs, const vec<T, 3>& rhs) noexcept { return vec<T, 3>(lhs - rhs.x, lhs - rhs.y, lhs - rhs.z); }

    template<arithmetic T>
    [[nodiscard]] vec<T, 3> operator-(const vec<T, 3>& lhs) noexcept { return vec<T, 3>(-lhs.x, -lhs.y, -lhs.z); }

    template<arithmetic T>
    [[nodiscard]] vec<T, 3> operator*(const vec<T, 3>& lhs, const vec<T, 3>& rhs) noexcept { return vec<T, 3>(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z); }

    template<arithmetic T>
    [[nodiscard]] vec<T, 3> operator*(const vec<T, 3>& lhs, const T rhs) noexcept { return vec<T, 3>(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs); }

    template<arithmetic T>
    [[nodiscard]] vec<T, 3> operator*(const T lhs, const vec<T, 3>& rhs) noexcept { return vec<T, 3>(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z); }

    template<arithmetic T>
    [[nodiscard]] vec<T, 3> operator/(const vec<T, 3>& lhs, const vec<T, 3>& rhs) noexcept { return vec<T, 3>(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z); }

    template<arithmetic T>
    [[nodiscard]] vec<T, 3> operator/(const vec<T, 3>& lhs, const T rhs) noexcept { return vec<T, 3>(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs); }

    template<arithmetic T>
    [[nodiscard]] vec<T, 3> operator/(const T lhs, const vec<T, 3>& rhs) noexcept { return vec<T, 3>(lhs / rhs.x, lhs / rhs.y, lhs / rhs.z); }

    ////////////////////////////////////////////////////////////////
    // Comparison operators.
    ////////////////////////////////////////////////////////////////

    template<std::equality_comparable T>
    [[nodiscard]] bool operator==(const vec<T, 3>& lhs, const vec<T, 3>& rhs) noexcept { return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z; }

    template<std::equality_comparable T>
    [[nodiscard]] bool operator!=(const vec<T, 3>& lhs, const vec<T, 3>& rhs) noexcept { return lhs.x != rhs.x || lhs.y != rhs.y || lhs.z != rhs.z; }

    ////////////////////////////////////////////////////////////////
    // Per-element comparisons.
    ////////////////////////////////////////////////////////////////

    template<std::totally_ordered T>
    [[nodiscard]] vec<bool, 3> cmpeq(const vec<T, 3>& lhs, const vec<T, 3>& rhs) noexcept { return vec<bool, 3>(lhs.x == rhs.x, lhs.y == rhs.y, lhs.z == rhs.z); }

    template<std::totally_ordered T>
    [[nodiscard]] vec<bool, 3> cmpeq(const vec<T, 3>& lhs, const T rhs) noexcept { return vec<bool, 3>(lhs.x == rhs, lhs.y == rhs, lhs.z == rhs); }

    template<std::totally_ordered T>
    [[nodiscard]] vec<bool, 3> cmpeq(const T lhs, const vec<T, 3>& rhs) noexcept { return vec<bool, 3>(lhs == rhs.x, lhs == rhs.y, lhs == rhs.z); }

    template<std::totally_ordered T>
    [[nodiscard]] vec<bool, 3> cmpneq(const vec<T, 3>& lhs, const vec<T, 3>& rhs) noexcept { return vec<bool, 3>(lhs.x != rhs.x, lhs.y != rhs.y, lhs.z != rhs.z); }

    template<std::totally_ordered T>
    [[nodiscard]] vec<bool, 3> cmpneq(const vec<T, 3>& lhs, const T rhs) noexcept { return vec<bool, 3>(lhs.x != rhs, lhs.y != rhs, lhs.z != rhs); }

    template<std::totally_ordered T>
    [[nodiscard]] vec<bool, 3> cmpneq(const T lhs, const vec<T, 3>& rhs) noexcept { return vec<bool, 3>(lhs != rhs.x, lhs != rhs.y, lhs != rhs.z); }

    template<std::totally_ordered T>
    [[nodiscard]] vec<bool, 3> cmplt(const vec<T, 3>& lhs, const vec<T, 3>& rhs) noexcept { return vec<bool, 3>(lhs.x < rhs.x, lhs.y < rhs.y, lhs.z < rhs.z); }

    template<std::totally_ordered T>
    [[nodiscard]] vec<bool, 3> cmplt(const vec<T, 3>& lhs, const T rhs) noexcept { return vec<bool, 3>(lhs.x < rhs, lhs.y < rhs, lhs.z < rhs); }

    template<std::totally_ordered T>
    [[nodiscard]] vec<bool, 3> cmplt(const T lhs, const vec<T, 3>& rhs) noexcept { return vec<bool, 3>(lhs < rhs.x, lhs < rhs.y, lhs < rhs.z); }

    template<std::totally_ordered T>
    [[nodiscard]] vec<bool, 3> cmpgt(const vec<T, 3>& lhs, const vec<T, 3>& rhs) noexcept { return vec<bool, 3>(lhs.x > rhs.x, lhs.y > rhs.y, lhs.z > rhs.z); }

    template<std::totally_ordered T>
    [[nodiscard]] vec<bool, 3> cmpgt(const vec<T, 3>& lhs, const T rhs) noexcept { return vec<bool, 3>(lhs.x > rhs, lhs.y > rhs, lhs.z > rhs); }

    template<std::totally_ordered T>
    [[nodiscard]] vec<bool, 3> cmpgt(const T lhs, const vec<T, 3>& rhs) noexcept { return vec<bool, 3>(lhs > rhs.x, lhs > rhs.y, lhs > rhs.z); }

    template<std::totally_ordered T>
    [[nodiscard]] vec<bool, 3> cmple(const vec<T, 3>& lhs, const vec<T, 3>& rhs) noexcept { return vec<bool, 3>(lhs.x <= rhs.x, lhs.y <= rhs.y, lhs.z <= rhs.z); }

    template<std::totally_ordered T>
    [[nodiscard]] vec<bool, 3> cmple(const vec<T, 3>& lhs, const T rhs) noexcept { return vec<bool, 3>(lhs.x <= rhs, lhs.y <= rhs, lhs.z <= rhs); }

    template<std::totally_ordered T>
    [[nodiscard]] vec<bool, 3> cmple(const T lhs, const vec<T, 3>& rhs) noexcept { return vec<bool, 3>(lhs <= rhs.x, lhs <= rhs.y, lhs <= rhs.z); }

    template<std::totally_ordered T>
    [[nodiscard]] vec<bool, 3> cmpge(const vec<T, 3>& lhs, const vec<T, 3>& rhs) noexcept { return vec<bool, 3>(lhs.x >= rhs.x, lhs.y >= rhs.y, lhs.z >= rhs.z); }

    template<std::totally_ordered T>
    [[nodiscard]] vec<bool, 3> cmpge(const vec<T, 3>& lhs, const T rhs) noexcept { return vec<bool, 3>(lhs.x >= rhs, lhs.y >= rhs, lhs.z >= rhs); }

    template<std::totally_ordered T>
    [[nodiscard]] vec<bool, 3> cmpge(const T lhs, const vec<T, 3>& rhs) noexcept { return vec<bool, 3>(lhs >= rhs.x, lhs >= rhs.y, lhs >= rhs.z); }

    ////////////////////////////////////////////////////////////////
    // Dot product etc.
    ////////////////////////////////////////////////////////////////
    
    template<arithmetic T>
    [[nodiscard]] T dot(const vec<T, 3>& lhs, const vec<T, 3>& rhs) noexcept { return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z; }

    template<arithmetic T>
    [[nodiscard]] vec<T, 3> cross(const vec<T, 3>& lhs, const vec<T, 3>& rhs) noexcept { return vec<T, 3>(lhs.y * rhs.z - lhs.z * rhs.y, lhs.z * rhs.x - lhs.x * rhs.z, lhs.x * rhs.y - lhs.y * rhs.x); }
    
    template<arithmetic T>
    [[nodiscard]] vec<T, 3> lerp(const vec<T, 3>& a, const vec<T, 3>& b, const vec<T, 3>& t) noexcept { return vec<T, 3>(lerp(a.x, b.x, t.x), lerp(a.y, b.y, t.y), lerp(a.z, b.z, t.z)); }

    template<arithmetic T>
    [[nodiscard]] vec<T, 3> lerp(const vec<T, 3>& a, const vec<T, 3>& b, const T t) noexcept { return vec<T, 3>(lerp(a.x, b.x, t), lerp(a.y, b.y, t), lerp(a.z, b.z, t)); }

    ////////////////////////////////////////////////////////////////
    // Trigonometry.
    ////////////////////////////////////////////////////////////////

    template<std::floating_point T>
    [[nodiscard]] vec<T, 3> acos(const vec<T, 3>& lhs) noexcept { return vec<T, 3>(acos(lhs.x), acos(lhs.y), acos(lhs.z)); }

    template<std::floating_point T>
    [[nodiscard]] vec<T, 3> asin(const vec<T, 3>& lhs) noexcept { return vec<T, 3>(asin(lhs.x), asin(lhs.y), asin(lhs.z)); }

    template<std::floating_point T>
    [[nodiscard]] vec<T, 3> atan(const vec<T, 3>& lhs) noexcept { return vec<T, 3>(atan(lhs.x), atan(lhs.y), atan(lhs.z)); }

    template<std::floating_point T>
    [[nodiscard]] vec<T, 3> atan2(const vec<T, 3>& lhs, const vec<T, 3>& rhs) noexcept { return vec<T, 3>(atan2(lhs.x, rhs.x), atan2(lhs.y, rhs.y), atan2(lhs.z, rhs.z)); }

    template<std::floating_point T>
    [[nodiscard]] vec<T, 3> cos(const vec<T, 3>& lhs) noexcept { return vec<T, 3>(cos(lhs.x), cos(lhs.y), cos(lhs.z)); }

    template<std::floating_point T>
    [[nodiscard]] vec<T, 3> cosh(const vec<T, 3>& lhs) noexcept { return vec<T, 3>(cosh(lhs.x), cosh(lhs.y), cosh(lhs.z)); }

    template<std::floating_point T>
    [[nodiscard]] vec<T, 3> sin(const vec<T, 3>& lhs) noexcept { return vec<T, 3>(sin(lhs.x), sin(lhs.y), sin(lhs.z)); }

    template<std::floating_point T>
    [[nodiscard]] vec<T, 3> sinh(const vec<T, 3>& lhs) noexcept { return vec<T, 3>(sinh(lhs.x), sinh(lhs.y), sinh(lhs.z)); }

    template<std::floating_point T>
    [[nodiscard]] vec<T, 3> tan(const vec<T, 3>& lhs) noexcept { return vec<T, 3>(tan(lhs.x), tan(lhs.y), tan(lhs.z)); }

    template<std::floating_point T>
    [[nodiscard]] vec<T, 3> tanh(const vec<T, 3>& lhs) noexcept { return vec<T, 3>(tanh(lhs.x), tanh(lhs.y), tanh(lhs.z)); }

    ////////////////////////////////////////////////////////////////
    // Exponential / Logarithmic.
    ////////////////////////////////////////////////////////////////

    template<std::floating_point T>
    [[nodiscard]] vec<T, 3> exp(const vec<T, 3>& lhs) noexcept { return vec<T, 3>(exp(lhs.x), exp(lhs.y), exp(lhs.z)); }

    template<std::floating_point T>
    [[nodiscard]] vec<T, 3> exp2(const vec<T, 3>& lhs) noexcept { return vec<T, 3>(exp2(lhs.x), exp2(lhs.y), exp2(lhs.z)); }

    template<std::floating_point T>
    [[nodiscard]] vec<T, 3> log(const vec<T, 3>& lhs) noexcept { return vec<T, 3>(log(lhs.x), log(lhs.y), log(lhs.z)); }

    template<std::floating_point T>
    [[nodiscard]] vec<T, 3> log2(const vec<T, 3>& lhs) noexcept { return vec<T, 3>(log2(lhs.x), log2(lhs.y), log2(lhs.z)); }

    template<std::floating_point T>
    [[nodiscard]] vec<T, 3> log10(const vec<T, 3>& lhs) noexcept { return vec<T, 3>(log10(lhs.x), log10(lhs.y), log10(lhs.z)); }

    ////////////////////////////////////////////////////////////////
    // Power.
    ////////////////////////////////////////////////////////////////

    template<std::floating_point T>
    [[nodiscard]] vec<T, 3> pow(const vec<T, 3>& lhs, const vec<T, 3>& rhs) noexcept { return vec<T, 3>(pow(lhs.x, rhs.x), pow(lhs.y, rhs.y), pow(lhs.z, rhs.z)); }

    template<std::floating_point T>
    [[nodiscard]] vec<T, 3> pow(const vec<T, 3>& lhs, const T rhs) noexcept { return vec<T, 3>(pow(lhs.x, rhs), pow(lhs.y, rhs), pow(lhs.z, rhs)); }

    template<std::floating_point T>
    [[nodiscard]] vec<T, 3> sqrt(const vec<T, 3>& lhs) noexcept { return vec<T, 3>(sqrt(lhs.x), sqrt(lhs.y), sqrt(lhs.z)); }

    template<std::floating_point T>
    [[nodiscard]] vec<T, 3> rsqrt(const vec<T, 3>& lhs) noexcept { return vec<T, 3>(rsqrt(lhs.x), rsqrt(lhs.y), rsqrt(lhs.z)); }

    ////////////////////////////////////////////////////////////////
    // Min/max, abs and clamp.
    ////////////////////////////////////////////////////////////////

    template<has_min T>
    [[nodiscard]] vec<T, 3> min(const vec<T, 3>& lhs, const vec<T, 3>& rhs) noexcept { return vec<T, 3>(min(lhs.x, rhs.x), min(lhs.y, rhs.y), min(lhs.z, rhs.z)); }

    template<has_min T>
    [[nodiscard]] vec<T, 3> min(const vec<T, 3>& lhs, const T rhs) noexcept { return vec<T, 3>(min(lhs.x, rhs), min(lhs.y, rhs), min(lhs.z, rhs)); }

    template<has_min T>
    [[nodiscard]] vec<T, 3> min(const T lhs, const vec<T, 3>& rhs) noexcept { return vec<T, 3>(min(lhs, rhs.x), min(lhs, rhs.y), min(lhs, rhs.z)); }

    template<has_max T>
    [[nodiscard]] vec<T, 3> max(const vec<T, 3>& lhs, const vec<T, 3>& rhs) noexcept { return vec<T, 3>(max(lhs.x, rhs.x), max(lhs.y, rhs.y), max(lhs.z, rhs.z)); }

    template<has_max T>
    [[nodiscard]] vec<T, 3> max(const vec<T, 3>& lhs, const T rhs) noexcept { return vec<T, 3>(max(lhs.x, rhs), max(lhs.y, rhs), max(lhs.z, rhs)); }

    template<has_max T>
    [[nodiscard]] vec<T, 3> max(const T lhs, const vec<T, 3>& rhs) noexcept { return vec<T, 3>(max(lhs, rhs.x), max(lhs, rhs.y), max(lhs, rhs.z)); }

    template<has_clamp T>
    [[nodiscard]] vec<T, 3> clamp(const vec<T, 3>& a, const vec<T, 3>& min, const vec<T, 3>& max) noexcept { return vec<T, 3>(clamp(a.x, min.x, max.x), clamp(a.y, min.y, max.y), clamp(a.z, min.z, max.z)); }

    template<has_clamp T>
    [[nodiscard]] vec<T, 3> clamp(const vec<T, 3>& a, const vec<T, 3>& min, const T max) noexcept { return vec<T, 3>(clamp(a.x, min.x, max), clamp(a.y, min.y, max), clamp(a.z, min.z, max)); }

    template<has_clamp T>
    [[nodiscard]] vec<T, 3> clamp(const vec<T, 3>& a, const T min, const vec<T, 3>& max) noexcept { return vec<T, 3>(clamp(a.x, min, max.x), clamp(a.y, min, max.y), clamp(a.z, min, max.z)); }

    template<has_clamp T>
    [[nodiscard]] vec<T, 3> clamp(const vec<T, 3>& a, const T min, const T max) noexcept { return vec<T, 3>(clamp(a.x, min, max), clamp(a.y, min, max), clamp(a.z, min, max)); }

    ////////////////////////////////////////////////////////////////
    // Rounding, abs, etc.
    ////////////////////////////////////////////////////////////////

    template<has_abs T>
    [[nodiscard]] vec<T, 3> abs(const vec<T, 3>& lhs) noexcept { return vec<T, 3>(abs(lhs.x), abs(lhs.y), abs(lhs.z)); }

    template<has_ceil T>
    [[nodiscard]] vec<T, 3> ceil(const vec<T, 3>& lhs) noexcept { return vec<T, 3>(ceil(lhs.x), ceil(lhs.y), ceil(lhs.z)); }

    template<has_floor T>
    [[nodiscard]] vec<T, 3> floor(const vec<T, 3>& lhs) noexcept { return vec<T, 3>(floor(lhs.x), floor(lhs.y), floor(lhs.z)); }

    template<has_frac T>
    [[nodiscard]] vec<T, 3> frac(const vec<T, 3>& lhs) noexcept { return vec<T, 3>(frac(lhs.x), frac(lhs.y), frac(lhs.z)); }

    template<has_round T>
    [[nodiscard]] vec<T, 3> round(const vec<T, 3>& lhs) noexcept { return vec<T, 3>(round(lhs.x), round(lhs.y), round(lhs.z)); }

    template<has_trunc T>
    [[nodiscard]] vec<T, 3> trunc(const vec<T, 3>& lhs) noexcept { return vec<T, 3>(trunc(lhs.x), trunc(lhs.y), trunc(lhs.z)); }

    ////////////////////////////////////////////////////////////////
    // Select.
    ////////////////////////////////////////////////////////////////

    template<typename T>
    [[nodiscard]] vec<T, 3> select(const vec<T, 3>& t, const vec<T, 3>& f, const vec<bool, 3>& b) noexcept { return vec<T, 3>(select(t.x, f.x, b.x), select(t.y, f.y, b.y), select(t.z, f.z, b.z)); }

    ////////////////////////////////////////////////////////////////
    // Multiply and add.
    ////////////////////////////////////////////////////////////////

    template<arithmetic T>
    [[nodiscard]] vec<T, 3> madd(const vec<T, 3>& a, const vec<T, 3>& b, const vec<T, 3>& c) noexcept { return vec<T, 3>(madd(a.x, b.x, c.x), madd(a.y, b.y, c.y), madd(a.z, b.z, c.z)); }

    template<arithmetic T>
    [[nodiscard]] vec<T, 3> nmadd(const vec<T, 3>& a, const vec<T, 3>& b, const vec<T, 3>& c) noexcept { return vec<T, 3>(nmadd(a.x, b.x, c.x), nmadd(a.y, b.y, c.y), nmadd(a.z, b.z, c.z)); }

    template<arithmetic T>
    [[nodiscard]] vec<T, 3> msub(const vec<T, 3>& a, const vec<T, 3>& b, const vec<T, 3>& c) noexcept { return vec<T, 3>(msub(a.x, b.x, c.x), msub(a.y, b.y, c.y), msub(a.z, b.z, c.z)); }

    template<arithmetic T>
    [[nodiscard]] vec<T, 3> nmsub(const vec<T, 3>& a, const vec<T, 3>& b, const vec<T, 3>& c) noexcept { return vec<T, 3>(nmsub(a.x, b.x, c.x), nmsub(a.y, b.y, c.y), nmsub(a.z, b.z, c.z)); }

    ////////////////////////////////////////////////////////////////
    // Reduction.
    ////////////////////////////////////////////////////////////////

    template<arithmetic T>
    [[nodiscard]] T reduce_add(const vec<T, 3>& lhs) noexcept { return lhs.x + lhs.y + lhs.z; }

    template<arithmetic T>
    [[nodiscard]] T reduce_mul(const vec<T, 3>& lhs) noexcept { return lhs.x * lhs.y * lhs.z; }

    template<arithmetic T>
    [[nodiscard]] T reduce_min(const vec<T, 3>& lhs) noexcept { return min(lhs.x, lhs.y, lhs.z); }

    template<arithmetic T>
    [[nodiscard]] T reduce_max(const vec<T, 3>& lhs) noexcept { return max(lhs.x, lhs.y, lhs.z); }

    ////////////////////////////////////////////////////////////////
    // Shift operators.
    ////////////////////////////////////////////////////////////////

    template<std::integral T, std::integral U>
    [[nodiscard]] vec<T, 3> operator<<(const vec<T, 3>& lhs, const vec<U, 3>& rhs) noexcept { return vec<T, 3>(lhs.x << rhs.x, lhs.y << rhs.y, lhs.z << rhs.z); }

    template<std::integral T, std::integral U>
    [[nodiscard]] vec<T, 3> operator<<(const vec<T, 3>& lhs, const U rhs) noexcept { return vec<T, 3>(lhs.x << rhs, lhs.y << rhs, lhs.z << rhs); }

    template<std::integral T, std::integral U>
    [[nodiscard]] vec<T, 3> operator<<(const T lhs, const vec<U, 3>& rhs) noexcept { return vec<T, 3>(lhs << rhs.x, lhs << rhs.y, lhs << rhs.z); }

    template<std::integral T, std::integral U>
    [[nodiscard]] vec<T, 3> operator>>(const vec<T, 3>& lhs, const vec<U, 3>& rhs) noexcept { return vec<T, 3>(lhs.x >> rhs.x, lhs.y >> rhs.y, lhs.z >> rhs.z); }

    template<std::integral T, std::integral U>
    [[nodiscard]] vec<T, 3> operator>>(const vec<T, 3>& lhs, const U rhs) noexcept { return vec<T, 3>(lhs.x >> rhs, lhs.y >> rhs, lhs.z >> rhs); }

    template<std::integral T, std::integral U>
    [[nodiscard]] vec<T, 3> operator>>(const T lhs, const vec<U, 3>& rhs) noexcept { return vec<T, 3>(lhs >> rhs.x, lhs >> rhs.y, lhs >> rhs.z); }

    ////////////////////////////////////////////////////////////////
    // Bitwise operators.
    ////////////////////////////////////////////////////////////////

    template<std::integral T>
    [[nodiscard]] vec<T, 3> operator|(const vec<T, 3>& lhs, const vec<T, 3>& rhs) noexcept { return vec<T, 3>(lhs.x | rhs.x, lhs.y | rhs.y, lhs.z | rhs.z); }

    template<std::integral T>
    [[nodiscard]] vec<T, 3> operator|(const vec<T, 3>& lhs, const T rhs) noexcept { return vec<T, 3>(lhs.x | rhs, lhs.y | rhs, lhs.z | rhs); }

    template<std::integral T>
    [[nodiscard]] vec<T, 3> operator|(const T lhs, const vec<T, 3>& rhs) noexcept { return vec<T, 3>(lhs | rhs.x, lhs | rhs.y, lhs | rhs.z); }

    template<std::integral T>
    [[nodiscard]] vec<T, 3> operator&(const vec<T, 3>& lhs, const vec<T, 3>& rhs) noexcept { return vec<T, 3>(lhs.x & rhs.x, lhs.y & rhs.y, lhs.z & rhs.z); }

    template<std::integral T>
    [[nodiscard]] vec<T, 3> operator&(const vec<T, 3>& lhs, const T rhs) noexcept { return vec<T, 3>(lhs.x & rhs, lhs.y & rhs, lhs.z & rhs); }

    template<std::integral T>
    [[nodiscard]] vec<T, 3> operator&(const T lhs, const vec<T, 3>& rhs) noexcept { return vec<T, 3>(lhs & rhs.x, lhs & rhs.y, lhs & rhs.z); }

    template<std::integral T>
    [[nodiscard]] vec<T, 3> operator^(const vec<T, 3>& lhs, const vec<T, 3>& rhs) noexcept { return vec<T, 3>(lhs.x ^ rhs.x, lhs.y ^ rhs.y, lhs.z ^ rhs.z); }

    template<std::integral T>
    [[nodiscard]] vec<T, 3> operator^(const vec<T, 3>& lhs, const T rhs) noexcept { return vec<T, 3>(lhs.x ^ rhs, lhs.y ^ rhs, lhs.z ^ rhs); }

    template<std::integral T>
    [[nodiscard]] vec<T, 3> operator^(const T lhs, const vec<T, 3>& rhs) noexcept { return vec<T, 3>(lhs ^ rhs.x, lhs ^ rhs.y, lhs ^ rhs.z); }

    template<std::integral T>
    [[nodiscard]] vec<T, 3> operator~(const vec<T, 3>& lhs) noexcept { return vec<T, 3>(~lhs.x, ~lhs.y, ~lhs.z); }

    ////////////////////////////////////////////////////////////////
    // Boolean vector reduction.
    ////////////////////////////////////////////////////////////////

    [[nodiscard]] inline bool all(const vec<bool, 3>& lhs) noexcept { return lhs.x & lhs.y & lhs.z; }

    [[nodiscard]] inline bool any(const vec<bool, 3>& lhs) noexcept { return lhs.x | lhs.y | lhs.z; }

    ////////////////////////////////////////////////////////////////
    // Output.
    ////////////////////////////////////////////////////////////////
    
    template<typename T>
    std::ostream& operator<<(std::ostream& out, const vec<T, 3>& v) { return out << "(" << v.x << ", " << v.y << ", " << v.z << ")"; }
}
