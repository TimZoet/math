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

namespace math
{
    template<typename T>
    struct vec<T, 4>
    {
        static constexpr size_t size = 4;
        using element_type = T;

        T x, y, z, w;
        
        ////////////////////////////////////////////////////////////////
        // Constructors.
        ////////////////////////////////////////////////////////////////

        // Default.

        [[nodiscard]] vec() noexcept : x(0), y(0), z(0), w(0) {}

        // From values.

        [[nodiscard]] explicit vec(const T v) noexcept : x(v), y(v), z(v), w(v) {}

        [[nodiscard]] vec(const T x, const T y) noexcept : x(x), y(y), z(0), w(0) { }

        [[nodiscard]] vec(const T x, const T y, const T z) noexcept : x(x), y(y), z(z), w(0) { }

        [[nodiscard]] vec(const T x, const T y, const T z, const T w) noexcept : x(x), y(y), z(z), w(w) { }

        // From convertible values.

        template<std::convertible_to<T> U>
        [[nodiscard]] explicit vec(const U v) : x(static_cast<T>(v)), y(static_cast<T>(v)), z(static_cast<T>(v)), w(static_cast<T>(v)) {}

        template<std::convertible_to<T> U>
        [[nodiscard]] vec(const U x, const U y) : x(static_cast<T>(x)), y(static_cast<T>(y)), z(0), w(0) {}

        template<std::convertible_to<T> U>
        [[nodiscard]] vec(const U x, const U y, const U z) : x(static_cast<T>(x)), y(static_cast<T>(y)), z(static_cast<T>(z)), w(0) {}

        template<std::convertible_to<T> U>
        [[nodiscard]] vec(const U x, const U y, const U z, const U w) : x(static_cast<T>(x)), y(static_cast<T>(y)), z(static_cast<T>(z)), w(static_cast<T>(w)) {}

        // From pointer.

        [[nodiscard]] explicit vec(const T* ptr) : x(ptr[0]), y(ptr[1]), z(ptr[2]), w(ptr[3]) {}

        // Copy.

        [[nodiscard]] vec(const vec<T, 2>& rhs) noexcept : x(rhs.x), y(rhs.y), z(0), w(0) {}

        [[nodiscard]] vec(const vec<T, 3>& rhs) noexcept : x(rhs.x), y(rhs.y), z(rhs.z), w(0) {}

        [[nodiscard]] vec(const vec<T, 4>& rhs) noexcept : x(rhs.x), y(rhs.y), z(rhs.z), w(rhs.w) {}

        // Move.

        [[nodiscard]] vec(vec<T, 2>&& rhs) noexcept : x(rhs.x), y(rhs.y), z(0), w(0) {}

        [[nodiscard]] vec(vec<T, 3>&& rhs) noexcept : x(rhs.x), y(rhs.y), z(rhs.z), w(0) {}

        [[nodiscard]] vec(vec<T, 4>&& rhs) noexcept : x(rhs.x), y(rhs.y), z(rhs.z), w(rhs.w) {}

        // Copy from convertible.

        template<std::convertible_to<T> U>
        [[nodiscard]] explicit vec(const vec<U, 2>& rhs) : x(static_cast<T>(rhs.x)), y(static_cast<T>(rhs.y)), z(0), w(0) {}

        template<std::convertible_to<T> U>
        [[nodiscard]] explicit vec(const vec<U, 3>& rhs) : x(static_cast<T>(rhs.x)), y(static_cast<T>(rhs.y)), z(static_cast<T>(rhs.z)), w(0) {}

        template<std::convertible_to<T> U>
        [[nodiscard]] explicit vec(const vec<U, 4>& rhs) : x(static_cast<T>(rhs.x)), y(static_cast<T>(rhs.y)), z(static_cast<T>(rhs.z)), w(static_cast<T>(rhs.w)) {}

        // Move from convertible.

        // Copy from vector and value.

        [[nodiscard]] vec(const vec<T, 3>& xyz, const T w) noexcept : x(xyz.x), y(xyz.y), z(xyz.z), w(w) {}

        template<std::convertible_to<T> U, std::convertible_to<T> V>
        [[nodiscard]] vec(const vec<U, 3>& xyz, const V w) noexcept : x(static_cast<T>(xyz.x)), y(static_cast<T>(xyz.y)), z(static_cast<T>(xyz.z)), w(static_cast<T>(w)) {}

        ////////////////////////////////////////////////////////////////
        // Assignment operators.
        ////////////////////////////////////////////////////////////////

        // Copy.

        vec<T, 4>& operator=(const vec<T, 2>& rhs) noexcept { x = rhs.x; y = rhs.y; z = 0; w = 0; return *this; }

        vec<T, 4>& operator=(const vec<T, 3>& rhs) noexcept { x = rhs.x; y = rhs.y; z = rhs.z; w = 0; return *this; }

        vec<T, 4>& operator=(const vec<T, 4>& rhs) noexcept { x = rhs.x; y = rhs.y; z = rhs.z; w = rhs.w; return *this; }

        // Move.

        vec<T, 4>& operator=(vec<T, 2>&& rhs) noexcept { x = rhs.x; y = rhs.y; z = 0; w = 0; return *this; }

        vec<T, 4>& operator=(vec<T, 3>&& rhs) noexcept { x = rhs.x; y = rhs.y; z = rhs.z; w = 0; return *this; }

        vec<T, 4>& operator=(vec<T, 4>&& rhs) noexcept { x = rhs.x; y = rhs.y; z = rhs.z; w = rhs.w; return *this; }

        // Assign from value.

        vec<T, 4>& operator=(const T rhs) noexcept { x = rhs; y = rhs; z = rhs; w = rhs; return *this; }

        // Assign from convertible value.

        template<std::convertible_to<T> U>
        vec<T, 4>& operator=(const U rhs) { x = static_cast<T>(rhs); y = static_cast<T>(rhs); z = static_cast<T>(rhs); w = static_cast<T>(rhs); return *this; }

        // Assign from convertible.

        template<std::convertible_to<T> U>
        vec<T, 4>& operator=(const vec<U, 2>& rhs) { x = static_cast<T>(rhs.x); y = static_cast<T>(rhs.y); z = 0; w = 0; return *this; }

        template<std::convertible_to<T> U>
        vec<T, 4>& operator=(const vec<U, 3>& rhs) { x = static_cast<T>(rhs.x); y = static_cast<T>(rhs.y); z = static_cast<T>(rhs.z); w = 0; return *this; }

        template<std::convertible_to<T> U>
        vec<T, 4>& operator=(const vec<U, 4>& rhs) { x = static_cast<T>(rhs.x); y = static_cast<T>(rhs.y); z = static_cast<T>(rhs.z); w = static_cast<T>(rhs.w); return *this; }

        ////////////////////////////////////////////////////////////////
        // Destructor.
        ////////////////////////////////////////////////////////////////

        ~vec() noexcept = default;

        ////////////////////////////////////////////////////////////////
        // Element access.
        ////////////////////////////////////////////////////////////////

        [[nodiscard]] const T& operator[](const size_t i) const { assert(i < 4); return (&x)[i]; }

        [[nodiscard]] T& operator[](const size_t i) { assert(i < 4); return (&x)[i]; }

        ////////////////////////////////////////////////////////////////
        // Swizzling.
        ////////////////////////////////////////////////////////////////
        
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

        [[nodiscard]] vec<T, 4> xxxx() const noexcept { return vec<T, 4>(x, x, x, x); }
        [[nodiscard]] vec<T, 4> xxxy() const noexcept { return vec<T, 4>(x, x, x, y); }
        [[nodiscard]] vec<T, 4> xxxz() const noexcept { return vec<T, 4>(x, x, x, z); }
        [[nodiscard]] vec<T, 4> xxxw() const noexcept { return vec<T, 4>(x, x, x, w); }
        [[nodiscard]] vec<T, 4> xxyx() const noexcept { return vec<T, 4>(x, x, y, x); }
        [[nodiscard]] vec<T, 4> xxyy() const noexcept { return vec<T, 4>(x, x, y, y); }
        [[nodiscard]] vec<T, 4> xxyz() const noexcept { return vec<T, 4>(x, x, y, z); }
        [[nodiscard]] vec<T, 4> xxyw() const noexcept { return vec<T, 4>(x, x, y, w); }
        [[nodiscard]] vec<T, 4> xxzx() const noexcept { return vec<T, 4>(x, x, z, x); }
        [[nodiscard]] vec<T, 4> xxzy() const noexcept { return vec<T, 4>(x, x, z, y); }
        [[nodiscard]] vec<T, 4> xxzz() const noexcept { return vec<T, 4>(x, x, z, z); }
        [[nodiscard]] vec<T, 4> xxzw() const noexcept { return vec<T, 4>(x, x, z, w); }
        [[nodiscard]] vec<T, 4> xxwx() const noexcept { return vec<T, 4>(x, x, w, x); }
        [[nodiscard]] vec<T, 4> xxwy() const noexcept { return vec<T, 4>(x, x, w, y); }
        [[nodiscard]] vec<T, 4> xxwz() const noexcept { return vec<T, 4>(x, x, w, z); }
        [[nodiscard]] vec<T, 4> xxww() const noexcept { return vec<T, 4>(x, x, w, w); }
        [[nodiscard]] vec<T, 4> xyxx() const noexcept { return vec<T, 4>(x, y, x, x); }
        [[nodiscard]] vec<T, 4> xyxy() const noexcept { return vec<T, 4>(x, y, x, y); }
        [[nodiscard]] vec<T, 4> xyxz() const noexcept { return vec<T, 4>(x, y, x, z); }
        [[nodiscard]] vec<T, 4> xyxw() const noexcept { return vec<T, 4>(x, y, x, w); }
        [[nodiscard]] vec<T, 4> xyyx() const noexcept { return vec<T, 4>(x, y, y, x); }
        [[nodiscard]] vec<T, 4> xyyy() const noexcept { return vec<T, 4>(x, y, y, y); }
        [[nodiscard]] vec<T, 4> xyyz() const noexcept { return vec<T, 4>(x, y, y, z); }
        [[nodiscard]] vec<T, 4> xyyw() const noexcept { return vec<T, 4>(x, y, y, w); }
        [[nodiscard]] vec<T, 4> xyzx() const noexcept { return vec<T, 4>(x, y, z, x); }
        [[nodiscard]] vec<T, 4> xyzy() const noexcept { return vec<T, 4>(x, y, z, y); }
        [[nodiscard]] vec<T, 4> xyzz() const noexcept { return vec<T, 4>(x, y, z, z); }
        [[nodiscard]] vec<T, 4> xyzw() const noexcept { return vec<T, 4>(x, y, z, w); }
        [[nodiscard]] vec<T, 4> xywx() const noexcept { return vec<T, 4>(x, y, w, x); }
        [[nodiscard]] vec<T, 4> xywy() const noexcept { return vec<T, 4>(x, y, w, y); }
        [[nodiscard]] vec<T, 4> xywz() const noexcept { return vec<T, 4>(x, y, w, z); }
        [[nodiscard]] vec<T, 4> xyww() const noexcept { return vec<T, 4>(x, y, w, w); }
        [[nodiscard]] vec<T, 4> xzxx() const noexcept { return vec<T, 4>(x, z, x, x); }
        [[nodiscard]] vec<T, 4> xzxy() const noexcept { return vec<T, 4>(x, z, x, y); }
        [[nodiscard]] vec<T, 4> xzxz() const noexcept { return vec<T, 4>(x, z, x, z); }
        [[nodiscard]] vec<T, 4> xzxw() const noexcept { return vec<T, 4>(x, z, x, w); }
        [[nodiscard]] vec<T, 4> xzyx() const noexcept { return vec<T, 4>(x, z, y, x); }
        [[nodiscard]] vec<T, 4> xzyy() const noexcept { return vec<T, 4>(x, z, y, y); }
        [[nodiscard]] vec<T, 4> xzyz() const noexcept { return vec<T, 4>(x, z, y, z); }
        [[nodiscard]] vec<T, 4> xzyw() const noexcept { return vec<T, 4>(x, z, y, w); }
        [[nodiscard]] vec<T, 4> xzzx() const noexcept { return vec<T, 4>(x, z, z, x); }
        [[nodiscard]] vec<T, 4> xzzy() const noexcept { return vec<T, 4>(x, z, z, y); }
        [[nodiscard]] vec<T, 4> xzzz() const noexcept { return vec<T, 4>(x, z, z, z); }
        [[nodiscard]] vec<T, 4> xzzw() const noexcept { return vec<T, 4>(x, z, z, w); }
        [[nodiscard]] vec<T, 4> xzwx() const noexcept { return vec<T, 4>(x, z, w, x); }
        [[nodiscard]] vec<T, 4> xzwy() const noexcept { return vec<T, 4>(x, z, w, y); }
        [[nodiscard]] vec<T, 4> xzwz() const noexcept { return vec<T, 4>(x, z, w, z); }
        [[nodiscard]] vec<T, 4> xzww() const noexcept { return vec<T, 4>(x, z, w, w); }
        [[nodiscard]] vec<T, 4> xwxx() const noexcept { return vec<T, 4>(x, w, x, x); }
        [[nodiscard]] vec<T, 4> xwxy() const noexcept { return vec<T, 4>(x, w, x, y); }
        [[nodiscard]] vec<T, 4> xwxz() const noexcept { return vec<T, 4>(x, w, x, z); }
        [[nodiscard]] vec<T, 4> xwxw() const noexcept { return vec<T, 4>(x, w, x, w); }
        [[nodiscard]] vec<T, 4> xwyx() const noexcept { return vec<T, 4>(x, w, y, x); }
        [[nodiscard]] vec<T, 4> xwyy() const noexcept { return vec<T, 4>(x, w, y, y); }
        [[nodiscard]] vec<T, 4> xwyz() const noexcept { return vec<T, 4>(x, w, y, z); }
        [[nodiscard]] vec<T, 4> xwyw() const noexcept { return vec<T, 4>(x, w, y, w); }
        [[nodiscard]] vec<T, 4> xwzx() const noexcept { return vec<T, 4>(x, w, z, x); }
        [[nodiscard]] vec<T, 4> xwzy() const noexcept { return vec<T, 4>(x, w, z, y); }
        [[nodiscard]] vec<T, 4> xwzz() const noexcept { return vec<T, 4>(x, w, z, z); }
        [[nodiscard]] vec<T, 4> xwzw() const noexcept { return vec<T, 4>(x, w, z, w); }
        [[nodiscard]] vec<T, 4> xwwx() const noexcept { return vec<T, 4>(x, w, w, x); }
        [[nodiscard]] vec<T, 4> xwwy() const noexcept { return vec<T, 4>(x, w, w, y); }
        [[nodiscard]] vec<T, 4> xwwz() const noexcept { return vec<T, 4>(x, w, w, z); }
        [[nodiscard]] vec<T, 4> xwww() const noexcept { return vec<T, 4>(x, w, w, w); }
        [[nodiscard]] vec<T, 4> yxxx() const noexcept { return vec<T, 4>(y, x, x, x); }
        [[nodiscard]] vec<T, 4> yxxy() const noexcept { return vec<T, 4>(y, x, x, y); }
        [[nodiscard]] vec<T, 4> yxxz() const noexcept { return vec<T, 4>(y, x, x, z); }
        [[nodiscard]] vec<T, 4> yxxw() const noexcept { return vec<T, 4>(y, x, x, w); }
        [[nodiscard]] vec<T, 4> yxyx() const noexcept { return vec<T, 4>(y, x, y, x); }
        [[nodiscard]] vec<T, 4> yxyy() const noexcept { return vec<T, 4>(y, x, y, y); }
        [[nodiscard]] vec<T, 4> yxyz() const noexcept { return vec<T, 4>(y, x, y, z); }
        [[nodiscard]] vec<T, 4> yxyw() const noexcept { return vec<T, 4>(y, x, y, w); }
        [[nodiscard]] vec<T, 4> yxzx() const noexcept { return vec<T, 4>(y, x, z, x); }
        [[nodiscard]] vec<T, 4> yxzy() const noexcept { return vec<T, 4>(y, x, z, y); }
        [[nodiscard]] vec<T, 4> yxzz() const noexcept { return vec<T, 4>(y, x, z, z); }
        [[nodiscard]] vec<T, 4> yxzw() const noexcept { return vec<T, 4>(y, x, z, w); }
        [[nodiscard]] vec<T, 4> yxwx() const noexcept { return vec<T, 4>(y, x, w, x); }
        [[nodiscard]] vec<T, 4> yxwy() const noexcept { return vec<T, 4>(y, x, w, y); }
        [[nodiscard]] vec<T, 4> yxwz() const noexcept { return vec<T, 4>(y, x, w, z); }
        [[nodiscard]] vec<T, 4> yxww() const noexcept { return vec<T, 4>(y, x, w, w); }
        [[nodiscard]] vec<T, 4> yyxx() const noexcept { return vec<T, 4>(y, y, x, x); }
        [[nodiscard]] vec<T, 4> yyxy() const noexcept { return vec<T, 4>(y, y, x, y); }
        [[nodiscard]] vec<T, 4> yyxz() const noexcept { return vec<T, 4>(y, y, x, z); }
        [[nodiscard]] vec<T, 4> yyxw() const noexcept { return vec<T, 4>(y, y, x, w); }
        [[nodiscard]] vec<T, 4> yyyx() const noexcept { return vec<T, 4>(y, y, y, x); }
        [[nodiscard]] vec<T, 4> yyyy() const noexcept { return vec<T, 4>(y, y, y, y); }
        [[nodiscard]] vec<T, 4> yyyz() const noexcept { return vec<T, 4>(y, y, y, z); }
        [[nodiscard]] vec<T, 4> yyyw() const noexcept { return vec<T, 4>(y, y, y, w); }
        [[nodiscard]] vec<T, 4> yyzx() const noexcept { return vec<T, 4>(y, y, z, x); }
        [[nodiscard]] vec<T, 4> yyzy() const noexcept { return vec<T, 4>(y, y, z, y); }
        [[nodiscard]] vec<T, 4> yyzz() const noexcept { return vec<T, 4>(y, y, z, z); }
        [[nodiscard]] vec<T, 4> yyzw() const noexcept { return vec<T, 4>(y, y, z, w); }
        [[nodiscard]] vec<T, 4> yywx() const noexcept { return vec<T, 4>(y, y, w, x); }
        [[nodiscard]] vec<T, 4> yywy() const noexcept { return vec<T, 4>(y, y, w, y); }
        [[nodiscard]] vec<T, 4> yywz() const noexcept { return vec<T, 4>(y, y, w, z); }
        [[nodiscard]] vec<T, 4> yyww() const noexcept { return vec<T, 4>(y, y, w, w); }
        [[nodiscard]] vec<T, 4> yzxx() const noexcept { return vec<T, 4>(y, z, x, x); }
        [[nodiscard]] vec<T, 4> yzxy() const noexcept { return vec<T, 4>(y, z, x, y); }
        [[nodiscard]] vec<T, 4> yzxz() const noexcept { return vec<T, 4>(y, z, x, z); }
        [[nodiscard]] vec<T, 4> yzxw() const noexcept { return vec<T, 4>(y, z, x, w); }
        [[nodiscard]] vec<T, 4> yzyx() const noexcept { return vec<T, 4>(y, z, y, x); }
        [[nodiscard]] vec<T, 4> yzyy() const noexcept { return vec<T, 4>(y, z, y, y); }
        [[nodiscard]] vec<T, 4> yzyz() const noexcept { return vec<T, 4>(y, z, y, z); }
        [[nodiscard]] vec<T, 4> yzyw() const noexcept { return vec<T, 4>(y, z, y, w); }
        [[nodiscard]] vec<T, 4> yzzx() const noexcept { return vec<T, 4>(y, z, z, x); }
        [[nodiscard]] vec<T, 4> yzzy() const noexcept { return vec<T, 4>(y, z, z, y); }
        [[nodiscard]] vec<T, 4> yzzz() const noexcept { return vec<T, 4>(y, z, z, z); }
        [[nodiscard]] vec<T, 4> yzzw() const noexcept { return vec<T, 4>(y, z, z, w); }
        [[nodiscard]] vec<T, 4> yzwx() const noexcept { return vec<T, 4>(y, z, w, x); }
        [[nodiscard]] vec<T, 4> yzwy() const noexcept { return vec<T, 4>(y, z, w, y); }
        [[nodiscard]] vec<T, 4> yzwz() const noexcept { return vec<T, 4>(y, z, w, z); }
        [[nodiscard]] vec<T, 4> yzww() const noexcept { return vec<T, 4>(y, z, w, w); }
        [[nodiscard]] vec<T, 4> ywxx() const noexcept { return vec<T, 4>(y, w, x, x); }
        [[nodiscard]] vec<T, 4> ywxy() const noexcept { return vec<T, 4>(y, w, x, y); }
        [[nodiscard]] vec<T, 4> ywxz() const noexcept { return vec<T, 4>(y, w, x, z); }
        [[nodiscard]] vec<T, 4> ywxw() const noexcept { return vec<T, 4>(y, w, x, w); }
        [[nodiscard]] vec<T, 4> ywyx() const noexcept { return vec<T, 4>(y, w, y, x); }
        [[nodiscard]] vec<T, 4> ywyy() const noexcept { return vec<T, 4>(y, w, y, y); }
        [[nodiscard]] vec<T, 4> ywyz() const noexcept { return vec<T, 4>(y, w, y, z); }
        [[nodiscard]] vec<T, 4> ywyw() const noexcept { return vec<T, 4>(y, w, y, w); }
        [[nodiscard]] vec<T, 4> ywzx() const noexcept { return vec<T, 4>(y, w, z, x); }
        [[nodiscard]] vec<T, 4> ywzy() const noexcept { return vec<T, 4>(y, w, z, y); }
        [[nodiscard]] vec<T, 4> ywzz() const noexcept { return vec<T, 4>(y, w, z, z); }
        [[nodiscard]] vec<T, 4> ywzw() const noexcept { return vec<T, 4>(y, w, z, w); }
        [[nodiscard]] vec<T, 4> ywwx() const noexcept { return vec<T, 4>(y, w, w, x); }
        [[nodiscard]] vec<T, 4> ywwy() const noexcept { return vec<T, 4>(y, w, w, y); }
        [[nodiscard]] vec<T, 4> ywwz() const noexcept { return vec<T, 4>(y, w, w, z); }
        [[nodiscard]] vec<T, 4> ywww() const noexcept { return vec<T, 4>(y, w, w, w); }
        [[nodiscard]] vec<T, 4> zxxx() const noexcept { return vec<T, 4>(z, x, x, x); }
        [[nodiscard]] vec<T, 4> zxxy() const noexcept { return vec<T, 4>(z, x, x, y); }
        [[nodiscard]] vec<T, 4> zxxz() const noexcept { return vec<T, 4>(z, x, x, z); }
        [[nodiscard]] vec<T, 4> zxxw() const noexcept { return vec<T, 4>(z, x, x, w); }
        [[nodiscard]] vec<T, 4> zxyx() const noexcept { return vec<T, 4>(z, x, y, x); }
        [[nodiscard]] vec<T, 4> zxyy() const noexcept { return vec<T, 4>(z, x, y, y); }
        [[nodiscard]] vec<T, 4> zxyz() const noexcept { return vec<T, 4>(z, x, y, z); }
        [[nodiscard]] vec<T, 4> zxyw() const noexcept { return vec<T, 4>(z, x, y, w); }
        [[nodiscard]] vec<T, 4> zxzx() const noexcept { return vec<T, 4>(z, x, z, x); }
        [[nodiscard]] vec<T, 4> zxzy() const noexcept { return vec<T, 4>(z, x, z, y); }
        [[nodiscard]] vec<T, 4> zxzz() const noexcept { return vec<T, 4>(z, x, z, z); }
        [[nodiscard]] vec<T, 4> zxzw() const noexcept { return vec<T, 4>(z, x, z, w); }
        [[nodiscard]] vec<T, 4> zxwx() const noexcept { return vec<T, 4>(z, x, w, x); }
        [[nodiscard]] vec<T, 4> zxwy() const noexcept { return vec<T, 4>(z, x, w, y); }
        [[nodiscard]] vec<T, 4> zxwz() const noexcept { return vec<T, 4>(z, x, w, z); }
        [[nodiscard]] vec<T, 4> zxww() const noexcept { return vec<T, 4>(z, x, w, w); }
        [[nodiscard]] vec<T, 4> zyxx() const noexcept { return vec<T, 4>(z, y, x, x); }
        [[nodiscard]] vec<T, 4> zyxy() const noexcept { return vec<T, 4>(z, y, x, y); }
        [[nodiscard]] vec<T, 4> zyxz() const noexcept { return vec<T, 4>(z, y, x, z); }
        [[nodiscard]] vec<T, 4> zyxw() const noexcept { return vec<T, 4>(z, y, x, w); }
        [[nodiscard]] vec<T, 4> zyyx() const noexcept { return vec<T, 4>(z, y, y, x); }
        [[nodiscard]] vec<T, 4> zyyy() const noexcept { return vec<T, 4>(z, y, y, y); }
        [[nodiscard]] vec<T, 4> zyyz() const noexcept { return vec<T, 4>(z, y, y, z); }
        [[nodiscard]] vec<T, 4> zyyw() const noexcept { return vec<T, 4>(z, y, y, w); }
        [[nodiscard]] vec<T, 4> zyzx() const noexcept { return vec<T, 4>(z, y, z, x); }
        [[nodiscard]] vec<T, 4> zyzy() const noexcept { return vec<T, 4>(z, y, z, y); }
        [[nodiscard]] vec<T, 4> zyzz() const noexcept { return vec<T, 4>(z, y, z, z); }
        [[nodiscard]] vec<T, 4> zyzw() const noexcept { return vec<T, 4>(z, y, z, w); }
        [[nodiscard]] vec<T, 4> zywx() const noexcept { return vec<T, 4>(z, y, w, x); }
        [[nodiscard]] vec<T, 4> zywy() const noexcept { return vec<T, 4>(z, y, w, y); }
        [[nodiscard]] vec<T, 4> zywz() const noexcept { return vec<T, 4>(z, y, w, z); }
        [[nodiscard]] vec<T, 4> zyww() const noexcept { return vec<T, 4>(z, y, w, w); }
        [[nodiscard]] vec<T, 4> zzxx() const noexcept { return vec<T, 4>(z, z, x, x); }
        [[nodiscard]] vec<T, 4> zzxy() const noexcept { return vec<T, 4>(z, z, x, y); }
        [[nodiscard]] vec<T, 4> zzxz() const noexcept { return vec<T, 4>(z, z, x, z); }
        [[nodiscard]] vec<T, 4> zzxw() const noexcept { return vec<T, 4>(z, z, x, w); }
        [[nodiscard]] vec<T, 4> zzyx() const noexcept { return vec<T, 4>(z, z, y, x); }
        [[nodiscard]] vec<T, 4> zzyy() const noexcept { return vec<T, 4>(z, z, y, y); }
        [[nodiscard]] vec<T, 4> zzyz() const noexcept { return vec<T, 4>(z, z, y, z); }
        [[nodiscard]] vec<T, 4> zzyw() const noexcept { return vec<T, 4>(z, z, y, w); }
        [[nodiscard]] vec<T, 4> zzzx() const noexcept { return vec<T, 4>(z, z, z, x); }
        [[nodiscard]] vec<T, 4> zzzy() const noexcept { return vec<T, 4>(z, z, z, y); }
        [[nodiscard]] vec<T, 4> zzzz() const noexcept { return vec<T, 4>(z, z, z, z); }
        [[nodiscard]] vec<T, 4> zzzw() const noexcept { return vec<T, 4>(z, z, z, w); }
        [[nodiscard]] vec<T, 4> zzwx() const noexcept { return vec<T, 4>(z, z, w, x); }
        [[nodiscard]] vec<T, 4> zzwy() const noexcept { return vec<T, 4>(z, z, w, y); }
        [[nodiscard]] vec<T, 4> zzwz() const noexcept { return vec<T, 4>(z, z, w, z); }
        [[nodiscard]] vec<T, 4> zzww() const noexcept { return vec<T, 4>(z, z, w, w); }
        [[nodiscard]] vec<T, 4> zwxx() const noexcept { return vec<T, 4>(z, w, x, x); }
        [[nodiscard]] vec<T, 4> zwxy() const noexcept { return vec<T, 4>(z, w, x, y); }
        [[nodiscard]] vec<T, 4> zwxz() const noexcept { return vec<T, 4>(z, w, x, z); }
        [[nodiscard]] vec<T, 4> zwxw() const noexcept { return vec<T, 4>(z, w, x, w); }
        [[nodiscard]] vec<T, 4> zwyx() const noexcept { return vec<T, 4>(z, w, y, x); }
        [[nodiscard]] vec<T, 4> zwyy() const noexcept { return vec<T, 4>(z, w, y, y); }
        [[nodiscard]] vec<T, 4> zwyz() const noexcept { return vec<T, 4>(z, w, y, z); }
        [[nodiscard]] vec<T, 4> zwyw() const noexcept { return vec<T, 4>(z, w, y, w); }
        [[nodiscard]] vec<T, 4> zwzx() const noexcept { return vec<T, 4>(z, w, z, x); }
        [[nodiscard]] vec<T, 4> zwzy() const noexcept { return vec<T, 4>(z, w, z, y); }
        [[nodiscard]] vec<T, 4> zwzz() const noexcept { return vec<T, 4>(z, w, z, z); }
        [[nodiscard]] vec<T, 4> zwzw() const noexcept { return vec<T, 4>(z, w, z, w); }
        [[nodiscard]] vec<T, 4> zwwx() const noexcept { return vec<T, 4>(z, w, w, x); }
        [[nodiscard]] vec<T, 4> zwwy() const noexcept { return vec<T, 4>(z, w, w, y); }
        [[nodiscard]] vec<T, 4> zwwz() const noexcept { return vec<T, 4>(z, w, w, z); }
        [[nodiscard]] vec<T, 4> zwww() const noexcept { return vec<T, 4>(z, w, w, w); }
        [[nodiscard]] vec<T, 4> wxxx() const noexcept { return vec<T, 4>(w, x, x, x); }
        [[nodiscard]] vec<T, 4> wxxy() const noexcept { return vec<T, 4>(w, x, x, y); }
        [[nodiscard]] vec<T, 4> wxxz() const noexcept { return vec<T, 4>(w, x, x, z); }
        [[nodiscard]] vec<T, 4> wxxw() const noexcept { return vec<T, 4>(w, x, x, w); }
        [[nodiscard]] vec<T, 4> wxyx() const noexcept { return vec<T, 4>(w, x, y, x); }
        [[nodiscard]] vec<T, 4> wxyy() const noexcept { return vec<T, 4>(w, x, y, y); }
        [[nodiscard]] vec<T, 4> wxyz() const noexcept { return vec<T, 4>(w, x, y, z); }
        [[nodiscard]] vec<T, 4> wxyw() const noexcept { return vec<T, 4>(w, x, y, w); }
        [[nodiscard]] vec<T, 4> wxzx() const noexcept { return vec<T, 4>(w, x, z, x); }
        [[nodiscard]] vec<T, 4> wxzy() const noexcept { return vec<T, 4>(w, x, z, y); }
        [[nodiscard]] vec<T, 4> wxzz() const noexcept { return vec<T, 4>(w, x, z, z); }
        [[nodiscard]] vec<T, 4> wxzw() const noexcept { return vec<T, 4>(w, x, z, w); }
        [[nodiscard]] vec<T, 4> wxwx() const noexcept { return vec<T, 4>(w, x, w, x); }
        [[nodiscard]] vec<T, 4> wxwy() const noexcept { return vec<T, 4>(w, x, w, y); }
        [[nodiscard]] vec<T, 4> wxwz() const noexcept { return vec<T, 4>(w, x, w, z); }
        [[nodiscard]] vec<T, 4> wxww() const noexcept { return vec<T, 4>(w, x, w, w); }
        [[nodiscard]] vec<T, 4> wyxx() const noexcept { return vec<T, 4>(w, y, x, x); }
        [[nodiscard]] vec<T, 4> wyxy() const noexcept { return vec<T, 4>(w, y, x, y); }
        [[nodiscard]] vec<T, 4> wyxz() const noexcept { return vec<T, 4>(w, y, x, z); }
        [[nodiscard]] vec<T, 4> wyxw() const noexcept { return vec<T, 4>(w, y, x, w); }
        [[nodiscard]] vec<T, 4> wyyx() const noexcept { return vec<T, 4>(w, y, y, x); }
        [[nodiscard]] vec<T, 4> wyyy() const noexcept { return vec<T, 4>(w, y, y, y); }
        [[nodiscard]] vec<T, 4> wyyz() const noexcept { return vec<T, 4>(w, y, y, z); }
        [[nodiscard]] vec<T, 4> wyyw() const noexcept { return vec<T, 4>(w, y, y, w); }
        [[nodiscard]] vec<T, 4> wyzx() const noexcept { return vec<T, 4>(w, y, z, x); }
        [[nodiscard]] vec<T, 4> wyzy() const noexcept { return vec<T, 4>(w, y, z, y); }
        [[nodiscard]] vec<T, 4> wyzz() const noexcept { return vec<T, 4>(w, y, z, z); }
        [[nodiscard]] vec<T, 4> wyzw() const noexcept { return vec<T, 4>(w, y, z, w); }
        [[nodiscard]] vec<T, 4> wywx() const noexcept { return vec<T, 4>(w, y, w, x); }
        [[nodiscard]] vec<T, 4> wywy() const noexcept { return vec<T, 4>(w, y, w, y); }
        [[nodiscard]] vec<T, 4> wywz() const noexcept { return vec<T, 4>(w, y, w, z); }
        [[nodiscard]] vec<T, 4> wyww() const noexcept { return vec<T, 4>(w, y, w, w); }
        [[nodiscard]] vec<T, 4> wzxx() const noexcept { return vec<T, 4>(w, z, x, x); }
        [[nodiscard]] vec<T, 4> wzxy() const noexcept { return vec<T, 4>(w, z, x, y); }
        [[nodiscard]] vec<T, 4> wzxz() const noexcept { return vec<T, 4>(w, z, x, z); }
        [[nodiscard]] vec<T, 4> wzxw() const noexcept { return vec<T, 4>(w, z, x, w); }
        [[nodiscard]] vec<T, 4> wzyx() const noexcept { return vec<T, 4>(w, z, y, x); }
        [[nodiscard]] vec<T, 4> wzyy() const noexcept { return vec<T, 4>(w, z, y, y); }
        [[nodiscard]] vec<T, 4> wzyz() const noexcept { return vec<T, 4>(w, z, y, z); }
        [[nodiscard]] vec<T, 4> wzyw() const noexcept { return vec<T, 4>(w, z, y, w); }
        [[nodiscard]] vec<T, 4> wzzx() const noexcept { return vec<T, 4>(w, z, z, x); }
        [[nodiscard]] vec<T, 4> wzzy() const noexcept { return vec<T, 4>(w, z, z, y); }
        [[nodiscard]] vec<T, 4> wzzz() const noexcept { return vec<T, 4>(w, z, z, z); }
        [[nodiscard]] vec<T, 4> wzzw() const noexcept { return vec<T, 4>(w, z, z, w); }
        [[nodiscard]] vec<T, 4> wzwx() const noexcept { return vec<T, 4>(w, z, w, x); }
        [[nodiscard]] vec<T, 4> wzwy() const noexcept { return vec<T, 4>(w, z, w, y); }
        [[nodiscard]] vec<T, 4> wzwz() const noexcept { return vec<T, 4>(w, z, w, z); }
        [[nodiscard]] vec<T, 4> wzww() const noexcept { return vec<T, 4>(w, z, w, w); }
        [[nodiscard]] vec<T, 4> wwxx() const noexcept { return vec<T, 4>(w, w, x, x); }
        [[nodiscard]] vec<T, 4> wwxy() const noexcept { return vec<T, 4>(w, w, x, y); }
        [[nodiscard]] vec<T, 4> wwxz() const noexcept { return vec<T, 4>(w, w, x, z); }
        [[nodiscard]] vec<T, 4> wwxw() const noexcept { return vec<T, 4>(w, w, x, w); }
        [[nodiscard]] vec<T, 4> wwyx() const noexcept { return vec<T, 4>(w, w, y, x); }
        [[nodiscard]] vec<T, 4> wwyy() const noexcept { return vec<T, 4>(w, w, y, y); }
        [[nodiscard]] vec<T, 4> wwyz() const noexcept { return vec<T, 4>(w, w, y, z); }
        [[nodiscard]] vec<T, 4> wwyw() const noexcept { return vec<T, 4>(w, w, y, w); }
        [[nodiscard]] vec<T, 4> wwzx() const noexcept { return vec<T, 4>(w, w, z, x); }
        [[nodiscard]] vec<T, 4> wwzy() const noexcept { return vec<T, 4>(w, w, z, y); }
        [[nodiscard]] vec<T, 4> wwzz() const noexcept { return vec<T, 4>(w, w, z, z); }
        [[nodiscard]] vec<T, 4> wwzw() const noexcept { return vec<T, 4>(w, w, z, w); }
        [[nodiscard]] vec<T, 4> wwwx() const noexcept { return vec<T, 4>(w, w, w, x); }
        [[nodiscard]] vec<T, 4> wwwy() const noexcept { return vec<T, 4>(w, w, w, y); }
        [[nodiscard]] vec<T, 4> wwwz() const noexcept { return vec<T, 4>(w, w, w, z); }
        [[nodiscard]] vec<T, 4> wwww() const noexcept { return vec<T, 4>(w, w, w, w); }
    };

    ////////////////////////////////////////////////////////////////
    // Check for special values.
    ////////////////////////////////////////////////////////////////

    template<typename T>
    [[nodiscard]] vec<bool, 4> is_finite(const vec<T, 4>& lhs) noexcept { return vec<bool, 4>(std::isfinite(lhs.x), std::isfinite(lhs.y), std::isfinite(lhs.z), std::isfinite(lhs.w)); }

    template<typename T>
    [[nodiscard]] vec<bool, 4> is_infinite(const vec<T, 4>& lhs) noexcept { return vec<bool, 4>(std::isinf(lhs.x), std::isinf(lhs.y), std::isinf(lhs.z), std::isinf(lhs.w)); }

    template<typename T>
    [[nodiscard]] vec<bool, 4> is_neg_infinite(const vec<T, 4>& lhs) noexcept { return vec<bool, 4>(lhs.x == -std::numeric_limits<T>::infinite(), lhs.y == -std::numeric_limits<T>::infinite(), lhs.z == -std::numeric_limits<T>::infinite(), lhs.w == -std::numeric_limits<T>::infinite()); }

    template<typename T>
    [[nodiscard]] vec<bool, 4> is_pos_infinite(const vec<T, 4>& lhs) noexcept { return vec<bool, 4>(lhs.x == std::numeric_limits<T>::infinite(), lhs.y == std::numeric_limits<T>::infinite(), lhs.z == std::numeric_limits<T>::infinite(), lhs.w == std::numeric_limits<T>::infinite()); }

    template<typename T>
    [[nodiscard]] vec<bool, 4> is_NaN(const vec<T, 4>& lhs) noexcept { return vec<bool, 4>(std::isnan(lhs.x), std::isnan(lhs.y), std::isnan(lhs.z), std::isnan(lhs.w)); }

    template<typename T>
    [[nodiscard]] vec<bool, 4> is_normal(const vec<T, 4>& lhs) noexcept { return vec<bool, 4>(std::isnormal(lhs.x), std::isnormal(lhs.y), std::isnormal(lhs.z), std::isnormal(lhs.w)); }

    ////////////////////////////////////////////////////////////////
    // Arithmetic operators.
    ////////////////////////////////////////////////////////////////

    template<arithmetic T>
    [[nodiscard]] vec<T, 4> operator+(const vec<T, 4>& lhs, const vec<T, 4>& rhs) noexcept { return vec<T, 4>(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w); }

    template<arithmetic T>
    [[nodiscard]] vec<T, 4> operator+(const vec<T, 4>& lhs, const T rhs) noexcept { return vec<T, 4>(lhs.x + rhs, lhs.y + rhs, lhs.z + rhs, lhs.w + rhs); }

    template<arithmetic T>
    [[nodiscard]] vec<T, 4> operator+(const T lhs, const vec<T, 4>& rhs) noexcept { return vec<T, 4>(lhs + rhs.x, lhs + rhs.y, lhs + rhs.z, lhs + rhs.w); }

    template<arithmetic T>
    [[nodiscard]] vec<T, 4> operator-(const vec<T, 4>& lhs, const vec<T, 4>& rhs) noexcept { return vec<T, 4>(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w); }

    template<arithmetic T>
    [[nodiscard]] vec<T, 4> operator-(const vec<T, 4>& lhs, const T rhs) noexcept { return vec<T, 4>(lhs.x - rhs, lhs.y - rhs, lhs.z - rhs, lhs.w - rhs); }

    template<arithmetic T>
    [[nodiscard]] vec<T, 4> operator-(const T lhs, const vec<T, 4>& rhs) noexcept { return vec<T, 4>(lhs - rhs.x, lhs - rhs.y, lhs - rhs.z, lhs - rhs.w); }

    template<arithmetic T>
    [[nodiscard]] vec<T, 4> operator-(const vec<T, 4>& lhs) noexcept { return vec<T, 4>(-lhs.x, -lhs.y, -lhs.z, -lhs.w); }

    template<arithmetic T>
    [[nodiscard]] vec<T, 4> operator*(const vec<T, 4>& lhs, const vec<T, 4>& rhs) noexcept { return vec<T, 4>(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z, lhs.w * rhs.w); }

    template<arithmetic T>
    [[nodiscard]] vec<T, 4> operator*(const vec<T, 4>& lhs, const T rhs) noexcept { return vec<T, 4>(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs, lhs.w * rhs); }

    template<arithmetic T>
    [[nodiscard]] vec<T, 4> operator*(const T lhs, const vec<T, 4>& rhs) noexcept { return vec<T, 4>(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z, lhs * rhs.w); }

    template<arithmetic T>
    [[nodiscard]] vec<T, 4> operator/(const vec<T, 4>& lhs, const vec<T, 4>& rhs) noexcept { return vec<T, 4>(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z, lhs.w / rhs.w); }

    template<arithmetic T>
    [[nodiscard]] vec<T, 4> operator/(const vec<T, 4>& lhs, const T rhs) noexcept { const T inv = T(1) / rhs; return vec<T, 4>(lhs.x * inv, lhs.y * inv, lhs.z * inv, lhs.w * inv); }

    template<arithmetic T>
    [[nodiscard]] vec<T, 4> operator/(const T lhs, const vec<T, 4>& rhs) noexcept { return vec<T, 4>(lhs / rhs.x, lhs / rhs.y, lhs / rhs.z, lhs / rhs.w); }

    ////////////////////////////////////////////////////////////////
    // Comparison operators.
    ////////////////////////////////////////////////////////////////
    
    template<std::equality_comparable T>
    [[nodiscard]] bool operator==(const vec<T, 4>& lhs, const vec<T, 4>& rhs) noexcept { return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w; }

    template<std::equality_comparable T>
    [[nodiscard]] bool operator!=(const vec<T, 4>& lhs, const vec<T, 4>& rhs) noexcept { return lhs.x != rhs.x || lhs.y != rhs.y || lhs.z != rhs.z || lhs.w != rhs.w; }

    ////////////////////////////////////////////////////////////////
    // Per-element comparisons.
    ////////////////////////////////////////////////////////////////
    
    template<std::totally_ordered T>
    [[nodiscard]] vec<bool, 4> cmpeq(const vec<T, 4>& lhs, const vec<T, 4>& rhs) noexcept { return vec<bool, 4>(lhs.x == rhs.x, lhs.y == rhs.y, lhs.z == rhs.z, lhs.w == rhs.w); }

    template<std::totally_ordered T>
    [[nodiscard]] vec<bool, 4> cmpeq(const vec<T, 4>& lhs, const T rhs) noexcept { return vec<bool, 4>(lhs.x == rhs, lhs.y == rhs, lhs.z == rhs, lhs.w == rhs); }

    template<std::totally_ordered T>
    [[nodiscard]] vec<bool, 4> cmpeq(const T lhs, const vec<T, 4>& rhs) noexcept { return vec<bool, 4>(lhs == rhs.x, lhs == rhs.y, lhs == rhs.z, lhs == rhs.w); }

    template<std::totally_ordered T>
    [[nodiscard]] vec<bool, 4> cmpneq(const vec<T, 4>& lhs, const vec<T, 4>& rhs) noexcept { return vec<bool, 4>(lhs.x != rhs.x, lhs.y != rhs.y, lhs.z != rhs.z, lhs.w != rhs.w); }

    template<std::totally_ordered T>
    [[nodiscard]] vec<bool, 4> cmpneq(const vec<T, 4>& lhs, const T rhs) noexcept { return vec<bool, 4>(lhs.x != rhs, lhs.y != rhs, lhs.z != rhs, lhs.w != rhs); }

    template<std::totally_ordered T>
    [[nodiscard]] vec<bool, 4> cmpneq(const T lhs, const vec<T, 4>& rhs) noexcept { return vec<bool, 4>(lhs != rhs.x, lhs != rhs.y, lhs != rhs.z, lhs != rhs.w); }

    template<std::totally_ordered T>
    [[nodiscard]] vec<bool, 4> cmplt(const vec<T, 4>& lhs, const vec<T, 4>& rhs) noexcept { return vec<bool, 4>(lhs.x < rhs.x, lhs.y < rhs.y, lhs.z < rhs.z, lhs.w < rhs.w); }

    template<std::totally_ordered T>
    [[nodiscard]] vec<bool, 4> cmplt(const vec<T, 4>& lhs, const T rhs) noexcept { return vec<bool, 4>(lhs.x < rhs, lhs.y < rhs, lhs.z < rhs, lhs.w < rhs); }

    template<std::totally_ordered T>
    [[nodiscard]] vec<bool, 4> cmplt(const T lhs, const vec<T, 4>& rhs) noexcept { return vec<bool, 4>(lhs < rhs.x, lhs < rhs.y, lhs < rhs.z, lhs < rhs.w); }
    
    template<std::totally_ordered T>
    [[nodiscard]] vec<bool, 4> cmpgt(const vec<T, 4>& lhs, const vec<T, 4>& rhs) noexcept { return vec<bool, 4>(lhs.x > rhs.x, lhs.y > rhs.y, lhs.z > rhs.z, lhs.w > rhs.w); }

    template<std::totally_ordered T>
    [[nodiscard]] vec<bool, 4> cmpgt(const vec<T, 4>& lhs, const T rhs) noexcept { return vec<bool, 4>(lhs.x > rhs, lhs.y > rhs, lhs.z > rhs, lhs.w > rhs); }

    template<std::totally_ordered T>
    [[nodiscard]] vec<bool, 4> cmpgt(const T lhs, const vec<T, 4>& rhs) noexcept { return vec<bool, 4>(lhs > rhs.x, lhs > rhs.y, lhs > rhs.z, lhs > rhs.w); }

    template<std::totally_ordered T>
    [[nodiscard]] vec<bool, 4> cmple(const vec<T, 4>& lhs, const vec<T, 4>& rhs) noexcept { return vec<bool, 4>(lhs.x <= rhs.x, lhs.y <= rhs.y, lhs.z <= rhs.z, lhs.w <= rhs.w); }

    template<std::totally_ordered T>
    [[nodiscard]] vec<bool, 4> cmple(const vec<T, 4>& lhs, const T rhs) noexcept { return vec<bool, 4>(lhs.x <= rhs, lhs.y <= rhs, lhs.z <= rhs, lhs.w <= rhs); }

    template<std::totally_ordered T>
    [[nodiscard]] vec<bool, 4> cmple(const T lhs, const vec<T, 4>& rhs) noexcept { return vec<bool, 4>(lhs <= rhs.x, lhs <= rhs.y, lhs <= rhs.z, lhs <= rhs.w); }

    template<std::totally_ordered T>
    [[nodiscard]] vec<bool, 4> cmpge(const vec<T, 4>& lhs, const vec<T, 4>& rhs) noexcept { return vec<bool, 4>(lhs.x >= rhs.x, lhs.y >= rhs.y, lhs.z >= rhs.z, lhs.w >= rhs.w); }

    template<std::totally_ordered T>
    [[nodiscard]] vec<bool, 4> cmpge(const vec<T, 4>& lhs, const T rhs) noexcept { return vec<bool, 4>(lhs.x >= rhs, lhs.y >= rhs, lhs.z >= rhs, lhs.w >= rhs); }

    template<std::totally_ordered T>
    [[nodiscard]] vec<bool, 4> cmpge(const T lhs, const vec<T, 4>& rhs) noexcept { return vec<bool, 4>(lhs >= rhs.x, lhs >= rhs.y, lhs >= rhs.z, lhs >= rhs.w); }

    ////////////////////////////////////////////////////////////////
    // Dot product etc.
    ////////////////////////////////////////////////////////////////

    template<arithmetic T>
    [[nodiscard]] T dot(const vec<T, 4>& lhs, const vec<T, 4>& rhs) noexcept { return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w; }

    template<arithmetic T>
    [[nodiscard]] vec<T, 4> lerp(const vec<T, 4>& a, const vec<T, 4>& b, const vec<T, 4>& t) noexcept { return vec<T, 4>(lerp(a.x, b.x, t.x), lerp(a.y, b.y, t.y), lerp(a.z, b.z, t.z), lerp(a.w, b.w, t.w)); }

    template<arithmetic T>
    [[nodiscard]] vec<T, 4> lerp(const vec<T, 4>& a, const vec<T, 4>& b, const T t) noexcept { return vec<T, 4>(lerp(a.x, b.x, t), lerp(a.y, b.y, t), lerp(a.z, b.z, t), lerp(a.w, b.w, t)); }

    ////////////////////////////////////////////////////////////////
    // Trigonometry.
    ////////////////////////////////////////////////////////////////

    template<std::floating_point T>
    [[nodiscard]] vec<T, 4> acos(const vec<T, 4>& lhs) noexcept { return vec<T, 4>(acos(lhs.x), acos(lhs.y), acos(lhs.z), acos(lhs.w)); }

    template<std::floating_point T>
    [[nodiscard]] vec<T, 4> asin(const vec<T, 4>& lhs) noexcept { return vec<T, 4>(asin(lhs.x), asin(lhs.y), asin(lhs.z), asin(lhs.w)); }

    template<std::floating_point T>
    [[nodiscard]] vec<T, 4> atan(const vec<T, 4>& lhs) noexcept { return vec<T, 4>(atan(lhs.x), atan(lhs.y), atan(lhs.z), atan(lhs.w)); }

    template<std::floating_point T>
    [[nodiscard]] vec<T, 4> atan2(const vec<T, 4>& lhs, const vec<T, 4>& rhs) noexcept { return vec<T, 4>(atan2(lhs.x, rhs.x), atan2(lhs.y, rhs.y), atan2(lhs.z, rhs.z), atan2(lhs.w, rhs.w)); }

    template<std::floating_point T>
    [[nodiscard]] vec<T, 4> cos(const vec<T, 4>& lhs) noexcept { return vec<T, 4>(cos(lhs.x), cos(lhs.y), cos(lhs.z), cos(lhs.w)); }

    template<std::floating_point T>
    [[nodiscard]] vec<T, 4> cosh(const vec<T, 4>& lhs) noexcept { return vec<T, 4>(cosh(lhs.x), cosh(lhs.y), cosh(lhs.z), cosh(lhs.w)); }

    template<std::floating_point T>
    [[nodiscard]] vec<T, 4> sin(const vec<T, 4>& lhs) noexcept { return vec<T, 4>(sin(lhs.x), sin(lhs.y), sin(lhs.z), sin(lhs.w)); }

    template<std::floating_point T>
    [[nodiscard]] vec<T, 4> sinh(const vec<T, 4>& lhs) noexcept { return vec<T, 4>(sinh(lhs.x), sinh(lhs.y), sinh(lhs.z), sinh(lhs.w)); }

    template<std::floating_point T>
    [[nodiscard]] vec<T, 4> tan(const vec<T, 4>& lhs) noexcept { return vec<T, 4>(tan(lhs.x), tan(lhs.y), tan(lhs.z), tan(lhs.w)); }

    template<std::floating_point T>
    [[nodiscard]] vec<T, 4> tanh(const vec<T, 4>& lhs) noexcept { return vec<T, 4>(tanh(lhs.x), tanh(lhs.y), tanh(lhs.z), tanh(lhs.w)); }

    ////////////////////////////////////////////////////////////////
    // Exponential / Logarithmic.
    ////////////////////////////////////////////////////////////////

    template<std::floating_point T>
    [[nodiscard]] vec<T, 4> exp(const vec<T, 4>& lhs) noexcept { return vec<T, 4>(exp(lhs.x), exp(lhs.y), exp(lhs.z), exp(lhs.w)); }

    template<std::floating_point T>
    [[nodiscard]] vec<T, 4> exp2(const vec<T, 4>& lhs) noexcept { return vec<T, 4>(exp2(lhs.x), exp2(lhs.y), exp2(lhs.z), exp2(lhs.w)); }

    template<std::floating_point T>
    [[nodiscard]] vec<T, 4> log(const vec<T, 4>& lhs) noexcept { return vec<T, 4>(log(lhs.x), log(lhs.y), log(lhs.z), log(lhs.w)); }

    template<std::floating_point T>
    [[nodiscard]] vec<T, 4> log2(const vec<T, 4>& lhs) noexcept { return vec<T, 4>(log2(lhs.x), log2(lhs.y), log2(lhs.z), log2(lhs.w)); }

    template<std::floating_point T>
    [[nodiscard]] vec<T, 4> log10(const vec<T, 4>& lhs) noexcept { return vec<T, 4>(log10(lhs.x), log10(lhs.y), log10(lhs.z), log10(lhs.w)); }

    ////////////////////////////////////////////////////////////////
    // Power.
    ////////////////////////////////////////////////////////////////

    template<std::floating_point T>
    [[nodiscard]] vec<T, 4> pow(const vec<T, 4>& lhs, const vec<T, 4>& rhs) noexcept { return vec<T, 4>(pow(lhs.x, rhs.x), pow(lhs.y, rhs.y), pow(lhs.z, rhs.z), pow(lhs.w, rhs.w)); }

    template<std::floating_point T>
    [[nodiscard]] vec<T, 4> pow(const vec<T, 4>& lhs, const T rhs) noexcept { return vec<T, 4>(pow(lhs.x, rhs), pow(lhs.y, rhs), pow(lhs.z, rhs), pow(lhs.w, rhs)); }

    template<std::floating_point T>
    [[nodiscard]] vec<T, 4> sqrt(const vec<T, 4>& lhs) noexcept { return vec<T, 4>(sqrt(lhs.x), sqrt(lhs.y), sqrt(lhs.z), sqrt(lhs.w)); }

    template<std::floating_point T>
    [[nodiscard]] vec<T, 4> rsqrt(const vec<T, 4>& lhs) noexcept { return vec<T, 4>(rsqrt(lhs.x), rsqrt(lhs.y), rsqrt(lhs.z), rsqrt(lhs.w)); }

    ////////////////////////////////////////////////////////////////
    // Min/max, abs and clamp.
    ////////////////////////////////////////////////////////////////

    template<has_min T>
    [[nodiscard]] vec<T, 4> min(const vec<T, 4>& lhs, const vec<T, 4>& rhs) noexcept { return vec<T, 4>(min(lhs.x, rhs.x), min(lhs.y, rhs.y), min(lhs.z, rhs.z), min(lhs.w, rhs.w)); }

    template<has_min T>
    [[nodiscard]] vec<T, 4> min(const vec<T, 4>& lhs, const T rhs) noexcept { return vec<T, 4>(min(lhs.x, rhs), min(lhs.y, rhs), min(lhs.z, rhs), min(lhs.w, rhs)); }

    template<has_min T>
    [[nodiscard]] vec<T, 4> min(const T lhs, const vec<T, 4>& rhs) noexcept { return vec<T, 4>(min(lhs, rhs.x), min(lhs, rhs.y), min(lhs, rhs.z), min(lhs, rhs.w)); }

    template<has_max T>
    [[nodiscard]] vec<T, 4> max(const vec<T, 4>& lhs, const vec<T, 4>& rhs) noexcept { return vec<T, 4>(max(lhs.x, rhs.x), max(lhs.y, rhs.y), max(lhs.z, rhs.z), max(lhs.w, rhs.w)); }

    template<has_max T>
    [[nodiscard]] vec<T, 4> max(const vec<T, 4>& lhs, const T rhs) noexcept { return vec<T, 4>(max(lhs.x, rhs), max(lhs.y, rhs), max(lhs.z, rhs), max(lhs.w, rhs)); }

    template<has_max T>
    [[nodiscard]] vec<T, 4> max(const T lhs, const vec<T, 4>& rhs) noexcept { return vec<T, 4>(max(lhs, rhs.x), max(lhs, rhs.y), max(lhs, rhs.z), max(lhs, rhs.w)); }

    template<has_clamp T>
    [[nodiscard]] vec<T, 4> clamp(const vec<T, 4>& a, const vec<T, 4>& min, const vec<T, 4>& max) noexcept { return vec<T, 4>(clamp(a.x, min.x, max.x), clamp(a.y, min.y, max.y), clamp(a.z, min.z, max.z), clamp(a.w, min.w, max.w)); }

    template<has_clamp T>
    [[nodiscard]] vec<T, 4> clamp(const vec<T, 4>& a, const vec<T, 4>& min, const T max) noexcept { return vec<T, 4>(clamp(a.x, min.x, max), clamp(a.y, min.y, max), clamp(a.z, min.z, max), clamp(a.w, min.w, max)); }

    template<has_clamp T>
    [[nodiscard]] vec<T, 4> clamp(const vec<T, 4>& a, const T min, const vec<T, 4>& max) noexcept { return vec<T, 4>(clamp(a.x, min, max.x), clamp(a.y, min, max.y), clamp(a.z, min, max.z), clamp(a.w, min, max.w)); }

    template<has_clamp T>
    [[nodiscard]] vec<T, 4> clamp(const vec<T, 4>& a, const T min, const T max) noexcept { return vec<T, 4>(clamp(a.x, min, max), clamp(a.y, min, max), clamp(a.z, min, max), clamp(a.w, min, max)); }

    ////////////////////////////////////////////////////////////////
    // Rounding, abs, etc.
    ////////////////////////////////////////////////////////////////
    
    template<has_abs T>
    [[nodiscard]] vec<T, 4> abs(const vec<T, 4>& lhs) noexcept { return vec<T, 4>(abs(lhs.x), abs(lhs.y), abs(lhs.z), abs(lhs.w)); }

    template<has_ceil T>
    [[nodiscard]] vec<T, 4> ceil(const vec<T, 4>& lhs) noexcept { return vec<T, 4>(ceil(lhs.x), ceil(lhs.y), ceil(lhs.z), ceil(lhs.w)); }

    template<has_floor T>
    [[nodiscard]] vec<T, 4> floor(const vec<T, 4>& lhs) noexcept { return vec<T, 4>(floor(lhs.x), floor(lhs.y), floor(lhs.z), floor(lhs.w)); }

    template<has_frac T>
    [[nodiscard]] vec<T, 4> frac(const vec<T, 4>& lhs) noexcept { return vec<T, 4>(frac(lhs.x), frac(lhs.y), frac(lhs.z), frac(lhs.w)); }

    template<has_round T>
    [[nodiscard]] vec<T, 4> round(const vec<T, 4>& lhs) noexcept { return vec<T, 4>(round(lhs.x), round(lhs.y), round(lhs.z), round(lhs.w)); }

    template<has_trunc T>
    [[nodiscard]] vec<T, 4> trunc(const vec<T, 4>& lhs) noexcept { return vec<T, 4>(trunc(lhs.x), trunc(lhs.y), trunc(lhs.z), trunc(lhs.w)); }

    ////////////////////////////////////////////////////////////////
    // Select.
    ////////////////////////////////////////////////////////////////

    template<typename T>
    [[nodiscard]] vec<T, 4> select(const vec<T, 4>& t, const vec<T, 4>& f, const vec<bool, 4>& b) noexcept { return vec<T, 4>(select(t.x, f.x, b.x), select(t.y, f.y, b.y), select(t.z, f.z, b.z), select(t.w, f.w, b.w)); }

    ////////////////////////////////////////////////////////////////
    // Multiply and add.
    ////////////////////////////////////////////////////////////////

    template<arithmetic T>
    [[nodiscard]] vec<T, 4> madd(const vec<T, 4>& a, const vec<T, 4>& b, const vec<T, 4>& c) noexcept { return vec<T, 4>(madd(a.x, b.x, c.x), madd(a.y, b.y, c.y), madd(a.z, b.z, c.z), madd(a.w, b.w, c.w)); }

    template<arithmetic T>
    [[nodiscard]] vec<T, 4> nmadd(const vec<T, 4>& a, const vec<T, 4>& b, const vec<T, 4>& c) noexcept { return vec<T, 4>(nmadd(a.x, b.x, c.x), nmadd(a.y, b.y, c.y), nmadd(a.z, b.z, c.z), nmadd(a.w, b.w, c.w)); }

    template<arithmetic T>
    [[nodiscard]] vec<T, 4> msub(const vec<T, 4>& a, const vec<T, 4>& b, const vec<T, 4>& c) noexcept { return vec<T, 4>(msub(a.x, b.x, c.x), msub(a.y, b.y, c.y), msub(a.z, b.z, c.z), msub(a.w, b.w, c.w)); }

    template<arithmetic T>
    [[nodiscard]] vec<T, 4> nmsub(const vec<T, 4>& a, const vec<T, 4>& b, const vec<T, 4>& c) noexcept { return vec<T, 4>(nmsub(a.x, b.x, c.x), nmsub(a.y, b.y, c.y), nmsub(a.z, b.z, c.z), nmsub(a.w, b.w, c.w)); }

    ////////////////////////////////////////////////////////////////
    // Reduction.
    ////////////////////////////////////////////////////////////////

    template<arithmetic T>
    [[nodiscard]] T reduce_add(const vec<T, 4>& lhs) noexcept { return lhs.x + lhs.y + lhs.z + lhs.w; }

    template<arithmetic T>
    [[nodiscard]] T reduce_mul(const vec<T, 4>& lhs) noexcept { return lhs.x * lhs.y * lhs.z * lhs.w; }

    template<arithmetic T>
    [[nodiscard]] T reduce_min(const vec<T, 4>& lhs) noexcept { return min(lhs.x, lhs.y, lhs.z, lhs.w); }

    template<arithmetic T>
    [[nodiscard]] T reduce_max(const vec<T, 4>& lhs) noexcept { return max(lhs.x, lhs.y, lhs.z, lhs.w); }

    ////////////////////////////////////////////////////////////////
    // Shift operators.
    ////////////////////////////////////////////////////////////////

    template<std::integral T, std::integral U>
    [[nodiscard]] vec<T, 4> operator<<(const vec<T, 4>& lhs, const vec<U, 4>& rhs) noexcept { return vec<T, 4>(lhs.x << rhs.x, lhs.y << rhs.y, lhs.z << rhs.z, lhs.w << rhs.w); }

    template<std::integral T, std::integral U>
    [[nodiscard]] vec<T, 4> operator<<(const vec<T, 4>& lhs, const U rhs) noexcept { return vec<T, 4>(lhs.x << rhs, lhs.y << rhs, lhs.z << rhs, lhs.w << rhs); }

    template<std::integral T, std::integral U>
    [[nodiscard]] vec<T, 4> operator<<(const T lhs, const vec<U, 4>& rhs) noexcept { return vec<T, 4>(lhs << rhs.x, lhs << rhs.y, lhs << rhs.z, lhs << rhs.w); }

    template<std::integral T, std::integral U>
    [[nodiscard]] vec<T, 4> operator>>(const vec<T, 4>& lhs, const vec<U, 4>& rhs) noexcept { return vec<T, 4>(lhs.x >> rhs.x, lhs.y >> rhs.y, lhs.z >> rhs.z, lhs.w >> rhs.w); }

    template<std::integral T, std::integral U>
    [[nodiscard]] vec<T, 4> operator>>(const vec<T, 4>& lhs, const U rhs) noexcept { return vec<T, 4>(lhs.x >> rhs, lhs.y >> rhs, lhs.z >> rhs, lhs.w >> rhs); }

    template<std::integral T, std::integral U>
    [[nodiscard]] vec<T, 4> operator>>(const T lhs, const vec<U, 4>& rhs) noexcept { return vec<T, 4>(lhs >> rhs.x, lhs >> rhs.y, lhs >> rhs.z, lhs >> rhs.w); }

    ////////////////////////////////////////////////////////////////
    // Bitwise operators.
    ////////////////////////////////////////////////////////////////

    template<std::integral T>
    [[nodiscard]] vec<T, 4> operator|(const vec<T, 4>& lhs, const vec<T, 4>& rhs) noexcept { return vec<T, 4>(lhs.x | rhs.x, lhs.y | rhs.y, lhs.z | rhs.z, lhs.w | rhs.w); }

    template<std::integral T>
    [[nodiscard]] vec<T, 4> operator|(const vec<T, 4>& lhs, const T rhs) noexcept { return vec<T, 4>(lhs.x | rhs, lhs.y | rhs, lhs.z | rhs, lhs.w | rhs); }

    template<std::integral T>
    [[nodiscard]] vec<T, 4> operator|(const T lhs, const vec<T, 4>& rhs) noexcept { return vec<T, 4>(lhs | rhs.x, lhs | rhs.y, lhs | rhs.z, lhs | rhs.w); }

    template<std::integral T>
    [[nodiscard]] vec<T, 4> operator&(const vec<T, 4>& lhs, const vec<T, 4>& rhs) noexcept { return vec<T, 4>(lhs.x & rhs.x, lhs.y & rhs.y, lhs.z & rhs.z, lhs.w & rhs.w); }

    template<std::integral T>
    [[nodiscard]] vec<T, 4> operator&(const vec<T, 4>& lhs, const T rhs) noexcept { return vec<T, 4>(lhs.x & rhs, lhs.y & rhs, lhs.z & rhs, lhs.w & rhs); }

    template<std::integral T>
    [[nodiscard]] vec<T, 4> operator&(const T lhs, const vec<T, 4>& rhs) noexcept { return vec<T, 4>(lhs & rhs.x, lhs & rhs.y, lhs & rhs.z, lhs & rhs.w); }

    template<std::integral T>
    [[nodiscard]] vec<T, 4> operator^(const vec<T, 4>& lhs, const vec<T, 4>& rhs) noexcept { return vec<T, 4>(lhs.x ^ rhs.x, lhs.y ^ rhs.y, lhs.z ^ rhs.z, lhs.w ^ rhs.w); }

    template<std::integral T>
    [[nodiscard]] vec<T, 4> operator^(const vec<T, 4>& lhs, const T rhs) noexcept { return vec<T, 4>(lhs.x ^ rhs, lhs.y ^ rhs, lhs.z ^ rhs, lhs.w ^ rhs); }

    template<std::integral T>
    [[nodiscard]] vec<T, 4> operator^(const T lhs, const vec<T, 4>& rhs) noexcept { return vec<T, 4>(lhs ^ rhs.x, lhs ^ rhs.y, lhs ^ rhs.z, lhs ^ rhs.w); }

    template<std::integral T>
    [[nodiscard]] vec<T, 4> operator~(const vec<T, 4>& lhs) noexcept { return vec<T, 4>(~lhs.x, ~lhs.y, ~lhs.z, ~lhs.w); }

    ////////////////////////////////////////////////////////////////
    // Boolean vector reduction.
    ////////////////////////////////////////////////////////////////

    [[nodiscard]] inline bool all(const vec<bool, 4>& lhs) noexcept { return lhs.x & lhs.y & lhs.z & lhs.w; }

    [[nodiscard]] inline bool any(const vec<bool, 4>& lhs) noexcept { return lhs.x | lhs.y | lhs.z | lhs.w; }

    ////////////////////////////////////////////////////////////////
    // Output.
    ////////////////////////////////////////////////////////////////

    template<typename T>
    std::ostream& operator<<(std::ostream& out, const vec<T, 4>& v) { return out << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")"; }
}
