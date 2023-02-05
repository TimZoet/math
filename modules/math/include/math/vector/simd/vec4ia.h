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

#include "math/vector/simd/vec4ba.h"

namespace math
{
    struct alignas(16) vec4ia
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

        [[nodiscard]] vec4ia() noexcept : m128(_mm_set1_epi32(0)) {}

        [[nodiscard]] explicit vec4ia(const int32_t v) noexcept : m128(_mm_set1_epi32(v)) {}

        [[nodiscard]] vec4ia(const int32_t x, const int32_t y, const int32_t z, const int32_t w) noexcept : m128(_mm_setr_epi32(x, y, z, w)) {}

        [[nodiscard]] vec4ia(const __m128i m128) noexcept : m128(m128) {}

        [[nodiscard]] explicit vec4ia(const __m128 m128) noexcept : m128(_mm_castps_si128(m128)) {}

        [[nodiscard]] vec4ia(const vec4ia& rhs) noexcept : m128(rhs.m128) {}

        [[nodiscard]] explicit vec4ia(const vec<int32_t, 4>& rhs) noexcept : x(rhs.x), y(rhs.y), z(rhs.z), w(rhs.w) {}

        ////////////////////////////////////////////////////////////////
        // Assignment operators.
        ////////////////////////////////////////////////////////////////

        vec4ia& operator=(const vec4ia& rhs) noexcept { m128 = rhs.m128; return *this; }

        vec4ia& operator=(const int32_t rhs) noexcept { m128 = _mm_set1_epi32(rhs); return *this; }

        ////////////////////////////////////////////////////////////////
        // Load/store.
        ////////////////////////////////////////////////////////////////
        
        [[nodiscard]] static vec4ia load(const void* const ptr) { return vec4ia(_mm_load_si128(static_cast<const __m128i*>(ptr))); }

        [[nodiscard]] static vec4ia loadu(const void* const ptr) { return vec4ia(_mm_loadu_si128(static_cast<const __m128i*>(ptr))); }

        static void store(void* ptr, const vec4ia& v) { _mm_store_si128(static_cast<__m128i*>(ptr), v.m128); }

        static void storeu(void* ptr, const vec4ia& v) { _mm_storeu_si128(static_cast<__m128i*>(ptr), v.m128); }

        ////////////////////////////////////////////////////////////////
        // Defaulted constructors and operators.
        ////////////////////////////////////////////////////////////////

        ~vec4ia() noexcept = default;

        vec4ia(vec4ia&& rhs) noexcept = default;

        vec4ia& operator=(vec4ia&& rhs) noexcept = default;

        ////////////////////////////////////////////////////////////////
        // Casting operators.
        ////////////////////////////////////////////////////////////////

        [[nodiscard]] operator const __m128i& () const noexcept { return m128; }

        [[nodiscard]] operator __m128i& () noexcept { return m128; }
        
        [[nodiscard]] explicit operator __m128 () const noexcept { return _mm_castsi128_ps(m128); }

        [[nodiscard]] explicit operator vec<int32_t, 4>() const noexcept { return vec<int32_t, 4>(x, y, z, w); }

        ////////////////////////////////////////////////////////////////
        // Element access.
        ////////////////////////////////////////////////////////////////

        [[nodiscard]] const int32_t& operator[](const size_t i) const { assert(i < 4); return (&x)[i]; }

        [[nodiscard]] int32_t& operator[](const size_t i) { assert(i < 4); return (&x)[i]; }

        ////////////////////////////////////////////////////////////////
        // Swizzling.
        ////////////////////////////////////////////////////////////////

#ifdef __AVX__
        [[nodiscard]] vec4ia xxx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 0, 0, 0))); }
        [[nodiscard]] vec4ia xxy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 1, 0, 0))); }
        [[nodiscard]] vec4ia xxz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 2, 0, 0))); }
        [[nodiscard]] vec4ia xyx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 0, 1, 0))); }
        [[nodiscard]] vec4ia xyy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 1, 1, 0))); }
        [[nodiscard]] vec4ia xyz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 2, 1, 0))); }
        [[nodiscard]] vec4ia xzx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 0, 2, 0))); }
        [[nodiscard]] vec4ia xzy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 1, 2, 0))); }
        [[nodiscard]] vec4ia xzz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 2, 2, 0))); }
        [[nodiscard]] vec4ia yxx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 0, 0, 1))); }
        [[nodiscard]] vec4ia yxy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 1, 0, 1))); }
        [[nodiscard]] vec4ia yxz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 2, 0, 1))); }
        [[nodiscard]] vec4ia yyx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 0, 1, 1))); }
        [[nodiscard]] vec4ia yyy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 1, 1, 1))); }
        [[nodiscard]] vec4ia yyz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 2, 1, 1))); }
        [[nodiscard]] vec4ia yzx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 0, 2, 1))); }
        [[nodiscard]] vec4ia yzy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 1, 2, 1))); }
        [[nodiscard]] vec4ia yzz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 2, 2, 1))); }
        [[nodiscard]] vec4ia zxx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 0, 0, 2))); }
        [[nodiscard]] vec4ia zxy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 1, 0, 2))); }
        [[nodiscard]] vec4ia zxz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 2, 0, 2))); }
        [[nodiscard]] vec4ia zyx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 0, 1, 2))); }
        [[nodiscard]] vec4ia zyy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 1, 1, 2))); }
        [[nodiscard]] vec4ia zyz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 2, 1, 2))); }
        [[nodiscard]] vec4ia zzx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 0, 2, 2))); }
        [[nodiscard]] vec4ia zzy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 1, 2, 2))); }
        [[nodiscard]] vec4ia zzz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 2, 2, 2))); }

        [[nodiscard]] vec4ia xxxx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 0, 0, 0))); }
        [[nodiscard]] vec4ia xxxy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 0, 0, 0))); }
        [[nodiscard]] vec4ia xxxz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 0, 0, 0))); }
        [[nodiscard]] vec4ia xxxw() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 0, 0, 0))); }
        [[nodiscard]] vec4ia xxyx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 1, 0, 0))); }
        [[nodiscard]] vec4ia xxyy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 1, 0, 0))); }
        [[nodiscard]] vec4ia xxyz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 1, 0, 0))); }
        [[nodiscard]] vec4ia xxyw() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 1, 0, 0))); }
        [[nodiscard]] vec4ia xxzx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 2, 0, 0))); }
        [[nodiscard]] vec4ia xxzy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 2, 0, 0))); }
        [[nodiscard]] vec4ia xxzz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 2, 0, 0))); }
        [[nodiscard]] vec4ia xxzw() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 2, 0, 0))); }
        [[nodiscard]] vec4ia xxwx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 3, 0, 0))); }
        [[nodiscard]] vec4ia xxwy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 3, 0, 0))); }
        [[nodiscard]] vec4ia xxwz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 3, 0, 0))); }
        [[nodiscard]] vec4ia xxww() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 3, 0, 0))); }
        [[nodiscard]] vec4ia xyxx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 0, 1, 0))); }
        [[nodiscard]] vec4ia xyxy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 0, 1, 0))); }
        [[nodiscard]] vec4ia xyxz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 0, 1, 0))); }
        [[nodiscard]] vec4ia xyxw() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 0, 1, 0))); }
        [[nodiscard]] vec4ia xyyx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 1, 1, 0))); }
        [[nodiscard]] vec4ia xyyy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 1, 1, 0))); }
        [[nodiscard]] vec4ia xyyz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 1, 1, 0))); }
        [[nodiscard]] vec4ia xyyw() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 1, 1, 0))); }
        [[nodiscard]] vec4ia xyzx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 2, 1, 0))); }
        [[nodiscard]] vec4ia xyzy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 2, 1, 0))); }
        [[nodiscard]] vec4ia xyzz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 2, 1, 0))); }
        [[nodiscard]] vec4ia xyzw() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 2, 1, 0))); }
        [[nodiscard]] vec4ia xywx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 3, 1, 0))); }
        [[nodiscard]] vec4ia xywy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 3, 1, 0))); }
        [[nodiscard]] vec4ia xywz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 3, 1, 0))); }
        [[nodiscard]] vec4ia xyww() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 3, 1, 0))); }
        [[nodiscard]] vec4ia xzxx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 0, 2, 0))); }
        [[nodiscard]] vec4ia xzxy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 0, 2, 0))); }
        [[nodiscard]] vec4ia xzxz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 0, 2, 0))); }
        [[nodiscard]] vec4ia xzxw() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 0, 2, 0))); }
        [[nodiscard]] vec4ia xzyx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 1, 2, 0))); }
        [[nodiscard]] vec4ia xzyy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 1, 2, 0))); }
        [[nodiscard]] vec4ia xzyz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 1, 2, 0))); }
        [[nodiscard]] vec4ia xzyw() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 1, 2, 0))); }
        [[nodiscard]] vec4ia xzzx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 2, 2, 0))); }
        [[nodiscard]] vec4ia xzzy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 2, 2, 0))); }
        [[nodiscard]] vec4ia xzzz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 2, 2, 0))); }
        [[nodiscard]] vec4ia xzzw() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 2, 2, 0))); }
        [[nodiscard]] vec4ia xzwx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 3, 2, 0))); }
        [[nodiscard]] vec4ia xzwy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 3, 2, 0))); }
        [[nodiscard]] vec4ia xzwz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 3, 2, 0))); }
        [[nodiscard]] vec4ia xzww() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 3, 2, 0))); }
        [[nodiscard]] vec4ia xwxx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 0, 3, 0))); }
        [[nodiscard]] vec4ia xwxy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 0, 3, 0))); }
        [[nodiscard]] vec4ia xwxz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 0, 3, 0))); }
        [[nodiscard]] vec4ia xwxw() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 0, 3, 0))); }
        [[nodiscard]] vec4ia xwyx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 1, 3, 0))); }
        [[nodiscard]] vec4ia xwyy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 1, 3, 0))); }
        [[nodiscard]] vec4ia xwyz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 1, 3, 0))); }
        [[nodiscard]] vec4ia xwyw() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 1, 3, 0))); }
        [[nodiscard]] vec4ia xwzx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 2, 3, 0))); }
        [[nodiscard]] vec4ia xwzy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 2, 3, 0))); }
        [[nodiscard]] vec4ia xwzz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 2, 3, 0))); }
        [[nodiscard]] vec4ia xwzw() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 2, 3, 0))); }
        [[nodiscard]] vec4ia xwwx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 3, 3, 0))); }
        [[nodiscard]] vec4ia xwwy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 3, 3, 0))); }
        [[nodiscard]] vec4ia xwwz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 3, 3, 0))); }
        [[nodiscard]] vec4ia xwww() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 3, 3, 0))); }
        [[nodiscard]] vec4ia yxxx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 0, 0, 1))); }
        [[nodiscard]] vec4ia yxxy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 0, 0, 1))); }
        [[nodiscard]] vec4ia yxxz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 0, 0, 1))); }
        [[nodiscard]] vec4ia yxxw() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 0, 0, 1))); }
        [[nodiscard]] vec4ia yxyx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 1, 0, 1))); }
        [[nodiscard]] vec4ia yxyy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 1, 0, 1))); }
        [[nodiscard]] vec4ia yxyz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 1, 0, 1))); }
        [[nodiscard]] vec4ia yxyw() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 1, 0, 1))); }
        [[nodiscard]] vec4ia yxzx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 2, 0, 1))); }
        [[nodiscard]] vec4ia yxzy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 2, 0, 1))); }
        [[nodiscard]] vec4ia yxzz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 2, 0, 1))); }
        [[nodiscard]] vec4ia yxzw() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 2, 0, 1))); }
        [[nodiscard]] vec4ia yxwx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 3, 0, 1))); }
        [[nodiscard]] vec4ia yxwy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 3, 0, 1))); }
        [[nodiscard]] vec4ia yxwz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 3, 0, 1))); }
        [[nodiscard]] vec4ia yxww() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 3, 0, 1))); }
        [[nodiscard]] vec4ia yyxx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 0, 1, 1))); }
        [[nodiscard]] vec4ia yyxy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 0, 1, 1))); }
        [[nodiscard]] vec4ia yyxz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 0, 1, 1))); }
        [[nodiscard]] vec4ia yyxw() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 0, 1, 1))); }
        [[nodiscard]] vec4ia yyyx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 1, 1, 1))); }
        [[nodiscard]] vec4ia yyyy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 1, 1, 1))); }
        [[nodiscard]] vec4ia yyyz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 1, 1, 1))); }
        [[nodiscard]] vec4ia yyyw() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 1, 1, 1))); }
        [[nodiscard]] vec4ia yyzx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 2, 1, 1))); }
        [[nodiscard]] vec4ia yyzy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 2, 1, 1))); }
        [[nodiscard]] vec4ia yyzz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 2, 1, 1))); }
        [[nodiscard]] vec4ia yyzw() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 2, 1, 1))); }
        [[nodiscard]] vec4ia yywx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 3, 1, 1))); }
        [[nodiscard]] vec4ia yywy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 3, 1, 1))); }
        [[nodiscard]] vec4ia yywz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 3, 1, 1))); }
        [[nodiscard]] vec4ia yyww() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 3, 1, 1))); }
        [[nodiscard]] vec4ia yzxx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 0, 2, 1))); }
        [[nodiscard]] vec4ia yzxy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 0, 2, 1))); }
        [[nodiscard]] vec4ia yzxz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 0, 2, 1))); }
        [[nodiscard]] vec4ia yzxw() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 0, 2, 1))); }
        [[nodiscard]] vec4ia yzyx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 1, 2, 1))); }
        [[nodiscard]] vec4ia yzyy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 1, 2, 1))); }
        [[nodiscard]] vec4ia yzyz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 1, 2, 1))); }
        [[nodiscard]] vec4ia yzyw() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 1, 2, 1))); }
        [[nodiscard]] vec4ia yzzx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 2, 2, 1))); }
        [[nodiscard]] vec4ia yzzy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 2, 2, 1))); }
        [[nodiscard]] vec4ia yzzz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 2, 2, 1))); }
        [[nodiscard]] vec4ia yzzw() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 2, 2, 1))); }
        [[nodiscard]] vec4ia yzwx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 3, 2, 1))); }
        [[nodiscard]] vec4ia yzwy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 3, 2, 1))); }
        [[nodiscard]] vec4ia yzwz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 3, 2, 1))); }
        [[nodiscard]] vec4ia yzww() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 3, 2, 1))); }
        [[nodiscard]] vec4ia ywxx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 0, 3, 1))); }
        [[nodiscard]] vec4ia ywxy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 0, 3, 1))); }
        [[nodiscard]] vec4ia ywxz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 0, 3, 1))); }
        [[nodiscard]] vec4ia ywxw() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 0, 3, 1))); }
        [[nodiscard]] vec4ia ywyx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 1, 3, 1))); }
        [[nodiscard]] vec4ia ywyy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 1, 3, 1))); }
        [[nodiscard]] vec4ia ywyz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 1, 3, 1))); }
        [[nodiscard]] vec4ia ywyw() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 1, 3, 1))); }
        [[nodiscard]] vec4ia ywzx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 2, 3, 1))); }
        [[nodiscard]] vec4ia ywzy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 2, 3, 1))); }
        [[nodiscard]] vec4ia ywzz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 2, 3, 1))); }
        [[nodiscard]] vec4ia ywzw() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 2, 3, 1))); }
        [[nodiscard]] vec4ia ywwx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 3, 3, 1))); }
        [[nodiscard]] vec4ia ywwy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 3, 3, 1))); }
        [[nodiscard]] vec4ia ywwz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 3, 3, 1))); }
        [[nodiscard]] vec4ia ywww() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 3, 3, 1))); }
        [[nodiscard]] vec4ia zxxx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 0, 0, 2))); }
        [[nodiscard]] vec4ia zxxy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 0, 0, 2))); }
        [[nodiscard]] vec4ia zxxz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 0, 0, 2))); }
        [[nodiscard]] vec4ia zxxw() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 0, 0, 2))); }
        [[nodiscard]] vec4ia zxyx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 1, 0, 2))); }
        [[nodiscard]] vec4ia zxyy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 1, 0, 2))); }
        [[nodiscard]] vec4ia zxyz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 1, 0, 2))); }
        [[nodiscard]] vec4ia zxyw() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 1, 0, 2))); }
        [[nodiscard]] vec4ia zxzx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 2, 0, 2))); }
        [[nodiscard]] vec4ia zxzy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 2, 0, 2))); }
        [[nodiscard]] vec4ia zxzz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 2, 0, 2))); }
        [[nodiscard]] vec4ia zxzw() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 2, 0, 2))); }
        [[nodiscard]] vec4ia zxwx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 3, 0, 2))); }
        [[nodiscard]] vec4ia zxwy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 3, 0, 2))); }
        [[nodiscard]] vec4ia zxwz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 3, 0, 2))); }
        [[nodiscard]] vec4ia zxww() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 3, 0, 2))); }
        [[nodiscard]] vec4ia zyxx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 0, 1, 2))); }
        [[nodiscard]] vec4ia zyxy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 0, 1, 2))); }
        [[nodiscard]] vec4ia zyxz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 0, 1, 2))); }
        [[nodiscard]] vec4ia zyxw() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 0, 1, 2))); }
        [[nodiscard]] vec4ia zyyx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 1, 1, 2))); }
        [[nodiscard]] vec4ia zyyy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 1, 1, 2))); }
        [[nodiscard]] vec4ia zyyz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 1, 1, 2))); }
        [[nodiscard]] vec4ia zyyw() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 1, 1, 2))); }
        [[nodiscard]] vec4ia zyzx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 2, 1, 2))); }
        [[nodiscard]] vec4ia zyzy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 2, 1, 2))); }
        [[nodiscard]] vec4ia zyzz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 2, 1, 2))); }
        [[nodiscard]] vec4ia zyzw() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 2, 1, 2))); }
        [[nodiscard]] vec4ia zywx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 3, 1, 2))); }
        [[nodiscard]] vec4ia zywy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 3, 1, 2))); }
        [[nodiscard]] vec4ia zywz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 3, 1, 2))); }
        [[nodiscard]] vec4ia zyww() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 3, 1, 2))); }
        [[nodiscard]] vec4ia zzxx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 0, 2, 2))); }
        [[nodiscard]] vec4ia zzxy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 0, 2, 2))); }
        [[nodiscard]] vec4ia zzxz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 0, 2, 2))); }
        [[nodiscard]] vec4ia zzxw() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 0, 2, 2))); }
        [[nodiscard]] vec4ia zzyx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 1, 2, 2))); }
        [[nodiscard]] vec4ia zzyy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 1, 2, 2))); }
        [[nodiscard]] vec4ia zzyz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 1, 2, 2))); }
        [[nodiscard]] vec4ia zzyw() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 1, 2, 2))); }
        [[nodiscard]] vec4ia zzzx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 2, 2, 2))); }
        [[nodiscard]] vec4ia zzzy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 2, 2, 2))); }
        [[nodiscard]] vec4ia zzzz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 2, 2, 2))); }
        [[nodiscard]] vec4ia zzzw() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 2, 2, 2))); }
        [[nodiscard]] vec4ia zzwx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 3, 2, 2))); }
        [[nodiscard]] vec4ia zzwy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 3, 2, 2))); }
        [[nodiscard]] vec4ia zzwz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 3, 2, 2))); }
        [[nodiscard]] vec4ia zzww() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 3, 2, 2))); }
        [[nodiscard]] vec4ia zwxx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 0, 3, 2))); }
        [[nodiscard]] vec4ia zwxy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 0, 3, 2))); }
        [[nodiscard]] vec4ia zwxz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 0, 3, 2))); }
        [[nodiscard]] vec4ia zwxw() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 0, 3, 2))); }
        [[nodiscard]] vec4ia zwyx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 1, 3, 2))); }
        [[nodiscard]] vec4ia zwyy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 1, 3, 2))); }
        [[nodiscard]] vec4ia zwyz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 1, 3, 2))); }
        [[nodiscard]] vec4ia zwyw() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 1, 3, 2))); }
        [[nodiscard]] vec4ia zwzx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 2, 3, 2))); }
        [[nodiscard]] vec4ia zwzy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 2, 3, 2))); }
        [[nodiscard]] vec4ia zwzz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 2, 3, 2))); }
        [[nodiscard]] vec4ia zwzw() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 2, 3, 2))); }
        [[nodiscard]] vec4ia zwwx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 3, 3, 2))); }
        [[nodiscard]] vec4ia zwwy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 3, 3, 2))); }
        [[nodiscard]] vec4ia zwwz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 3, 3, 2))); }
        [[nodiscard]] vec4ia zwww() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 3, 3, 2))); }
        [[nodiscard]] vec4ia wxxx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 0, 0, 3))); }
        [[nodiscard]] vec4ia wxxy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 0, 0, 3))); }
        [[nodiscard]] vec4ia wxxz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 0, 0, 3))); }
        [[nodiscard]] vec4ia wxxw() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 0, 0, 3))); }
        [[nodiscard]] vec4ia wxyx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 1, 0, 3))); }
        [[nodiscard]] vec4ia wxyy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 1, 0, 3))); }
        [[nodiscard]] vec4ia wxyz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 1, 0, 3))); }
        [[nodiscard]] vec4ia wxyw() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 1, 0, 3))); }
        [[nodiscard]] vec4ia wxzx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 2, 0, 3))); }
        [[nodiscard]] vec4ia wxzy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 2, 0, 3))); }
        [[nodiscard]] vec4ia wxzz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 2, 0, 3))); }
        [[nodiscard]] vec4ia wxzw() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 2, 0, 3))); }
        [[nodiscard]] vec4ia wxwx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 3, 0, 3))); }
        [[nodiscard]] vec4ia wxwy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 3, 0, 3))); }
        [[nodiscard]] vec4ia wxwz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 3, 0, 3))); }
        [[nodiscard]] vec4ia wxww() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 3, 0, 3))); }
        [[nodiscard]] vec4ia wyxx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 0, 1, 3))); }
        [[nodiscard]] vec4ia wyxy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 0, 1, 3))); }
        [[nodiscard]] vec4ia wyxz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 0, 1, 3))); }
        [[nodiscard]] vec4ia wyxw() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 0, 1, 3))); }
        [[nodiscard]] vec4ia wyyx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 1, 1, 3))); }
        [[nodiscard]] vec4ia wyyy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 1, 1, 3))); }
        [[nodiscard]] vec4ia wyyz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 1, 1, 3))); }
        [[nodiscard]] vec4ia wyyw() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 1, 1, 3))); }
        [[nodiscard]] vec4ia wyzx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 2, 1, 3))); }
        [[nodiscard]] vec4ia wyzy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 2, 1, 3))); }
        [[nodiscard]] vec4ia wyzz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 2, 1, 3))); }
        [[nodiscard]] vec4ia wyzw() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 2, 1, 3))); }
        [[nodiscard]] vec4ia wywx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 3, 1, 3))); }
        [[nodiscard]] vec4ia wywy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 3, 1, 3))); }
        [[nodiscard]] vec4ia wywz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 3, 1, 3))); }
        [[nodiscard]] vec4ia wyww() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 3, 1, 3))); }
        [[nodiscard]] vec4ia wzxx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 0, 2, 3))); }
        [[nodiscard]] vec4ia wzxy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 0, 2, 3))); }
        [[nodiscard]] vec4ia wzxz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 0, 2, 3))); }
        [[nodiscard]] vec4ia wzxw() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 0, 2, 3))); }
        [[nodiscard]] vec4ia wzyx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 1, 2, 3))); }
        [[nodiscard]] vec4ia wzyy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 1, 2, 3))); }
        [[nodiscard]] vec4ia wzyz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 1, 2, 3))); }
        [[nodiscard]] vec4ia wzyw() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 1, 2, 3))); }
        [[nodiscard]] vec4ia wzzx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 2, 2, 3))); }
        [[nodiscard]] vec4ia wzzy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 2, 2, 3))); }
        [[nodiscard]] vec4ia wzzz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 2, 2, 3))); }
        [[nodiscard]] vec4ia wzzw() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 2, 2, 3))); }
        [[nodiscard]] vec4ia wzwx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 3, 2, 3))); }
        [[nodiscard]] vec4ia wzwy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 3, 2, 3))); }
        [[nodiscard]] vec4ia wzwz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 3, 2, 3))); }
        [[nodiscard]] vec4ia wzww() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 3, 2, 3))); }
        [[nodiscard]] vec4ia wwxx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 0, 3, 3))); }
        [[nodiscard]] vec4ia wwxy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 0, 3, 3))); }
        [[nodiscard]] vec4ia wwxz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 0, 3, 3))); }
        [[nodiscard]] vec4ia wwxw() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 0, 3, 3))); }
        [[nodiscard]] vec4ia wwyx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 1, 3, 3))); }
        [[nodiscard]] vec4ia wwyy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 1, 3, 3))); }
        [[nodiscard]] vec4ia wwyz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 1, 3, 3))); }
        [[nodiscard]] vec4ia wwyw() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 1, 3, 3))); }
        [[nodiscard]] vec4ia wwzx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 2, 3, 3))); }
        [[nodiscard]] vec4ia wwzy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 2, 3, 3))); }
        [[nodiscard]] vec4ia wwzz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 2, 3, 3))); }
        [[nodiscard]] vec4ia wwzw() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 2, 3, 3))); }
        [[nodiscard]] vec4ia wwwx() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 3, 3, 3))); }
        [[nodiscard]] vec4ia wwwy() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(1, 3, 3, 3))); }
        [[nodiscard]] vec4ia wwwz() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(2, 3, 3, 3))); }
        [[nodiscard]] vec4ia wwww() const noexcept { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(3, 3, 3, 3))); }
#endif
    };

    ////////////////////////////////////////////////////////////////
    // Shuffle.
    ////////////////////////////////////////////////////////////////

#ifdef __AVX__
    template<int32_t i0, int32_t i1, int32_t i2, int32_t i3>
    [[nodiscard]] vec4ia shuffle(const vec4ia& v) { return vec4ia(_mm_permute_ps(_mm_castsi128_ps(v), _MM_SHUFFLE(i3, i2, i1, i0))); }
#endif

    ////////////////////////////////////////////////////////////////
    // Arithmetic operators.
    ////////////////////////////////////////////////////////////////

    [[nodiscard]] inline vec4ia operator+(const vec4ia& lhs, const vec4ia& rhs) { return _mm_add_epi32(lhs, rhs); }

    [[nodiscard]] inline vec4ia operator+(const vec4ia& lhs, const int32_t rhs) { return lhs + vec4ia(rhs); }

    [[nodiscard]] inline vec4ia operator+(const int32_t lhs, const vec4ia& rhs) { return vec4ia(lhs) + rhs; }

    [[nodiscard]] inline vec4ia operator-(const vec4ia& lhs, const vec4ia& rhs) { return _mm_sub_epi32(lhs, rhs); }

    [[nodiscard]] inline vec4ia operator-(const vec4ia& lhs, const int32_t rhs) { return lhs - vec4ia(rhs); }

    [[nodiscard]] inline vec4ia operator-(const int32_t lhs, const vec4ia& rhs) { return vec4ia(lhs) - rhs; }

    [[nodiscard]] inline vec4ia operator-(const vec4ia& lhs) { const __m128i mask = _mm_set1_epi32(0x80000000); return _mm_xor_si128(lhs, mask); }

    [[nodiscard]] inline vec4ia operator*(const vec4ia& lhs, const vec4ia& rhs)
    {
#ifdef __SSE4_1__
        return _mm_mullo_epi32(lhs, rhs);
#else
        const __m128i tmp1 = _mm_mul_epu32(lhs, rhs);
        const __m128i tmp2 = _mm_mul_epu32(_mm_srli_si128(lhs, 4), _mm_srli_si128(rhs, 4));
        return _mm_unpacklo_epi32(_mm_shuffle_epi32(tmp1, _MM_SHUFFLE(0, 0, 2, 0)), _mm_shuffle_epi32(tmp2, _MM_SHUFFLE(0, 0, 2, 0)));
#endif
    }

    [[nodiscard]] inline vec4ia operator*(const vec4ia& lhs, const int32_t rhs) { return lhs * vec4ia(rhs); }

    [[nodiscard]] inline vec4ia operator*(const int32_t lhs, const vec4ia& rhs) { return vec4ia(lhs) * rhs; }

    [[nodiscard]] inline vec4ia operator/(const vec4ia& lhs, const vec4ia& rhs)
    {
        // Cast to float and round with truncation.
        return _mm_cvtps_epi32(_mm_round_ps(_mm_div_ps(_mm_cvtepi32_ps(lhs), _mm_cvtepi32_ps(rhs)), _MM_FROUND_TRUNC));
    }

    [[nodiscard]] inline vec4ia operator/(const vec4ia& lhs, const int32_t rhs) { return lhs / vec4ia(rhs); }

    [[nodiscard]] inline vec4ia operator/(const int32_t lhs, const vec4ia& rhs) { return vec4ia(lhs) / rhs; }

    inline vec4ia& operator+=(vec4ia& lhs, const vec4ia& rhs) { return lhs = lhs + rhs; }

    inline vec4ia& operator+=(vec4ia& lhs, const int32_t rhs) { return lhs = lhs + rhs; }

    inline vec4ia& operator-=(vec4ia& lhs, const vec4ia& rhs) { return lhs = lhs - rhs; }

    inline vec4ia& operator-=(vec4ia& lhs, const int32_t rhs) { return lhs = lhs - rhs; }

    inline vec4ia& operator*=(vec4ia& lhs, const vec4ia& rhs) { return lhs = lhs * rhs; }

    inline vec4ia& operator*=(vec4ia& lhs, const int32_t rhs) { return lhs = lhs * rhs; }

    inline vec4ia& operator/=(vec4ia& lhs, const vec4ia& rhs) { return lhs = lhs / rhs; }

    inline vec4ia& operator/=(vec4ia& lhs, const int32_t rhs) { return lhs = lhs / rhs; }

    ////////////////////////////////////////////////////////////////
    // Comparison operators.
    ////////////////////////////////////////////////////////////////

    [[nodiscard]] inline bool operator==(const vec4ia& lhs, const vec4ia& rhs) { return (_mm_movemask_ps(_mm_castsi128_ps(_mm_cmpeq_epi32(lhs, rhs))) & 0x15) == 0x15; }

    [[nodiscard]] inline bool operator!=(const vec4ia& lhs, const vec4ia& rhs) { return (_mm_movemask_ps(_mm_castsi128_ps(_mm_cmpeq_epi32(lhs, rhs))) & 0x15) != 0x15; }

    ////////////////////////////////////////////////////////////////
    // Per-element comparisons.
    ////////////////////////////////////////////////////////////////

    [[nodiscard]] inline vec4ba cmpeq(const vec4ia& lhs, const vec4ia& rhs) { return _mm_cmpeq_epi32(lhs, rhs); }

    [[nodiscard]] inline vec4ba cmpeq(const vec4ia& lhs, const int32_t rhs) { return cmpeq(lhs, vec4ia(rhs)); }

    [[nodiscard]] inline vec4ba cmpeq(const int32_t lhs, const vec4ia& rhs) { return cmpeq(vec4ia(lhs), rhs); }

    [[nodiscard]] inline vec4ba cmpneq(const vec4ia& lhs, const vec4ia& rhs) { return _mm_andnot_si128(_mm_cmpeq_epi32(lhs, rhs), _mm_set1_epi32(-1)); }

    [[nodiscard]] inline vec4ba cmpneq(const vec4ia& lhs, const int32_t rhs) { return cmpneq(lhs, vec4ia(rhs)); }

    [[nodiscard]] inline vec4ba cmpneq(const int32_t lhs, const vec4ia& rhs) { return cmpneq(vec4ia(lhs), rhs); }

    [[nodiscard]] inline vec4ba cmplt(const vec4ia& lhs, const vec4ia& rhs) { return _mm_cmplt_epi32(lhs, rhs); }

    [[nodiscard]] inline vec4ba cmplt(const vec4ia& lhs, const int32_t rhs) { return cmplt(lhs, vec4ia(rhs)); }

    [[nodiscard]] inline vec4ba cmplt(const int32_t lhs, const vec4ia& rhs) { return cmplt(vec4ia(lhs), rhs); }

    [[nodiscard]] inline vec4ba cmpgt(const vec4ia& lhs, const vec4ia& rhs) { return _mm_cmpgt_epi32(lhs, rhs); }

    [[nodiscard]] inline vec4ba cmpgt(const vec4ia& lhs, const int32_t rhs) { return cmpgt(lhs, vec4ia(rhs)); }

    [[nodiscard]] inline vec4ba cmpgt(const int32_t lhs, const vec4ia& rhs) { return cmpgt(vec4ia(lhs), rhs); }

    [[nodiscard]] inline vec4ba cmple(const vec4ia& lhs, const vec4ia& rhs) { return _mm_andnot_si128(_mm_cmpgt_epi32(lhs, rhs), _mm_set1_epi32(-1)); }

    [[nodiscard]] inline vec4ba cmple(const vec4ia& lhs, const int32_t rhs) { return cmple(lhs, vec4ia(rhs)); }

    [[nodiscard]] inline vec4ba cmple(const int32_t lhs, const vec4ia& rhs) { return cmple(vec4ia(lhs), rhs); }

    [[nodiscard]] inline vec4ba cmpge(const vec4ia& lhs, const vec4ia& rhs) { return _mm_andnot_si128(_mm_cmplt_epi32(lhs, rhs), _mm_set1_epi32(-1)); }

    [[nodiscard]] inline vec4ba cmpge(const vec4ia& lhs, const int32_t rhs) { return cmpge(lhs, vec4ia(rhs)); }

    [[nodiscard]] inline vec4ba cmpge(const int32_t lhs, const vec4ia& rhs) { return cmpge(vec4ia(lhs), rhs); }

    ////////////////////////////////////////////////////////////////
    // Min/max, abs and clamp.
    ////////////////////////////////////////////////////////////////

    [[nodiscard]] inline vec4ia min(const vec4ia& lhs, const vec4ia& rhs) { return _mm_min_epi32(lhs, rhs); }

    [[nodiscard]] inline vec4ia min(const vec4ia& lhs, const int32_t rhs) { return min(lhs, vec4ia(rhs)); }

    [[nodiscard]] inline vec4ia min(const int32_t lhs, const vec4ia& rhs) { return min(vec4ia(lhs), rhs); }

    [[nodiscard]] inline vec4ia max(const vec4ia& lhs, const vec4ia& rhs) { return _mm_max_epi32(lhs, rhs); }

    [[nodiscard]] inline vec4ia max(const vec4ia& lhs, const int32_t rhs) { return max(lhs, vec4ia(rhs)); }

    [[nodiscard]] inline vec4ia max(const int32_t lhs, const vec4ia& rhs) { return max(vec4ia(lhs), rhs); }

    [[nodiscard]] inline vec4ia clamp(const vec4ia& a, const vec4ia& min, const vec4ia& max) { return math::max(min, math::min(a, max)); }

    [[nodiscard]] inline vec4ia clamp(const vec4ia& a, const vec4ia& min, const int32_t max) { return clamp(a, min, vec4ia(max)); }

    [[nodiscard]] inline vec4ia clamp(const vec4ia& a, const int32_t min, const vec4ia& max) { return clamp(a, vec4ia(min), max); }

    [[nodiscard]] inline vec4ia clamp(const vec4ia& a, const int32_t min, const int32_t max) { return clamp(a, vec4ia(min), vec4ia(max)); }


    ////////////////////////////////////////////////////////////////
    // Reduction.
    ////////////////////////////////////////////////////////////////

    [[nodiscard]] inline int32_t reduce_add(const vec4ia& lhs)
    {
        const vec4ia zw = lhs.zwxx();
        const vec4ia sum1 = lhs + zw;
        const vec4ia sum = sum1 + sum1.yxxx();
        return _mm_cvtsi128_si32(sum);
    }

    [[nodiscard]] inline int32_t reduce_mul(const vec4ia& lhs)
    {
        const vec4ia zw = lhs.zwxx();
        const vec4ia sum1 = lhs * zw;
        const vec4ia sum = sum1 * sum1.yxxx();
        return _mm_cvtsi128_si32(sum);
    }

    [[nodiscard]] inline int32_t reduce_min(const vec4ia& lhs)
    {
        const vec4ia zw = lhs.zwxx();
        const vec4ia sum1 = min(lhs, zw);
        const vec4ia sum = min(sum1, sum1.yxxx());
        return _mm_cvtsi128_si32(sum);
    }

    [[nodiscard]] inline int32_t reduce_max(const vec4ia& lhs)
    {
        const vec4ia zw = lhs.zwxx();
        const vec4ia sum1 = max(lhs, zw);
        const vec4ia sum = max(sum1, sum1.yxxx());
        return _mm_cvtsi128_si32(sum);
    }

    ////////////////////////////////////////////////////////////////
    // Dot product etc.
    ////////////////////////////////////////////////////////////////

#if 0
    inline int32_t dot(const vec4ia& lhs, const vec4ia& rhs)
    {
        return reduce_add(lhs * rhs);
    }

    inline int32_t length(const vec4ia& lhs) { return sqrt(dot(lhs, lhs)); }

    inline int32_t sqr_length(const vec4ia& lhs) { return dot(lhs, lhs); }

    inline int32_t rcp_length(const vec4ia& lhs) { return rsqrt(dot(lhs, lhs)); }

    inline vec4ia normalize(const vec4ia& lhs) { return lhs * rcp_length(lhs); }

    inline vec4ia normalize(const vec4ia& lhs, int32_t& length) { length = math::length(lhs); return lhs / length; }

    inline int32_t distance(const vec4ia& lhs, const vec4ia& rhs) { return length(lhs - rhs); }
#endif

    ////////////////////////////////////////////////////////////////
    // Exponential / Logarithmic.
    ////////////////////////////////////////////////////////////////

#if 0
    inline vec4ia exp(const vec4ia& lhs) { return vec4ia(exp(lhs.x), exp(lhs.y), exp(lhs.z), exp(lhs.w)); }

    inline vec4ia exp2(const vec4ia& lhs) { return vec4ia(exp2(lhs.x), exp2(lhs.y), exp2(lhs.z), exp2(lhs.w)); }

    inline vec4ia log(const vec4ia& lhs) { return vec4ia(log(lhs.x), log(lhs.y), log(lhs.z), log(lhs.w)); }

    inline vec4ia log2(const vec4ia& lhs) { return vec4ia(log2(lhs.x), log2(lhs.y), log2(lhs.z), log2(lhs.w)); }

    inline vec4ia log10(const vec4ia& lhs) { return vec4ia(log10(lhs.x), log10(lhs.y), log10(lhs.z), log10(lhs.w)); }
#endif

    ////////////////////////////////////////////////////////////////
    // Power.
    ////////////////////////////////////////////////////////////////

#if 0
    inline vec4ia pow(const vec4ia& lhs, const vec4ia& rhs) { return vec4ia(pow(lhs.x, rhs.x), pow(lhs.y, rhs.y), pow(lhs.z, rhs.z), pow(lhs.w, rhs.w)); }

    inline vec4ia sqr(const vec4ia& lhs) { return lhs * lhs; }

    inline vec4ia sqrt(const vec4ia& lhs) { return _mm_cvtps_epi32(_mm_sqrt_ps(_mm_cvtepi32_ps(lhs))); }

    inline vec4ia rsqrt(const vec4ia& lhs) { return _mm_cvtps_epi32(_mm_rsqrt_ps(_mm_cvtepi32_ps(lhs))); }
#endif

    ////////////////////////////////////////////////////////////////
    // Rounding, abs, etc.
    ////////////////////////////////////////////////////////////////

    [[nodiscard]] inline vec4ia abs(const vec4ia& lhs)
    {
        const __m128i mask = _mm_set1_epi32(0x7fffffff);
        return _mm_and_si128(lhs, mask);
    }

    ////////////////////////////////////////////////////////////////
    // Select.
    ////////////////////////////////////////////////////////////////

    [[nodiscard]] inline vec4ia select(const vec4ia& t, const vec4ia& f, const vec4ba& b)
    {
#ifdef __SSE4_1__
        return vec4ia(_mm_blendv_ps(_mm_castsi128_ps(f), _mm_castsi128_ps(t), _mm_castsi128_ps(b)));
#else
        return vec4ia(math::select(t.x, f.x, b.x & 0x80000000), math::select(t.y, f.y, b.y & 0x80000000), math::select(t.z, f.z, b.z & 0x80000000), math::select(t.w, f.w, b.w & 0x80000000));
#endif
    }

    ////////////////////////////////////////////////////////////////
    // Multiply and add.
    ////////////////////////////////////////////////////////////////

    [[nodiscard]] inline vec4ia madd(const vec4ia& a, const vec4ia& b, const vec4ia& c) { return a * b + c; }

    [[nodiscard]] inline vec4ia nmadd(const vec4ia& a, const vec4ia& b, const vec4ia& c) { return -a * b + c; }

    [[nodiscard]] inline vec4ia msub(const vec4ia& a, const vec4ia& b, const vec4ia& c) { return a * b - c; }

    [[nodiscard]] inline vec4ia nmsub(const vec4ia& a, const vec4ia& b, const vec4ia& c) { return -a * b - c; }

    ////////////////////////////////////////////////////////////////
    // Shift operators.
    ////////////////////////////////////////////////////////////////

#ifdef __AVX2__
    [[nodiscard]] inline vec4ia operator<<(const vec4ia& lhs, const vec4ia& rhs) { return _mm_sllv_epi32(lhs, rhs); }
#endif
    [[nodiscard]] inline vec4ia operator<<(const vec4ia& lhs, const int32_t rhs) { return _mm_slli_epi32(lhs, rhs); }
#ifdef __AVX2__
    [[nodiscard]] inline vec4ia operator<<(const int32_t lhs, const vec4ia& rhs) { return _mm_sllv_epi32(_mm_set1_epi32(lhs), rhs); }
#endif
#ifdef __AVX2__
    [[nodiscard]] inline vec4ia operator>>(const vec4ia& lhs, const vec4ia& rhs) { return _mm_srlv_epi32(lhs, rhs); }
#endif
    [[nodiscard]] inline vec4ia operator>>(const vec4ia& lhs, const int32_t rhs) { return _mm_srli_epi32(lhs, rhs); }
#ifdef __AVX2__
    [[nodiscard]] inline vec4ia operator>>(const int32_t lhs, const vec4ia& rhs) { return _mm_srlv_epi32(_mm_set1_epi32(lhs), rhs); }
#endif
#ifdef __AVX2__
    inline vec4ia& operator<<=(vec4ia& lhs, const vec4ia& rhs) { return lhs = lhs << rhs; }
#endif
    inline vec4ia& operator<<=(vec4ia& lhs, const int32_t rhs) { return lhs = lhs << rhs; }
#ifdef __AVX2__
    inline vec4ia& operator>>=(vec4ia& lhs, const vec4ia& rhs) { return lhs = lhs >> rhs; }
#endif
    inline vec4ia& operator>>=(vec4ia& lhs, const int32_t rhs) { return lhs = lhs >> rhs; }

    ////////////////////////////////////////////////////////////////
    // Bitwise operators.
    ////////////////////////////////////////////////////////////////

    [[nodiscard]] inline vec4ia operator|(const vec4ia& lhs, const vec4ia& rhs) { return _mm_or_si128(lhs, rhs); }

    [[nodiscard]] inline vec4ia operator|(const vec4ia& lhs, const int32_t rhs) { return _mm_or_si128(lhs, vec4ia(rhs)); }

    [[nodiscard]] inline vec4ia operator|(const int32_t lhs, const vec4ia& rhs) { return _mm_or_si128(vec4ia(lhs), rhs); }

    [[nodiscard]] inline vec4ia operator&(const vec4ia& lhs, const vec4ia& rhs) { return _mm_and_si128(lhs, rhs); }

    [[nodiscard]] inline vec4ia operator&(const vec4ia& lhs, const int32_t rhs) { return _mm_and_si128(lhs, vec4ia(rhs)); }

    [[nodiscard]] inline vec4ia operator&(const int32_t lhs, const vec4ia& rhs) { return _mm_and_si128(vec4ia(lhs), rhs); }

    [[nodiscard]] inline vec4ia operator^(const vec4ia& lhs, const vec4ia& rhs) { return _mm_xor_si128(lhs, rhs); }

    [[nodiscard]] inline vec4ia operator^(const vec4ia& lhs, const int32_t rhs) { return _mm_xor_si128(lhs, vec4ia(rhs)); }

    [[nodiscard]] inline vec4ia operator^(const int32_t lhs, const vec4ia& rhs) { return _mm_xor_si128(vec4ia(lhs), rhs); }

    [[nodiscard]] inline vec4ia operator~(const vec4ia& lhs) { return _mm_sub_epi32(_mm_set1_epi32(0), lhs); }

    inline vec4ia& operator|=(vec4ia& lhs, const vec4ia& rhs) { return lhs = lhs | rhs; }

    inline vec4ia& operator|=(vec4ia& lhs, const int32_t rhs) { return lhs = lhs | rhs; }

    inline vec4ia& operator&=(vec4ia& lhs, const vec4ia& rhs) { return lhs = lhs & rhs; }

    inline vec4ia& operator&=(vec4ia& lhs, const int32_t rhs) { return lhs = lhs & rhs; }

    inline vec4ia& operator^=(vec4ia& lhs, const vec4ia& rhs) { return lhs = lhs ^ rhs; }

    inline vec4ia& operator^=(vec4ia& lhs, const int32_t rhs) { return lhs = lhs ^ rhs; }

    ////////////////////////////////////////////////////////////////
    // Output.
    ////////////////////////////////////////////////////////////////

    inline std::ostream& operator<<(std::ostream& out, const vec4ia& v) { return out << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")"; }

}
