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

#include "math/vector/vec4.h"

namespace math
{
    struct alignas(16) vec4ba
    {
        static constexpr size_t size = 4;
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

        [[nodiscard]] vec4ba() noexcept : m128(_mm_set1_epi32(0)) {}

        [[nodiscard]] explicit vec4ba(const bool b) noexcept : m128(_mm_set1_epi32(0 - static_cast<int32_t>(b))) {}

        [[nodiscard]] vec4ba(const bool x, const bool y, const bool z, const bool w) noexcept : m128(_mm_setr_epi32(0 - static_cast<int32_t>(x), 0 - static_cast<int32_t>(y), 0 - static_cast<int32_t>(z), 0 - static_cast<int32_t>(w))) {}

        [[nodiscard]] vec4ba(const __m128i m128) noexcept : m128(m128) {}

        [[nodiscard]] explicit vec4ba(const __m128 m128) noexcept : m128(_mm_castps_si128(m128)) {}

        [[nodiscard]] vec4ba(const vec4ba& rhs) noexcept : m128(rhs.m128) {}

        [[nodiscard]] explicit vec4ba(const vec<bool, 4>& rhs) noexcept : m128(_mm_setr_epi32(0 - static_cast<int32_t>(rhs.x), 0 - static_cast<int32_t>(rhs.y), 0 - static_cast<int32_t>(rhs.z), 0 - static_cast<int32_t>(rhs.w))) {}

        ////////////////////////////////////////////////////////////////
        // Assignment operators.
        ////////////////////////////////////////////////////////////////
        
        vec4ba& operator=(const vec4ba& rhs) noexcept { m128 = rhs.m128; return *this; }

        vec4ba& operator=(const bool rhs) noexcept { m128 = _mm_set1_epi32(0 - static_cast<int32_t>(rhs)); return *this; }

        ////////////////////////////////////////////////////////////////
        // Defaulted constructors and operators.
        ////////////////////////////////////////////////////////////////

        ~vec4ba() noexcept = default;

        vec4ba(vec4ba&& rhs) noexcept = default;

        vec4ba& operator=(vec4ba&& rhs) noexcept = default;

        ////////////////////////////////////////////////////////////////
        // Casting operators.
        ////////////////////////////////////////////////////////////////

        [[nodiscard]] operator const __m128i&() const noexcept { return m128; }

        [[nodiscard]] operator __m128i&() noexcept { return m128; }

        [[nodiscard]] explicit operator __m128 () const noexcept { return _mm_castsi128_ps(m128); }

        [[nodiscard]] explicit operator vec<int32_t, 4>() const noexcept { return vec<int32_t, 4>(x, y, z, w); }

        ////////////////////////////////////////////////////////////////
        // Element access.
        ////////////////////////////////////////////////////////////////

        [[nodiscard]] bool operator[](const size_t i) const { assert(i < 4); return static_cast<bool>((_mm_movemask_ps(_mm_castsi128_ps(m128)) >> i) & 0x1); }

        [[nodiscard]] int32_t& operator[](const size_t i) { assert(i < 4); return (&x)[i]; }

        ////////////////////////////////////////////////////////////////
        // Swizzling.
        ////////////////////////////////////////////////////////////////

#ifdef __AVX__
        [[nodiscard]] vec4ba xxx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 0, 0, 0))); }
        [[nodiscard]] vec4ba xxy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 1, 0, 0))); }
        [[nodiscard]] vec4ba xxz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 2, 0, 0))); }
        [[nodiscard]] vec4ba xyx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 0, 1, 0))); }
        [[nodiscard]] vec4ba xyy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 1, 1, 0))); }
        [[nodiscard]] vec4ba xyz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 2, 1, 0))); }
        [[nodiscard]] vec4ba xzx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 0, 2, 0))); }
        [[nodiscard]] vec4ba xzy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 1, 2, 0))); }
        [[nodiscard]] vec4ba xzz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 2, 2, 0))); }
        [[nodiscard]] vec4ba yxx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 0, 0, 1))); }
        [[nodiscard]] vec4ba yxy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 1, 0, 1))); }
        [[nodiscard]] vec4ba yxz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 2, 0, 1))); }
        [[nodiscard]] vec4ba yyx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 0, 1, 1))); }
        [[nodiscard]] vec4ba yyy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 1, 1, 1))); }
        [[nodiscard]] vec4ba yyz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 2, 1, 1))); }
        [[nodiscard]] vec4ba yzx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 0, 2, 1))); }
        [[nodiscard]] vec4ba yzy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 1, 2, 1))); }
        [[nodiscard]] vec4ba yzz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 2, 2, 1))); }
        [[nodiscard]] vec4ba zxx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 0, 0, 2))); }
        [[nodiscard]] vec4ba zxy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 1, 0, 2))); }
        [[nodiscard]] vec4ba zxz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 2, 0, 2))); }
        [[nodiscard]] vec4ba zyx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 0, 1, 2))); }
        [[nodiscard]] vec4ba zyy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 1, 1, 2))); }
        [[nodiscard]] vec4ba zyz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 2, 1, 2))); }
        [[nodiscard]] vec4ba zzx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 0, 2, 2))); }
        [[nodiscard]] vec4ba zzy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 1, 2, 2))); }
        [[nodiscard]] vec4ba zzz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 2, 2, 2))); }

        [[nodiscard]] vec4ba xxxx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 0, 0, 0))); }
        [[nodiscard]] vec4ba xxxy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 0, 0, 0))); }
        [[nodiscard]] vec4ba xxxz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 0, 0, 0))); }
        [[nodiscard]] vec4ba xxxw() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 0, 0, 0))); }
        [[nodiscard]] vec4ba xxyx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 1, 0, 0))); }
        [[nodiscard]] vec4ba xxyy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 1, 0, 0))); }
        [[nodiscard]] vec4ba xxyz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 1, 0, 0))); }
        [[nodiscard]] vec4ba xxyw() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 1, 0, 0))); }
        [[nodiscard]] vec4ba xxzx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 2, 0, 0))); }
        [[nodiscard]] vec4ba xxzy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 2, 0, 0))); }
        [[nodiscard]] vec4ba xxzz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 2, 0, 0))); }
        [[nodiscard]] vec4ba xxzw() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 2, 0, 0))); }
        [[nodiscard]] vec4ba xxwx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 3, 0, 0))); }
        [[nodiscard]] vec4ba xxwy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 3, 0, 0))); }
        [[nodiscard]] vec4ba xxwz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 3, 0, 0))); }
        [[nodiscard]] vec4ba xxww() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 3, 0, 0))); }
        [[nodiscard]] vec4ba xyxx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 0, 1, 0))); }
        [[nodiscard]] vec4ba xyxy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 0, 1, 0))); }
        [[nodiscard]] vec4ba xyxz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 0, 1, 0))); }
        [[nodiscard]] vec4ba xyxw() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 0, 1, 0))); }
        [[nodiscard]] vec4ba xyyx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 1, 1, 0))); }
        [[nodiscard]] vec4ba xyyy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 1, 1, 0))); }
        [[nodiscard]] vec4ba xyyz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 1, 1, 0))); }
        [[nodiscard]] vec4ba xyyw() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 1, 1, 0))); }
        [[nodiscard]] vec4ba xyzx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 2, 1, 0))); }
        [[nodiscard]] vec4ba xyzy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 2, 1, 0))); }
        [[nodiscard]] vec4ba xyzz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 2, 1, 0))); }
        [[nodiscard]] vec4ba xyzw() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 2, 1, 0))); }
        [[nodiscard]] vec4ba xywx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 3, 1, 0))); }
        [[nodiscard]] vec4ba xywy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 3, 1, 0))); }
        [[nodiscard]] vec4ba xywz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 3, 1, 0))); }
        [[nodiscard]] vec4ba xyww() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 3, 1, 0))); }
        [[nodiscard]] vec4ba xzxx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 0, 2, 0))); }
        [[nodiscard]] vec4ba xzxy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 0, 2, 0))); }
        [[nodiscard]] vec4ba xzxz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 0, 2, 0))); }
        [[nodiscard]] vec4ba xzxw() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 0, 2, 0))); }
        [[nodiscard]] vec4ba xzyx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 1, 2, 0))); }
        [[nodiscard]] vec4ba xzyy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 1, 2, 0))); }
        [[nodiscard]] vec4ba xzyz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 1, 2, 0))); }
        [[nodiscard]] vec4ba xzyw() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 1, 2, 0))); }
        [[nodiscard]] vec4ba xzzx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 2, 2, 0))); }
        [[nodiscard]] vec4ba xzzy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 2, 2, 0))); }
        [[nodiscard]] vec4ba xzzz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 2, 2, 0))); }
        [[nodiscard]] vec4ba xzzw() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 2, 2, 0))); }
        [[nodiscard]] vec4ba xzwx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 3, 2, 0))); }
        [[nodiscard]] vec4ba xzwy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 3, 2, 0))); }
        [[nodiscard]] vec4ba xzwz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 3, 2, 0))); }
        [[nodiscard]] vec4ba xzww() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 3, 2, 0))); }
        [[nodiscard]] vec4ba xwxx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 0, 3, 0))); }
        [[nodiscard]] vec4ba xwxy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 0, 3, 0))); }
        [[nodiscard]] vec4ba xwxz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 0, 3, 0))); }
        [[nodiscard]] vec4ba xwxw() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 0, 3, 0))); }
        [[nodiscard]] vec4ba xwyx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 1, 3, 0))); }
        [[nodiscard]] vec4ba xwyy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 1, 3, 0))); }
        [[nodiscard]] vec4ba xwyz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 1, 3, 0))); }
        [[nodiscard]] vec4ba xwyw() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 1, 3, 0))); }
        [[nodiscard]] vec4ba xwzx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 2, 3, 0))); }
        [[nodiscard]] vec4ba xwzy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 2, 3, 0))); }
        [[nodiscard]] vec4ba xwzz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 2, 3, 0))); }
        [[nodiscard]] vec4ba xwzw() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 2, 3, 0))); }
        [[nodiscard]] vec4ba xwwx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 3, 3, 0))); }
        [[nodiscard]] vec4ba xwwy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 3, 3, 0))); }
        [[nodiscard]] vec4ba xwwz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 3, 3, 0))); }
        [[nodiscard]] vec4ba xwww() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 3, 3, 0))); }
        [[nodiscard]] vec4ba yxxx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 0, 0, 1))); }
        [[nodiscard]] vec4ba yxxy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 0, 0, 1))); }
        [[nodiscard]] vec4ba yxxz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 0, 0, 1))); }
        [[nodiscard]] vec4ba yxxw() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 0, 0, 1))); }
        [[nodiscard]] vec4ba yxyx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 1, 0, 1))); }
        [[nodiscard]] vec4ba yxyy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 1, 0, 1))); }
        [[nodiscard]] vec4ba yxyz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 1, 0, 1))); }
        [[nodiscard]] vec4ba yxyw() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 1, 0, 1))); }
        [[nodiscard]] vec4ba yxzx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 2, 0, 1))); }
        [[nodiscard]] vec4ba yxzy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 2, 0, 1))); }
        [[nodiscard]] vec4ba yxzz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 2, 0, 1))); }
        [[nodiscard]] vec4ba yxzw() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 2, 0, 1))); }
        [[nodiscard]] vec4ba yxwx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 3, 0, 1))); }
        [[nodiscard]] vec4ba yxwy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 3, 0, 1))); }
        [[nodiscard]] vec4ba yxwz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 3, 0, 1))); }
        [[nodiscard]] vec4ba yxww() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 3, 0, 1))); }
        [[nodiscard]] vec4ba yyxx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 0, 1, 1))); }
        [[nodiscard]] vec4ba yyxy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 0, 1, 1))); }
        [[nodiscard]] vec4ba yyxz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 0, 1, 1))); }
        [[nodiscard]] vec4ba yyxw() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 0, 1, 1))); }
        [[nodiscard]] vec4ba yyyx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 1, 1, 1))); }
        [[nodiscard]] vec4ba yyyy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 1, 1, 1))); }
        [[nodiscard]] vec4ba yyyz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 1, 1, 1))); }
        [[nodiscard]] vec4ba yyyw() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 1, 1, 1))); }
        [[nodiscard]] vec4ba yyzx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 2, 1, 1))); }
        [[nodiscard]] vec4ba yyzy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 2, 1, 1))); }
        [[nodiscard]] vec4ba yyzz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 2, 1, 1))); }
        [[nodiscard]] vec4ba yyzw() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 2, 1, 1))); }
        [[nodiscard]] vec4ba yywx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 3, 1, 1))); }
        [[nodiscard]] vec4ba yywy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 3, 1, 1))); }
        [[nodiscard]] vec4ba yywz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 3, 1, 1))); }
        [[nodiscard]] vec4ba yyww() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 3, 1, 1))); }
        [[nodiscard]] vec4ba yzxx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 0, 2, 1))); }
        [[nodiscard]] vec4ba yzxy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 0, 2, 1))); }
        [[nodiscard]] vec4ba yzxz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 0, 2, 1))); }
        [[nodiscard]] vec4ba yzxw() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 0, 2, 1))); }
        [[nodiscard]] vec4ba yzyx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 1, 2, 1))); }
        [[nodiscard]] vec4ba yzyy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 1, 2, 1))); }
        [[nodiscard]] vec4ba yzyz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 1, 2, 1))); }
        [[nodiscard]] vec4ba yzyw() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 1, 2, 1))); }
        [[nodiscard]] vec4ba yzzx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 2, 2, 1))); }
        [[nodiscard]] vec4ba yzzy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 2, 2, 1))); }
        [[nodiscard]] vec4ba yzzz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 2, 2, 1))); }
        [[nodiscard]] vec4ba yzzw() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 2, 2, 1))); }
        [[nodiscard]] vec4ba yzwx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 3, 2, 1))); }
        [[nodiscard]] vec4ba yzwy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 3, 2, 1))); }
        [[nodiscard]] vec4ba yzwz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 3, 2, 1))); }
        [[nodiscard]] vec4ba yzww() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 3, 2, 1))); }
        [[nodiscard]] vec4ba ywxx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 0, 3, 1))); }
        [[nodiscard]] vec4ba ywxy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 0, 3, 1))); }
        [[nodiscard]] vec4ba ywxz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 0, 3, 1))); }
        [[nodiscard]] vec4ba ywxw() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 0, 3, 1))); }
        [[nodiscard]] vec4ba ywyx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 1, 3, 1))); }
        [[nodiscard]] vec4ba ywyy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 1, 3, 1))); }
        [[nodiscard]] vec4ba ywyz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 1, 3, 1))); }
        [[nodiscard]] vec4ba ywyw() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 1, 3, 1))); }
        [[nodiscard]] vec4ba ywzx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 2, 3, 1))); }
        [[nodiscard]] vec4ba ywzy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 2, 3, 1))); }
        [[nodiscard]] vec4ba ywzz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 2, 3, 1))); }
        [[nodiscard]] vec4ba ywzw() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 2, 3, 1))); }
        [[nodiscard]] vec4ba ywwx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 3, 3, 1))); }
        [[nodiscard]] vec4ba ywwy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 3, 3, 1))); }
        [[nodiscard]] vec4ba ywwz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 3, 3, 1))); }
        [[nodiscard]] vec4ba ywww() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 3, 3, 1))); }
        [[nodiscard]] vec4ba zxxx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 0, 0, 2))); }
        [[nodiscard]] vec4ba zxxy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 0, 0, 2))); }
        [[nodiscard]] vec4ba zxxz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 0, 0, 2))); }
        [[nodiscard]] vec4ba zxxw() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 0, 0, 2))); }
        [[nodiscard]] vec4ba zxyx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 1, 0, 2))); }
        [[nodiscard]] vec4ba zxyy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 1, 0, 2))); }
        [[nodiscard]] vec4ba zxyz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 1, 0, 2))); }
        [[nodiscard]] vec4ba zxyw() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 1, 0, 2))); }
        [[nodiscard]] vec4ba zxzx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 2, 0, 2))); }
        [[nodiscard]] vec4ba zxzy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 2, 0, 2))); }
        [[nodiscard]] vec4ba zxzz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 2, 0, 2))); }
        [[nodiscard]] vec4ba zxzw() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 2, 0, 2))); }
        [[nodiscard]] vec4ba zxwx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 3, 0, 2))); }
        [[nodiscard]] vec4ba zxwy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 3, 0, 2))); }
        [[nodiscard]] vec4ba zxwz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 3, 0, 2))); }
        [[nodiscard]] vec4ba zxww() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 3, 0, 2))); }
        [[nodiscard]] vec4ba zyxx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 0, 1, 2))); }
        [[nodiscard]] vec4ba zyxy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 0, 1, 2))); }
        [[nodiscard]] vec4ba zyxz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 0, 1, 2))); }
        [[nodiscard]] vec4ba zyxw() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 0, 1, 2))); }
        [[nodiscard]] vec4ba zyyx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 1, 1, 2))); }
        [[nodiscard]] vec4ba zyyy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 1, 1, 2))); }
        [[nodiscard]] vec4ba zyyz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 1, 1, 2))); }
        [[nodiscard]] vec4ba zyyw() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 1, 1, 2))); }
        [[nodiscard]] vec4ba zyzx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 2, 1, 2))); }
        [[nodiscard]] vec4ba zyzy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 2, 1, 2))); }
        [[nodiscard]] vec4ba zyzz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 2, 1, 2))); }
        [[nodiscard]] vec4ba zyzw() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 2, 1, 2))); }
        [[nodiscard]] vec4ba zywx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 3, 1, 2))); }
        [[nodiscard]] vec4ba zywy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 3, 1, 2))); }
        [[nodiscard]] vec4ba zywz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 3, 1, 2))); }
        [[nodiscard]] vec4ba zyww() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 3, 1, 2))); }
        [[nodiscard]] vec4ba zzxx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 0, 2, 2))); }
        [[nodiscard]] vec4ba zzxy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 0, 2, 2))); }
        [[nodiscard]] vec4ba zzxz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 0, 2, 2))); }
        [[nodiscard]] vec4ba zzxw() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 0, 2, 2))); }
        [[nodiscard]] vec4ba zzyx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 1, 2, 2))); }
        [[nodiscard]] vec4ba zzyy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 1, 2, 2))); }
        [[nodiscard]] vec4ba zzyz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 1, 2, 2))); }
        [[nodiscard]] vec4ba zzyw() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 1, 2, 2))); }
        [[nodiscard]] vec4ba zzzx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 2, 2, 2))); }
        [[nodiscard]] vec4ba zzzy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 2, 2, 2))); }
        [[nodiscard]] vec4ba zzzz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 2, 2, 2))); }
        [[nodiscard]] vec4ba zzzw() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 2, 2, 2))); }
        [[nodiscard]] vec4ba zzwx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 3, 2, 2))); }
        [[nodiscard]] vec4ba zzwy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 3, 2, 2))); }
        [[nodiscard]] vec4ba zzwz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 3, 2, 2))); }
        [[nodiscard]] vec4ba zzww() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 3, 2, 2))); }
        [[nodiscard]] vec4ba zwxx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 0, 3, 2))); }
        [[nodiscard]] vec4ba zwxy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 0, 3, 2))); }
        [[nodiscard]] vec4ba zwxz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 0, 3, 2))); }
        [[nodiscard]] vec4ba zwxw() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 0, 3, 2))); }
        [[nodiscard]] vec4ba zwyx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 1, 3, 2))); }
        [[nodiscard]] vec4ba zwyy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 1, 3, 2))); }
        [[nodiscard]] vec4ba zwyz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 1, 3, 2))); }
        [[nodiscard]] vec4ba zwyw() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 1, 3, 2))); }
        [[nodiscard]] vec4ba zwzx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 2, 3, 2))); }
        [[nodiscard]] vec4ba zwzy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 2, 3, 2))); }
        [[nodiscard]] vec4ba zwzz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 2, 3, 2))); }
        [[nodiscard]] vec4ba zwzw() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 2, 3, 2))); }
        [[nodiscard]] vec4ba zwwx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 3, 3, 2))); }
        [[nodiscard]] vec4ba zwwy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 3, 3, 2))); }
        [[nodiscard]] vec4ba zwwz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 3, 3, 2))); }
        [[nodiscard]] vec4ba zwww() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 3, 3, 2))); }
        [[nodiscard]] vec4ba wxxx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 0, 0, 3))); }
        [[nodiscard]] vec4ba wxxy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 0, 0, 3))); }
        [[nodiscard]] vec4ba wxxz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 0, 0, 3))); }
        [[nodiscard]] vec4ba wxxw() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 0, 0, 3))); }
        [[nodiscard]] vec4ba wxyx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 1, 0, 3))); }
        [[nodiscard]] vec4ba wxyy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 1, 0, 3))); }
        [[nodiscard]] vec4ba wxyz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 1, 0, 3))); }
        [[nodiscard]] vec4ba wxyw() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 1, 0, 3))); }
        [[nodiscard]] vec4ba wxzx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 2, 0, 3))); }
        [[nodiscard]] vec4ba wxzy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 2, 0, 3))); }
        [[nodiscard]] vec4ba wxzz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 2, 0, 3))); }
        [[nodiscard]] vec4ba wxzw() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 2, 0, 3))); }
        [[nodiscard]] vec4ba wxwx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 3, 0, 3))); }
        [[nodiscard]] vec4ba wxwy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 3, 0, 3))); }
        [[nodiscard]] vec4ba wxwz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 3, 0, 3))); }
        [[nodiscard]] vec4ba wxww() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 3, 0, 3))); }
        [[nodiscard]] vec4ba wyxx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 0, 1, 3))); }
        [[nodiscard]] vec4ba wyxy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 0, 1, 3))); }
        [[nodiscard]] vec4ba wyxz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 0, 1, 3))); }
        [[nodiscard]] vec4ba wyxw() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 0, 1, 3))); }
        [[nodiscard]] vec4ba wyyx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 1, 1, 3))); }
        [[nodiscard]] vec4ba wyyy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 1, 1, 3))); }
        [[nodiscard]] vec4ba wyyz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 1, 1, 3))); }
        [[nodiscard]] vec4ba wyyw() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 1, 1, 3))); }
        [[nodiscard]] vec4ba wyzx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 2, 1, 3))); }
        [[nodiscard]] vec4ba wyzy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 2, 1, 3))); }
        [[nodiscard]] vec4ba wyzz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 2, 1, 3))); }
        [[nodiscard]] vec4ba wyzw() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 2, 1, 3))); }
        [[nodiscard]] vec4ba wywx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 3, 1, 3))); }
        [[nodiscard]] vec4ba wywy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 3, 1, 3))); }
        [[nodiscard]] vec4ba wywz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 3, 1, 3))); }
        [[nodiscard]] vec4ba wyww() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 3, 1, 3))); }
        [[nodiscard]] vec4ba wzxx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 0, 2, 3))); }
        [[nodiscard]] vec4ba wzxy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 0, 2, 3))); }
        [[nodiscard]] vec4ba wzxz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 0, 2, 3))); }
        [[nodiscard]] vec4ba wzxw() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 0, 2, 3))); }
        [[nodiscard]] vec4ba wzyx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 1, 2, 3))); }
        [[nodiscard]] vec4ba wzyy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 1, 2, 3))); }
        [[nodiscard]] vec4ba wzyz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 1, 2, 3))); }
        [[nodiscard]] vec4ba wzyw() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 1, 2, 3))); }
        [[nodiscard]] vec4ba wzzx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 2, 2, 3))); }
        [[nodiscard]] vec4ba wzzy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 2, 2, 3))); }
        [[nodiscard]] vec4ba wzzz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 2, 2, 3))); }
        [[nodiscard]] vec4ba wzzw() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 2, 2, 3))); }
        [[nodiscard]] vec4ba wzwx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 3, 2, 3))); }
        [[nodiscard]] vec4ba wzwy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 3, 2, 3))); }
        [[nodiscard]] vec4ba wzwz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 3, 2, 3))); }
        [[nodiscard]] vec4ba wzww() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 3, 2, 3))); }
        [[nodiscard]] vec4ba wwxx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 0, 3, 3))); }
        [[nodiscard]] vec4ba wwxy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 0, 3, 3))); }
        [[nodiscard]] vec4ba wwxz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 0, 3, 3))); }
        [[nodiscard]] vec4ba wwxw() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 0, 3, 3))); }
        [[nodiscard]] vec4ba wwyx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 1, 3, 3))); }
        [[nodiscard]] vec4ba wwyy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 1, 3, 3))); }
        [[nodiscard]] vec4ba wwyz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 1, 3, 3))); }
        [[nodiscard]] vec4ba wwyw() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 1, 3, 3))); }
        [[nodiscard]] vec4ba wwzx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 2, 3, 3))); }
        [[nodiscard]] vec4ba wwzy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 2, 3, 3))); }
        [[nodiscard]] vec4ba wwzz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 2, 3, 3))); }
        [[nodiscard]] vec4ba wwzw() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 2, 3, 3))); }
        [[nodiscard]] vec4ba wwwx() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 3, 3, 3))); }
        [[nodiscard]] vec4ba wwwy() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 3, 3, 3))); }
        [[nodiscard]] vec4ba wwwz() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 3, 3, 3))); }
        [[nodiscard]] vec4ba wwww() const noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 3, 3, 3))); }
#endif
    };

    ////////////////////////////////////////////////////////////////
    // Shuffle.
    ////////////////////////////////////////////////////////////////

#ifdef __AVX__
    template<int32_t i0, int32_t i1, int32_t i2, int32_t i3>
    [[nodiscard]] vec4ba shuffle(const vec4ba& v) noexcept { return vec4ba(_mm_permute_ps(_mm_castsi128_ps(v), _MM_SHUFFLE(i3, i2, i1, i0))); }
#endif

    ////////////////////////////////////////////////////////////////
    // Bitwise operators.
    ////////////////////////////////////////////////////////////////

    [[nodiscard]] inline vec4ba operator!(const vec4ba& lhs) noexcept { return _mm_xor_si128(lhs, one<vec4ba>()); }

    [[nodiscard]] inline vec4ba operator&(const vec4ba& lhs, const vec4ba& rhs) noexcept { return _mm_and_si128(lhs, rhs); }

    [[nodiscard]] inline vec4ba operator|(const vec4ba& lhs, const vec4ba& rhs) noexcept { return _mm_or_si128(lhs, rhs); }

    [[nodiscard]] inline vec4ba operator^(const vec4ba& lhs, const vec4ba& rhs) noexcept { return _mm_xor_si128(lhs, rhs); }

    inline vec4ba& operator&=(vec4ba& lhs, const vec4ba& rhs) noexcept { return lhs = lhs & rhs; }

    inline vec4ba& operator|=(vec4ba& lhs, const vec4ba& rhs) noexcept { return lhs = lhs | rhs; }

    inline vec4ba& operator^=(vec4ba& lhs, const vec4ba& rhs) noexcept { return lhs = lhs ^ rhs; }

    ////////////////////////////////////////////////////////////////
    // Comparison operators.
    ////////////////////////////////////////////////////////////////

    [[nodiscard]] inline bool operator==(const vec4ba& lhs, const vec4ba& rhs) noexcept { return (_mm_movemask_ps(_mm_castsi128_ps(_mm_cmpeq_epi32(lhs, rhs))) & 0x15) == 0x15; }

    [[nodiscard]] inline bool operator!=(const vec4ba& lhs, const vec4ba& rhs) noexcept { return (_mm_movemask_ps(_mm_castsi128_ps(_mm_cmpeq_epi32(lhs, rhs))) & 0x15) != 0x15; }

    ////////////////////////////////////////////////////////////////
    // Per-element comparisons.
    ////////////////////////////////////////////////////////////////

    [[nodiscard]] inline vec4ba cmpeq(const vec4ba& lhs, const vec4ba& rhs) noexcept { return _mm_cmpeq_epi32(lhs, rhs); }

    [[nodiscard]] inline vec4ba cmpneq(const vec4ba& lhs, const vec4ba& rhs) noexcept { return !cmpeq(lhs, rhs); }

    ////////////////////////////////////////////////////////////////
    // Select.
    ////////////////////////////////////////////////////////////////

    [[nodiscard]] inline vec4ba select(const vec4ba& t, const vec4ba& f, const vec4ba& b) noexcept
    {
#ifdef __SSE4_1__
        return vec4ba(_mm_blendv_ps(_mm_castsi128_ps(f), _mm_castsi128_ps(t), _mm_castsi128_ps(b)));
#else
        return vec4ba(math::select(t.x, f.x, b.x & 0x80000000), math::select(t.y, f.y, b.y & 0x80000000), math::select(t.z, f.z, b.z & 0x80000000), math::select(t.w, f.w, b.w & 0x80000000));
#endif
    }

    ////////////////////////////////////////////////////////////////
    // Boolean vector reduction.
    ////////////////////////////////////////////////////////////////

    [[nodiscard]] inline bool all(const vec4ba& lhs) noexcept { return (_mm_movemask_ps(_mm_castsi128_ps(lhs)) & 0x15) == 0x15; }

    [[nodiscard]] inline bool any(const vec4ba& lhs) noexcept { return (_mm_movemask_ps(_mm_castsi128_ps(lhs)) & 0x15) != 0x0; }

    [[nodiscard]] inline bool none(const vec4ba& lhs) noexcept { return (_mm_movemask_ps(_mm_castsi128_ps(lhs)) & 0x15) == 0x0; }

    ////////////////////////////////////////////////////////////////
    // Output.
    ////////////////////////////////////////////////////////////////

    inline std::ostream& operator<<(std::ostream& out, const vec4ba& v) { return out << "(" << (v.x ? true : false) << ", " << (v.y ? true : false) << ", " << (v.z ? true : false) << ", " << (v.w ? true : false) << ")"; }

}
