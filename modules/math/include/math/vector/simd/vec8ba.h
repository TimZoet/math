#pragma once

////////////////////////////////////////////////////////////////
// Standard includes.
////////////////////////////////////////////////////////////////

#include <cassert>
#include <immintrin.h>
#include <iostream>

////////////////////////////////////////////////////////////////
// Current target includes.
////////////////////////////////////////////////////////////////

#include "math/vector/vector.h"

namespace math
{
#ifdef __AVX__
    struct alignas(32) vec8ba
    {
        static constexpr size_t size = 8;
        using element_type = int32_t;

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4201)
#endif
        union
        {
            __m256i m256;
            float floats[8];
            int32_t ints[8];
        };
#ifdef _MSC_VER
#pragma warning(pop)
#endif

        ////////////////////////////////////////////////////////////////
        // Constructors.
        ////////////////////////////////////////////////////////////////

        [[nodiscard]] vec8ba() noexcept : m256(_mm256_set1_epi32(0)) {}

        [[nodiscard]] explicit vec8ba(const bool b) noexcept : m256(_mm256_set1_epi32(0 - static_cast<int32_t>(b))) {}

        [[nodiscard]] vec8ba(const bool a, const bool b, const bool c, const bool d, const bool e, const bool f, const bool g, const bool h) noexcept : m256(_mm256_setr_epi32(0 - static_cast<int32_t>(a), 0 - static_cast<int32_t>(b), 0 - static_cast<int32_t>(c), 0 - static_cast<int32_t>(d), 0 - static_cast<int32_t>(e), 0 - static_cast<int32_t>(f), 0 - static_cast<int32_t>(g), 0 - static_cast<int32_t>(h))) {}

        [[nodiscard]] vec8ba(const __m256i m256) noexcept : m256(m256) {}

        [[nodiscard]] explicit vec8ba(const __m256 m256) noexcept : m256(_mm256_castps_si256(m256)) {}

        [[nodiscard]] vec8ba(const vec8ba & rhs) noexcept : m256(rhs.m256) {}

        [[nodiscard]] explicit vec8ba(const vec<bool, 8>& rhs) noexcept : m256(_mm256_setr_epi32(0 - static_cast<int32_t>(rhs[0]), 0 - static_cast<int32_t>(rhs[1]), 0 - static_cast<int32_t>(rhs[2]), 0 - static_cast<int32_t>(rhs[3]), 0 - static_cast<int32_t>(rhs[4]), 0 - static_cast<int32_t>(rhs[5]), 0 - static_cast<int32_t>(rhs[6]), 0 - static_cast<int32_t>(rhs[7]))) {}

        ////////////////////////////////////////////////////////////////
        // Assignment operators.
        ////////////////////////////////////////////////////////////////

        vec8ba& operator=(const vec8ba& rhs) noexcept { m256 = rhs.m256; return *this; }

        vec8ba& operator=(const bool rhs) noexcept { m256 = _mm256_set1_epi32(0 - static_cast<int32_t>(rhs)); return *this; }

        ////////////////////////////////////////////////////////////////
        // Defaulted constructors and operators.
        ////////////////////////////////////////////////////////////////

        ~vec8ba() noexcept = default;

        vec8ba(vec8ba&& rhs) noexcept = default;

        vec8ba& operator=(vec8ba&& rhs) noexcept = default;

        ////////////////////////////////////////////////////////////////
        // Casting operators.
        ////////////////////////////////////////////////////////////////

        [[nodiscard]] operator const __m256i& () const noexcept { return m256; }

        [[nodiscard]] operator __m256i& () noexcept { return m256; }
        
        [[nodiscard]] explicit operator __m256 () const noexcept { return _mm256_castsi256_ps(m256); }

        [[nodiscard]] explicit operator vec<int32_t, 8>() const noexcept { return vec<int32_t, 8>(ints[0], ints[1], ints[2], ints[3], ints[4], ints[5], ints[6], ints[7]); }

        ////////////////////////////////////////////////////////////////
        // Element access.
        ////////////////////////////////////////////////////////////////

        [[nodiscard]] bool operator[](const size_t i) const { assert(i < 8); return static_cast<bool>((_mm256_movemask_ps(_mm256_castsi256_ps(m256)) >> i) & 0x1); }

        [[nodiscard]] int32_t& operator[](const size_t i) { assert(i < 8); return ints[i]; }
    };

    ////////////////////////////////////////////////////////////////
    // Bitwise operators.
    ////////////////////////////////////////////////////////////////

#ifdef __AVX2__
    [[nodiscard]] inline vec8ba operator!(const vec8ba& lhs) noexcept { return _mm256_xor_si256(lhs, one<vec8ba>()); }

    [[nodiscard]] inline vec8ba operator&(const vec8ba& lhs, const vec8ba& rhs) noexcept { return _mm256_and_si256(lhs, rhs); }

    [[nodiscard]] inline vec8ba operator|(const vec8ba& lhs, const vec8ba& rhs) noexcept { return _mm256_or_si256(lhs, rhs); }

    [[nodiscard]] inline vec8ba operator^(const vec8ba& lhs, const vec8ba& rhs) noexcept { return _mm256_xor_si256(lhs, rhs); }

    inline vec8ba& operator&=(vec8ba& lhs, const vec8ba& rhs) noexcept { return lhs = lhs & rhs; }

    inline vec8ba& operator|=(vec8ba& lhs, const vec8ba& rhs) noexcept { return lhs = lhs | rhs; }

    inline vec8ba& operator^=(vec8ba& lhs, const vec8ba& rhs) noexcept { return lhs = lhs ^ rhs; }
#endif

    ////////////////////////////////////////////////////////////////
    // Comparison operators.
    ////////////////////////////////////////////////////////////////

#ifdef __AVX2__
    [[nodiscard]] inline bool operator==(const vec8ba& lhs, const vec8ba& rhs) noexcept { return (_mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(lhs, rhs))) & 0x31) == 0x31; }

    [[nodiscard]] inline bool operator!=(const vec8ba& lhs, const vec8ba& rhs) noexcept { return (_mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(lhs, rhs))) & 0x31) != 0x31; }
#endif

    ////////////////////////////////////////////////////////////////
    // Per-element comparisons.
    ////////////////////////////////////////////////////////////////

#ifdef __AVX2__
    [[nodiscard]] inline vec8ba cmpeq(const vec8ba& lhs, const vec8ba& rhs) noexcept { return _mm256_cmpeq_epi32(lhs, rhs); }

    [[nodiscard]] inline vec8ba cmpneq(const vec8ba& lhs, const vec8ba& rhs) noexcept { return !cmpeq(lhs, rhs); }
#endif

    ////////////////////////////////////////////////////////////////
    // Select.
    ////////////////////////////////////////////////////////////////

    [[nodiscard]] inline vec8ba select(const vec8ba& t, const vec8ba& f, const vec8ba& b) noexcept { return vec8ba(_mm256_blendv_ps(_mm256_castsi256_ps(f), _mm256_castsi256_ps(t), _mm256_castsi256_ps(b))); }

    ////////////////////////////////////////////////////////////////
    // Boolean vector reduction.
    ////////////////////////////////////////////////////////////////

    [[nodiscard]] inline bool all(const vec8ba& lhs) noexcept { return (_mm256_movemask_ps(_mm256_castsi256_ps(lhs)) & 0x31) == 0x31; }

    [[nodiscard]] inline bool any(const vec8ba& lhs) noexcept { return (_mm256_movemask_ps(_mm256_castsi256_ps(lhs)) & 0x31) != 0x0; }

    [[nodiscard]] inline bool none(const vec8ba& lhs) noexcept { return (_mm256_movemask_ps(_mm256_castsi256_ps(lhs)) & 0x31) == 0x0; }

    ////////////////////////////////////////////////////////////////
    // Output.
    ////////////////////////////////////////////////////////////////

    inline std::ostream& operator<<(std::ostream& out, const vec8ba& v) { return out << "(" << (v[0] ? true : false) << ", " << (v[1] ? true : false) << ", " << (v[2] ? true : false) << ", " << (v[3] ? true : false) << ", " << (v[4] ? true : false) << ", " << (v[5] ? true : false) << ", " << (v[6] ? true : false) << ", " << (v[7] ? true : false) << ")"; }
#endif
}
