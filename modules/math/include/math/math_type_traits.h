#pragma once

////////////////////////////////////////////////////////////////
// Standard includes.
////////////////////////////////////////////////////////////////

#include <type_traits>

namespace math
{
    template<typename T>
    concept arithmetic = std::is_arithmetic_v<T>;

    template<typename T>
    concept less_than_comparable = requires (T x)
    {
        { x < x } -> std::same_as<bool>;
    };

    ////////////////////////////////////////////////////////////////
    // constructible
    ////////////////////////////////////////////////////////////////

    template<typename T>
    concept element_type_constructible = requires
    {
        { T(typename T::element_type()) };
    };

    template<typename T>
    concept element_type_pair_constructible = requires
    {
        { T(typename T::element_type(), typename T::element_type()) };
    };

    ////////////////////////////////////////////////////////////////
    // is_class
    ////////////////////////////////////////////////////////////////

    /*template<typename T>
    concept is_vector = requires (T x)
    {
        typename T::element_type;
        { T::size } -> std::same_as<size_t>;
        { x[std::declval<size_t>()]} -> std::same_as<typename T::element_type>;
    };*/

    template<typename T>
    concept is_aabb = element_type_pair_constructible<T> && requires (T aabb)
    {
        //{ T::size } -> std::same_as<size_t>;
        { aabb.lower } -> std::same_as<typename T::element_type>;
        { aabb.upper } -> std::same_as<typename T::element_type>;
    };

    /*is_matrix*/

    template<typename T>
    concept is_square_matrix = std::is_same_v<typename T::row_type, typename T::column_type>;

    template<typename T, size_t N>
    concept is_size = N == T::size;

    ////////////////////////////////////////////////////////////////
    // is_floating_point
    ////////////////////////////////////////////////////////////////

    template<typename T>
    struct _is_floating_point : std::false_type {};

    // This is what the overload for float16 would look like.
    /*template<>
    struct _is_floating_point<float16> : std::true_type {};*/

    template<typename T>
    inline constexpr bool _is_floating_point_v = _is_floating_point<T>::value;

    template<typename T>
    inline constexpr bool is_floating_point_v = _is_floating_point_v<T> || std::is_floating_point_v<T>;

    template<typename T>
    concept floating_point = is_floating_point_v<T>;

    ////////////////////////////////////////////////////////////////
    // is_integral
    ////////////////////////////////////////////////////////////////

    template<typename T>
    struct _is_integral : std::false_type {};

    template<typename T>
    inline constexpr bool _is_integral_v = _is_integral<T>::value;

    template<typename T>
    inline constexpr bool is_integral_v = _is_integral_v<T> || std::is_integral_v<T>;

    template<typename T>
    concept integral = is_integral_v<T>;

    ////////////////////////////////////////////////////////////////
    // is_signed
    ////////////////////////////////////////////////////////////////

    template<typename T>
    struct _is_signed : std::false_type {};

    template<typename T>
    inline constexpr bool _is_signed_v = _is_signed<T>::value;

    template<typename T>
    inline constexpr bool is_signed_v = _is_signed_v<T> || std::is_signed_v<T>;

    ////////////////////////////////////////////////////////////////
    // is_unsigned
    ////////////////////////////////////////////////////////////////

    template<typename T>
    struct _is_unsigned : std::false_type {};

    template<typename T>
    inline constexpr bool _is_unsigned_v = _is_unsigned<T>::value;

    template<typename T>
    inline constexpr bool is_unsigned_v = _is_unsigned_v<T> || std::is_unsigned_v<T>;

    ////////////////////////////////////////////////////////////////
    // is_signed_integral
    ////////////////////////////////////////////////////////////////

    template<typename T>
    inline constexpr bool _is_signed_integral_v = is_integral_v<T> && is_signed_v<T>;

    template<typename T>
    inline constexpr bool is_signed_integral_v = _is_signed_integral_v<T> || (std::is_integral_v<T> && std::is_signed_v<T>);

    template<typename T>
    concept signed_integral = is_signed_integral_v<T>;

    ////////////////////////////////////////////////////////////////
    // is_unsigned_integral
    ////////////////////////////////////////////////////////////////

    template<typename T>
    inline constexpr bool _is_unsigned_integral_v = is_integral_v<T> && is_unsigned_v<T>;

    template<typename T>
    inline constexpr bool is_unsigned_integral_v = _is_unsigned_integral_v<T> || (std::is_integral_v<T> && std::is_unsigned_v<T>);

    template<typename T>
    concept unsigned_integral = is_unsigned_integral_v<T>;

    ////////////////////////////////////////////////////////////////
    // make_signed
    ////////////////////////////////////////////////////////////////

    template<typename T, typename U = void>
    struct make_signed;

    // This is what the overload for uint128 would look like.
    /*template<>
    struct make_signed<uint128>
    {
        using type = int128;
    };*/

    template<typename T>
    struct make_signed<T, void>
    {
        using type = std::make_signed_t<T>;
    };

    template<typename T>
    using make_signed_t = typename make_signed<T>::type;

    ////////////////////////////////////////////////////////////////
    // make_unsigned
    ////////////////////////////////////////////////////////////////

    template<typename T, typename U = void>
    struct make_unsigned;

    template<typename T>
    struct make_unsigned<T, void>
    {
        using type = std::make_unsigned_t<T>;
    };

    template<typename T>
    using make_unsigned_t = typename make_unsigned<T>::type;
}
