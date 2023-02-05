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

#include "math/vector/vec3.h"

namespace math
{
    struct alignas(16) vec3ba
    {
        static constexpr size_t size = 3;
        using element_type = int32_t;

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4201)
#endif
        union
        {
            __m128i m128;
            struct
            {
                int32_t x, y, z, w;
            };
        };
#ifdef _MSC_VER
#pragma warning(pop)
#endif

        ////////////////////////////////////////////////////////////////
        // Constructors.
        ////////////////////////////////////////////////////////////////

        [[nodiscard]] vec3ba() noexcept : m128(_mm_set1_epi32(0)) {}

        [[nodiscard]] explicit vec3ba(const bool b) noexcept : m128(_mm_set1_epi32(0 - static_cast<int32_t>(b))) {}

        [[nodiscard]] vec3ba(const bool x, const bool y, const bool z) noexcept : m128(_mm_setr_epi32(0 - static_cast<int32_t>(x), 0 - static_cast<int32_t>(y), 0 - static_cast<int32_t>(z), 0)) {}

        [[nodiscard]] vec3ba(const bool x, const bool y, const bool z, const bool w) noexcept : m128(_mm_setr_epi32(0 - static_cast<int32_t>(x), 0 - static_cast<int32_t>(y), 0 - static_cast<int32_t>(z), 0 - static_cast<int32_t>(w))) {}

        [[nodiscard]] vec3ba(const __m128i m128) noexcept : m128(m128) {}

        [[nodiscard]] explicit vec3ba(const __m128 m128) noexcept : m128(_mm_castps_si128(m128)) {}

        [[nodiscard]] vec3ba(const vec3ba& rhs) noexcept : m128(rhs.m128) {}

        [[nodiscard]] explicit vec3ba(const vec<bool, 3>& rhs) noexcept : m128(_mm_setr_epi32(0 - static_cast<int32_t>(rhs.x), 0 - static_cast<int32_t>(rhs.y), 0 - static_cast<int32_t>(rhs.z), 0)) {}

        ////////////////////////////////////////////////////////////////
        // Assignment operators.
        ////////////////////////////////////////////////////////////////

        vec3ba& operator=(const vec3ba& rhs) noexcept { m128 = rhs.m128; return *this; }

        vec3ba& operator=(const bool rhs) noexcept { m128 = _mm_set1_epi32(0 - static_cast<int32_t>(rhs)); return *this; }

        ////////////////////////////////////////////////////////////////
        // Defaulted constructors and operators.
        ////////////////////////////////////////////////////////////////

        ~vec3ba() noexcept = default;

        vec3ba(vec3ba&& rhs) noexcept = default;

        vec3ba& operator=(vec3ba&& rhs) noexcept = default;

        ////////////////////////////////////////////////////////////////
        // Casting operators.
        ////////////////////////////////////////////////////////////////

        [[nodiscard]] operator const __m128i&() const noexcept { return m128; }

        [[nodiscard]] operator __m128i&() noexcept { return m128; }
        
        [[nodiscard]] explicit operator __m128() const noexcept { return _mm_castsi128_ps(m128); }

        [[nodiscard]] explicit operator vec<int32_t, 3>() const noexcept { return vec<int32_t, 3>(x, y, z); }

        ////////////////////////////////////////////////////////////////
        // Element access.
        ////////////////////////////////////////////////////////////////

        [[nodiscard]] bool operator[](const size_t i) const { assert(i < 3); return static_cast<bool>((_mm_movemask_ps(_mm_castsi128_ps(m128)) >> i) & 0x1); }

        //[[nodiscard]] const int32_t& operator[](const size_t i) const { assert(i < 3); return (&x)[i]; }

        [[nodiscard]] int32_t& operator[](const size_t i) { assert(i < 3); return (&x)[i]; }

        ////////////////////////////////////////////////////////////////
        // Swizzling.
        ////////////////////////////////////////////////////////////////

#ifdef __AVX__
        [[nodiscard]] vec3ba xxx() const noexcept { return vec3ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 0, 0, 0))); }
        [[nodiscard]] vec3ba xxy() const noexcept { return vec3ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 1, 0, 0))); }
        [[nodiscard]] vec3ba xxz() const noexcept { return vec3ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 2, 0, 0))); }
        [[nodiscard]] vec3ba xyx() const noexcept { return vec3ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 0, 1, 0))); }
        [[nodiscard]] vec3ba xyy() const noexcept { return vec3ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 1, 1, 0))); }
        [[nodiscard]] vec3ba xyz() const noexcept { return vec3ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 2, 1, 0))); }
        [[nodiscard]] vec3ba xzx() const noexcept { return vec3ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 0, 2, 0))); }
        [[nodiscard]] vec3ba xzy() const noexcept { return vec3ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 1, 2, 0))); }
        [[nodiscard]] vec3ba xzz() const noexcept { return vec3ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 2, 2, 0))); }
        [[nodiscard]] vec3ba yxx() const noexcept { return vec3ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 0, 0, 1))); }
        [[nodiscard]] vec3ba yxy() const noexcept { return vec3ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 1, 0, 1))); }
        [[nodiscard]] vec3ba yxz() const noexcept { return vec3ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 2, 0, 1))); }
        [[nodiscard]] vec3ba yyx() const noexcept { return vec3ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 0, 1, 1))); }
        [[nodiscard]] vec3ba yyy() const noexcept { return vec3ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 1, 1, 1))); }
        [[nodiscard]] vec3ba yyz() const noexcept { return vec3ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 2, 1, 1))); }
        [[nodiscard]] vec3ba yzx() const noexcept { return vec3ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 0, 2, 1))); }
        [[nodiscard]] vec3ba yzy() const noexcept { return vec3ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 1, 2, 1))); }
        [[nodiscard]] vec3ba yzz() const noexcept { return vec3ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 2, 2, 1))); }
        [[nodiscard]] vec3ba zxx() const noexcept { return vec3ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 0, 0, 2))); }
        [[nodiscard]] vec3ba zxy() const noexcept { return vec3ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 1, 0, 2))); }
        [[nodiscard]] vec3ba zxz() const noexcept { return vec3ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 2, 0, 2))); }
        [[nodiscard]] vec3ba zyx() const noexcept { return vec3ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 0, 1, 2))); }
        [[nodiscard]] vec3ba zyy() const noexcept { return vec3ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 1, 1, 2))); }
        [[nodiscard]] vec3ba zyz() const noexcept { return vec3ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 2, 1, 2))); }
        [[nodiscard]] vec3ba zzx() const noexcept { return vec3ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 0, 2, 2))); }
        [[nodiscard]] vec3ba zzy() const noexcept { return vec3ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 1, 2, 2))); }
        [[nodiscard]] vec3ba zzz() const noexcept { return vec3ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 2, 2, 2))); }
#endif
    };

    ////////////////////////////////////////////////////////////////
    // Shuffle.
    ////////////////////////////////////////////////////////////////

#ifdef __AVX__
    template<int32_t i0, int32_t i1, int32_t i2>
    [[nodiscard]] vec3ba shuffle(const vec3ba& v) noexcept { return vec3ba(_mm_permute_ps(_mm_castsi128_ps(v), _MM_SHUFFLE(0, i2, i1, i0))); }
#endif

    ////////////////////////////////////////////////////////////////
    // Bitwise operators.
    ////////////////////////////////////////////////////////////////

    [[nodiscard]] inline vec3ba operator!(const vec3ba& lhs) noexcept { return _mm_xor_si128(lhs, one<vec3ba>()); }

    [[nodiscard]] inline vec3ba operator&(const vec3ba& lhs, const vec3ba& rhs) noexcept { return _mm_and_si128(lhs, rhs); }

    [[nodiscard]] inline vec3ba operator|(const vec3ba& lhs, const vec3ba& rhs) noexcept { return _mm_or_si128(lhs, rhs); }

    [[nodiscard]] inline vec3ba operator^(const vec3ba& lhs, const vec3ba& rhs) noexcept { return _mm_xor_si128(lhs, rhs); }

    inline vec3ba& operator&=(vec3ba& lhs, const vec3ba& rhs) noexcept { return lhs = lhs & rhs; }

    inline vec3ba& operator|=(vec3ba& lhs, const vec3ba& rhs) noexcept { return lhs = lhs | rhs; }

    inline vec3ba& operator^=(vec3ba& lhs, const vec3ba& rhs) noexcept { return lhs = lhs ^ rhs; }

    ////////////////////////////////////////////////////////////////
    // Comparison operators.
    ////////////////////////////////////////////////////////////////

    [[nodiscard]] inline bool operator==(const vec3ba& lhs, const vec3ba& rhs) noexcept { return (_mm_movemask_ps(_mm_castsi128_ps(_mm_cmpeq_epi32(lhs, rhs))) & 0x7) == 0x7; }

    [[nodiscard]] inline bool operator!=(const vec3ba& lhs, const vec3ba& rhs) noexcept { return (_mm_movemask_ps(_mm_castsi128_ps(_mm_cmpeq_epi32(lhs, rhs))) & 0x7) != 0x7; }

    ////////////////////////////////////////////////////////////////
    // Per-element comparisons.
    ////////////////////////////////////////////////////////////////
    
    [[nodiscard]] inline vec3ba cmpeq(const vec3ba& lhs, const vec3ba& rhs) noexcept { return _mm_cmpeq_epi32(lhs, rhs); }

    [[nodiscard]] inline vec3ba cmpneq(const vec3ba& lhs, const vec3ba& rhs) noexcept { return !cmpeq(lhs, rhs); }

    ////////////////////////////////////////////////////////////////
    // Select.
    ////////////////////////////////////////////////////////////////

    [[nodiscard]] inline vec3ba select(const vec3ba& t, const vec3ba& f, const vec3ba& b) noexcept
    {
#ifdef __SSE4_1__
        return vec3ba(_mm_blendv_ps(_mm_castsi128_ps(f), _mm_castsi128_ps(t), _mm_castsi128_ps(b)));
#else
        return vec3ba(math::select(t.x, f.x, b.x & 0x80000000), math::select(t.y, f.y, b.y & 0x80000000), math::select(t.z, f.z, b.z & 0x80000000));
#endif
    }

    ////////////////////////////////////////////////////////////////
    // Boolean vector reduction.
    ////////////////////////////////////////////////////////////////

    [[nodiscard]] inline bool all(const vec3ba& lhs) noexcept { return (_mm_movemask_ps(_mm_castsi128_ps(lhs)) & 0x7) == 0x7; }

    [[nodiscard]] inline bool any(const vec3ba& lhs) noexcept { return (_mm_movemask_ps(_mm_castsi128_ps(lhs)) & 0x7) != 0x0; }

    [[nodiscard]] inline bool none(const vec3ba& lhs) noexcept { return (_mm_movemask_ps(_mm_castsi128_ps(lhs)) & 0x7) == 0x0; }

    ////////////////////////////////////////////////////////////////
    // Output.
    ////////////////////////////////////////////////////////////////

    inline std::ostream& operator<<(std::ostream& out, const vec3ba& v) { return out << "(" << (v.x ? true : false) << ", " << (v.y ? true : false) << ", " << (v.z ? true : false) << ")"; }

}
