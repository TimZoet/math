#pragma once

////////////////////////////////////////////////////////////////
// Standard includes.
////////////////////////////////////////////////////////////////

#include <cassert>
#include <iostream>

////////////////////////////////////////////////////////////////
// Current target includes.
////////////////////////////////////////////////////////////////

#include "math/math_type_traits.h"
#include "math/vector/vector.h"
#include "math/vector/vector_type_traits.h"

namespace math
{
    template<typename T>
    struct AABB
    {
        static constexpr size_t size = T::size;
        using element_type = T;

        /** @brief    Lower bounds. */
        T lower;

        /** @brief    Upper bounds. */
        T upper;

        ////////////////////////////////////////////////////////////////
        // Constructors.
        ////////////////////////////////////////////////////////////////

        [[nodiscard]] AABB() noexcept : lower(), upper() {};

        [[nodiscard]] AABB(const T& lower, const T& upper) noexcept : lower(lower), upper(upper) {}

        [[nodiscard]] AABB(const AABB<T>& rhs) noexcept : lower(rhs.lower), upper(rhs.upper) {}

        template<is_same_size_vector<T> U>
        [[nodiscard]] explicit AABB(const AABB<U>& rhs) noexcept : lower(static_cast<T>(rhs.lower)), upper(static_cast<T>(rhs.upper)) {}

        ////////////////////////////////////////////////////////////////
        // Assignment operators.
        ////////////////////////////////////////////////////////////////

        AABB<T>& operator=(const AABB<T>& rhs) noexcept { lower = rhs.lower; upper = rhs.upper; return *this; }

        template<is_same_size_vector<T> U>
        AABB<T>& operator=(const AABB<U>& rhs) noexcept { lower = static_cast<T>(rhs.lower); upper = static_cast<T>(rhs.upper); return *this; }

        ////////////////////////////////////////////////////////////////
        // Defaulted constructors and operators.
        ////////////////////////////////////////////////////////////////

        ~AABB() noexcept = default;

        AABB(AABB<T>&& rhs) noexcept = default;

        AABB<T>& operator=(AABB<T>&& rhs) noexcept = default;

        ////////////////////////////////////////////////////////////////
        // Element access.
        ////////////////////////////////////////////////////////////////

        [[nodiscard]] const T& operator[](const size_t i) const { assert(i < 2); return (&lower)[i]; }

        [[nodiscard]] T& operator[](const size_t i) { assert(i < 2); return (&lower)[i]; }
    };

    ////////////////////////////////////////////////////////////////
    // Construct special values.
    ////////////////////////////////////////////////////////////////

    template<is_aabb T>
    [[nodiscard]] T infinite() noexcept { return T(pos_infinity<T::element_type>(), neg_infinity<T::element_type>()); }

    template<is_aabb T>
    [[nodiscard]] T zero() noexcept { return T(T::element_type(0), T::element_type(0)); }

    template<is_aabb T>
    [[nodiscard]] T one() noexcept { return T(T::element_type(0), T::element_type(1)); }

    ////////////////////////////////////////////////////////////////
    // Check for special values.
    ////////////////////////////////////////////////////////////////

    template<is_aabb T>
    [[nodiscard]] bool is_valid(const AABB<T>& lhs) noexcept { return all(cmple(lhs.lower, lhs.upper)); }

    template<is_aabb T>
    [[nodiscard]] bool is_finite(const AABB<T>& lhs) noexcept { return none(is_infinite(lhs.lower)) & none(is_infinite(lhs.upper)); }

    template<is_aabb T>
    [[nodiscard]] bool is_infinite(const AABB<T>& lhs) noexcept { return all(is_pos_infinite(lhs.lower)) & all(is_neg_infinite(lhs.upper)); }

    ////////////////////////////////////////////////////////////////
    // Basic operators.
    ////////////////////////////////////////////////////////////////

    template<typename T>
    [[nodiscard]] AABB<T> operator+(const AABB<T>& lhs, const AABB<T>& rhs) noexcept { return AABB<T>(min(lhs.lower, rhs.lower), max(lhs.upper, rhs.upper)); }

    template<typename T>
    AABB<T>& operator+=(AABB<T>& lhs, const AABB<T>& rhs) noexcept { return lhs = lhs + rhs;; }

    ////////////////////////////////////////////////////////////////
    // Comparison operators.
    ////////////////////////////////////////////////////////////////

    template<typename T>
    [[nodiscard]] bool operator==(const AABB<T>& lhs, const AABB<T>& rhs) noexcept { return lhs.lower == rhs.lower && lhs.upper == rhs.upper; }

    template<typename T>
    [[nodiscard]] bool operator!=(const AABB<T>& lhs, const AABB<T>& rhs) noexcept { return !(lhs == rhs); }

    ////////////////////////////////////////////////////////////////
    // Center, clamp, distance etc.
    ////////////////////////////////////////////////////////////////

    template<typename T>
    [[nodiscard]] T center(const AABB<T>& lhs) noexcept { return (lhs.lower + lhs.upper) * T::element_type(0.5); }

    template<typename T>
    [[nodiscard]] AABB<T> clamp(const AABB<T>& lhs, const AABB<T>& rhs) noexcept { return AABB<T>(clamp(lhs.lower, rhs.lower, rhs.upper), clamp(lhs.upper, rhs.lower, rhs.upper)); }

    template<typename T>
    [[nodiscard]] T clamp(const AABB<T>& aabb, T& v) noexcept { return clamp(v, aabb.lower, aabb.upper); }

    template<typename T>
    [[nodiscard]] T clamp(T& v, const AABB<T>& aabb) noexcept { return clamp(aabb, v); }

    template<typename T>
    [[nodiscard]] T distance(const AABB<T>& aabb, const T& v) noexcept { return length(max(max(aabb.lower - v, v - aabb.upper, T::element_type(0)))); }

    template<typename T>
    [[nodiscard]] T distance(const T& v, const AABB<T>& aabb) noexcept { return distance(aabb, v); }

    template<typename T>
    [[nodiscard]] T sqr_distance(const AABB<T>& aabb, const T& v) noexcept { return sqr_length(max(max(aabb.lower - v, v - aabb.upper, T::element_type(0)))); }

    template<typename T>
    [[nodiscard]] T sqr_distance(const T& v, const AABB<T>& aabb) noexcept { return sqr_distance(aabb, v); }

    template<typename T>
    [[nodiscard]] bool inside(const AABB<T>& inner, const AABB<T>& outer)
    {
        return all(cmpge(inner.lower, outer.lower)) && all(cmple(inner.upper, outer.upper));
    }
    
    template<typename T>
    [[nodiscard]] bool inside(const T& v, const AABB<T>& aabb)
    {
        return all(cmpge(v, aabb.lower)) && all(cmplt(v, aabb.upper));
    }

    ////////////////////////////////////////////////////////////////
    // Output.
    ////////////////////////////////////////////////////////////////

    template<typename T>
    std::ostream& operator<<(std::ostream& out, const AABB<T>& aabb)
    {
        return out << "[" << aabb.lower << ", " << aabb.upper << "]";
    }
}
