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

#include "math/foldpoly.h"
#include "math/vector/simd/vec3ba.h"
#include "math/vector/simd/vec4fa.h"

namespace math
{
    struct alignas(16) vec3fa
    {
        static constexpr size_t size = 3;
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

        [[nodiscard]] vec3fa() noexcept : m128(_mm_set1_ps(0)) {}

        [[nodiscard]] explicit vec3fa(const float v) noexcept : m128(_mm_set1_ps(v)) {}

        [[nodiscard]] vec3fa(const float x, const float y, const float z) noexcept : m128(_mm_setr_ps(x, y, z, 0.0f)) {}

        [[nodiscard]] vec3fa(const float x, const float y, const float z, const float w) noexcept : m128(_mm_setr_ps(x, y, z, w)) {}

        [[nodiscard]] explicit vec3fa(const __m128 m128) noexcept : m128(m128) {}

        [[nodiscard]] explicit vec3fa(const __m128i m128) noexcept : m128(_mm_castsi128_ps(m128)) {}

        [[nodiscard]] vec3fa(const vec3fa & rhs) noexcept : m128(rhs.m128) {}

        [[nodiscard]] explicit vec3fa(const vec<float, 3> & rhs) noexcept : m128(_mm_setr_ps(rhs.x, rhs.y, rhs.z, 0.0f)) {}

        ////////////////////////////////////////////////////////////////
        // Assignment operators.
        ////////////////////////////////////////////////////////////////

        vec3fa& operator=(const vec3fa& rhs) noexcept { m128 = rhs.m128; return *this; }

        vec3fa& operator=(const vec4fa& rhs) noexcept { m128 = rhs.m128; return *this; }

        vec3fa& operator=(const float rhs) noexcept { m128 = _mm_set1_ps(rhs); return *this; }

        ////////////////////////////////////////////////////////////////
        // Load/store.
        ////////////////////////////////////////////////////////////////

        [[nodiscard]] static vec3fa load(const void* const ptr) { return vec3fa(_mm_load_ps(static_cast<const float*>(ptr))); }

        [[nodiscard]] static vec3fa loadu(const void* const ptr) { return vec3fa(_mm_loadu_ps(static_cast<const float*>(ptr))); }

        static void store(void* ptr, const vec3fa & v) { _mm_store_ps(static_cast<float*>(ptr), v.m128); }

        static void storeu(void* ptr, const vec3fa & v) { _mm_storeu_ps(static_cast<float*>(ptr), v.m128); }

        ////////////////////////////////////////////////////////////////
        // Defaulted constructors and operators.
        ////////////////////////////////////////////////////////////////

        ~vec3fa() noexcept = default;

        vec3fa(vec3fa && rhs) noexcept = default;

        vec3fa& operator=(vec3fa && rhs) noexcept = default;

        ////////////////////////////////////////////////////////////////
        // Casting operators.
        ////////////////////////////////////////////////////////////////

        [[nodiscard]] operator const __m128& () const noexcept { return m128; }

        [[nodiscard]] operator __m128& () noexcept { return m128; }

        [[nodiscard]] explicit operator __m128i () const noexcept { return _mm_castps_si128(m128); }

        [[nodiscard]] explicit operator vec<float, 3>() const noexcept { return vec<float, 3>(x, y, z); }

        ////////////////////////////////////////////////////////////////
        // Element access.
        ////////////////////////////////////////////////////////////////

        [[nodiscard]] const float& operator[](const size_t i) const { assert(i < 3); return (&x)[i]; }

        [[nodiscard]] float& operator[](const size_t i) { assert(i < 3); return (&x)[i]; }

        ////////////////////////////////////////////////////////////////
        // Swizzling.
        ////////////////////////////////////////////////////////////////

#ifdef __AVX__
        [[nodiscard]] vec3fa xxx() const noexcept { return vec3fa(_mm_permute_ps(m128, _MM_SHUFFLE(0, 0, 0, 0))); }
        [[nodiscard]] vec3fa xxy() const noexcept { return vec3fa(_mm_permute_ps(m128, _MM_SHUFFLE(0, 1, 0, 0))); }
        [[nodiscard]] vec3fa xxz() const noexcept { return vec3fa(_mm_permute_ps(m128, _MM_SHUFFLE(0, 2, 0, 0))); }
        [[nodiscard]] vec3fa xyx() const noexcept { return vec3fa(_mm_permute_ps(m128, _MM_SHUFFLE(0, 0, 1, 0))); }
        [[nodiscard]] vec3fa xyy() const noexcept { return vec3fa(_mm_permute_ps(m128, _MM_SHUFFLE(0, 1, 1, 0))); }
        [[nodiscard]] vec3fa xyz() const noexcept { return vec3fa(_mm_permute_ps(m128, _MM_SHUFFLE(0, 2, 1, 0))); }
        [[nodiscard]] vec3fa xzx() const noexcept { return vec3fa(_mm_permute_ps(m128, _MM_SHUFFLE(0, 0, 2, 0))); }
        [[nodiscard]] vec3fa xzy() const noexcept { return vec3fa(_mm_permute_ps(m128, _MM_SHUFFLE(0, 1, 2, 0))); }
        [[nodiscard]] vec3fa xzz() const noexcept { return vec3fa(_mm_permute_ps(m128, _MM_SHUFFLE(0, 2, 2, 0))); }
        [[nodiscard]] vec3fa yxx() const noexcept { return vec3fa(_mm_permute_ps(m128, _MM_SHUFFLE(0, 0, 0, 1))); }
        [[nodiscard]] vec3fa yxy() const noexcept { return vec3fa(_mm_permute_ps(m128, _MM_SHUFFLE(0, 1, 0, 1))); }
        [[nodiscard]] vec3fa yxz() const noexcept { return vec3fa(_mm_permute_ps(m128, _MM_SHUFFLE(0, 2, 0, 1))); }
        [[nodiscard]] vec3fa yyx() const noexcept { return vec3fa(_mm_permute_ps(m128, _MM_SHUFFLE(0, 0, 1, 1))); }
        [[nodiscard]] vec3fa yyy() const noexcept { return vec3fa(_mm_permute_ps(m128, _MM_SHUFFLE(0, 1, 1, 1))); }
        [[nodiscard]] vec3fa yyz() const noexcept { return vec3fa(_mm_permute_ps(m128, _MM_SHUFFLE(0, 2, 1, 1))); }
        [[nodiscard]] vec3fa yzx() const noexcept { return vec3fa(_mm_permute_ps(m128, _MM_SHUFFLE(0, 0, 2, 1))); }
        [[nodiscard]] vec3fa yzy() const noexcept { return vec3fa(_mm_permute_ps(m128, _MM_SHUFFLE(0, 1, 2, 1))); }
        [[nodiscard]] vec3fa yzz() const noexcept { return vec3fa(_mm_permute_ps(m128, _MM_SHUFFLE(0, 2, 2, 1))); }
        [[nodiscard]] vec3fa zxx() const noexcept { return vec3fa(_mm_permute_ps(m128, _MM_SHUFFLE(0, 0, 0, 2))); }
        [[nodiscard]] vec3fa zxy() const noexcept { return vec3fa(_mm_permute_ps(m128, _MM_SHUFFLE(0, 1, 0, 2))); }
        [[nodiscard]] vec3fa zxz() const noexcept { return vec3fa(_mm_permute_ps(m128, _MM_SHUFFLE(0, 2, 0, 2))); }
        [[nodiscard]] vec3fa zyx() const noexcept { return vec3fa(_mm_permute_ps(m128, _MM_SHUFFLE(0, 0, 1, 2))); }
        [[nodiscard]] vec3fa zyy() const noexcept { return vec3fa(_mm_permute_ps(m128, _MM_SHUFFLE(0, 1, 1, 2))); }
        [[nodiscard]] vec3fa zyz() const noexcept { return vec3fa(_mm_permute_ps(m128, _MM_SHUFFLE(0, 2, 1, 2))); }
        [[nodiscard]] vec3fa zzx() const noexcept { return vec3fa(_mm_permute_ps(m128, _MM_SHUFFLE(0, 0, 2, 2))); }
        [[nodiscard]] vec3fa zzy() const noexcept { return vec3fa(_mm_permute_ps(m128, _MM_SHUFFLE(0, 1, 2, 2))); }
        [[nodiscard]] vec3fa zzz() const noexcept { return vec3fa(_mm_permute_ps(m128, _MM_SHUFFLE(0, 2, 2, 2))); }
#endif
    };

    ////////////////////////////////////////////////////////////////
    // Shuffle.
    ////////////////////////////////////////////////////////////////

#ifdef __AVX__
    template<int32_t i0, int32_t i1, int32_t i2>
    [[nodiscard]] vec3fa shuffle(const vec3fa& v) noexcept { return vec3fa(_mm_permute_ps(v, _MM_SHUFFLE(0, i2, i1, i0))); }
#endif

    ////////////////////////////////////////////////////////////////
    // Arithmetic operators.
    ////////////////////////////////////////////////////////////////

    [[nodiscard]] inline vec3fa operator+(const vec3fa& lhs, const vec3fa& rhs) noexcept { return vec3fa(_mm_add_ps(lhs, rhs)); }

    [[nodiscard]] inline vec3fa operator+(const vec3fa& lhs, const float rhs) noexcept { return lhs + vec3fa(rhs); }

    [[nodiscard]] inline vec3fa operator+(const float lhs, const vec3fa& rhs) noexcept { return vec3fa(lhs) + rhs; }

    [[nodiscard]] inline vec3fa operator-(const vec3fa& lhs, const vec3fa& rhs) noexcept { return vec3fa(_mm_sub_ps(lhs, rhs)); }

    [[nodiscard]] inline vec3fa operator-(const vec3fa& lhs, const float rhs) noexcept { return lhs - vec3fa(rhs); }

    [[nodiscard]] inline vec3fa operator-(const float lhs, const vec3fa& rhs) noexcept { return vec3fa(lhs) - rhs; }

    [[nodiscard]] inline vec3fa operator-(const vec3fa& lhs) noexcept { const __m128 mask = _mm_castsi128_ps(_mm_set1_epi32(0x80000000)); return vec3fa(_mm_xor_ps(lhs, mask)); }

    [[nodiscard]] inline vec3fa operator*(const vec3fa& lhs, const vec3fa& rhs) noexcept { return vec3fa(_mm_mul_ps(lhs, rhs)); }

    [[nodiscard]] inline vec3fa operator*(const vec3fa& lhs, const float rhs) noexcept { return lhs * vec3fa(rhs); }

    [[nodiscard]] inline vec3fa operator*(const float lhs, const vec3fa& rhs) noexcept { return vec3fa(lhs) * rhs; }

    [[nodiscard]] inline vec3fa operator/(const vec3fa& lhs, const vec3fa& rhs) noexcept { return vec3fa(_mm_div_ps(lhs, rhs)); }

    [[nodiscard]] inline vec3fa operator/(const vec3fa& lhs, const float rhs) noexcept { return lhs / vec3fa(rhs); }

    [[nodiscard]] inline vec3fa operator/(const float lhs, const vec3fa& rhs) noexcept { return vec3fa(lhs) / rhs; }

    inline vec3fa& operator+=(vec3fa& lhs, const vec3fa& rhs) noexcept { return lhs = lhs + rhs; }

    inline vec3fa& operator+=(vec3fa& lhs, const float rhs) noexcept { return lhs = lhs + rhs; }

    inline vec3fa& operator-=(vec3fa& lhs, const vec3fa& rhs) noexcept { return lhs = lhs - rhs; }

    inline vec3fa& operator-=(vec3fa& lhs, const float rhs) noexcept { return lhs = lhs - rhs; }

    inline vec3fa& operator*=(vec3fa& lhs, const vec3fa& rhs) noexcept { return lhs = lhs * rhs; }

    inline vec3fa& operator*=(vec3fa& lhs, const float rhs) noexcept { return lhs = lhs * rhs; }

    inline vec3fa& operator/=(vec3fa& lhs, const vec3fa& rhs) noexcept { return lhs = lhs / rhs; }

    inline vec3fa& operator/=(vec3fa& lhs, const float rhs) noexcept { return lhs = lhs / rhs; }

    ////////////////////////////////////////////////////////////////
    // Comparison operators.
    ////////////////////////////////////////////////////////////////

    [[nodiscard]] inline bool operator==(const vec3fa& lhs, const vec3fa& rhs) noexcept { return (_mm_movemask_ps(_mm_cmpeq_ps(lhs, rhs)) & 0x7) == 0x7; }

    [[nodiscard]] inline bool operator!=(const vec3fa& lhs, const vec3fa& rhs) noexcept { return (_mm_movemask_ps(_mm_cmpeq_ps(lhs, rhs)) & 0x7) != 0x7; }

    ////////////////////////////////////////////////////////////////
    // Per-element comparisons.
    ////////////////////////////////////////////////////////////////

    [[nodiscard]] inline vec3ba cmpeq(const vec3fa& lhs, const vec3fa& rhs) noexcept { return vec3ba(_mm_cmpeq_ps(lhs, rhs)); }

    [[nodiscard]] inline vec3ba cmpeq(const vec3fa& lhs, const float rhs) noexcept { return cmpeq(lhs, vec3fa(rhs)); }

    [[nodiscard]] inline vec3ba cmpeq(const float lhs, const vec3fa& rhs) noexcept { return cmpeq(vec3fa(lhs), rhs); }

    [[nodiscard]] inline vec3ba cmpneq(const vec3fa& lhs, const vec3fa& rhs) noexcept { return vec3ba(_mm_cmpneq_ps(lhs, rhs)); }

    [[nodiscard]] inline vec3ba cmpneq(const vec3fa& lhs, const float rhs) noexcept { return cmpneq(lhs, vec3fa(rhs)); }

    [[nodiscard]] inline vec3ba cmpneq(const float lhs, const vec3fa& rhs) noexcept { return cmpneq(vec3fa(lhs), rhs); }

    [[nodiscard]] inline vec3ba cmplt(const vec3fa& lhs, const vec3fa& rhs) noexcept { return vec3ba(_mm_cmplt_ps(lhs, rhs)); }

    [[nodiscard]] inline vec3ba cmplt(const vec3fa& lhs, const float rhs) noexcept { return cmplt(lhs, vec3fa(rhs)); }

    [[nodiscard]] inline vec3ba cmplt(const float lhs, const vec3fa& rhs) noexcept { return cmplt(vec3fa(lhs), rhs); }

    [[nodiscard]] inline vec3ba cmpgt(const vec3fa& lhs, const vec3fa& rhs) noexcept { return vec3ba(_mm_cmpgt_ps(lhs, rhs)); }

    [[nodiscard]] inline vec3ba cmpgt(const vec3fa& lhs, const float rhs) noexcept { return cmpgt(lhs, vec3fa(rhs)); }

    [[nodiscard]] inline vec3ba cmpgt(const float lhs, const vec3fa& rhs) noexcept { return cmpgt(vec3fa(lhs), rhs); }

    [[nodiscard]] inline vec3ba cmple(const vec3fa& lhs, const vec3fa& rhs) noexcept { return vec3ba(_mm_cmple_ps(lhs, rhs)); }

    [[nodiscard]] inline vec3ba cmple(const vec3fa& lhs, const float rhs) noexcept { return cmple(lhs, vec3fa(rhs)); }

    [[nodiscard]] inline vec3ba cmple(const float lhs, const vec3fa& rhs) noexcept { return cmple(vec3fa(lhs), rhs); }

    [[nodiscard]] inline vec3ba cmpge(const vec3fa& lhs, const vec3fa& rhs) noexcept { return vec3ba(_mm_cmpge_ps(lhs, rhs)); }

    [[nodiscard]] inline vec3ba cmpge(const vec3fa& lhs, const float rhs) noexcept { return cmpge(lhs, vec3fa(rhs)); }

    [[nodiscard]] inline vec3ba cmpge(const float lhs, const vec3fa& rhs) noexcept { return cmpge(vec3fa(lhs), rhs); }

    ////////////////////////////////////////////////////////////////
    // Min/max, abs and clamp.
    ////////////////////////////////////////////////////////////////

    [[nodiscard]] inline vec3fa min(const vec3fa& lhs, const vec3fa& rhs) noexcept { return vec3fa(_mm_min_ps(lhs, rhs)); }

    [[nodiscard]] inline vec3fa min(const vec3fa& lhs, const float rhs) noexcept { return min(lhs, vec3fa(rhs)); }

    [[nodiscard]] inline vec3fa min(const float lhs, const vec3fa& rhs) noexcept { return min(vec3fa(lhs), rhs); }

    [[nodiscard]] inline vec3fa max(const vec3fa& lhs, const vec3fa& rhs) noexcept { return vec3fa(_mm_max_ps(lhs, rhs)); }

    [[nodiscard]] inline vec3fa max(const vec3fa& lhs, const float rhs) noexcept { return max(lhs, vec3fa(rhs)); }

    [[nodiscard]] inline vec3fa max(const float lhs, const vec3fa& rhs) noexcept { return max(vec3fa(lhs), rhs); }

    [[nodiscard]] inline vec3fa clamp(const vec3fa& a, const vec3fa& min, const vec3fa& max) noexcept { return math::max(min, math::min(a, max)); }

    [[nodiscard]] inline vec3fa clamp(const vec3fa& a, const vec3fa& min, const float max) noexcept { return clamp(a, min, vec3fa(max)); }

    [[nodiscard]] inline vec3fa clamp(const vec3fa& a, const float min, const vec3fa& max) noexcept { return clamp(a, vec3fa(min), max); }

    [[nodiscard]] inline vec3fa clamp(const vec3fa& a, const float min, const float max) noexcept { return clamp(a, vec3fa(min), vec3fa(max)); }

    ////////////////////////////////////////////////////////////////
    // Reduction.
    ////////////////////////////////////////////////////////////////

    [[nodiscard]] inline float reduce_add(const vec3fa& lhs) noexcept
    {
        const __m128 sum1 = _mm_add_ss(lhs, lhs.yxx());
        const __m128 sum2 = _mm_add_ss(sum1, lhs.zxx());
        return _mm_cvtss_f32(sum2);
    }

    [[nodiscard]] inline float reduce_mul(const vec3fa& lhs) noexcept
    {
        const __m128 sum1 = _mm_mul_ss(lhs, lhs.yxx());
        const __m128 sum2 = _mm_mul_ss(sum1, lhs.zxx());
        return _mm_cvtss_f32(sum2);
    }

    [[nodiscard]] inline float reduce_min(const vec3fa& lhs) noexcept
    {
        const __m128 sum1 = _mm_min_ss(lhs, lhs.yxx());
        const __m128 sum2 = _mm_min_ss(sum1, lhs.zxx());
        return _mm_cvtss_f32(sum2);
    }

    [[nodiscard]] inline float reduce_max(const vec3fa& lhs) noexcept
    {
        const __m128 sum1 = _mm_max_ss(lhs, lhs.yxx());
        const __m128 sum2 = _mm_max_ss(sum1, lhs.zxx());
        return _mm_cvtss_f32(sum2);
    }

    ////////////////////////////////////////////////////////////////
    // Multiply and add.
    ////////////////////////////////////////////////////////////////

    [[nodiscard]] inline vec3fa madd(const vec3fa& a, const vec3fa& b, const vec3fa& c) noexcept
    {
#ifdef __FMA__
        return vec3fa(_mm_fmadd_ps(a, b, c));
#else
        return a * b + c;
#endif
    }

    [[nodiscard]] inline vec3fa nmadd(const vec3fa& a, const vec3fa& b, const vec3fa& c) noexcept
    {
#ifdef __FMA__
        return vec3fa(_mm_fnmadd_ps(a, b, c));
#else
        return -a * b + c;
#endif
    }

    [[nodiscard]] inline vec3fa msub(const vec3fa& a, const vec3fa& b, const vec3fa& c) noexcept
    {
#ifdef __FMA__
        return vec3fa(_mm_fmsub_ps(a, b, c));
#else
        return a * b - c;
#endif
    }

    [[nodiscard]] inline vec3fa nmsub(const vec3fa& a, const vec3fa& b, const vec3fa& c) noexcept
    {
#ifdef __FMA__
        return vec3fa(_mm_fnmsub_ps(a, b, c));
#else
        return -a * b - c;
#endif
    }

    ////////////////////////////////////////////////////////////////
    // Dot product etc.
    ////////////////////////////////////////////////////////////////

    [[nodiscard]] inline float dot(const vec3fa& lhs, const vec3fa& rhs) noexcept
    {
#ifdef __SSE4_1__
        return _mm_cvtss_f32(_mm_dp_ps(lhs, rhs, 0b0111'0111));
#else
        return reduce_add(lhs * rhs);
#endif
    }

    [[nodiscard]] inline vec3fa cross(const vec3fa& lhs, const vec3fa& rhs) noexcept { return msub(lhs.yzx(), rhs.zxy(), lhs.zxy() * rhs.yzx()); }

    [[nodiscard]] inline float length(const vec3fa& lhs) noexcept { return sqrt(dot(lhs, lhs)); }

    [[nodiscard]] inline float sqr_length(const vec3fa& lhs) noexcept { return dot(lhs, lhs); }

    [[nodiscard]] inline float rcp_length(const vec3fa& lhs) noexcept { return rsqrt(dot(lhs, lhs)); }

    [[nodiscard]] inline vec3fa normalize(const vec3fa& lhs) noexcept { return lhs * rcp_length(lhs); }

    [[nodiscard]] inline vec3fa normalize(const vec3fa& lhs, float& length) noexcept { length = math::length(lhs); return lhs / length; }

    [[nodiscard]] inline float distance(const vec3fa& lhs, const vec3fa& rhs) noexcept { return length(lhs - rhs); }

    [[nodiscard]] inline vec3fa lerp(const vec3fa& a, const vec3fa& b, const vec3fa& t) noexcept { return madd(t, b - a, a); }

    [[nodiscard]] inline vec3fa lerp(const vec3fa& a, const vec3fa& b, const float t) noexcept { return madd(vec3fa(t), b - a, a); }

    ////////////////////////////////////////////////////////////////
    // Trigonometry.
    ////////////////////////////////////////////////////////////////

    [[nodiscard]] inline vec3fa acos(const vec3fa& lhs) noexcept { return vec3fa(acos(lhs.x), acos(lhs.y), acos(lhs.z)); }

    [[nodiscard]] inline vec3fa asin(const vec3fa& lhs) noexcept { return vec3fa(asin(lhs.x), asin(lhs.y), asin(lhs.z)); }

    [[nodiscard]] inline vec3fa atan(const vec3fa& lhs) noexcept { return vec3fa(atan(lhs.x), atan(lhs.y), atan(lhs.z)); }

    [[nodiscard]] inline vec3fa atan2(const vec3fa& lhs, const vec3fa& rhs) noexcept { return vec3fa(atan2(lhs.x, rhs.x), atan2(lhs.y, rhs.y), atan2(lhs.z, rhs.z)); }

    [[nodiscard]] inline vec3fa cos(const vec3fa& lhs) noexcept { return vec3fa(cos(lhs.x), cos(lhs.y), cos(lhs.z)); }

    [[nodiscard]] inline vec3fa cosh(const vec3fa& lhs) noexcept { return vec3fa(cosh(lhs.x), cosh(lhs.y), cosh(lhs.z)); }

    [[nodiscard]] inline vec3fa sin(const vec3fa& lhs) noexcept { return vec3fa(sin(lhs.x), sin(lhs.y), sin(lhs.z)); }

    [[nodiscard]] inline vec3fa sinh(const vec3fa& lhs) noexcept { return vec3fa(sinh(lhs.x), sinh(lhs.y), sinh(lhs.z)); }

    [[nodiscard]] inline vec3fa tan(const vec3fa& lhs) noexcept { return vec3fa(tan(lhs.x), tan(lhs.y), tan(lhs.z)); }

    [[nodiscard]] inline vec3fa tanh(const vec3fa& lhs) noexcept { return vec3fa(tanh(lhs.x), tanh(lhs.y), tanh(lhs.z)); }

    ////////////////////////////////////////////////////////////////
    // Exponential / Logarithmic.
    ////////////////////////////////////////////////////////////////

    template<size_t Precision = 5>
    [[nodiscard]] vec3fa exp2(const vec3fa& lhs) noexcept
    {
        static_assert(Precision >= 2 && Precision <= 5, "Provided precision is outside of supported range.");

        // Based on http://jrfonseca.blogspot.com/2008/09/fast-sse2-pow-tables-or-polynomials.html.
        const vec4fa x = vec4fa(clamp(lhs, -126.99999f, 129.00000f));
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

        return vec3fa(expipart * expfpart);
    }

    template<size_t Precision = 5>
    [[nodiscard]] vec3fa log2(const vec3fa& lhs) noexcept
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

        // Must still deal with edge cases. Also in vec4fa and vec8fa.

        return vec3fa(p * (mant - one) + exp);
    }

    template<size_t Precision = 5>
    [[nodiscard]] vec3fa exp(const vec3fa& lhs) noexcept { return exp2<Precision>(lhs * log2<Precision>(vec3fa(m_e))); }

    template<size_t Precision = 5>
    [[nodiscard]] vec3fa log(const vec3fa& lhs) noexcept { return log2<Precision>(lhs) / log2<Precision>(vec3fa(m_e)); }

    template<size_t Precision = 5>
    [[nodiscard]] vec3fa log10(const vec3fa& lhs) noexcept { return log2<Precision>(lhs) / log2<Precision>(vec3fa(10.0f)); }

    ////////////////////////////////////////////////////////////////
    // Power.
    ////////////////////////////////////////////////////////////////

    template<size_t Precision = 5>
    [[nodiscard]] vec3fa pow(const vec3fa& lhs, const vec3fa& rhs) noexcept { return exp2<Precision>(rhs * log2<Precision>(lhs)); }

    template<size_t Precision = 5>
    [[nodiscard]] vec3fa pow(const vec3fa& lhs, const float rhs) noexcept { return exp2<Precision>(vec3fa(rhs) * log2<Precision>(lhs)); }

    template<size_t Precision = 5>
    [[nodiscard]] vec3fa pow(const float lhs, const vec3fa& rhs) noexcept { return exp2<Precision>(rhs * log2<Precision>(vec3fa(lhs))); }

    [[nodiscard]] inline vec3fa sqr(const vec3fa& lhs) noexcept { return lhs * lhs; }

    [[nodiscard]] inline vec3fa sqrt(const vec3fa& lhs) noexcept { return vec3fa(_mm_sqrt_ps(lhs)); }

    [[nodiscard]] inline vec3fa rsqrt(const vec3fa& lhs) noexcept { return vec3fa(_mm_rsqrt_ps(lhs)); }

    ////////////////////////////////////////////////////////////////
    // Rounding, abs, etc.
    ////////////////////////////////////////////////////////////////

    [[nodiscard]] inline vec3fa abs(const vec3fa& lhs) noexcept
    {
        const __m128 mask = _mm_castsi128_ps(_mm_set1_epi32(0x7fffffff));
        return vec3fa(_mm_and_ps(lhs, mask));
    }

#ifdef __SSE4_1__
    [[nodiscard]] inline vec3fa round(const vec3fa& lhs) noexcept { return vec3fa(_mm_round_ps(lhs, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC)); }

    [[nodiscard]] inline vec3fa ceil(const vec3fa& lhs) noexcept { return vec3fa(_mm_round_ps(lhs, _MM_FROUND_CEIL)); }

    [[nodiscard]] inline vec3fa floor(const vec3fa& lhs) noexcept { return vec3fa(_mm_round_ps(lhs, _MM_FROUND_FLOOR)); }

    [[nodiscard]] inline vec3fa frac(const vec3fa& lhs) noexcept { return vec3fa(_mm_sub_ps(lhs, _mm_round_ps(lhs, _MM_FROUND_TRUNC))); }

    [[nodiscard]] inline vec3fa trunc(const vec3fa& lhs) noexcept { return vec3fa(_mm_round_ps(lhs, _MM_FROUND_TRUNC)); }
#endif

    ////////////////////////////////////////////////////////////////
    // Select.
    ////////////////////////////////////////////////////////////////

    [[nodiscard]] inline vec3fa select(const vec3fa& t, const vec3fa& f, const vec3ba& b) noexcept
    {
#ifdef __SSE4_1__
        return vec3fa(_mm_blendv_ps(f, t, _mm_castsi128_ps(b)));
#else
        return vec3fa(math::select(t.x, f.x, b.x & 0x80000000), math::select(t.y, f.y, b.y & 0x80000000), math::select(t.z, f.z, b.z & 0x80000000));
#endif
    }

    ////////////////////////////////////////////////////////////////
    // Output.
    ////////////////////////////////////////////////////////////////

    inline std::ostream& operator<<(std::ostream& out, const vec3fa& v) { return out << "(" << v.x << ", " << v.y << ", " << v.z << ")"; }

}
