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

#include "math/vector/simd/vec3ba.h"
#include "math/vector/simd/vec4ia.h"

namespace math
{
    struct alignas(16) vec3ia
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

        [[nodiscard]] vec3ia() noexcept : m128(_mm_set1_epi32(0)) {}

        [[nodiscard]] explicit vec3ia(const int32_t v) noexcept : m128(_mm_set1_epi32(v)) {}

        [[nodiscard]] vec3ia(const int32_t x, const int32_t y, const int32_t z) noexcept : m128(_mm_setr_epi32(x, y, z, 0)) {}

        [[nodiscard]] vec3ia(const int32_t x, const int32_t y, const int32_t z, const int32_t w) noexcept : m128(_mm_setr_epi32(x, y, z, w)) {}

        [[nodiscard]] vec3ia(const __m128i m128) noexcept : m128(m128) {}

        [[nodiscard]] explicit vec3ia(const __m128 m128) noexcept : m128(_mm_castps_si128(m128)) {}

        [[nodiscard]] vec3ia(const vec3ia& rhs) noexcept : m128(rhs.m128) {}

        [[nodiscard]] explicit vec3ia(const vec<int32_t, 3>& rhs) noexcept : m128(_mm_setr_epi32(rhs.x, rhs.y, rhs.z, 0)) {}

        ////////////////////////////////////////////////////////////////
        // Assignment operators.
        ////////////////////////////////////////////////////////////////

        vec3ia& operator=(const vec3ia& rhs) noexcept { m128 = rhs.m128; return *this; }

        vec3ia& operator=(const vec4ia& rhs) noexcept { m128 = rhs.m128; return *this; }

        vec3ia& operator=(const int32_t rhs) noexcept { m128 = _mm_set1_epi32(rhs); return *this; }

        ////////////////////////////////////////////////////////////////
        // Load/store.
        ////////////////////////////////////////////////////////////////

        [[nodiscard]] static vec3ia load(const void* const ptr) { return vec3ia(_mm_load_si128(static_cast<const __m128i*>(ptr))); }

        [[nodiscard]] static vec3ia loadu(const void* const ptr) { return vec3ia(_mm_loadu_si128(static_cast<const __m128i*>(ptr))); }

        static void store(void* ptr, const vec3ia & v) { _mm_store_si128(static_cast<__m128i*>(ptr), v.m128); }

        static void storeu(void* ptr, const vec3ia & v) { _mm_storeu_si128(static_cast<__m128i*>(ptr), v.m128); }

        ////////////////////////////////////////////////////////////////
        // Defaulted constructors and operators.
        ////////////////////////////////////////////////////////////////

        ~vec3ia() noexcept = default;

        vec3ia(vec3ia&& rhs) noexcept = default;

        vec3ia& operator=(vec3ia&& rhs) noexcept = default;

        ////////////////////////////////////////////////////////////////
        // Casting operators.
        ////////////////////////////////////////////////////////////////

        [[nodiscard]] operator const __m128i& () const noexcept { return m128; }

        [[nodiscard]] operator __m128i& () noexcept { return m128; }

        [[nodiscard]] explicit operator __m128 () const noexcept { return _mm_castsi128_ps(m128); }

        [[nodiscard]] explicit operator vec<int32_t, 3>() const noexcept { return vec<int32_t, 3>(x, y, z); }

        ////////////////////////////////////////////////////////////////
        // Element access.
        ////////////////////////////////////////////////////////////////

        [[nodiscard]] const int32_t& operator[](const size_t i) const { assert(i < 3); return (&x)[i]; }

        [[nodiscard]] int32_t& operator[](const size_t i) { assert(i < 3); return (&x)[i]; }

        ////////////////////////////////////////////////////////////////
        // Swizzling.
        ////////////////////////////////////////////////////////////////

#ifdef __AVX__
        [[nodiscard]] vec3ia xxx() const noexcept { return vec3ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 0, 0, 0))); }
        [[nodiscard]] vec3ia xxy() const noexcept { return vec3ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 1, 0, 0))); }
        [[nodiscard]] vec3ia xxz() const noexcept { return vec3ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 2, 0, 0))); }
        [[nodiscard]] vec3ia xyx() const noexcept { return vec3ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 0, 1, 0))); }
        [[nodiscard]] vec3ia xyy() const noexcept { return vec3ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 1, 1, 0))); }
        [[nodiscard]] vec3ia xyz() const noexcept { return vec3ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 2, 1, 0))); }
        [[nodiscard]] vec3ia xzx() const noexcept { return vec3ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 0, 2, 0))); }
        [[nodiscard]] vec3ia xzy() const noexcept { return vec3ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 1, 2, 0))); }
        [[nodiscard]] vec3ia xzz() const noexcept { return vec3ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 2, 2, 0))); }
        [[nodiscard]] vec3ia yxx() const noexcept { return vec3ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 0, 0, 1))); }
        [[nodiscard]] vec3ia yxy() const noexcept { return vec3ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 1, 0, 1))); }
        [[nodiscard]] vec3ia yxz() const noexcept { return vec3ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 2, 0, 1))); }
        [[nodiscard]] vec3ia yyx() const noexcept { return vec3ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 0, 1, 1))); }
        [[nodiscard]] vec3ia yyy() const noexcept { return vec3ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 1, 1, 1))); }
        [[nodiscard]] vec3ia yyz() const noexcept { return vec3ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 2, 1, 1))); }
        [[nodiscard]] vec3ia yzx() const noexcept { return vec3ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 0, 2, 1))); }
        [[nodiscard]] vec3ia yzy() const noexcept { return vec3ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 1, 2, 1))); }
        [[nodiscard]] vec3ia yzz() const noexcept { return vec3ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 2, 2, 1))); }
        [[nodiscard]] vec3ia zxx() const noexcept { return vec3ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 0, 0, 2))); }
        [[nodiscard]] vec3ia zxy() const noexcept { return vec3ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 1, 0, 2))); }
        [[nodiscard]] vec3ia zxz() const noexcept { return vec3ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 2, 0, 2))); }
        [[nodiscard]] vec3ia zyx() const noexcept { return vec3ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 0, 1, 2))); }
        [[nodiscard]] vec3ia zyy() const noexcept { return vec3ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 1, 1, 2))); }
        [[nodiscard]] vec3ia zyz() const noexcept { return vec3ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 2, 1, 2))); }
        [[nodiscard]] vec3ia zzx() const noexcept { return vec3ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 0, 2, 2))); }
        [[nodiscard]] vec3ia zzy() const noexcept { return vec3ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 1, 2, 2))); }
        [[nodiscard]] vec3ia zzz() const noexcept { return vec3ia(_mm_permute_ps(_mm_castsi128_ps(m128), _MM_SHUFFLE(0, 2, 2, 2))); }
#endif
    };
    
    ////////////////////////////////////////////////////////////////
    // Shuffle.
    ////////////////////////////////////////////////////////////////

#ifdef __AVX__
    template<int32_t i0, int32_t i1, int32_t i2>
    [[nodiscard]] vec3ia shuffle(const vec3ia& v) noexcept { return vec3ia(_mm_permute_ps(_mm_castsi128_ps(v), _MM_SHUFFLE(0, i2, i1, i0))); }
#endif

    ////////////////////////////////////////////////////////////////
    // Arithmetic operators.
    ////////////////////////////////////////////////////////////////

    [[nodiscard]] inline vec3ia operator+(const vec3ia& lhs, const vec3ia& rhs) noexcept { return _mm_add_epi32(lhs, rhs); }

    [[nodiscard]] inline vec3ia operator+(const vec3ia& lhs, const int32_t rhs) noexcept { return lhs + vec3ia(rhs); }

    [[nodiscard]] inline vec3ia operator+(const int32_t lhs, const vec3ia& rhs) noexcept { return vec3ia(lhs) + rhs; }

    [[nodiscard]] inline vec3ia operator-(const vec3ia& lhs, const vec3ia& rhs) noexcept { return _mm_sub_epi32(lhs, rhs); }

    [[nodiscard]] inline vec3ia operator-(const vec3ia& lhs, const int32_t rhs) noexcept { return lhs - vec3ia(rhs); }

    [[nodiscard]] inline vec3ia operator-(const int32_t lhs, const vec3ia& rhs) noexcept { return vec3ia(lhs) - rhs; }

    [[nodiscard]] inline vec3ia operator-(const vec3ia& lhs) noexcept { const __m128i mask = _mm_set1_epi32(0x80000000); return _mm_xor_si128(lhs, mask); }

    [[nodiscard]] inline vec3ia operator*(const vec3ia& lhs, const vec3ia& rhs) noexcept { return _mm_mul_epi32(lhs, rhs); }

    [[nodiscard]] inline vec3ia operator*(const vec3ia& lhs, const int32_t rhs) noexcept { return lhs * vec3ia(rhs); }

    [[nodiscard]] inline vec3ia operator*(const int32_t lhs, const vec3ia& rhs) noexcept { return vec3ia(lhs) * rhs; }

#if 0
// TODO: Integer division?
    [[nodiscard]] inline vec3ia operator/(const vec3ia& lhs, const vec3ia& rhs) noexcept { return _mm_div_epi32(lhs, rhs); }
#else
    [[nodiscard]] inline vec3ia operator/(const vec3ia& lhs, const vec3ia&) noexcept { return lhs; }
#endif

    [[nodiscard]] inline vec3ia operator/(const vec3ia& lhs, const int32_t rhs) noexcept { return lhs / vec3ia(rhs); }

    [[nodiscard]] inline vec3ia operator/(const int32_t lhs, const vec3ia& rhs) noexcept { return vec3ia(lhs) / rhs; }

    inline vec3ia& operator+=(vec3ia& lhs, const vec3ia& rhs) noexcept { return lhs = lhs + rhs; }

    inline vec3ia& operator+=(vec3ia& lhs, const int32_t rhs) noexcept { return lhs = lhs + rhs; }

    inline vec3ia& operator-=(vec3ia& lhs, const vec3ia& rhs) noexcept { return lhs = lhs - rhs; }

    inline vec3ia& operator-=(vec3ia& lhs, const int32_t rhs) noexcept { return lhs = lhs - rhs; }

    inline vec3ia& operator*=(vec3ia& lhs, const vec3ia& rhs) noexcept { return lhs = lhs * rhs; }

    inline vec3ia& operator*=(vec3ia& lhs, const int32_t rhs) noexcept { return lhs = lhs * rhs; }

    inline vec3ia& operator/=(vec3ia& lhs, const vec3ia& rhs) noexcept { return lhs = lhs / rhs; }

    inline vec3ia& operator/=(vec3ia& lhs, const int32_t rhs) noexcept { return lhs = lhs / rhs; }

    ////////////////////////////////////////////////////////////////
    // Comparison operators.
    ////////////////////////////////////////////////////////////////

    [[nodiscard]] inline bool operator==(const vec3ia& lhs, const vec3ia& rhs) noexcept { return (_mm_movemask_ps(_mm_castsi128_ps(_mm_cmpeq_epi32(lhs, rhs))) & 0x7) == 0x7; }

    [[nodiscard]] inline bool operator!=(const vec3ia& lhs, const vec3ia& rhs) noexcept { return (_mm_movemask_ps(_mm_castsi128_ps(_mm_cmpeq_epi32(lhs, rhs))) & 0x7) != 0x7; }

    ////////////////////////////////////////////////////////////////
    // Per-element comparisons.
    ////////////////////////////////////////////////////////////////

    [[nodiscard]] inline vec3ba cmpeq(const vec3ia& lhs, const vec3ia& rhs) noexcept { return _mm_cmpeq_epi32(lhs, rhs); }

    [[nodiscard]] inline vec3ba cmpeq(const vec3ia& lhs, const int32_t rhs) noexcept { return cmpeq(lhs, vec3ia(rhs)); }

    [[nodiscard]] inline vec3ba cmpeq(const int32_t lhs, const vec3ia& rhs) noexcept { return cmpeq(vec3ia(lhs), rhs); }

    [[nodiscard]] inline vec3ba cmpneq(const vec3ia& lhs, const vec3ia& rhs) noexcept { return _mm_andnot_si128(_mm_cmpeq_epi32(lhs, rhs), _mm_set1_epi32(-1)); }

    [[nodiscard]] inline vec3ba cmpneq(const vec3ia& lhs, const int32_t rhs) noexcept { return cmpneq(lhs, vec3ia(rhs)); }

    [[nodiscard]] inline vec3ba cmpneq(const int32_t lhs, const vec3ia& rhs) noexcept { return cmpneq(vec3ia(lhs), rhs); }

    [[nodiscard]] inline vec3ba cmplt(const vec3ia& lhs, const vec3ia& rhs) noexcept { return _mm_cmplt_epi32(lhs, rhs); }

    [[nodiscard]] inline vec3ba cmplt(const vec3ia& lhs, const int32_t rhs) noexcept { return cmplt(lhs, vec3ia(rhs)); }

    [[nodiscard]] inline vec3ba cmplt(const int32_t lhs, const vec3ia& rhs) noexcept { return cmplt(vec3ia(lhs), rhs); }

    [[nodiscard]] inline vec3ba cmpgt(const vec3ia& lhs, const vec3ia& rhs) noexcept { return _mm_cmpgt_epi32(lhs, rhs); }

    [[nodiscard]] inline vec3ba cmpgt(const vec3ia& lhs, const int32_t rhs) noexcept { return cmpgt(lhs, vec3ia(rhs)); }

    [[nodiscard]] inline vec3ba cmpgt(const int32_t lhs, const vec3ia& rhs) noexcept { return cmpgt(vec3ia(lhs), rhs); }

    [[nodiscard]] inline vec3ba cmple(const vec3ia& lhs, const vec3ia& rhs) noexcept { return _mm_andnot_si128(_mm_cmpgt_epi32(lhs, rhs), _mm_set1_epi32(-1)); }

    [[nodiscard]] inline vec3ba cmple(const vec3ia& lhs, const int32_t rhs) noexcept { return cmple(lhs, vec3ia(rhs)); }

    [[nodiscard]] inline vec3ba cmple(const int32_t lhs, const vec3ia& rhs) noexcept { return cmple(vec3ia(lhs), rhs); }

    [[nodiscard]] inline vec3ba cmpge(const vec3ia& lhs, const vec3ia& rhs) noexcept { return _mm_andnot_si128(_mm_cmplt_epi32(lhs, rhs), _mm_set1_epi32(-1)); }

    [[nodiscard]] inline vec3ba cmpge(const vec3ia& lhs, const int32_t rhs) noexcept { return cmpge(lhs, vec3ia(rhs)); }

    [[nodiscard]] inline vec3ba cmpge(const int32_t lhs, const vec3ia& rhs) noexcept { return cmpge(vec3ia(lhs), rhs); }

    ////////////////////////////////////////////////////////////////
    // Min/max, abs and clamp.
    ////////////////////////////////////////////////////////////////

    [[nodiscard]] inline vec3ia min(const vec3ia& lhs, const vec3ia& rhs) noexcept { return _mm_min_epi32(lhs, rhs); }

    [[nodiscard]] inline vec3ia min(const vec3ia& lhs, const int32_t rhs) noexcept { return min(lhs, vec3ia(rhs)); }

    [[nodiscard]] inline vec3ia min(const int32_t lhs, const vec3ia& rhs) noexcept { return min(vec3ia(lhs), rhs); }

    [[nodiscard]] inline vec3ia max(const vec3ia& lhs, const vec3ia& rhs) noexcept { return _mm_max_epi32(lhs, rhs); }

    [[nodiscard]] inline vec3ia max(const vec3ia& lhs, const int32_t rhs) noexcept { return max(lhs, vec3ia(rhs)); }

    [[nodiscard]] inline vec3ia max(const int32_t lhs, const vec3ia& rhs) noexcept { return max(vec3ia(lhs), rhs); }

    [[nodiscard]] inline vec3ia clamp(const vec3ia& a, const vec3ia& min, const vec3ia& max) noexcept { return math::max(min, math::min(a, max)); }

    [[nodiscard]] inline vec3ia clamp(const vec3ia& a, const vec3ia& min, const int32_t max) noexcept { return clamp(a, min, vec3ia(max)); }

    [[nodiscard]] inline vec3ia clamp(const vec3ia& a, const int32_t min, const vec3ia& max) noexcept { return clamp(a, vec3ia(min), max); }

    [[nodiscard]] inline vec3ia clamp(const vec3ia& a, const int32_t min, const int32_t max) noexcept { return clamp(a, vec3ia(min), vec3ia(max)); }

    ////////////////////////////////////////////////////////////////
    // Reduction.
    ////////////////////////////////////////////////////////////////

    [[nodiscard]] inline int32_t reduce_add(const vec3ia& lhs) noexcept
    {
        const vec3ia sum1 = _mm_add_epi32(lhs, lhs.yxx());
        const vec3ia sum2 = _mm_add_epi32(sum1, lhs.zxx());
        return _mm_cvtsi128_si32(sum2);
    }

    [[nodiscard]] inline int32_t reduce_mul(const vec3ia& lhs) noexcept
    {
        const vec3ia sum1 = _mm_mul_epi32(lhs, lhs.yxx());
        const vec3ia sum2 = _mm_mul_epi32(sum1, lhs.zxx());
        return _mm_cvtsi128_si32(sum2);
    }

    [[nodiscard]] inline int32_t reduce_min(const vec3ia& lhs) noexcept
    {
        const vec3ia sum1 = _mm_min_epi32(lhs, lhs.yxx());
        const vec3ia sum2 = _mm_min_epi32(sum1, lhs.zxx());
        return _mm_cvtsi128_si32(sum2);
    }

    [[nodiscard]] inline int32_t reduce_max(const vec3ia& lhs) noexcept
    {
        const vec3ia sum1 = _mm_max_epi32(lhs, lhs.yxx());
        const vec3ia sum2 = _mm_max_epi32(sum1, lhs.zxx());
        return _mm_cvtsi128_si32(sum2);
    }

    ////////////////////////////////////////////////////////////////
    // Dot product etc.
    ////////////////////////////////////////////////////////////////

#if 0
    inline int32_t dot(const vec3ia& lhs, const vec3ia& rhs)
    {
        return reduce_add(lhs * rhs);
    }

    inline int32_t length(const vec3ia& lhs) { return sqrt(dot(lhs, lhs)); }

    inline int32_t sqr_length(const vec3ia& lhs) { return dot(lhs, lhs); }

    inline int32_t rcp_length(const vec3ia& lhs) { return rsqrt(dot(lhs, lhs)); }

    inline vec3ia normalize(const vec3ia& lhs) { return lhs * rcp_length(lhs); }

    inline vec3ia normalize(const vec3ia& lhs, int32_t& length) { length = math::length(lhs); return lhs / length; }

    inline int32_t distance(const vec3ia& lhs, const vec3ia& rhs) { return length(lhs - rhs); }
#endif

    ////////////////////////////////////////////////////////////////
    // Exponential / Logarithmic.
    ////////////////////////////////////////////////////////////////

#if 0
    inline vec3ia exp(const vec3ia& lhs) { return vec3ia(exp(lhs.x), exp(lhs.y), exp(lhs.z)); }

    inline vec3ia exp2(const vec3ia& lhs) { return vec3ia(exp2(lhs.x), exp2(lhs.y), exp2(lhs.z)); }

    inline vec3ia log(const vec3ia& lhs) { return vec3ia(log(lhs.x), log(lhs.y), log(lhs.z)); }

    inline vec3ia log2(const vec3ia& lhs) { return vec3ia(log2(lhs.x), log2(lhs.y), log2(lhs.z)); }

    inline vec3ia log10(const vec3ia& lhs) { return vec3ia(log10(lhs.x), log10(lhs.y), log10(lhs.z)); }
#endif

    ////////////////////////////////////////////////////////////////
    // Power.
    ////////////////////////////////////////////////////////////////

#if 0
    inline vec3ia pow(const vec3ia& lhs, const vec3ia& rhs) { return vec3ia(pow(lhs.x, rhs.x), pow(lhs.y, rhs.y), pow(lhs.z, rhs.z)); }

    inline vec3ia sqr(const vec3ia& lhs) { return lhs * lhs; }

    inline vec3ia sqrt(const vec3ia& lhs) { return _mm_cvtps_epi32(_mm_sqrt_ps(_mm_cvtepi32_ps(lhs))); }

    inline vec3ia rsqrt(const vec3ia& lhs) { return _mm_cvtps_epi32(_mm_rsqrt_ps(_mm_cvtepi32_ps(lhs))); }
#endif

    ////////////////////////////////////////////////////////////////
    // Rounding, abs, etc.
    ////////////////////////////////////////////////////////////////

    [[nodiscard]] inline vec3ia abs(const vec3ia& lhs) noexcept
    {
        const __m128i mask = _mm_set1_epi32(0x7fffffff);
        return _mm_and_si128(lhs, mask);
    }

    ////////////////////////////////////////////////////////////////
    // Select.
    ////////////////////////////////////////////////////////////////

    [[nodiscard]] inline vec3ia select(const vec3ia& t, const vec3ia& f, const vec3ba& b) noexcept
    {
#ifdef __SSE4_1__
        return vec3ia(_mm_blendv_ps(_mm_castsi128_ps(f), _mm_castsi128_ps(t), _mm_castsi128_ps(b)));
#else
        return vec3ia(math::select(t.x, f.x, b.x & 0x80000000), math::select(t.y, f.y, b.y & 0x80000000), math::select(t.z, f.z, b.z & 0x80000000));
#endif
    }

    ////////////////////////////////////////////////////////////////
    // Multiply and add.
    ////////////////////////////////////////////////////////////////

    [[nodiscard]] inline vec3ia madd(const vec3ia& a, const vec3ia& b, const vec3ia& c) noexcept { return a * b + c; }

    [[nodiscard]] inline vec3ia nmadd(const vec3ia& a, const vec3ia& b, const vec3ia& c) noexcept { return -a * b + c; }

    [[nodiscard]] inline vec3ia msub(const vec3ia& a, const vec3ia& b, const vec3ia& c) noexcept { return a * b - c; }

    [[nodiscard]] inline vec3ia nmsub(const vec3ia& a, const vec3ia& b, const vec3ia& c) noexcept { return -a * b - c; }

    ////////////////////////////////////////////////////////////////
    // Shift operators.
    ////////////////////////////////////////////////////////////////

#ifdef __AVX2__
    [[nodiscard]] inline vec3ia operator<<(const vec3ia& lhs, const vec3ia& rhs) noexcept { return _mm_sllv_epi32(lhs, rhs); }
#endif
    [[nodiscard]] inline vec3ia operator<<(const vec3ia& lhs, const int32_t rhs) noexcept { return _mm_slli_epi32(lhs, rhs); }
#ifdef __AVX2__
    [[nodiscard]] inline vec3ia operator<<(const int32_t lhs, const vec3ia& rhs) noexcept { return _mm_sllv_epi32(_mm_set1_epi32(lhs), rhs); }
#endif
#ifdef __AVX2__
    [[nodiscard]] inline vec3ia operator>>(const vec3ia& lhs, const vec3ia& rhs) noexcept { return _mm_srlv_epi32(lhs, rhs); }
#endif
    [[nodiscard]] inline vec3ia operator>>(const vec3ia& lhs, const int32_t rhs) noexcept { return _mm_srli_epi32(lhs, rhs); }
#ifdef __AVX2__
    [[nodiscard]] inline vec3ia operator>>(const int32_t lhs, const vec3ia& rhs) noexcept { return _mm_srlv_epi32(_mm_set1_epi32(lhs), rhs); }
#endif
#ifdef __AVX2__
    inline vec3ia& operator<<=(vec3ia& lhs, const vec3ia& rhs) noexcept { return lhs = lhs << rhs; }
#endif
    inline vec3ia& operator<<=(vec3ia& lhs, const int32_t rhs) noexcept { return lhs = lhs << rhs; }
#ifdef __AVX2__
    inline vec3ia& operator>>=(vec3ia& lhs, const vec3ia& rhs) noexcept { return lhs = lhs >> rhs; }
#endif
    inline vec3ia& operator>>=(vec3ia& lhs, const int32_t rhs) noexcept { return lhs = lhs >> rhs; }

    ////////////////////////////////////////////////////////////////
    // Bitwise operators.
    ////////////////////////////////////////////////////////////////

    [[nodiscard]] inline vec3ia operator|(const vec3ia& lhs, const vec3ia& rhs) noexcept { return _mm_or_si128(lhs, rhs); }

    [[nodiscard]] inline vec3ia operator|(const vec3ia& lhs, const int32_t rhs) noexcept { return _mm_or_si128(lhs, vec3ia(rhs)); }

    [[nodiscard]] inline vec3ia operator|(const int32_t lhs, const vec3ia& rhs) noexcept { return _mm_or_si128(vec3ia(lhs), rhs); }

    [[nodiscard]] inline vec3ia operator&(const vec3ia& lhs, const vec3ia& rhs) noexcept { return _mm_and_si128(lhs, rhs); }

    [[nodiscard]] inline vec3ia operator&(const vec3ia& lhs, const int32_t rhs) noexcept { return _mm_and_si128(lhs, vec3ia(rhs)); }

    [[nodiscard]] inline vec3ia operator&(const int32_t lhs, const vec3ia& rhs) noexcept { return _mm_and_si128(vec3ia(lhs), rhs); }

    [[nodiscard]] inline vec3ia operator^(const vec3ia& lhs, const vec3ia& rhs) noexcept { return _mm_xor_si128(lhs, rhs); }

    [[nodiscard]] inline vec3ia operator^(const vec3ia& lhs, const int32_t rhs) noexcept { return _mm_xor_si128(lhs, vec3ia(rhs)); }

    [[nodiscard]] inline vec3ia operator^(const int32_t lhs, const vec3ia& rhs) noexcept { return _mm_xor_si128(vec3ia(lhs), rhs); }

    [[nodiscard]] inline vec3ia operator~(const vec3ia& lhs) noexcept { return _mm_sub_epi32(_mm_set1_epi32(0), lhs); }

    inline vec3ia& operator|=(vec3ia& lhs, const vec3ia& rhs) noexcept { return lhs = lhs | rhs; }

    inline vec3ia& operator|=(vec3ia& lhs, const int32_t rhs) noexcept { return lhs = lhs | rhs; }

    inline vec3ia& operator&=(vec3ia& lhs, const vec3ia& rhs) noexcept { return lhs = lhs & rhs; }

    inline vec3ia& operator&=(vec3ia& lhs, const int32_t rhs) noexcept { return lhs = lhs & rhs; }

    inline vec3ia& operator^=(vec3ia& lhs, const vec3ia& rhs) noexcept { return lhs = lhs ^ rhs; }

    inline vec3ia& operator^=(vec3ia& lhs, const int32_t rhs) noexcept { return lhs = lhs ^ rhs; }

    ////////////////////////////////////////////////////////////////
    // Output.
    ////////////////////////////////////////////////////////////////

    inline std::ostream& operator<<(std::ostream& out, const vec3ia& v) { return out << "(" << v.x << ", " << v.y << ", " << v.z << ")"; }

}
