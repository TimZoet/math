#pragma once

////////////////////////////////////////////////////////////////
// Standard includes.
////////////////////////////////////////////////////////////////

#include <array>
#include <cassert>
#include <concepts>
#include <iostream>

////////////////////////////////////////////////////////////////
// Current target includes.
////////////////////////////////////////////////////////////////

#include "math/math_functions.h"
#include "math/math_type_traits.h"

namespace math
{
    /**=================================================================================================
     * Struct: vec
     * =================================================================================================
     * @struct  vec
     *
     * @brief   Generic vector type.
     *
     * @tparam  T   Component type.
     * @tparam  N   Number of dimensions.
    **/
    template<typename T, size_t N>
    struct vec
    {
        static inline size_t size = N;
        using element_type = T;

        std::array<T, N> data;

        ////////////////////////////////////////////////////////////////
        // Constructors.
        ////////////////////////////////////////////////////////////////
        // Note: The order of these constructors is very important.

        // Default.

        [[nodiscard]] vec() noexcept : data() { }

        // From values.

        [[nodiscard]] explicit vec(const T v) noexcept
        {
            for (size_t i = 0; i < N; i++)
                data[i] = v;
        }

        // From convertible values.

        template<std::convertible_to<T> U>
        [[nodiscard]] explicit vec(const U v) noexcept
        {
            for (size_t i = 0; i < N; i++)
                data[i] = static_cast<T>(v);
        }

        template<std::convertible_to<T> U, std::convertible_to<T>... Us> // TODO: requires sizeof...(Us) < N - 1
        [[nodiscard]] vec(const U v, const Us... vs) noexcept
        {
            data[0] = static_cast<T>(v);
            size_t i = 0;
            ((data[++i] = static_cast<T>(vs)), ...);
        }

        // From pointer.

        [[nodiscard]] explicit vec(const T* ptr) noexcept
        {
            std::copy(ptr, ptr + N, &(data[0]));
        }
        // TODO: U* ptr
        // Copy.
        
        [[nodiscard]] vec(const vec<T, N>& rhs) noexcept : data(rhs.data) {}

        // Move.

        [[nodiscard]] vec(vec<T, N>&& rhs) noexcept : data(std::move(rhs.data)) {}

        // Copy from convertible.

        template<std::convertible_to<T> U>
        [[nodiscard]] explicit vec(const vec<U, N>& rhs)
        {
            for (size_t i = 0; i < N; i++)
                data[i] = static_cast<T>(rhs.data[i]);
        }

        // Move from convertible.

        ////////////////////////////////////////////////////////////////
        // Assignment operators.
        ////////////////////////////////////////////////////////////////

        // Copy.

        vec<T, N>& operator=(const vec<T, N>& rhs) noexcept
        {
            data = rhs.data;
            return *this;
        }

        // Move.

        vec<T, N>& operator=(vec<T, N>&& rhs) noexcept
        {
            data = std::move(rhs.data);
            return *this;
        }

        // Assign from value.

        vec<T, N>& operator=(const T rhs) noexcept
        {
            for (size_t i = 0; i < N; i++)
                data[i] = rhs;
            return *this;
        }

        // Assign from convertible value.
        template<std::convertible_to<T> U>

        vec<T, N>& operator=(const U rhs) noexcept
        {
            for (size_t i = 0; i < N; i++)
                data[i] = static_cast<T>(rhs);
            return *this;
        }

        // Assign from convertible.

        template<std::convertible_to<T> U>
        vec<T, N>& operator=(const vec<U, N>& rhs)
        {
            for (size_t i = 0; i < N; i++)
                data[i] = static_cast<T>(rhs.data[i]);
            return *this;
        }

        ////////////////////////////////////////////////////////////////
        // Destructor.
        ////////////////////////////////////////////////////////////////

        ~vec() noexcept = default;

        ////////////////////////////////////////////////////////////////
        // Element access.
        ////////////////////////////////////////////////////////////////

        [[nodiscard]] const T& operator[](const size_t i) const { assert(i < N); return data[i]; }

        [[nodiscard]] T& operator[](const size_t i) { assert(i < N); return data[i]; }
    };

    ////////////////////////////////////////////////////////////////
    // Construct special values.
    ////////////////////////////////////////////////////////////////

    template<element_type_constructible T>
    [[nodiscard]] T zero() noexcept { return T(typename T::element_type(0)); }

    template<element_type_constructible T>
    [[nodiscard]] T one() noexcept { return T(typename T::element_type(1)); }

    template<element_type_constructible T>
    [[nodiscard]] T highest() noexcept { return T(std::numeric_limits<typename T::element_type>::max()); }

    template<element_type_constructible T>
    [[nodiscard]] T lowest() noexcept { return T(std::numeric_limits<typename T::element_type>::lowest()); }

    template<element_type_constructible T>
    [[nodiscard]] T pos_infinity() noexcept { return T(std::numeric_limits<typename T::element_type>::infinity()); }

    template<element_type_constructible T>
    [[nodiscard]] T neg_infinity() noexcept { return T(-std::numeric_limits<typename T::element_type>::infinity()); }

    template<element_type_constructible T>
    [[nodiscard]] T NaN() noexcept { return T(std::numeric_limits<typename T::element_type>::quiet_NaN()); }

    ////////////////////////////////////////////////////////////////
    // Check for special values.
    ////////////////////////////////////////////////////////////////
    
    template<typename T, size_t N>
    [[nodiscard]] vec<bool, N> is_finite(const vec<T, N>& lhs) noexcept
    {
        vec<bool, N> b;
        for (size_t i = 0; i < N; i++)
            b[i] = std::isfinite(lhs[i]);
        return b;
    }

    template<typename T, size_t N>
    [[nodiscard]] vec<bool, N> is_infinite(const vec<T, N>& lhs) noexcept
    {
        vec<bool, N> b;
        for (size_t i = 0; i < N; i++)
            b[i] = std::isinf(lhs[i]);
        return b;
    }

    template<typename T, size_t N>
    [[nodiscard]] vec<bool, N> is_neg_infinite(const vec<T, N>& lhs) noexcept
    {
        vec<bool, N> b;
        for (size_t i = 0; i < N; i++)
            b[i] = lhs[i] == -std::numeric_limits<T>::infinity();
        return b;
    }

    template<typename T, size_t N>
    [[nodiscard]] vec<bool, N> is_pos_infinite(const vec<T, N>& lhs) noexcept
    {
        vec<bool, N> b;
        for (size_t i = 0; i < N; i++)
            b[i] = lhs[i] == std::numeric_limits<T>::infinity();
        return b;
    }

    template<typename T, size_t N>
    [[nodiscard]] vec<bool, N> is_NaN(const vec<T, N>& lhs) noexcept
    {
        vec<bool, N> b;
        for (size_t i = 0; i < N; i++)
            b[i] = std::isnan(lhs[i]);
        return b;
    }

    template<typename T, size_t N>
    [[nodiscard]] vec<bool, N> is_normal(const vec<T, N>& lhs) noexcept
    {
        vec<bool, N> b;
        for (size_t i = 0; i < N; i++)
            b[i] = std::isnormal(lhs[i]);
        return b;
    }

    ////////////////////////////////////////////////////////////////
    // Shuffle.
    ////////////////////////////////////////////////////////////////

    template<size_t ... Indices, template<typename, size_t> class V, typename T, size_t N> requires std::is_same_v<V<T, N>, vec<T, N>>
    [[nodiscard]] auto shuffle(const V<T, N>& v)
    {
        return vec<T, sizeof...(Indices)>(v[Indices]...);
    }

    template<std::integral ... Indices, template<typename, size_t> class V, typename T, size_t N> requires std::is_same_v<V<T, N>, vec<T, N>>
    [[nodiscard]] auto shuffle_v(const V<T, N>& v, const Indices... i)
    {
        return vec<T, sizeof...(Indices)>(v[i]...);
    }

    template<typename T, std::integral I, size_t N>
    [[nodiscard]] auto shuffle_v(const vec<T, N>& v, const vec<I, N>& indices)
    {
        vec<T, N> v2;
        for (I i = 0; i < N; ++i)
            v2[i] = v[indices[i]];
        return v2;
    }

    ////////////////////////////////////////////////////////////////
    // Arithmetic operators.
    ////////////////////////////////////////////////////////////////

    template<arithmetic T, size_t N>
    [[nodiscard]] vec<T, N> operator+(const vec<T, N>& lhs, const vec<T, N>& rhs) noexcept
    {
        vec<T, N> v;
        for (size_t i = 0; i < N; i++)
            v[i] = lhs[i] + rhs[i];
        return v;
    }

    template<arithmetic T, size_t N>
    [[nodiscard]] vec<T, N> operator+(const vec<T, N>& lhs, const T rhs) noexcept
    {
        vec<T, N> v;
        for (size_t i = 0; i < N; i++)
            v[i] = lhs[i] + rhs;
        return v;
    }

    template<arithmetic T, size_t N>
    [[nodiscard]] vec<T, N> operator+(const T lhs, const vec<T, N>& rhs) noexcept
    {
        vec<T, N> v;
        for (size_t i = 0; i < N; i++)
            v[i] = lhs + rhs[i];
        return v;
    }

    template<arithmetic T, size_t N>
    [[nodiscard]] vec<T, N> operator-(const vec<T, N>& lhs, const vec<T, N>& rhs) noexcept
    {
        vec<T, N> v;
        for (size_t i = 0; i < N; i++)
            v[i] = lhs[i] - rhs[i];
        return v;
    }

    template<arithmetic T, size_t N>
    [[nodiscard]] vec<T, N> operator-(const vec<T, N>& lhs, const T rhs) noexcept
    {
        vec<T, N> v;
        for (size_t i = 0; i < N; i++)
            v[i] = lhs[i] - rhs;
        return v;
    }

    template<arithmetic T, size_t N>
    [[nodiscard]] vec<T, N> operator-(const T lhs, const vec<T, N>& rhs) noexcept
    {
        vec<T, N> v;
        for (size_t i = 0; i < N; i++)
            v[i] = lhs - rhs[i];
        return v;
    }

    template<arithmetic T, size_t N>
    [[nodiscard]] vec<T, N> operator-(const vec<T, N>& lhs) noexcept
    {
        vec<T, N> v;
        for (size_t i = 0; i < N; i++)
            v[i] = -lhs[i];
        return v;
    }

    template<arithmetic T, size_t N>
    [[nodiscard]] vec<T, N> operator*(const vec<T, N>& lhs, const vec<T, N>& rhs) noexcept
    {
        vec<T, N> v;
        for (size_t i = 0; i < N; i++)
            v[i] = lhs[i] * rhs[i];
        return v;
    }

    template<arithmetic T, size_t N>
    [[nodiscard]] vec<T, N> operator*(const vec<T, N>& lhs, const T rhs) noexcept
    {
        vec<T, N> v;
        for (size_t i = 0; i < N; i++)
            v[i] = lhs[i] * rhs;
        return v;
    }

    template<arithmetic T, size_t N>
    [[nodiscard]] vec<T, N> operator*(const T lhs, const vec<T, N>& rhs) noexcept
    {
        vec<T, N> v;
        for (size_t i = 0; i < N; i++)
            v[i] = lhs * rhs[i];
        return v;
    }

    template<arithmetic T, size_t N>
    [[nodiscard]] vec<T, N> operator/(const vec<T, N>& lhs, const vec<T, N>& rhs) noexcept
    {
        vec<T, N> v;
        for (size_t i = 0; i < N; i++)
            v[i] = lhs[i] / rhs[i];
        return v;
    }

    template<arithmetic T, size_t N>
    [[nodiscard]] vec<T, N> operator/(const vec<T, N>& lhs, const T rhs) noexcept
    {
        vec<T, N> v;
        for (size_t i = 0; i < N; i++)
            v[i] = lhs[i] / rhs;
        return v;
    }

    template<arithmetic T, size_t N>
    [[nodiscard]] vec<T, N> operator/(const T lhs, const vec<T, N>& rhs) noexcept
    {
        vec<T, N> v;
        for (size_t i = 0; i < N; i++)
            v[i] = lhs / rhs[i];
        return v;
    }

    template<arithmetic T, size_t N>
    vec<T, N>& operator+=(vec<T, N>& lhs, const vec<T, N>& rhs) noexcept { return lhs = lhs + rhs; }

    template<arithmetic T, size_t N>
    vec<T, N>& operator+=(vec<T, N>& lhs, const T rhs) noexcept { return lhs = lhs + rhs; }

    template<arithmetic T, size_t N>
    vec<T, N>& operator-=(vec<T, N>& lhs, const vec<T, N>& rhs) noexcept { return lhs = lhs - rhs; }

    template<arithmetic T, size_t N>
    vec<T, N>& operator-=(vec<T, N>& lhs, const T rhs) noexcept { return lhs = lhs - rhs; }

    template<arithmetic T, size_t N>
    vec<T, N>& operator*=(vec<T, N>& lhs, const vec<T, N>& rhs) noexcept { return lhs = lhs * rhs; }

    template<arithmetic T, size_t N>
    vec<T, N>& operator*=(vec<T, N>& lhs, const T rhs) noexcept { return lhs = lhs * rhs; }

    template<arithmetic T, size_t N>
    vec<T, N>& operator/=(vec<T, N>& lhs, const vec<T, N>& rhs) noexcept { return lhs = lhs / rhs; }

    template<arithmetic T, size_t N>
    vec<T, N>& operator/=(vec<T, N>& lhs, const T rhs) noexcept { return lhs = lhs / rhs; }

    ////////////////////////////////////////////////////////////////
    // Comparison operators.
    ////////////////////////////////////////////////////////////////

    template<std::equality_comparable T, size_t N>
    [[nodiscard]] bool operator==(const vec<T, N>& lhs, const vec<T, N>& rhs) noexcept
    {
        for (size_t i = 0; i < N; i++)
            if (lhs[i] != rhs[i])
                return false;
        return true;
    }

    template<std::equality_comparable T, size_t N>
    [[nodiscard]] bool operator!=(const vec<T, N>& lhs, const vec<T, N>& rhs) noexcept
    {
        for (size_t i = 0; i < N; i++)
            if (lhs[i] == rhs[i])
                return true;
        return false;
    }

    ////////////////////////////////////////////////////////////////
    // Per-element comparisons.
    ////////////////////////////////////////////////////////////////

    template<std::totally_ordered T, size_t N>
    [[nodiscard]] vec<bool, N> cmpeq(const vec<T, N>& lhs, const vec<T, N>& rhs) noexcept
    {
        vec<bool, N> b;
        for (size_t i = 0; i < N; i++)
            b[i] = lhs[i] == rhs[i];
        return b;
    }

    template<std::totally_ordered T, size_t N>
    [[nodiscard]] vec<bool, N> cmpeq(const vec<T, N>& lhs, const T rhs) noexcept
    {
        vec<bool, N> b;
        for (size_t i = 0; i < N; i++)
            b[i] = lhs[i] == rhs;
        return b;
    }

    template<std::totally_ordered T, size_t N>
    [[nodiscard]] vec<bool, N> cmpeq(const T lhs, const vec<T, N>& rhs) noexcept
    {
        vec<bool, N> b;
        for (size_t i = 0; i < N; i++)
            b[i] = lhs == rhs[i];
        return b;
    }

    template<std::totally_ordered T, size_t N>
    [[nodiscard]] vec<bool, N> cmpneq(const vec<T, N>& lhs, const vec<T, N>& rhs) noexcept
    {
        vec<bool, N> b;
        for (size_t i = 0; i < N; i++)
            b[i] = lhs[i] != rhs[i];
        return b;
    }

    template<std::totally_ordered T, size_t N>
    [[nodiscard]] vec<bool, N> cmpneq(const vec<T, N>& lhs, const T rhs) noexcept
    {
        vec<bool, N> b;
        for (size_t i = 0; i < N; i++)
            b[i] = lhs[i] != rhs;
        return b;
    }

    template<std::totally_ordered T, size_t N>
    [[nodiscard]] vec<bool, N> cmpneq(const T lhs, const vec<T, N>& rhs) noexcept
    {
        vec<bool, N> b;
        for (size_t i = 0; i < N; i++)
            b[i] = lhs != rhs[i];
        return b;
    }

    template<std::totally_ordered T, size_t N>
    [[nodiscard]] vec<bool, N> cmplt(const vec<T, N>& lhs, const vec<T, N>& rhs) noexcept
    {
        vec<bool, N> b;
        for (size_t i = 0; i < N; i++)
            b[i] = lhs[i] < rhs[i];
        return b;
    }

    template<std::totally_ordered T, size_t N>
    [[nodiscard]] vec<bool, N> cmplt(const vec<T, N>& lhs, const T rhs) noexcept
    {
        vec<bool, N> b;
        for (size_t i = 0; i < N; i++)
            b[i] = lhs[i] < rhs;
        return b;
    }

    template<std::totally_ordered T, size_t N>
    [[nodiscard]] vec<bool, N> cmplt(const T lhs, const vec<T, N>& rhs) noexcept
    {
        vec<bool, N> b;
        for (size_t i = 0; i < N; i++)
            b[i] = lhs < rhs[i];
        return b;
    }

    template<std::totally_ordered T, size_t N>
    [[nodiscard]] vec<bool, N> cmpgt(const vec<T, N>& lhs, const vec<T, N>& rhs) noexcept
    {
        vec<bool, N> b;
        for (size_t i = 0; i < N; i++)
            b[i] = lhs[i] > rhs[i];
        return b;
    }

    template<std::totally_ordered T, size_t N>
    [[nodiscard]] vec<bool, N> cmpgt(const vec<T, N>& lhs, const T rhs) noexcept
    {
        vec<bool, N> b;
        for (size_t i = 0; i < N; i++)
            b[i] = lhs[i] > rhs;
        return b;
    }

    template<std::totally_ordered T, size_t N>
    [[nodiscard]] vec<bool, N> cmpgt(const T lhs, const vec<T, N>& rhs) noexcept
    {
        vec<bool, N> b;
        for (size_t i = 0; i < N; i++)
            b[i] = lhs > rhs[i];
        return b;
    }

    template<std::totally_ordered T, size_t N>
    [[nodiscard]] vec<bool, N> cmple(const vec<T, N>& lhs, const vec<T, N>& rhs) noexcept
    {
        vec<bool, N> b;
        for (size_t i = 0; i < N; i++)
            b[i] = lhs[i] <= rhs[i];
        return b;
    }

    template<std::totally_ordered T, size_t N>
    [[nodiscard]] vec<bool, N> cmple(const vec<T, N>& lhs, const T rhs) noexcept
    {
        vec<bool, N> b;
        for (size_t i = 0; i < N; i++)
            b[i] = lhs[i] <= rhs;
        return b;
    }

    template<std::totally_ordered T, size_t N>
    [[nodiscard]] vec<bool, N> cmple(const T lhs, const vec<T, N>& rhs) noexcept
    {
        vec<bool, N> b;
        for (size_t i = 0; i < N; i++)
            b[i] = lhs <= rhs[i];
        return b;
    }

    template<std::totally_ordered T, size_t N>
    [[nodiscard]] vec<bool, N> cmpge(const vec<T, N>& lhs, const vec<T, N>& rhs) noexcept
    {
        vec<bool, N> b;
        for (size_t i = 0; i < N; i++)
            b[i] = lhs[i] >= rhs[i];
        return b;
    }

    template<std::totally_ordered T, size_t N>
    [[nodiscard]] vec<bool, N> cmpge(const vec<T, N>& lhs, const T rhs) noexcept
    {
        vec<bool, N> b;
        for (size_t i = 0; i < N; i++)
            b[i] = lhs[i] >= rhs;
        return b;
    }

    template<std::totally_ordered T, size_t N>
    [[nodiscard]] vec<bool, N> cmpge(const T lhs, const vec<T, N>& rhs) noexcept
    {
        vec<bool, N> b;
        for (size_t i = 0; i < N; i++)
            b[i] = lhs >= rhs[i];
        return b;
    }

    ////////////////////////////////////////////////////////////////
    // Min/max and clamp.
    ////////////////////////////////////////////////////////////////

    template<has_min T, size_t N>
    [[nodiscard]] vec<T, N> min(const vec<T, N>& lhs, const vec<T, N>& rhs) noexcept
    {
        vec<T, N> v;
        for (size_t i = 0; i < N; i++)
            v[i] = min(lhs[i], rhs[i]);
        return v;
    }

    template<has_min T, size_t N>
    [[nodiscard]] vec<T, N> min(const vec<T, N>& lhs, const T rhs) noexcept
    {
        vec<T, N> v;
        for (size_t i = 0; i < N; i++)
            v[i] = min(lhs[i], rhs);
        return v;
    }

    template<has_min T, size_t N>
    [[nodiscard]] vec<T, N> min(const T lhs, const vec<T, N>& rhs) noexcept
    {
        vec<T, N> v;
        for (size_t i = 0; i < N; i++)
            v[i] = min(lhs, rhs[i]);
        return v;
    }

    template<has_max T, size_t N>
    [[nodiscard]] vec<T, N> max(const vec<T, N>& lhs, const vec<T, N>& rhs) noexcept
    {
        vec<T, N> v;
        for (size_t i = 0; i < N; i++)
            v[i] = max(lhs[i], rhs[i]);
        return v;
    }

    template<has_max T, size_t N>
    [[nodiscard]] vec<T, N> max(const vec<T, N>& lhs, const T rhs) noexcept
    {
        vec<T, N> v;
        for (size_t i = 0; i < N; i++)
            v[i] = max(lhs[i], rhs);
        return v;
    }

    template<has_max T, size_t N>
    [[nodiscard]] vec<T, N> max(const T lhs, const vec<T, N>& rhs) noexcept
    {
        vec<T, N> v;
        for (size_t i = 0; i < N; i++)
            v[i] = max(lhs, rhs[i]);
        return v;
    }

    template<has_clamp T, size_t N>
    [[nodiscard]] vec<T, N> clamp(const vec<T, N>& a, const vec<T, N>& b, const vec<T, N>& c) noexcept
    {
        vec<T, N> v;
        for (size_t i = 0; i < N; i++)
            v[i] = clamp(a[i], b[i], c[i]);
        return v;
    }

    template<has_clamp T, size_t N>
    [[nodiscard]] vec<T, N> clamp(const vec<T, N>& a, const vec<T, N>& b, const T c) noexcept
    {
        vec<T, N> v;
        for (size_t i = 0; i < N; i++)
            v[i] = clamp(a[i], b[i], c);
        return v;
    }

    template<has_clamp T, size_t N>
    [[nodiscard]] vec<T, N> clamp(const vec<T, N>& a, const T b, const vec<T, N>& c) noexcept
    {
        vec<T, N> v;
        for (size_t i = 0; i < N; i++)
            v[i] = clamp(a[i], b, c[i]);
        return v;
    }

    template<has_clamp T, size_t N>
    [[nodiscard]] vec<T, N> clamp(const vec<T, N>& a, const T b, const T c) noexcept
    {
        vec<T, N> v;
        for (size_t i = 0; i < N; i++)
            v[i] = clamp(a[i], b, c);
        return v;
    }

    ////////////////////////////////////////////////////////////////
    // Reduction.
    ////////////////////////////////////////////////////////////////

    template<arithmetic T, size_t N>
    [[nodiscard]] T reduce_add(const vec<T, N>& lhs) noexcept
    {
        T s = lhs[0];
        for (size_t i = 1; i < N; i++)
            s += lhs[i];
        return s;
    }

    template<arithmetic T, size_t N>
    [[nodiscard]] T reduce_mul(const vec<T, N>& lhs) noexcept
    {
        T s = lhs[0];
        for (size_t i = 1; i < N; i++)
            s *= lhs[i];
        return s;
    }

    template<arithmetic T, size_t N>
    [[nodiscard]] T reduce_min(const vec<T, N>& lhs) noexcept
    {
        T s = lhs[0];
        for (size_t i = 1; i < N; i++)
            s = min(s, lhs[i]);
        return s;
    }

    template<arithmetic T, size_t N>
    [[nodiscard]] T reduce_max(const vec<T, N>& lhs) noexcept
    {
        T s = lhs[0];
        for (size_t i = 1; i < N; i++)
            s = max(s, lhs[i]);
        return s;
    }

    ////////////////////////////////////////////////////////////////
    // Dot product etc.
    ////////////////////////////////////////////////////////////////

    template<arithmetic T, size_t N>
    [[nodiscard]] T dot(const vec<T, N>& lhs, const vec<T, N>& rhs) noexcept
    {
        T s(0);
        for (size_t i = 0; i < N; i++)
            s += lhs[i] * rhs[i];
        return s;
    }

    template<std::floating_point T, size_t N>
    [[nodiscard]] T length(const vec<T, N>& lhs) noexcept { return sqrt(dot(lhs, lhs)); }

    template<std::floating_point T, size_t N>
    [[nodiscard]] T sqr_length(const vec<T, N>& lhs) noexcept { return dot(lhs, lhs); }

    template<std::floating_point T, size_t N>
    [[nodiscard]] T rcp_length(const vec<T, N>& lhs) noexcept { return rsqrt(dot(lhs, lhs)); }

    template<std::floating_point T, size_t N>
    [[nodiscard]] vec<T, N> normalize(const vec<T, N>& lhs) noexcept { return lhs * rcp_length(lhs); }

    template<std::floating_point T, size_t N>
    [[nodiscard]] vec<T, N> normalize(const vec<T, N>& lhs, T& length) noexcept { length = math::length(lhs); return lhs * (T(1) / length); }

    template<std::floating_point T, size_t N>
    [[nodiscard]] T distance(const vec<T, N>& lhs, const vec<T, N>& rhs) noexcept { return length(lhs - rhs); }

    template<arithmetic T, size_t N>
    [[nodiscard]] vec<T, N> lerp(const vec<T, N>& a, const vec<T, N>& b, const vec<T, N>& t) noexcept
    {
        vec<T, N> v;
        for (size_t i = 0; i < N; i++)
            v[i] = lerp(a[i], b[i], t[i]);
        return v;
    }

    template<arithmetic T, size_t N>
    [[nodiscard]] vec<T, N> lerp(const vec<T, N>& a, const vec<T, N>& b, const T t) noexcept
    {
        vec<T, N> v;
        for (size_t i = 0; i < N; i++)
            v[i] = lerp( a[i], b[i], t);
        return v;
    }

    ////////////////////////////////////////////////////////////////
    // Trigonometry.
    ////////////////////////////////////////////////////////////////

    template<std::floating_point T, size_t N>
    [[nodiscard]] vec<T, N> acos(const vec<T, N>& lhs) noexcept
    {
        vec<T, N> v;
        for (size_t i = 0; i < N; i++)
            v[i] = acos(lhs[i]);
        return v;
    }

    template<std::floating_point T, size_t N>
    [[nodiscard]] vec<T, N> asin(const vec<T, N>& lhs) noexcept
    {
        vec<T, N> v;
        for (size_t i = 0; i < N; i++)
            v[i] = asin(lhs[i]);
        return v;
    }

    template<std::floating_point T, size_t N>
    [[nodiscard]] vec<T, N> atan(const vec<T, N>& lhs) noexcept
    {
        vec<T, N> v;
        for (size_t i = 0; i < N; i++)
            v[i] = atan(lhs[i]);
        return v;
    }

    template<std::floating_point T, size_t N>
    [[nodiscard]] vec<T, N> atan2(const vec<T, N>& lhs, const vec<T, N>& rhs) noexcept
    {
        vec<T, N> v;
        for (size_t i = 0; i < N; i++)
            v[i] = atan2(lhs[i], rhs[i]);
        return v;
    }

    template<std::floating_point T, size_t N>
    [[nodiscard]] vec<T, N> cos(const vec<T, N>& lhs) noexcept
    {
        vec<T, N> v;
        for (size_t i = 0; i < N; i++)
            v[i] = cos(lhs[i]);
        return v;
    }

    template<std::floating_point T, size_t N>
    [[nodiscard]] vec<T, N> cosh(const vec<T, N>& lhs) noexcept
    {
        vec<T, N> v;
        for (size_t i = 0; i < N; i++)
            v[i] = cosh(lhs[i]);
        return v;
    }

    template<std::floating_point T, size_t N>
    [[nodiscard]] vec<T, N> sin(const vec<T, N>& lhs) noexcept
    {
        vec<T, N> v;
        for (size_t i = 0; i < N; i++)
            v[i] = sin(lhs[i]);
        return v;
    }

    template<std::floating_point T, size_t N>
    [[nodiscard]] vec<T, N> sinh(const vec<T, N>& lhs) noexcept
    {
        vec<T, N> v;
        for (size_t i = 0; i < N; i++)
            v[i] = sinh(lhs[i]);
        return v;
    }

    template<std::floating_point T, size_t N>
    [[nodiscard]] vec<T, N> tan(const vec<T, N>& lhs) noexcept
    {
        vec<T, N> v;
        for (size_t i = 0; i < N; i++)
            v[i] = tan(lhs[i]);
        return v;
    }

    template<std::floating_point T, size_t N>
    [[nodiscard]] vec<T, N> tanh(const vec<T, N>& lhs) noexcept
    {
        vec<T, N> v;
        for (size_t i = 0; i < N; i++)
            v[i] = tanh(lhs[i]);
        return v;
    }

    ////////////////////////////////////////////////////////////////
    // Exponential / Logarithmic.
    ////////////////////////////////////////////////////////////////

    template<std::floating_point T, size_t N>
    [[nodiscard]] vec<T, N> exp(const vec<T, N>& lhs) noexcept
    {
        vec<T, N> v;
        for (size_t i = 0; i < N; i++)
            v[i] = exp(lhs[i]);
        return v;
    }

    template<std::floating_point T, size_t N>
    [[nodiscard]] vec<T, N> exp2(const vec<T, N>& lhs) noexcept
    {
        vec<T, N> v;
        for (size_t i = 0; i < N; i++)
            v[i] = exp2(lhs[i]);
        return v;
    }

    template<std::floating_point T, size_t N>
    [[nodiscard]] vec<T, N> log(const vec<T, N>& lhs) noexcept
    {
        vec<T, N> v;
        for (size_t i = 0; i < N; i++)
            v[i] = log(lhs[i]);
        return v;
    }

    template<std::floating_point T, size_t N>
    [[nodiscard]] vec<T, N> log2(const vec<T, N>& lhs) noexcept
    {
        vec<T, N> v;
        for (size_t i = 0; i < N; i++)
            v[i] = log2(lhs[i]);
        return v;
    }

    template<std::floating_point T, size_t N>
    [[nodiscard]] vec<T, N> log10(const vec<T, N>& lhs) noexcept
    {
        vec<T, N> v;
        for (size_t i = 0; i < N; i++)
            v[i] = log10(lhs[i]);
        return v;
    }

    ////////////////////////////////////////////////////////////////
    // Power.
    ////////////////////////////////////////////////////////////////

    template<std::floating_point T, size_t N>
    [[nodiscard]] vec<T, N> pow(const vec<T, N>& lhs, const vec<T, N>& rhs) noexcept
    {
        vec<T, N> v;
        for (size_t i = 0; i < N; i++)
            v[i] = pow(lhs[i], rhs[i]);
        return v;
    }

    template<std::floating_point T, size_t N>
    [[nodiscard]] vec<T, N> sqr(const vec<T, N>& lhs) noexcept { return lhs * lhs; }

    template<std::floating_point T, size_t N>
    [[nodiscard]] vec<T, N> sqrt(const vec<T, N>& lhs) noexcept
    {
        vec<T, N> v;
        for (size_t i = 0; i < N; i++)
            v[i] = sqrt(lhs[i]);
        return v;
    }

    template<std::floating_point T, size_t N>
    [[nodiscard]] vec<T, N> rsqrt(const vec<T, N>& lhs) noexcept
    {
        vec<T, N> v;
        for (size_t i = 0; i < N; i++)
            v[i] = rsqrt(lhs[i]);
        return v;
    }

    ////////////////////////////////////////////////////////////////
    // Rounding, abs, etc.
    ////////////////////////////////////////////////////////////////
    
    template<has_abs T, size_t N>
    [[nodiscard]] vec<T, N> abs(const vec<T, N>& lhs) noexcept
    {
        vec<T, N> v;
        for (size_t i = 0; i < N; i++)
            v[i] = abs(lhs[i]);
        return v;
    }

    template<has_ceil T, size_t N>
    [[nodiscard]] vec<T, N> ceil(const vec<T, N>& lhs) noexcept
    {
        vec<T, N> v;
        for (size_t i = 0; i < N; i++)
            v[i] = ceil(lhs[i]);
        return v;
    }

    template<has_floor T, size_t N>
    [[nodiscard]] vec<T, N> floor(const vec<T, N>& lhs) noexcept
    {
        vec<T, N> v;
        for (size_t i = 0; i < N; i++)
            v[i] = floor(lhs[i]);
        return v;
    }

    template<has_frac T, size_t N>
    [[nodiscard]] vec<T, N> frac(const vec<T, N>& lhs) noexcept
    {
        vec<T, N> v;
        for (size_t i = 0; i < N; i++)
            v[i] = frac(lhs[i]);
        return v;
    }

    template<has_round T, size_t N>
    [[nodiscard]] vec<T, N> round(const vec<T, N>& lhs) noexcept
    {
        vec<T, N> v;
        for (size_t i = 0; i < N; i++)
            v[i] = round(lhs[i]);
        return v;
    }

    template<has_trunc T, size_t N>
    [[nodiscard]] vec<T, N> trunc(const vec<T, N>& lhs) noexcept
    {
        vec<T, N> v;
        for (size_t i = 0; i < N; i++)
            v[i] = trunc(lhs[i]);
        return v;
    }

    ////////////////////////////////////////////////////////////////
    // Select.
    ////////////////////////////////////////////////////////////////

    template<typename T, size_t N>
    [[nodiscard]] vec<T, N> select(const vec<T, N>& t, const vec<T, N>& f, const vec<bool, N>& b) noexcept
    {
        vec<T, N> v;
        for (size_t i = 0; i < N; i++)
            v[i] = select(t[i], f[i], b[i]);
        return v;
    }

    ////////////////////////////////////////////////////////////////
    // Multiply and add.
    ////////////////////////////////////////////////////////////////

    template<arithmetic T, size_t N>
    [[nodiscard]] vec<T, N> madd(const vec<T, N>& a, const vec<T, N>& b, const vec<T, N>& c) noexcept
    {
        vec<T, N> v;
        for (size_t i = 0; i < N; i++)
            v[i] = madd(a[i], b[i], c[i]);
        return v;
    }

    template<arithmetic T, size_t N>
    [[nodiscard]] vec<T, N> nmadd(const vec<T, N>& a, const vec<T, N>& b, const vec<T, N>& c) noexcept
    {
        vec<T, N> v;
        for (size_t i = 0; i < N; i++)
            v[i] = nmadd(a[i], b[i], c[i]);
        return v;
    }

    template<arithmetic T, size_t N>
    [[nodiscard]] vec<T, N> msub(const vec<T, N>& a, const vec<T, N>& b, const vec<T, N>& c) noexcept
    {
        vec<T, N> v;
        for (size_t i = 0; i < N; i++)
            v[i] = msub(a[i], b[i], c[i]);
        return v;
    }

    template<arithmetic T, size_t N>
    [[nodiscard]] vec<T, N> nmsub(const vec<T, N>& a, const vec<T, N>& b, const vec<T, N>& c) noexcept
    {
        vec<T, N> v;
        for (size_t i = 0; i < N; i++)
            v[i] = nmsub(a[i], b[i], c[i]);
        return v;
    }

    ////////////////////////////////////////////////////////////////
    // Shift operators.
    ////////////////////////////////////////////////////////////////

    template<std::integral T, std::integral U, size_t N>
    [[nodiscard]] vec<T, N> operator<<(const vec<T, N>& lhs, const vec<U, N>& rhs) noexcept
    {
        vec<T, N> v;
        for (size_t i = 0; i < N; i++)
            v[i] = lhs[i] << rhs[i];
        return v;
    }

    template<std::integral T, std::integral U, size_t N>
    [[nodiscard]] vec<T, N> operator<<(const vec<T, N>& lhs, const U rhs) noexcept
    {
        vec<T, N> v;
        for (size_t i = 0; i < N; i++)
            v[i] = lhs[i] << rhs;
        return v;
    }

    template<std::integral T, std::integral U, size_t N>
    [[nodiscard]] vec<T, N> operator<<(const T lhs, const vec<U, N>& rhs) noexcept
    {
        vec<T, N> v;
        for (size_t i = 0; i < N; i++)
            v[i] = lhs << rhs[i];
        return v;
    }

    template<std::integral T, std::integral U, size_t N>
    [[nodiscard]] vec<T, N> operator>>(const vec<T, N>& lhs, const vec<U, N>& rhs) noexcept
    {
        vec<T, N> v;
        for (size_t i = 0; i < N; i++)
            v[i] = lhs[i] >> rhs[i];
        return v;
    }

    template<std::integral T, std::integral U, size_t N>
    [[nodiscard]] vec<T, N> operator>>(const vec<T, N>& lhs, const U rhs) noexcept
    {
        vec<T, N> v;
        for (size_t i = 0; i < N; i++)
            v[i] = lhs[i] >> rhs;
        return v;
    }

    template<std::integral T, std::integral U, size_t N>
    [[nodiscard]] vec<T, N> operator>>(const T lhs, const vec<U, N>& rhs) noexcept
    {
        vec<T, N> v;
        for (size_t i = 0; i < N; i++)
            v[i] = lhs >> rhs[i];
        return v;
    }

    template<std::integral T, std::integral U, size_t N>
    [[nodiscard]] vec<T, N>& operator<<=(vec<T, N>& lhs, const vec<U, N>& rhs) noexcept { return lhs = lhs << rhs; }

    template<std::integral T, std::integral U, size_t N>
    [[nodiscard]] vec<T, N>& operator<<=(vec<T, N>& lhs, const U rhs) noexcept { return lhs = lhs << rhs; }

    template<std::integral T, std::integral U, size_t N>
    [[nodiscard]] vec<T, N>& operator>>=(vec<T, N>& lhs, const vec<U, N>& rhs) noexcept { return lhs = lhs >> rhs; }

    template<std::integral T, std::integral U, size_t N>
    [[nodiscard]] vec<T, N>& operator>>=(vec<T, N>& lhs, const U rhs) noexcept { return lhs = lhs >> rhs; }

    ////////////////////////////////////////////////////////////////
    // Bitwise operators.
    ////////////////////////////////////////////////////////////////

    template<std::integral T, size_t N>
    [[nodiscard]] vec<T, N> operator|(const vec<T, N>& lhs, const vec<T, N>& rhs) noexcept
    {
        vec<T, N> v;
        for (size_t i = 0; i < N; i++)
            v[i] = lhs[i] | rhs[i];
        return v;
    }

    template<std::integral T, size_t N>
    [[nodiscard]] vec<T, N> operator|(const vec<T, N>& lhs, const T rhs) noexcept
    {
        vec<T, N> v;
        for (size_t i = 0; i < N; i++)
            v[i] = lhs[i] | rhs;
        return v;
    }

    template<std::integral T, size_t N>
    [[nodiscard]] vec<T, N> operator|(const T lhs, const vec<T, N>& rhs) noexcept
    {
        vec<T, N> v;
        for (size_t i = 0; i < N; i++)
            v[i] = lhs | rhs[i];
        return v;
    }

    template<std::integral T, size_t N>
    [[nodiscard]] vec<T, N> operator&(const vec<T, N>& lhs, const vec<T, N>& rhs) noexcept
    {
        vec<T, N> v;
        for (size_t i = 0; i < N; i++)
            v[i] = lhs[i] & rhs[i];
        return v;
    }

    template<std::integral T, size_t N>
    [[nodiscard]] vec<T, N> operator&(const vec<T, N>& lhs, const T rhs) noexcept
    {
        vec<T, N> v;
        for (size_t i = 0; i < N; i++)
            v[i] = lhs[i] & rhs;
        return v;
    }

    template<std::integral T, size_t N>
    [[nodiscard]] vec<T, N> operator&(const T lhs, const vec<T, N>& rhs) noexcept
    {
        vec<T, N> v;
        for (size_t i = 0; i < N; i++)
            v[i] = lhs & rhs[i];
        return v;
    }

    template<std::integral T, size_t N>
    [[nodiscard]] vec<T, N> operator^(const vec<T, N>& lhs, const vec<T, N>& rhs) noexcept
    {
        vec<T, N> v;
        for (size_t i = 0; i < N; i++)
            v[i] = lhs[i] ^ rhs[i];
        return v;
    }

    template<std::integral T, size_t N>
    [[nodiscard]] vec<T, N> operator^(const vec<T, N>& lhs, const T rhs) noexcept
    {
        vec<T, N> v;
        for (size_t i = 0; i < N; i++)
            v[i] = lhs[i] ^ rhs;
        return v;
    }
    
    template<std::integral T, size_t N>
    [[nodiscard]] vec<T, N> operator^(const T lhs, const vec<T, N>& rhs) noexcept
    {
        vec<T, N> v;
        for (size_t i = 0; i < N; i++)
            v[i] = lhs ^ rhs[i];
        return v;
    }

    template<std::integral T, size_t N>
    [[nodiscard]] vec<T, N> operator~(const vec<T, N>& lhs) noexcept
    {
        vec<T, N> v;
        for (size_t i = 0; i < N; i++)
            v[i] = ~lhs[i];
        return v;
    }

    template<std::integral T, size_t N>
    [[nodiscard]] vec<T, N>& operator|=(vec<T, N>& lhs, const vec<T, N>& rhs) noexcept { return lhs = lhs | rhs; }

    template<std::integral T, size_t N>
    [[nodiscard]] vec<T, N>& operator|=(vec<T, N>& lhs, const T rhs) noexcept { return lhs = lhs | rhs; }

    template<std::integral T, size_t N>
    [[nodiscard]] vec<T, N>& operator&=(vec<T, N>& lhs, const vec<T, N>& rhs) noexcept { return lhs = lhs & rhs; }

    template<std::integral T, size_t N>
    [[nodiscard]] vec<T, N>& operator&=(vec<T, N>& lhs, const T rhs) noexcept { return lhs = lhs & rhs; }

    template<std::integral T, size_t N>
    [[nodiscard]] vec<T, N>& operator^=(vec<T, N>& lhs, const vec<T, N>& rhs) noexcept { return lhs = lhs ^ rhs; }

    template<std::integral T, size_t N>
    [[nodiscard]] vec<T, N>& operator^=(vec<T, N>& lhs, const T rhs) noexcept { return lhs = lhs ^ rhs; }

    ////////////////////////////////////////////////////////////////
    // Boolean vector reduction.
    ////////////////////////////////////////////////////////////////

    template<size_t N>
    [[nodiscard]] bool all(const vec<bool, N>& lhs) noexcept
    {
        for (size_t i = 0; i < N; i++)
            if (!lhs[i])
                return false;
        return true;
    }

    template<size_t N>
    [[nodiscard]] bool any(const vec<bool, N>& lhs) noexcept
    {
        for (size_t i = 0; i < N; i++)
            if (lhs[i])
                return true;
        return false;
    }

    template<size_t N>
    [[nodiscard]] bool none(const vec<bool, N>& lhs) noexcept { return !any(lhs); }

    ////////////////////////////////////////////////////////////////
    // Output.
    ////////////////////////////////////////////////////////////////

    template<typename T, size_t N>
    std::ostream& operator<<(std::ostream& out, const vec<T, N>& v)
    {
        out << "(" << v[0];
        for (size_t i = 1; i < N; i++)
            out << ", " << v[i];
        return out << ")";
    }
}
