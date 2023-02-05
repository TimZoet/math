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
    struct alignas(16) vec4fa
    {
        static constexpr size_t size = 4;
        using element_type = float;

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4201)
#endif
        union
        {
            __m128 m128;
            struct
            {
                float x, y, z, w;
            };
        };
#ifdef _MSC_VER
#pragma warning(pop)
#endif

        ////////////////////////////////////////////////////////////////
        // Constructors.
        ////////////////////////////////////////////////////////////////

        [[nodiscard]] vec4fa() noexcept : m128(_mm_set1_ps(0)) {}

        [[nodiscard]] explicit vec4fa(const float v) noexcept : m128(_mm_set1_ps(v)) {}

        [[nodiscard]] vec4fa(const float x, const float y, const float z, const float w) noexcept : m128(_mm_setr_ps(x, y, z, w)) {}

        [[nodiscard]] vec4fa(const __m128 m128) noexcept : m128(m128) {}

        [[nodiscard]] explicit vec4fa(const __m128i m128) noexcept : m128(_mm_castsi128_ps(m128)) {}

        [[nodiscard]] vec4fa(const vec4fa& rhs) noexcept : m128(rhs.m128) {}

        [[nodiscard]] explicit vec4fa(const vec<float, 4>& rhs) noexcept : m128(_mm_setr_ps(rhs.x, rhs.y, rhs.z, rhs.w)) {}

        ////////////////////////////////////////////////////////////////
        // Assignment operators.
        ////////////////////////////////////////////////////////////////

        vec4fa& operator=(const vec4fa& rhs) noexcept { m128 = rhs.m128; return *this; }

        vec4fa& operator=(const float rhs) noexcept { m128 = _mm_set1_ps(rhs); return *this; }

        ////////////////////////////////////////////////////////////////
        // Load/store.
        ////////////////////////////////////////////////////////////////

        [[nodiscard]] static vec4fa load(const void* const ptr) { return vec4fa(_mm_load_ps(static_cast<const float*>(ptr))); }

        [[nodiscard]] static vec4fa loadu(const void* const ptr) { return vec4fa(_mm_loadu_ps(static_cast<const float*>(ptr))); }

        static void store(void* ptr, const vec4fa & v) { _mm_store_ps(static_cast<float*>(ptr), v.m128); }

        static void storeu(void* ptr, const vec4fa & v) { _mm_storeu_ps(static_cast<float*>(ptr), v.m128); }

        ////////////////////////////////////////////////////////////////
        // Defaulted constructors and operators.
        ////////////////////////////////////////////////////////////////

        ~vec4fa() noexcept = default;

        vec4fa(vec4fa && rhs) noexcept = default;

        vec4fa& operator=(vec4fa && rhs) noexcept = default;

        ////////////////////////////////////////////////////////////////
        // Casting operators.
        ////////////////////////////////////////////////////////////////

        [[nodiscard]] operator const __m128& () const noexcept { return m128; }

        [[nodiscard]] operator __m128& () noexcept { return m128; }

        [[nodiscard]] explicit operator __m128i () const noexcept { return _mm_castps_si128(m128); }

        [[nodiscard]] explicit operator vec<float, 4>() const noexcept { return vec<float, 4>(x, y, z, w); }

        ////////////////////////////////////////////////////////////////
        // Element access.
        ////////////////////////////////////////////////////////////////

        [[nodiscard]] const float& operator[](const size_t i) const { assert(i < 4); return (&x)[i]; }

        [[nodiscard]] float& operator[](const size_t i) { assert(i < 4); return (&x)[i]; }

        ////////////////////////////////////////////////////////////////
        // Swizzling.
        ////////////////////////////////////////////////////////////////

#ifdef __AVX__
        [[nodiscard]] vec4fa xxx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 0, 0, 0)); }
        [[nodiscard]] vec4fa xxy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 1, 0, 0)); }
        [[nodiscard]] vec4fa xxz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 2, 0, 0)); }
        [[nodiscard]] vec4fa xyx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 0, 1, 0)); }
        [[nodiscard]] vec4fa xyy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 1, 1, 0)); }
        [[nodiscard]] vec4fa xyz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 2, 1, 0)); }
        [[nodiscard]] vec4fa xzx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 0, 2, 0)); }
        [[nodiscard]] vec4fa xzy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 1, 2, 0)); }
        [[nodiscard]] vec4fa xzz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 2, 2, 0)); }
        [[nodiscard]] vec4fa yxx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 0, 0, 1)); }
        [[nodiscard]] vec4fa yxy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 1, 0, 1)); }
        [[nodiscard]] vec4fa yxz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 2, 0, 1)); }
        [[nodiscard]] vec4fa yyx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 0, 1, 1)); }
        [[nodiscard]] vec4fa yyy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 1, 1, 1)); }
        [[nodiscard]] vec4fa yyz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 2, 1, 1)); }
        [[nodiscard]] vec4fa yzx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 0, 2, 1)); }
        [[nodiscard]] vec4fa yzy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 1, 2, 1)); }
        [[nodiscard]] vec4fa yzz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 2, 2, 1)); }
        [[nodiscard]] vec4fa zxx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 0, 0, 2)); }
        [[nodiscard]] vec4fa zxy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 1, 0, 2)); }
        [[nodiscard]] vec4fa zxz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 2, 0, 2)); }
        [[nodiscard]] vec4fa zyx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 0, 1, 2)); }
        [[nodiscard]] vec4fa zyy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 1, 1, 2)); }
        [[nodiscard]] vec4fa zyz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 2, 1, 2)); }
        [[nodiscard]] vec4fa zzx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 0, 2, 2)); }
        [[nodiscard]] vec4fa zzy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 1, 2, 2)); }
        [[nodiscard]] vec4fa zzz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 2, 2, 2)); }

        [[nodiscard]] vec4fa xxxx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 0, 0, 0)); }
        [[nodiscard]] vec4fa xxxy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(1, 0, 0, 0)); }
        [[nodiscard]] vec4fa xxxz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(2, 0, 0, 0)); }
        [[nodiscard]] vec4fa xxxw() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(3, 0, 0, 0)); }
        [[nodiscard]] vec4fa xxyx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 1, 0, 0)); }
        [[nodiscard]] vec4fa xxyy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(1, 1, 0, 0)); }
        [[nodiscard]] vec4fa xxyz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(2, 1, 0, 0)); }
        [[nodiscard]] vec4fa xxyw() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(3, 1, 0, 0)); }
        [[nodiscard]] vec4fa xxzx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 2, 0, 0)); }
        [[nodiscard]] vec4fa xxzy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(1, 2, 0, 0)); }
        [[nodiscard]] vec4fa xxzz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(2, 2, 0, 0)); }
        [[nodiscard]] vec4fa xxzw() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(3, 2, 0, 0)); }
        [[nodiscard]] vec4fa xxwx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 3, 0, 0)); }
        [[nodiscard]] vec4fa xxwy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(1, 3, 0, 0)); }
        [[nodiscard]] vec4fa xxwz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(2, 3, 0, 0)); }
        [[nodiscard]] vec4fa xxww() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(3, 3, 0, 0)); }
        [[nodiscard]] vec4fa xyxx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 0, 1, 0)); }
        [[nodiscard]] vec4fa xyxy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(1, 0, 1, 0)); }
        [[nodiscard]] vec4fa xyxz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(2, 0, 1, 0)); }
        [[nodiscard]] vec4fa xyxw() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(3, 0, 1, 0)); }
        [[nodiscard]] vec4fa xyyx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 1, 1, 0)); }
        [[nodiscard]] vec4fa xyyy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(1, 1, 1, 0)); }
        [[nodiscard]] vec4fa xyyz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(2, 1, 1, 0)); }
        [[nodiscard]] vec4fa xyyw() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(3, 1, 1, 0)); }
        [[nodiscard]] vec4fa xyzx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 2, 1, 0)); }
        [[nodiscard]] vec4fa xyzy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(1, 2, 1, 0)); }
        [[nodiscard]] vec4fa xyzz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(2, 2, 1, 0)); }
        [[nodiscard]] vec4fa xyzw() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(3, 2, 1, 0)); }
        [[nodiscard]] vec4fa xywx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 3, 1, 0)); }
        [[nodiscard]] vec4fa xywy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(1, 3, 1, 0)); }
        [[nodiscard]] vec4fa xywz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(2, 3, 1, 0)); }
        [[nodiscard]] vec4fa xyww() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(3, 3, 1, 0)); }
        [[nodiscard]] vec4fa xzxx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 0, 2, 0)); }
        [[nodiscard]] vec4fa xzxy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(1, 0, 2, 0)); }
        [[nodiscard]] vec4fa xzxz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(2, 0, 2, 0)); }
        [[nodiscard]] vec4fa xzxw() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(3, 0, 2, 0)); }
        [[nodiscard]] vec4fa xzyx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 1, 2, 0)); }
        [[nodiscard]] vec4fa xzyy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(1, 1, 2, 0)); }
        [[nodiscard]] vec4fa xzyz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(2, 1, 2, 0)); }
        [[nodiscard]] vec4fa xzyw() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(3, 1, 2, 0)); }
        [[nodiscard]] vec4fa xzzx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 2, 2, 0)); }
        [[nodiscard]] vec4fa xzzy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(1, 2, 2, 0)); }
        [[nodiscard]] vec4fa xzzz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(2, 2, 2, 0)); }
        [[nodiscard]] vec4fa xzzw() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(3, 2, 2, 0)); }
        [[nodiscard]] vec4fa xzwx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 3, 2, 0)); }
        [[nodiscard]] vec4fa xzwy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(1, 3, 2, 0)); }
        [[nodiscard]] vec4fa xzwz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(2, 3, 2, 0)); }
        [[nodiscard]] vec4fa xzww() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(3, 3, 2, 0)); }
        [[nodiscard]] vec4fa xwxx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 0, 3, 0)); }
        [[nodiscard]] vec4fa xwxy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(1, 0, 3, 0)); }
        [[nodiscard]] vec4fa xwxz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(2, 0, 3, 0)); }
        [[nodiscard]] vec4fa xwxw() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(3, 0, 3, 0)); }
        [[nodiscard]] vec4fa xwyx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 1, 3, 0)); }
        [[nodiscard]] vec4fa xwyy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(1, 1, 3, 0)); }
        [[nodiscard]] vec4fa xwyz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(2, 1, 3, 0)); }
        [[nodiscard]] vec4fa xwyw() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(3, 1, 3, 0)); }
        [[nodiscard]] vec4fa xwzx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 2, 3, 0)); }
        [[nodiscard]] vec4fa xwzy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(1, 2, 3, 0)); }
        [[nodiscard]] vec4fa xwzz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(2, 2, 3, 0)); }
        [[nodiscard]] vec4fa xwzw() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(3, 2, 3, 0)); }
        [[nodiscard]] vec4fa xwwx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 3, 3, 0)); }
        [[nodiscard]] vec4fa xwwy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(1, 3, 3, 0)); }
        [[nodiscard]] vec4fa xwwz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(2, 3, 3, 0)); }
        [[nodiscard]] vec4fa xwww() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(3, 3, 3, 0)); }
        [[nodiscard]] vec4fa yxxx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 0, 0, 1)); }
        [[nodiscard]] vec4fa yxxy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(1, 0, 0, 1)); }
        [[nodiscard]] vec4fa yxxz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(2, 0, 0, 1)); }
        [[nodiscard]] vec4fa yxxw() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(3, 0, 0, 1)); }
        [[nodiscard]] vec4fa yxyx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 1, 0, 1)); }
        [[nodiscard]] vec4fa yxyy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(1, 1, 0, 1)); }
        [[nodiscard]] vec4fa yxyz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(2, 1, 0, 1)); }
        [[nodiscard]] vec4fa yxyw() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(3, 1, 0, 1)); }
        [[nodiscard]] vec4fa yxzx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 2, 0, 1)); }
        [[nodiscard]] vec4fa yxzy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(1, 2, 0, 1)); }
        [[nodiscard]] vec4fa yxzz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(2, 2, 0, 1)); }
        [[nodiscard]] vec4fa yxzw() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(3, 2, 0, 1)); }
        [[nodiscard]] vec4fa yxwx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 3, 0, 1)); }
        [[nodiscard]] vec4fa yxwy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(1, 3, 0, 1)); }
        [[nodiscard]] vec4fa yxwz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(2, 3, 0, 1)); }
        [[nodiscard]] vec4fa yxww() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(3, 3, 0, 1)); }
        [[nodiscard]] vec4fa yyxx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 0, 1, 1)); }
        [[nodiscard]] vec4fa yyxy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(1, 0, 1, 1)); }
        [[nodiscard]] vec4fa yyxz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(2, 0, 1, 1)); }
        [[nodiscard]] vec4fa yyxw() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(3, 0, 1, 1)); }
        [[nodiscard]] vec4fa yyyx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 1, 1, 1)); }
        [[nodiscard]] vec4fa yyyy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(1, 1, 1, 1)); }
        [[nodiscard]] vec4fa yyyz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(2, 1, 1, 1)); }
        [[nodiscard]] vec4fa yyyw() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(3, 1, 1, 1)); }
        [[nodiscard]] vec4fa yyzx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 2, 1, 1)); }
        [[nodiscard]] vec4fa yyzy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(1, 2, 1, 1)); }
        [[nodiscard]] vec4fa yyzz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(2, 2, 1, 1)); }
        [[nodiscard]] vec4fa yyzw() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(3, 2, 1, 1)); }
        [[nodiscard]] vec4fa yywx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 3, 1, 1)); }
        [[nodiscard]] vec4fa yywy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(1, 3, 1, 1)); }
        [[nodiscard]] vec4fa yywz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(2, 3, 1, 1)); }
        [[nodiscard]] vec4fa yyww() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(3, 3, 1, 1)); }
        [[nodiscard]] vec4fa yzxx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 0, 2, 1)); }
        [[nodiscard]] vec4fa yzxy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(1, 0, 2, 1)); }
        [[nodiscard]] vec4fa yzxz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(2, 0, 2, 1)); }
        [[nodiscard]] vec4fa yzxw() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(3, 0, 2, 1)); }
        [[nodiscard]] vec4fa yzyx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 1, 2, 1)); }
        [[nodiscard]] vec4fa yzyy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(1, 1, 2, 1)); }
        [[nodiscard]] vec4fa yzyz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(2, 1, 2, 1)); }
        [[nodiscard]] vec4fa yzyw() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(3, 1, 2, 1)); }
        [[nodiscard]] vec4fa yzzx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 2, 2, 1)); }
        [[nodiscard]] vec4fa yzzy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(1, 2, 2, 1)); }
        [[nodiscard]] vec4fa yzzz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(2, 2, 2, 1)); }
        [[nodiscard]] vec4fa yzzw() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(3, 2, 2, 1)); }
        [[nodiscard]] vec4fa yzwx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 3, 2, 1)); }
        [[nodiscard]] vec4fa yzwy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(1, 3, 2, 1)); }
        [[nodiscard]] vec4fa yzwz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(2, 3, 2, 1)); }
        [[nodiscard]] vec4fa yzww() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(3, 3, 2, 1)); }
        [[nodiscard]] vec4fa ywxx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 0, 3, 1)); }
        [[nodiscard]] vec4fa ywxy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(1, 0, 3, 1)); }
        [[nodiscard]] vec4fa ywxz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(2, 0, 3, 1)); }
        [[nodiscard]] vec4fa ywxw() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(3, 0, 3, 1)); }
        [[nodiscard]] vec4fa ywyx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 1, 3, 1)); }
        [[nodiscard]] vec4fa ywyy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(1, 1, 3, 1)); }
        [[nodiscard]] vec4fa ywyz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(2, 1, 3, 1)); }
        [[nodiscard]] vec4fa ywyw() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(3, 1, 3, 1)); }
        [[nodiscard]] vec4fa ywzx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 2, 3, 1)); }
        [[nodiscard]] vec4fa ywzy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(1, 2, 3, 1)); }
        [[nodiscard]] vec4fa ywzz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(2, 2, 3, 1)); }
        [[nodiscard]] vec4fa ywzw() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(3, 2, 3, 1)); }
        [[nodiscard]] vec4fa ywwx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 3, 3, 1)); }
        [[nodiscard]] vec4fa ywwy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(1, 3, 3, 1)); }
        [[nodiscard]] vec4fa ywwz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(2, 3, 3, 1)); }
        [[nodiscard]] vec4fa ywww() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(3, 3, 3, 1)); }
        [[nodiscard]] vec4fa zxxx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 0, 0, 2)); }
        [[nodiscard]] vec4fa zxxy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(1, 0, 0, 2)); }
        [[nodiscard]] vec4fa zxxz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(2, 0, 0, 2)); }
        [[nodiscard]] vec4fa zxxw() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(3, 0, 0, 2)); }
        [[nodiscard]] vec4fa zxyx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 1, 0, 2)); }
        [[nodiscard]] vec4fa zxyy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(1, 1, 0, 2)); }
        [[nodiscard]] vec4fa zxyz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(2, 1, 0, 2)); }
        [[nodiscard]] vec4fa zxyw() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(3, 1, 0, 2)); }
        [[nodiscard]] vec4fa zxzx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 2, 0, 2)); }
        [[nodiscard]] vec4fa zxzy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(1, 2, 0, 2)); }
        [[nodiscard]] vec4fa zxzz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(2, 2, 0, 2)); }
        [[nodiscard]] vec4fa zxzw() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(3, 2, 0, 2)); }
        [[nodiscard]] vec4fa zxwx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 3, 0, 2)); }
        [[nodiscard]] vec4fa zxwy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(1, 3, 0, 2)); }
        [[nodiscard]] vec4fa zxwz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(2, 3, 0, 2)); }
        [[nodiscard]] vec4fa zxww() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(3, 3, 0, 2)); }
        [[nodiscard]] vec4fa zyxx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 0, 1, 2)); }
        [[nodiscard]] vec4fa zyxy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(1, 0, 1, 2)); }
        [[nodiscard]] vec4fa zyxz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(2, 0, 1, 2)); }
        [[nodiscard]] vec4fa zyxw() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(3, 0, 1, 2)); }
        [[nodiscard]] vec4fa zyyx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 1, 1, 2)); }
        [[nodiscard]] vec4fa zyyy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(1, 1, 1, 2)); }
        [[nodiscard]] vec4fa zyyz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(2, 1, 1, 2)); }
        [[nodiscard]] vec4fa zyyw() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(3, 1, 1, 2)); }
        [[nodiscard]] vec4fa zyzx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 2, 1, 2)); }
        [[nodiscard]] vec4fa zyzy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(1, 2, 1, 2)); }
        [[nodiscard]] vec4fa zyzz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(2, 2, 1, 2)); }
        [[nodiscard]] vec4fa zyzw() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(3, 2, 1, 2)); }
        [[nodiscard]] vec4fa zywx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 3, 1, 2)); }
        [[nodiscard]] vec4fa zywy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(1, 3, 1, 2)); }
        [[nodiscard]] vec4fa zywz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(2, 3, 1, 2)); }
        [[nodiscard]] vec4fa zyww() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(3, 3, 1, 2)); }
        [[nodiscard]] vec4fa zzxx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 0, 2, 2)); }
        [[nodiscard]] vec4fa zzxy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(1, 0, 2, 2)); }
        [[nodiscard]] vec4fa zzxz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(2, 0, 2, 2)); }
        [[nodiscard]] vec4fa zzxw() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(3, 0, 2, 2)); }
        [[nodiscard]] vec4fa zzyx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 1, 2, 2)); }
        [[nodiscard]] vec4fa zzyy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(1, 1, 2, 2)); }
        [[nodiscard]] vec4fa zzyz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(2, 1, 2, 2)); }
        [[nodiscard]] vec4fa zzyw() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(3, 1, 2, 2)); }
        [[nodiscard]] vec4fa zzzx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 2, 2, 2)); }
        [[nodiscard]] vec4fa zzzy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(1, 2, 2, 2)); }
        [[nodiscard]] vec4fa zzzz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(2, 2, 2, 2)); }
        [[nodiscard]] vec4fa zzzw() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(3, 2, 2, 2)); }
        [[nodiscard]] vec4fa zzwx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 3, 2, 2)); }
        [[nodiscard]] vec4fa zzwy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(1, 3, 2, 2)); }
        [[nodiscard]] vec4fa zzwz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(2, 3, 2, 2)); }
        [[nodiscard]] vec4fa zzww() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(3, 3, 2, 2)); }
        [[nodiscard]] vec4fa zwxx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 0, 3, 2)); }
        [[nodiscard]] vec4fa zwxy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(1, 0, 3, 2)); }
        [[nodiscard]] vec4fa zwxz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(2, 0, 3, 2)); }
        [[nodiscard]] vec4fa zwxw() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(3, 0, 3, 2)); }
        [[nodiscard]] vec4fa zwyx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 1, 3, 2)); }
        [[nodiscard]] vec4fa zwyy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(1, 1, 3, 2)); }
        [[nodiscard]] vec4fa zwyz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(2, 1, 3, 2)); }
        [[nodiscard]] vec4fa zwyw() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(3, 1, 3, 2)); }
        [[nodiscard]] vec4fa zwzx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 2, 3, 2)); }
        [[nodiscard]] vec4fa zwzy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(1, 2, 3, 2)); }
        [[nodiscard]] vec4fa zwzz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(2, 2, 3, 2)); }
        [[nodiscard]] vec4fa zwzw() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(3, 2, 3, 2)); }
        [[nodiscard]] vec4fa zwwx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 3, 3, 2)); }
        [[nodiscard]] vec4fa zwwy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(1, 3, 3, 2)); }
        [[nodiscard]] vec4fa zwwz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(2, 3, 3, 2)); }
        [[nodiscard]] vec4fa zwww() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(3, 3, 3, 2)); }
        [[nodiscard]] vec4fa wxxx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 0, 0, 3)); }
        [[nodiscard]] vec4fa wxxy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(1, 0, 0, 3)); }
        [[nodiscard]] vec4fa wxxz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(2, 0, 0, 3)); }
        [[nodiscard]] vec4fa wxxw() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(3, 0, 0, 3)); }
        [[nodiscard]] vec4fa wxyx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 1, 0, 3)); }
        [[nodiscard]] vec4fa wxyy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(1, 1, 0, 3)); }
        [[nodiscard]] vec4fa wxyz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(2, 1, 0, 3)); }
        [[nodiscard]] vec4fa wxyw() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(3, 1, 0, 3)); }
        [[nodiscard]] vec4fa wxzx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 2, 0, 3)); }
        [[nodiscard]] vec4fa wxzy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(1, 2, 0, 3)); }
        [[nodiscard]] vec4fa wxzz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(2, 2, 0, 3)); }
        [[nodiscard]] vec4fa wxzw() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(3, 2, 0, 3)); }
        [[nodiscard]] vec4fa wxwx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 3, 0, 3)); }
        [[nodiscard]] vec4fa wxwy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(1, 3, 0, 3)); }
        [[nodiscard]] vec4fa wxwz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(2, 3, 0, 3)); }
        [[nodiscard]] vec4fa wxww() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(3, 3, 0, 3)); }
        [[nodiscard]] vec4fa wyxx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 0, 1, 3)); }
        [[nodiscard]] vec4fa wyxy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(1, 0, 1, 3)); }
        [[nodiscard]] vec4fa wyxz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(2, 0, 1, 3)); }
        [[nodiscard]] vec4fa wyxw() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(3, 0, 1, 3)); }
        [[nodiscard]] vec4fa wyyx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 1, 1, 3)); }
        [[nodiscard]] vec4fa wyyy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(1, 1, 1, 3)); }
        [[nodiscard]] vec4fa wyyz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(2, 1, 1, 3)); }
        [[nodiscard]] vec4fa wyyw() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(3, 1, 1, 3)); }
        [[nodiscard]] vec4fa wyzx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 2, 1, 3)); }
        [[nodiscard]] vec4fa wyzy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(1, 2, 1, 3)); }
        [[nodiscard]] vec4fa wyzz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(2, 2, 1, 3)); }
        [[nodiscard]] vec4fa wyzw() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(3, 2, 1, 3)); }
        [[nodiscard]] vec4fa wywx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 3, 1, 3)); }
        [[nodiscard]] vec4fa wywy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(1, 3, 1, 3)); }
        [[nodiscard]] vec4fa wywz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(2, 3, 1, 3)); }
        [[nodiscard]] vec4fa wyww() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(3, 3, 1, 3)); }
        [[nodiscard]] vec4fa wzxx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 0, 2, 3)); }
        [[nodiscard]] vec4fa wzxy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(1, 0, 2, 3)); }
        [[nodiscard]] vec4fa wzxz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(2, 0, 2, 3)); }
        [[nodiscard]] vec4fa wzxw() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(3, 0, 2, 3)); }
        [[nodiscard]] vec4fa wzyx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 1, 2, 3)); }
        [[nodiscard]] vec4fa wzyy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(1, 1, 2, 3)); }
        [[nodiscard]] vec4fa wzyz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(2, 1, 2, 3)); }
        [[nodiscard]] vec4fa wzyw() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(3, 1, 2, 3)); }
        [[nodiscard]] vec4fa wzzx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 2, 2, 3)); }
        [[nodiscard]] vec4fa wzzy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(1, 2, 2, 3)); }
        [[nodiscard]] vec4fa wzzz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(2, 2, 2, 3)); }
        [[nodiscard]] vec4fa wzzw() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(3, 2, 2, 3)); }
        [[nodiscard]] vec4fa wzwx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 3, 2, 3)); }
        [[nodiscard]] vec4fa wzwy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(1, 3, 2, 3)); }
        [[nodiscard]] vec4fa wzwz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(2, 3, 2, 3)); }
        [[nodiscard]] vec4fa wzww() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(3, 3, 2, 3)); }
        [[nodiscard]] vec4fa wwxx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 0, 3, 3)); }
        [[nodiscard]] vec4fa wwxy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(1, 0, 3, 3)); }
        [[nodiscard]] vec4fa wwxz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(2, 0, 3, 3)); }
        [[nodiscard]] vec4fa wwxw() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(3, 0, 3, 3)); }
        [[nodiscard]] vec4fa wwyx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 1, 3, 3)); }
        [[nodiscard]] vec4fa wwyy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(1, 1, 3, 3)); }
        [[nodiscard]] vec4fa wwyz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(2, 1, 3, 3)); }
        [[nodiscard]] vec4fa wwyw() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(3, 1, 3, 3)); }
        [[nodiscard]] vec4fa wwzx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 2, 3, 3)); }
        [[nodiscard]] vec4fa wwzy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(1, 2, 3, 3)); }
        [[nodiscard]] vec4fa wwzz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(2, 2, 3, 3)); }
        [[nodiscard]] vec4fa wwzw() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(3, 2, 3, 3)); }
        [[nodiscard]] vec4fa wwwx() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(0, 3, 3, 3)); }
        [[nodiscard]] vec4fa wwwy() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(1, 3, 3, 3)); }
        [[nodiscard]] vec4fa wwwz() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(2, 3, 3, 3)); }
        [[nodiscard]] vec4fa wwww() const noexcept { return _mm_permute_ps(m128, _MM_SHUFFLE(3, 3, 3, 3)); }
#endif
    };

    ////////////////////////////////////////////////////////////////
    // Shuffle.
    ////////////////////////////////////////////////////////////////

#ifdef __AVX__
    template<int32_t i0, int32_t i1, int32_t i2, int32_t i3>
    vec4fa shuffle(const vec4fa& v) noexcept { return _mm_permute_ps(v, _MM_SHUFFLE(i3, i2, i1, i0)); }
#endif

    ////////////////////////////////////////////////////////////////
    // Arithmetic operators.
    ////////////////////////////////////////////////////////////////

    [[nodiscard]] inline vec4fa operator+(const vec4fa& lhs, const vec4fa& rhs) noexcept { return _mm_add_ps(lhs, rhs); }

    [[nodiscard]] inline vec4fa operator+(const vec4fa& lhs, const float rhs) noexcept { return lhs + vec4fa(rhs); }

    [[nodiscard]] inline vec4fa operator+(const float lhs, const vec4fa& rhs) noexcept { return vec4fa(lhs) + rhs; }

    [[nodiscard]] inline vec4fa operator-(const vec4fa& lhs, const vec4fa& rhs) noexcept { return _mm_sub_ps(lhs, rhs); }

    [[nodiscard]] inline vec4fa operator-(const vec4fa& lhs, const float rhs) noexcept { return lhs - vec4fa(rhs); }

    [[nodiscard]] inline vec4fa operator-(const float lhs, const vec4fa& rhs) noexcept { return vec4fa(lhs) - rhs; }

    [[nodiscard]] inline vec4fa operator-(const vec4fa& lhs) noexcept { const __m128 mask = _mm_castsi128_ps(_mm_set1_epi32(0x80000000)); return _mm_xor_ps(lhs, mask); }

    [[nodiscard]] inline vec4fa operator*(const vec4fa& lhs, const vec4fa& rhs) noexcept { return _mm_mul_ps(lhs, rhs); }

    [[nodiscard]] inline vec4fa operator*(const vec4fa& lhs, const float rhs) noexcept { return lhs * vec4fa(rhs); }

    [[nodiscard]] inline vec4fa operator*(const float lhs, const vec4fa& rhs) noexcept { return vec4fa(lhs) * rhs; }

    [[nodiscard]] inline vec4fa operator/(const vec4fa& lhs, const vec4fa& rhs) noexcept { return _mm_div_ps(lhs, rhs); }

    [[nodiscard]] inline vec4fa operator/(const vec4fa& lhs, const float rhs) noexcept { return lhs / vec4fa(rhs); }

    [[nodiscard]] inline vec4fa operator/(const float lhs, const vec4fa& rhs) noexcept { return vec4fa(lhs) / rhs; }

    inline vec4fa& operator+=(vec4fa& lhs, const vec4fa& rhs) noexcept { return lhs = lhs + rhs; }

    inline vec4fa& operator+=(vec4fa& lhs, const float rhs) noexcept { return lhs = lhs + rhs; }

    inline vec4fa& operator-=(vec4fa& lhs, const vec4fa& rhs) noexcept { return lhs = lhs - rhs; }

    inline vec4fa& operator-=(vec4fa& lhs, const float rhs) noexcept { return lhs = lhs - rhs; }

    inline vec4fa& operator*=(vec4fa& lhs, const vec4fa& rhs) noexcept { return lhs = lhs * rhs; }

    inline vec4fa& operator*=(vec4fa& lhs, const float rhs) noexcept { return lhs = lhs * rhs; }

    inline vec4fa& operator/=(vec4fa& lhs, const vec4fa& rhs) noexcept { return lhs = lhs / rhs; }

    inline vec4fa& operator/=(vec4fa& lhs, const float rhs) noexcept { return lhs = lhs / rhs; }

    ////////////////////////////////////////////////////////////////
    // Comparison operators.
    ////////////////////////////////////////////////////////////////

    [[nodiscard]] inline bool operator==(const vec4fa& lhs, const vec4fa& rhs) noexcept { return (_mm_movemask_ps(_mm_cmpeq_ps(lhs, rhs)) & 0x15) == 0x15; }

    [[nodiscard]] inline bool operator!=(const vec4fa& lhs, const vec4fa& rhs) noexcept { return (_mm_movemask_ps(_mm_cmpeq_ps(lhs, rhs)) & 0x15) != 0x15; }

    ////////////////////////////////////////////////////////////////
    // Per-element comparisons.
    ////////////////////////////////////////////////////////////////

    [[nodiscard]] inline vec4ba cmpeq(const vec4fa& lhs, const vec4fa& rhs) noexcept { return vec4ba(_mm_cmpeq_ps(lhs, rhs)); }

    [[nodiscard]] inline vec4ba cmpeq(const vec4fa& lhs, const float rhs) noexcept { return cmpeq(lhs, vec4fa(rhs)); }

    [[nodiscard]] inline vec4ba cmpeq(const float lhs, const vec4fa& rhs) noexcept { return cmpeq(vec4fa(lhs), rhs); }

    [[nodiscard]] inline vec4ba cmpneq(const vec4fa& lhs, const vec4fa& rhs) noexcept { return vec4ba(_mm_cmpneq_ps(lhs, rhs)); }

    [[nodiscard]] inline vec4ba cmpneq(const vec4fa& lhs, const float rhs) noexcept { return cmpneq(lhs, vec4fa(rhs)); }

    [[nodiscard]] inline vec4ba cmpneq(const float lhs, const vec4fa& rhs) noexcept { return cmpneq(vec4fa(lhs), rhs); }

    [[nodiscard]] inline vec4ba cmplt(const vec4fa& lhs, const vec4fa& rhs) noexcept { return vec4ba(_mm_cmplt_ps(lhs, rhs)); }

    [[nodiscard]] inline vec4ba cmplt(const vec4fa& lhs, const float rhs) noexcept { return cmplt(lhs, vec4fa(rhs)); }

    [[nodiscard]] inline vec4ba cmplt(const float lhs, const vec4fa& rhs) noexcept { return cmplt(vec4fa(lhs), rhs); }

    [[nodiscard]] inline vec4ba cmpgt(const vec4fa& lhs, const vec4fa& rhs) noexcept { return vec4ba(_mm_cmpgt_ps(lhs, rhs)); }

    [[nodiscard]] inline vec4ba cmpgt(const vec4fa& lhs, const float rhs) noexcept { return cmpgt(lhs, vec4fa(rhs)); }

    [[nodiscard]] inline vec4ba cmpgt(const float lhs, const vec4fa& rhs) noexcept { return cmpgt(vec4fa(lhs), rhs); }

    [[nodiscard]] inline vec4ba cmple(const vec4fa& lhs, const vec4fa& rhs) noexcept { return vec4ba(_mm_cmple_ps(lhs, rhs)); }

    [[nodiscard]] inline vec4ba cmple(const vec4fa& lhs, const float rhs) noexcept { return cmple(lhs, vec4fa(rhs)); }

    [[nodiscard]] inline vec4ba cmple(const float lhs, const vec4fa& rhs) noexcept { return cmple(vec4fa(lhs), rhs); }

    [[nodiscard]] inline vec4ba cmpge(const vec4fa& lhs, const vec4fa& rhs) noexcept { return vec4ba(_mm_cmpge_ps(lhs, rhs)); }

    [[nodiscard]] inline vec4ba cmpge(const vec4fa& lhs, const float rhs) noexcept { return cmpge(lhs, vec4fa(rhs)); }

    [[nodiscard]] inline vec4ba cmpge(const float lhs, const vec4fa& rhs) noexcept { return cmpge(vec4fa(lhs), rhs); }

    ////////////////////////////////////////////////////////////////
    // Min/max, abs and clamp.
    ////////////////////////////////////////////////////////////////

    [[nodiscard]] inline vec4fa min(const vec4fa& lhs, const vec4fa& rhs) noexcept { return _mm_min_ps(lhs, rhs); }

    [[nodiscard]] inline vec4fa min(const vec4fa& lhs, const float rhs) noexcept { return min(lhs, vec4fa(rhs)); }

    [[nodiscard]] inline vec4fa min(const float lhs, const vec4fa& rhs) noexcept { return min(vec4fa(lhs), rhs); }

    [[nodiscard]] inline vec4fa max(const vec4fa& lhs, const vec4fa& rhs) noexcept { return _mm_max_ps(lhs, rhs); }

    [[nodiscard]] inline vec4fa max(const vec4fa& lhs, const float rhs) noexcept { return max(lhs, vec4fa(rhs)); }

    [[nodiscard]] inline vec4fa max(const float lhs, const vec4fa& rhs) noexcept { return max(vec4fa(lhs), rhs); }

    [[nodiscard]] inline vec4fa clamp(const vec4fa& a, const vec4fa& min, const vec4fa& max) noexcept { return math::max(min, math::min(a, max)); }

    [[nodiscard]] inline vec4fa clamp(const vec4fa& a, const vec4fa& min, const float max) noexcept { return clamp(a, min, vec4fa(max)); }

    [[nodiscard]] inline vec4fa clamp(const vec4fa& a, const float min, const vec4fa& max) noexcept { return clamp(a, vec4fa(min), max); }

    [[nodiscard]] inline vec4fa clamp(const vec4fa& a, const float min, const float max) noexcept { return clamp(a, vec4fa(min), vec4fa(max)); }

    ////////////////////////////////////////////////////////////////
    // Reduction.
    ////////////////////////////////////////////////////////////////

    [[nodiscard]] inline float reduce_add(const vec4fa& lhs) noexcept
    {
        const vec4fa zw = lhs.zwxx();
        const vec4fa sum1 = lhs + zw;
        const vec4fa sum = sum1 + sum1.yxxx();
        return _mm_cvtss_f32(sum);
    }

    [[nodiscard]] inline float reduce_mul(const vec4fa& lhs) noexcept
    {
        const vec4fa zw = lhs.zwxx();
        const vec4fa sum1 = lhs * zw;
        const vec4fa sum = sum1 * sum1.yxxx();
        return _mm_cvtss_f32(sum);
    }

    [[nodiscard]] inline float reduce_min(const vec4fa& lhs) noexcept
    {
        const vec4fa zw = lhs.zwxx();
        const vec4fa sum1 = min(lhs, zw);
        const vec4fa sum = min(sum1, sum1.yxxx());
        return _mm_cvtss_f32(sum);
    }

    [[nodiscard]] inline float reduce_max(const vec4fa& lhs) noexcept
    {
        const vec4fa zw = lhs.zwxx();
        const vec4fa sum1 = max(lhs, zw);
        const vec4fa sum = max(sum1, sum1.yxxx());
        return _mm_cvtss_f32(sum);
    }

    ////////////////////////////////////////////////////////////////
    // Multiply and add.
    ////////////////////////////////////////////////////////////////

    [[nodiscard]] inline vec4fa madd(const vec4fa& a, const vec4fa& b, const vec4fa& c) noexcept
    {
#ifdef __FMA__
        return _mm_fmadd_ps(a, b, c);
#else
        return a * b + c;
#endif
    }

    [[nodiscard]] inline vec4fa nmadd(const vec4fa& a, const vec4fa& b, const vec4fa& c) noexcept
    {
#ifdef __FMA__
        return _mm_fnmadd_ps(a, b, c);
#else
        return -a * b + c;
#endif
    }

    [[nodiscard]] inline vec4fa msub(const vec4fa& a, const vec4fa& b, const vec4fa& c) noexcept
    {
#ifdef __FMA__
        return _mm_fmsub_ps(a, b, c);
#else
        return a * b - c;
#endif
    }

    [[nodiscard]] inline vec4fa nmsub(const vec4fa& a, const vec4fa& b, const vec4fa& c) noexcept
    {
#ifdef __FMA__
        return _mm_fnmsub_ps(a, b, c);
#else
        return -a * b - c;
#endif
    }

    ////////////////////////////////////////////////////////////////
    // Dot product etc.
    ////////////////////////////////////////////////////////////////

    [[nodiscard]] inline float dot(const vec4fa& lhs, const vec4fa& rhs) noexcept
    {
#ifdef __SSE4_1__
        return _mm_cvtss_f32(_mm_dp_ps(lhs, rhs, 0xFF));
#else
        return reduce_add(lhs * rhs);
#endif
    }

    [[nodiscard]] inline float length(const vec4fa& lhs) noexcept { return sqrt(dot(lhs, lhs)); }

    [[nodiscard]] inline float sqr_length(const vec4fa& lhs) noexcept { return dot(lhs, lhs); }

    [[nodiscard]] inline float rcp_length(const vec4fa& lhs) noexcept { return rsqrt(dot(lhs, lhs)); }

    [[nodiscard]] inline vec4fa normalize(const vec4fa& lhs) noexcept { return lhs * rcp_length(lhs); }

    [[nodiscard]] inline vec4fa normalize(const vec4fa& lhs, float& length) noexcept { length = math::length(lhs); return lhs / length; }

    [[nodiscard]] inline float distance(const vec4fa& lhs, const vec4fa& rhs) noexcept { return length(lhs - rhs); }

    [[nodiscard]] inline vec4fa lerp(const vec4fa& a, const vec4fa& b, const vec4fa& t) noexcept { return madd(t, b - a, a); }

    [[nodiscard]] inline vec4fa lerp(const vec4fa& a, const vec4fa& b, const float t) noexcept { return madd(vec4fa(t), b - a, a); }

    ////////////////////////////////////////////////////////////////
    // Trigonometry.
    ////////////////////////////////////////////////////////////////

    [[nodiscard]] inline vec4fa acos(const vec4fa& lhs) noexcept { return vec4fa(acos(lhs.x), acos(lhs.y), acos(lhs.z), acos(lhs.w)); }

    [[nodiscard]] inline vec4fa asin(const vec4fa& lhs) noexcept { return vec4fa(asin(lhs.x), asin(lhs.y), asin(lhs.z), asin(lhs.w)); }

    [[nodiscard]] inline vec4fa atan(const vec4fa& lhs) noexcept { return vec4fa(atan(lhs.x), atan(lhs.y), atan(lhs.z), atan(lhs.w)); }

    [[nodiscard]] inline vec4fa atan2(const vec4fa& lhs, const vec4fa& rhs) noexcept { return vec4fa(atan2(lhs.x, rhs.x), atan2(lhs.y, rhs.y), atan2(lhs.z, rhs.z), atan2(lhs.w, rhs.w)); }

    [[nodiscard]] inline vec4fa cos(const vec4fa& lhs) noexcept { return vec4fa(cos(lhs.x), cos(lhs.y), cos(lhs.z), cos(lhs.w)); }

    [[nodiscard]] inline vec4fa cosh(const vec4fa& lhs) noexcept { return vec4fa(cosh(lhs.x), cosh(lhs.y), cosh(lhs.z), cosh(lhs.w)); }

    [[nodiscard]] inline vec4fa sin(const vec4fa& lhs) noexcept { return vec4fa(sin(lhs.x), sin(lhs.y), sin(lhs.z), sin(lhs.w)); }

    [[nodiscard]] inline vec4fa sinh(const vec4fa& lhs) noexcept { return vec4fa(sinh(lhs.x), sinh(lhs.y), sinh(lhs.z), sinh(lhs.w)); }

    [[nodiscard]] inline vec4fa tan(const vec4fa& lhs) noexcept { return vec4fa(tan(lhs.x), tan(lhs.y), tan(lhs.z), tan(lhs.w)); }

    [[nodiscard]] inline vec4fa tanh(const vec4fa& lhs) noexcept { return vec4fa(tanh(lhs.x), tanh(lhs.y), tanh(lhs.z), tanh(lhs.w)); }

    ////////////////////////////////////////////////////////////////
    // Exponential / Logarithmic.
    ////////////////////////////////////////////////////////////////

    template<size_t Precision = 5>
    [[nodiscard]] vec4fa exp2(const vec4fa& lhs) noexcept
    {
        static_assert(Precision >= 2 && Precision <= 5, "Provided precision is outside of supported range.");

        // Based on http://jrfonseca.blogspot.com/2008/09/fast-sse2-pow-tables-or-polynomials.html.
        const vec4fa x = clamp(lhs, -126.99999f, 129.00000f);
        const __m128i ipart = _mm_cvtps_epi32(x - 0.5f);
        const vec4fa fpart = x - _mm_cvtepi32_ps(ipart);
        const vec4fa expipart = _mm_castsi128_ps(_mm_slli_epi32(_mm_add_epi32(ipart, _mm_set1_epi32(127)), 23));

        vec4fa expfpart;
        if constexpr (Precision == 5)
            expfpart = foldpoly(fpart, 9.9999994e-1f, 6.9315308e-1f, 2.4015361e-1f, 5.5826318e-2f, 8.9893397e-3f, 1.8775767e-3f);
        else if constexpr (Precision == 4)
            expfpart = foldpoly(fpart, 1.0000026f, 6.9300383e-1f, 2.4144275e-1f, 5.2011464e-2f, 1.3534167e-2f);
        else if constexpr (Precision == 3)
            expfpart = foldpoly(fpart, 9.9992520e-1f, 6.9583356e-1f, 2.2606716e-1f, 7.8024521e-2f);
        else if constexpr (Precision == 2)
            expfpart = foldpoly(fpart, 1.0017247f, 6.5763628e-1f, 3.3718944e-1f);

        return expipart * expfpart;
    }

    template<size_t Precision = 5>
    [[nodiscard]] vec4fa log2(const vec4fa& lhs) noexcept
    {
        static_assert(Precision >= 2 && Precision <= 5, "Provided precision is outside of supported range.");

        const __m128i expmask = _mm_set1_epi32(0x7F800000);
        const __m128i mantmask = _mm_set1_epi32(0x007FFFFF);
        const vec4fa one = math::one<vec4fa>();

        const __m128i i = _mm_castps_si128(lhs);
        const vec4fa exp = _mm_cvtepi32_ps(_mm_sub_epi32(_mm_srli_epi32(_mm_and_si128(i, expmask), 23), _mm_set1_epi32(127)));

        const vec4fa mant = _mm_or_ps(_mm_castsi128_ps(_mm_and_si128(i, mantmask)), one);

        vec4fa p;
        if constexpr (Precision == 5)
            p = foldpoly(mant, 3.1157899f, -3.3241990f, 2.5988452f, -1.2315303f, 3.1821337e-1f, -3.4436006e-2f);
        else if constexpr (Precision == 4)
            p = foldpoly(mant, 2.8882704548164776201f, -2.52074962577807006663f, 1.48116647521213171641f, -0.465725644288844778798f, 0.0596515482674574969533f);
        else if constexpr (Precision == 3)
            p = foldpoly(mant, 2.61761038894603480148f, -1.75647175389045657003f, 0.688243882994381274313f, -0.107254423828329604454f);
        else if constexpr (Precision == 2)
            p = foldpoly(mant, 2.28330284476918490682f, -1.04913055217340124191f, 0.204446009836232697516f);

        return p * (mant - one) + exp;
    }

    template<size_t Precision = 5>
    [[nodiscard]] vec4fa exp(const vec4fa& lhs) noexcept { return exp2<Precision>(lhs * log2<Precision>(vec4fa(m_e))); }

    template<size_t Precision = 5>
    [[nodiscard]] vec4fa log(const vec4fa& lhs) noexcept { return log2<Precision>(lhs) / log2<Precision>(vec4fa(m_e)); }

    template<size_t Precision = 5>
    [[nodiscard]] vec4fa log10(const vec4fa& lhs) noexcept { return log2<Precision>(lhs) / log2<Precision>(vec4fa(10.0f)); }

    ////////////////////////////////////////////////////////////////
    // Power.
    ////////////////////////////////////////////////////////////////

    template<size_t Precision = 5>
    [[nodiscard]] vec4fa pow(const vec4fa& lhs, const vec4fa& rhs) noexcept { return exp2<Precision>(rhs * log2<Precision>(lhs)); }

    template<size_t Precision = 5>
    [[nodiscard]] vec4fa pow(const vec4fa& lhs, const float rhs) noexcept { return exp2<Precision>(vec4fa(rhs) * log2<Precision>(lhs)); }

    template<size_t Precision = 5>
    [[nodiscard]] vec4fa pow(const float lhs, const vec4fa& rhs) noexcept { return exp2<Precision>(rhs * log2<Precision>(vec4fa(lhs))); }

    [[nodiscard]] inline vec4fa sqr(const vec4fa& lhs) noexcept { return lhs * lhs; }

    [[nodiscard]] inline vec4fa sqrt(const vec4fa& lhs) noexcept { return _mm_sqrt_ps(lhs); }

    [[nodiscard]] inline vec4fa rsqrt(const vec4fa& lhs) noexcept { return _mm_rsqrt_ps(lhs); }

    ////////////////////////////////////////////////////////////////
    // Rounding, abs, etc.
    ////////////////////////////////////////////////////////////////

    [[nodiscard]] inline vec4fa abs(const vec4fa& lhs) noexcept
    {
        const __m128 mask = _mm_castsi128_ps(_mm_set1_epi32(0x7fffffff));
        return _mm_and_ps(lhs, mask);
    }

#ifdef __SSE4_1__
    [[nodiscard]] inline vec4fa round(const vec4fa& lhs) noexcept { return _mm_round_ps(lhs, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC); }

    [[nodiscard]] inline vec4fa ceil(const vec4fa& lhs) noexcept { return _mm_round_ps(lhs, _MM_FROUND_CEIL); }

    [[nodiscard]] inline vec4fa floor(const vec4fa& lhs) noexcept { return _mm_round_ps(lhs, _MM_FROUND_FLOOR); }

    [[nodiscard]] inline vec4fa frac(const vec4fa& lhs) noexcept { return _mm_sub_ps(lhs, _mm_round_ps(lhs, _MM_FROUND_TRUNC)); }

    [[nodiscard]] inline vec4fa trunc(const vec4fa& lhs) noexcept { return _mm_round_ps(lhs, _MM_FROUND_TRUNC); }
#endif

    ////////////////////////////////////////////////////////////////
    // Select.
    ////////////////////////////////////////////////////////////////

    [[nodiscard]] inline vec4fa select(const vec4fa& t, const vec4fa& f, const vec4ba& b) noexcept
    {
#ifdef __SSE4_1__
        return _mm_blendv_ps(f, t, _mm_castsi128_ps(b));
#else
        return vec4fa(math::select(t.x, f.x, b.x & 0x80000000), math::select(t.y, f.y, b.y & 0x80000000), math::select(t.z, f.z, b.z & 0x80000000), math::select(t.w, f.w, b.w & 0x80000000));
#endif
    }

    ////////////////////////////////////////////////////////////////
    // Output.
    ////////////////////////////////////////////////////////////////

    inline std::ostream& operator<<(std::ostream& out, const vec4fa& v) { return out << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")"; }

}
