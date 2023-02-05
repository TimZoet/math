#pragma once

////////////////////////////////////////////////////////////////
// Standard includes.
////////////////////////////////////////////////////////////////

#include <algorithm>
#include <cmath>

////////////////////////////////////////////////////////////////
// Current target includes.
////////////////////////////////////////////////////////////////

#include "math/math_type_traits.h"

namespace math
{   
    ////////////////////////////////////////////////////////////////
    // Trigonometry.
    ////////////////////////////////////////////////////////////////

    template<std::floating_point T>
    [[nodiscard]] T acos(const T x) noexcept { return std::acos(x); }

    template<std::floating_point T>
    [[nodiscard]] T asin(const T x) noexcept { return std::asin(x); }

    template<std::floating_point T>
    [[nodiscard]] T atan(const T x) noexcept { return std::atan(x); }

    template<std::floating_point T>
    [[nodiscard]] T atan2(const T y, const T x) noexcept { return std::atan2(y, x); }

    template<std::floating_point T>
    [[nodiscard]] T cos(const T x) noexcept { return std::cos(x); }

    template<std::floating_point T>
    [[nodiscard]] T cosh(const T x) noexcept { return std::cosh(x); }

    template<std::floating_point T>
    [[nodiscard]] T sin(const T x) noexcept { return std::sin(x); }

    template<std::floating_point T>
    [[nodiscard]] T sinh(const T x) noexcept { return std::sinh(x); }

    template<std::floating_point T>
    [[nodiscard]] T tan(const T x) noexcept { return std::tan(x); }

    template<std::floating_point T>
    [[nodiscard]] T tanh(const T x) noexcept { return std::tanh(x); }

    ////////////////////////////////////////////////////////////////
    // Rounding, abs, etc.
    ////////////////////////////////////////////////////////////////

    template<typename T> requires (std::floating_point<T> || std::signed_integral<T>)
    [[nodiscard]] T abs(const T x) noexcept { return std::abs(x); }

    template<std::floating_point T>
    [[nodiscard]] T ceil(const T x) noexcept { return std::ceil(x); }

    template<std::floating_point T>
    [[nodiscard]] T floor(const T x) noexcept { return std::floor(x); }

    template<std::floating_point T>
    [[nodiscard]] T fmod(const T x, const T y) noexcept { return std::fmod(x, y); }

    template<std::floating_point T>
    [[nodiscard]] T frac(const T x) noexcept { T y; return std::modf(x, &y); }

    template<std::floating_point T>
    [[nodiscard]] T round(const T x) noexcept { return std::nearbyint(x); }

    template<std::floating_point T>
    [[nodiscard]] T trunc(const T x) noexcept { return std::trunc(x); }

    template<typename T>
    concept has_abs = requires (T x)
    {
        { math::abs(x) } -> std::same_as<T>;
    };

    template<typename T>
    concept has_round = requires (T x)
    {
        { math::round(x) } -> std::same_as<T>;
    };

    template<typename T>
    concept has_ceil = requires (T x)
    {
        { math::ceil(x) } -> std::same_as<T>;
    };

    template<typename T>
    concept has_floor = requires (T x)
    {
        { math::floor(x) } -> std::same_as<T>;
    };

    template<typename T>
    concept has_frac = requires (T x)
    {
        { math::frac(x) } -> std::same_as<T>;
    };

    template<typename T>
    concept has_trunc = requires (T x)
    {
        { math::trunc(x) } -> std::same_as<T>;
    };

    ////////////////////////////////////////////////////////////////
    // Exponential / Logarithmic.
    ////////////////////////////////////////////////////////////////

    template<std::floating_point T>
    [[nodiscard]] T exp(const T x) noexcept { return std::exp(x); }

    template<std::floating_point T>
    [[nodiscard]] T exp2(const T x) noexcept { return std::exp2(x); }

    template<std::floating_point T>
    [[nodiscard]] T log(const T x) noexcept { return std::log(x); }

    template<std::floating_point T>
    [[nodiscard]] T log2(const T x) noexcept { return std::log2(x); }

    template<std::floating_point T>
    [[nodiscard]] T log10(const T x) noexcept { return std::log10(x); }

    ////////////////////////////////////////////////////////////////
    // Power.
    ////////////////////////////////////////////////////////////////

    template<std::floating_point T>
    [[nodiscard]] T pow(const T x, const T y) noexcept { return std::pow(x, y); }

    template<arithmetic T>
    [[nodiscard]] T sqr(const T x) noexcept { return x * x; }

    template<std::floating_point T>
    [[nodiscard]] T sqrt(const T x) noexcept { return std::sqrt(x); }

    template<std::floating_point T>
    [[nodiscard]] T rsqrt(const T x) noexcept { return T(1) / sqrt(x); }

    ////////////////////////////////////////////////////////////////
    // Min / Max / Clamp.
    ////////////////////////////////////////////////////////////////

    template<std::floating_point T>
    [[nodiscard]] T min(const T a, const T b) noexcept { return std::fmin(a, b); }

    template<typename T> requires (less_than_comparable<T> && !std::floating_point<T>)
    [[nodiscard]] T min(const T a, const T b) noexcept { return std::min(a, b); }

    template<std::floating_point T>
    [[nodiscard]] T max(const T a, const T b) noexcept { return std::fmax(a, b); }

    template<typename T> requires (less_than_comparable<T> && !std::floating_point<T>)
    [[nodiscard]] T max(const T a, const T b) noexcept { return std::max(a, b); }

    template<std::floating_point T>
    [[nodiscard]] T clamp(const T a, const T lo, const T hi) noexcept { return min(max(a, lo), hi); }

    template<typename T> requires (less_than_comparable<T> && !std::floating_point<T>)
    [[nodiscard]] T clamp(const T a, const T lo, const T hi) noexcept { return std::clamp(a, lo, hi); }

    template<typename T>
    concept has_min = requires (T x)
    {
        { math::min(x, x) } -> std::same_as<T>;
    };

    template<typename T>
    concept has_max = requires (T x)
    {
        { math::max(x, x) } -> std::same_as<T>;
    };

    template<typename T>
    concept has_clamp = requires (T x)
    {
        { math::clamp(x, x, x) } -> std::same_as<T>;
    };

    template<has_min T, has_min ... Ts>
    [[nodiscard]] T min(const T a, const T b, const Ts... cs) noexcept { return min(min(a, b), cs...); }

    template<has_max T, has_max ... Ts>
    [[nodiscard]] T max(const T a, const T b, const Ts... cs) noexcept { return max(max(a, b), cs...); }

    ////////////////////////////////////////////////////////////////
    // Select.
    ////////////////////////////////////////////////////////////////

    template<typename T>
    [[nodiscard]] T select(const T t, const T f, const bool b) noexcept { return b ? t : f; }

    ////////////////////////////////////////////////////////////////
    // Multiply and add.
    ////////////////////////////////////////////////////////////////

    template<arithmetic T>
    [[nodiscard]] T madd(const T a, const T b, const T c) noexcept { return a * b + c; }

    template<arithmetic T>
    [[nodiscard]] T nmadd(const T a, const T b, const T c) noexcept { return -a * b + c; }

    template<arithmetic T>
    [[nodiscard]] T msub(const T a, const T b, const T c) noexcept { return a * b - c; }

    template<arithmetic T>
    [[nodiscard]] T nmsub(const T a, const T b, const T c) noexcept { return -a * b - c; }

    ////////////////////////////////////////////////////////////////
    // Other.
    ////////////////////////////////////////////////////////////////
    
    [[nodiscard]] inline float lerp(const float a, const float b, const float t) noexcept { return madd(t, b - a, a); }

    [[nodiscard]] inline double lerp(const double a, const double b, const double t) noexcept { return madd(t, b - a, a); }

    template<typename A, typename B, typename T, typename R = A> requires (arithmetic<T> && arithmetic<A> && arithmetic<B> && std::convertible_to<double, R>)
    [[nodiscard]] R lerp(const A a, const B b, const T t) noexcept { return static_cast<R>(std::lerp(a, b, t)); }

    [[nodiscard]] inline float rcp(const float x) noexcept { return 1.0f / x; }

    [[nodiscard]] inline double rcp(const double x) noexcept { return 1.0 / x; }

    template <typename T> requires (arithmetic<T> && less_than_comparable<T>)
    [[nodiscard]] int32_t sign(const T x) noexcept { const T zero = T(0); return (zero < x) - (x < zero); }
}