#pragma once

////////////////////////////////////////////////////////////////
// Standard includes.
////////////////////////////////////////////////////////////////

#include <concepts>
#include <type_traits>

////////////////////////////////////////////////////////////////
// Current target includes.
////////////////////////////////////////////////////////////////

#include "math/math_type_traits.h"
#include "math/vector/vector.h"

namespace math
{
    ////////////////////////////////////////////////////////////////
    // is_floating_point
    ////////////////////////////////////////////////////////////////

    template<typename T>
    inline constexpr bool is_floating_point_vector_v = is_floating_point_v<typename T::element_type>;

    template<typename T>
    concept floating_point_vector = is_floating_point_vector_v<T>;

    ////////////////////////////////////////////////////////////////
    // is_integral
    ////////////////////////////////////////////////////////////////

    template<typename T>
    inline constexpr bool is_integral_vector_v = is_integral_v<typename T::element_type>;

    template<typename T>
    concept integral_vector = is_integral_vector_v<T>;

    ////////////////////////////////////////////////////////////////
    // is_signed
    ////////////////////////////////////////////////////////////////

    template<typename T>
    inline constexpr bool is_signed_vector_v = is_signed_v<typename T::element_type>;

    template<typename T>
    concept signed_vector = is_signed_vector_v<T>;

    ////////////////////////////////////////////////////////////////
    // is_unsigned
    ////////////////////////////////////////////////////////////////

    template<typename T>
    inline constexpr bool is_unsigned_vector_v = is_unsigned_v<typename T::element_type>;

    template<typename T>
    concept unsigned_vector = is_unsigned_vector_v<T>;

    ////////////////////////////////////////////////////////////////
    // is_signed_integral
    ////////////////////////////////////////////////////////////////

    template<typename T>
    inline constexpr bool is_signed_integral_vector_v = is_signed_integral_v<typename T::element_type>;

    template<typename T>
    concept signed_integral_vector = is_signed_integral_vector_v<T>;

    ////////////////////////////////////////////////////////////////
    // is_unsigned_integral
    ////////////////////////////////////////////////////////////////

    template<typename T>
    inline constexpr bool is_unsigned_integral_vector_v = is_unsigned_integral_v<typename T::element_type>;

    template<typename T>
    concept unsigned_integral_vector = is_unsigned_integral_vector_v<T>;

    ////////////////////////////////////////////////////////////////
    // make_signed
    ////////////////////////////////////////////////////////////////
    
    template<typename T>
    struct make_signed_vector
    {
        using type = vec<make_signed_t<typename T::element_type>, T::size>;
    };

    template<typename T>
    using make_signed_vector_t = typename make_signed_vector<T>::type;

    ////////////////////////////////////////////////////////////////
    // make_unsigned
    ////////////////////////////////////////////////////////////////

    template<typename T>
    struct make_unsigned_vector
    {
        using type = vec<make_unsigned_t<typename T::element_type>, T::size>;
    };

    template<typename T>
    using make_unsigned_vector_t = typename make_unsigned_vector<T>::type;

    ////////////////////////////////////////////////////////////////
    // make_different_size
    ////////////////////////////////////////////////////////////////

    template<typename T, size_t N>
    struct make_different_size_vector
    {
        using type = vec<typename T::element_type, N>;
    };

    template<typename T, size_t N>
    using make_different_size_vector_t = typename make_different_size_vector<T, N>::type;

    ////////////////////////////////////////////////////////////////
    // is_same
    ////////////////////////////////////////////////////////////////

    template<typename T, typename U>
    concept is_same_element_vector = std::is_same_v<typename T::element_type, typename U::element_type>;

    template<typename T, typename U>
    concept is_same_size_vector = T::size == U::size;

    template<typename T, typename U>
    concept is_same_vector = is_same_element_vector<T, U> && is_same_size_vector<T, U>;
}