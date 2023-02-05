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

#include "math/vector/simd/vec4ia.h"
#include "math/vector/simd/vec8ba.h"

namespace math
{
#ifdef __AVX__
    struct alignas(32) vec8ia
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
            struct
            {
                int32_t data[8];
            };
        };
#ifdef _MSC_VER
#pragma warning(pop)
#endif

        ////////////////////////////////////////////////////////////////
        // Constructors.
        ////////////////////////////////////////////////////////////////

        [[nodiscard]] vec8ia() noexcept : m256(_mm256_set1_epi32(0)) {}

        [[nodiscard]] explicit vec8ia(const int32_t v) noexcept : m256(_mm256_set1_epi32(v)) {}

        [[nodiscard]] vec8ia(const int32_t a, const int32_t b, const int32_t c, const int32_t d, const int32_t e, const int32_t f, const int32_t g, const int32_t h) noexcept : m256(_mm256_setr_epi32(a, b, c, d, e, f, g, h)) {}

        [[nodiscard]] vec8ia(const __m256i m256) noexcept : m256(m256) {}

        [[nodiscard]] explicit vec8ia(const __m256 m256) noexcept : m256(_mm256_castps_si256(m256)) {}

        [[nodiscard]] vec8ia(const vec8ia& rhs) noexcept : m256(rhs.m256) {}

        [[nodiscard]] vec8ia(const __m128i low, const __m128i high) noexcept : m256(_mm256_set_m128i(high, low)) {}

        [[nodiscard]] vec8ia(const vec4ia& low, const vec4ia& high) noexcept : m256(_mm256_set_m128i(high, low)) {}

        [[nodiscard]] explicit vec8ia(const vec<int32_t, 8>& rhs) noexcept : m256(_mm256_setr_epi32(rhs[0], rhs[1], rhs[2], rhs[3], rhs[4], rhs[5], rhs[6], rhs[7])) {}

        ////////////////////////////////////////////////////////////////
        // Assignment operators.
        ////////////////////////////////////////////////////////////////

        vec8ia& operator=(const vec8ia& rhs) noexcept { m256 = rhs.m256; return *this; }

        vec8ia& operator=(const int32_t rhs) noexcept { m256 = _mm256_set1_epi32(rhs); return *this; }

        ////////////////////////////////////////////////////////////////
        // Load/store.
        ////////////////////////////////////////////////////////////////

        [[nodiscard]] static vec8ia load(const void* const ptr) { return vec8ia(_mm256_load_si256(static_cast<const __m256i*>(ptr))); }

        [[nodiscard]] static vec8ia loadu(const void* const ptr) { return vec8ia(_mm256_loadu_si256(static_cast<const __m256i*>(ptr))); }

        static void store(void* ptr, const vec8ia & v) { _mm256_store_si256(static_cast<__m256i*>(ptr), v.m256); }

        static void storeu(void* ptr, const vec8ia & v) { _mm256_storeu_si256(static_cast<__m256i*>(ptr), v.m256); }

        ////////////////////////////////////////////////////////////////
        // Defaulted constructors and operators.
        ////////////////////////////////////////////////////////////////

        ~vec8ia() noexcept = default;

        vec8ia(vec8ia&& rhs) noexcept = default;

        vec8ia& operator=(vec8ia&& rhs) noexcept = default;

        ////////////////////////////////////////////////////////////////
        // Casting operators.
        ////////////////////////////////////////////////////////////////

        [[nodiscard]] operator const __m256i& () const noexcept { return m256; }
        
        [[nodiscard]] operator __m256i& () noexcept { return m256; }
        
        [[nodiscard]] explicit operator __m256 () const noexcept { return _mm256_castsi256_ps(m256); }

        [[nodiscard]] explicit operator vec<int32_t, 8>() const noexcept { return vec<int32_t, 8>(data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7]); }

        ////////////////////////////////////////////////////////////////
        // Element access.
        ////////////////////////////////////////////////////////////////

        [[nodiscard]] const int32_t& operator[](const size_t i) const { assert(i < 8); return data[i]; }

        [[nodiscard]] int32_t& operator[](const size_t i) { assert(i < 8); return data[i]; }
    };

    ////////////////////////////////////////////////////////////////
    // Arithmetic operators.
    ////////////////////////////////////////////////////////////////

#ifdef __AVX2__
    [[nodiscard]] inline vec8ia operator+(const vec8ia& lhs, const vec8ia& rhs) noexcept { return _mm256_add_epi32(lhs, rhs); }

    [[nodiscard]] inline vec8ia operator+(const vec8ia& lhs, const int32_t rhs) noexcept { return lhs + vec8ia(rhs); }

    [[nodiscard]] inline vec8ia operator+(const int32_t lhs, const vec8ia& rhs) noexcept { return vec8ia(lhs) + rhs; }

    [[nodiscard]] inline vec8ia operator-(const vec8ia& lhs, const vec8ia& rhs) noexcept { return _mm256_sub_epi32(lhs, rhs); }

    [[nodiscard]] inline vec8ia operator-(const vec8ia& lhs, const int32_t rhs) noexcept { return lhs - vec8ia(rhs); }

    [[nodiscard]] inline vec8ia operator-(const int32_t lhs, const vec8ia& rhs) noexcept { return vec8ia(lhs) - rhs; }

    [[nodiscard]] inline vec8ia operator-(const vec8ia& lhs) noexcept { const __m256i mask = _mm256_set1_epi32(0x80000000); return _mm256_xor_si256(lhs, mask); }

    [[nodiscard]] inline vec8ia operator*(const vec8ia& lhs, const vec8ia& rhs) noexcept { return _mm256_mullo_epi32(lhs, rhs); }

    [[nodiscard]] inline vec8ia operator*(const vec8ia& lhs, const int32_t rhs) noexcept { return lhs * vec8ia(rhs); }

    [[nodiscard]] inline vec8ia operator*(const int32_t lhs, const vec8ia& rhs) noexcept { return vec8ia(lhs) * rhs; }

    [[nodiscard]] inline vec8ia operator/(const vec8ia& lhs, const vec8ia& rhs) noexcept
    {
        // Cast to float and round with truncation.
        return _mm256_cvtps_epi32(_mm256_round_ps(_mm256_div_ps(_mm256_cvtepi32_ps(lhs), _mm256_cvtepi32_ps(rhs)), _MM_FROUND_TRUNC));
    }

    [[nodiscard]] inline vec8ia operator/(const vec8ia& lhs, const int32_t rhs) noexcept { return lhs / vec8ia(rhs); }

    [[nodiscard]] inline vec8ia operator/(const int32_t lhs, const vec8ia& rhs) noexcept { return vec8ia(lhs) / rhs; }

    inline vec8ia& operator+=(vec8ia& lhs, const vec8ia& rhs) noexcept { return lhs = lhs + rhs; }

    inline vec8ia& operator+=(vec8ia& lhs, const int32_t rhs) noexcept { return lhs = lhs + rhs; }

    inline vec8ia& operator-=(vec8ia& lhs, const vec8ia& rhs) noexcept { return lhs = lhs - rhs; }

    inline vec8ia& operator-=(vec8ia& lhs, const int32_t rhs) noexcept { return lhs = lhs - rhs; }

    inline vec8ia& operator*=(vec8ia& lhs, const vec8ia& rhs) noexcept { return lhs = lhs * rhs; }

    inline vec8ia& operator*=(vec8ia& lhs, const int32_t rhs) noexcept { return lhs = lhs * rhs; }

    inline vec8ia& operator/=(vec8ia& lhs, const vec8ia& rhs) noexcept { return lhs = lhs / rhs; }

    inline vec8ia& operator/=(vec8ia& lhs, const int32_t rhs) noexcept { return lhs = lhs / rhs; }
#endif

    ////////////////////////////////////////////////////////////////
    // Comparison operators.
    ////////////////////////////////////////////////////////////////

#ifdef __AVX2__
    [[nodiscard]] inline bool operator==(const vec8ia& lhs, const vec8ia& rhs) noexcept { return (_mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(lhs, rhs))) & 0x31) == 0x31; }

    [[nodiscard]] inline bool operator!=(const vec8ia& lhs, const vec8ia& rhs) noexcept { return (_mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(lhs, rhs))) & 0x31) != 0x31; }
#endif

    ////////////////////////////////////////////////////////////////
    // Per-element comparisons.
    ////////////////////////////////////////////////////////////////

#ifdef __AVX2__
    [[nodiscard]] inline vec8ba cmpeq(const vec8ia& lhs, const vec8ia& rhs) noexcept { return _mm256_cmpeq_epi32(lhs, rhs); }

    [[nodiscard]] inline vec8ba cmpeq(const vec8ia& lhs, const int32_t rhs) noexcept { return cmpeq(lhs, vec8ia(rhs)); }

    [[nodiscard]] inline vec8ba cmpeq(const int32_t lhs, const vec8ia& rhs) noexcept { return cmpeq(vec8ia(lhs), rhs); }

    [[nodiscard]] inline vec8ba cmpneq(const vec8ia& lhs, const vec8ia& rhs) noexcept { return _mm256_andnot_si256(_mm256_cmpeq_epi32(lhs, rhs), _mm256_set1_epi32(-1)); }

    [[nodiscard]] inline vec8ba cmpneq(const vec8ia& lhs, const int32_t rhs) noexcept { return cmpneq(lhs, vec8ia(rhs)); }

    [[nodiscard]] inline vec8ba cmpneq(const int32_t lhs, const vec8ia& rhs) noexcept { return cmpneq(vec8ia(lhs), rhs); }

    [[nodiscard]] inline vec8ba cmplt(const vec8ia& lhs, const vec8ia& rhs) noexcept { return !(vec8ba(_mm256_cmpgt_epi32(lhs, rhs)) | cmpeq(lhs, rhs)); }

    [[nodiscard]] inline vec8ba cmplt(const vec8ia& lhs, const int32_t rhs) noexcept { return cmplt(lhs, vec8ia(rhs)); }

    [[nodiscard]] inline vec8ba cmplt(const int32_t lhs, const vec8ia& rhs) noexcept { return cmplt(vec8ia(lhs), rhs); }

    [[nodiscard]] inline vec8ba cmpgt(const vec8ia& lhs, const vec8ia& rhs) noexcept { return _mm256_cmpgt_epi32(lhs, rhs); }

    [[nodiscard]] inline vec8ba cmpgt(const vec8ia& lhs, const int32_t rhs) noexcept { return cmpgt(lhs, vec8ia(rhs)); }

    [[nodiscard]] inline vec8ba cmpgt(const int32_t lhs, const vec8ia& rhs) noexcept { return cmpgt(vec8ia(lhs), rhs); }

    [[nodiscard]] inline vec8ba cmple(const vec8ia& lhs, const vec8ia& rhs) noexcept { return !(vec8ba(_mm256_cmpgt_epi32(lhs, rhs))); }

    [[nodiscard]] inline vec8ba cmple(const vec8ia& lhs, const int32_t rhs) noexcept { return cmple(lhs, vec8ia(rhs)); }

    [[nodiscard]] inline vec8ba cmple(const int32_t lhs, const vec8ia& rhs) noexcept { return cmple(vec8ia(lhs), rhs); }

    [[nodiscard]] inline vec8ba cmpge(const vec8ia& lhs, const vec8ia& rhs) noexcept { return vec8ba(_mm256_cmpgt_epi32(lhs, rhs)) | cmpeq(lhs, rhs); }

    [[nodiscard]] inline vec8ba cmpge(const vec8ia& lhs, const int32_t rhs) noexcept { return cmpge(lhs, vec8ia(rhs)); }

    [[nodiscard]] inline vec8ba cmpge(const int32_t lhs, const vec8ia& rhs) noexcept { return cmpge(vec8ia(lhs), rhs); }
#endif

    ////////////////////////////////////////////////////////////////
    // Min/max, abs and clamp.
    ////////////////////////////////////////////////////////////////

#ifdef __AVX2__
    [[nodiscard]] inline vec8ia min(const vec8ia& lhs, const vec8ia& rhs) noexcept { return _mm256_min_epi32(lhs, rhs); }

    [[nodiscard]] inline vec8ia min(const vec8ia& lhs, const int32_t rhs) noexcept { return min(lhs, vec8ia(rhs)); }

    [[nodiscard]] inline vec8ia min(const int32_t lhs, const vec8ia& rhs) noexcept { return min(vec8ia(lhs), rhs); }

    [[nodiscard]] inline vec8ia max(const vec8ia& lhs, const vec8ia& rhs) noexcept { return _mm256_max_epi32(lhs, rhs); }

    [[nodiscard]] inline vec8ia max(const vec8ia& lhs, const int32_t rhs) noexcept { return max(lhs, vec8ia(rhs)); }

    [[nodiscard]] inline vec8ia max(const int32_t lhs, const vec8ia& rhs) noexcept { return max(vec8ia(lhs), rhs); }

    [[nodiscard]] inline vec8ia clamp(const vec8ia& a, const vec8ia& min, const vec8ia& max) noexcept { return math::max(min, math::min(a, max)); }

    [[nodiscard]] inline vec8ia clamp(const vec8ia& a, const vec8ia& min, const int32_t max) noexcept { return clamp(a, min, vec8ia(max)); }

    [[nodiscard]] inline vec8ia clamp(const vec8ia& a, const int32_t min, const vec8ia& max) noexcept { return clamp(a, vec8ia(min), max); }

    [[nodiscard]] inline vec8ia clamp(const vec8ia& a, const int32_t min, const int32_t max) noexcept { return clamp(a, vec8ia(min), vec8ia(max)); }
#endif

    ////////////////////////////////////////////////////////////////
    // Reduction.
    ////////////////////////////////////////////////////////////////

#ifdef __AVX2__
    [[nodiscard]] inline int32_t reduce_add(const vec8ia& lhs) noexcept
    {
        const vec4ia low4 = _mm256_castsi256_si128(lhs);
        const vec4ia high4 = _mm256_extracti128_si256(lhs, 1);
        const vec4ia sum0 = low4 + high4;
        const vec4ia sum1 = sum0 + vec4ia(_mm_movehl_ps(static_cast<__m128>(sum0), static_cast<__m128>(sum0)));
        const vec4ia sum2 = sum1 + vec4ia(_mm_shuffle_ps(static_cast<__m128>(sum1), static_cast<__m128>(sum1), 0x1));
        return _mm_cvtsi128_si32(sum2);
    }

    [[nodiscard]] inline int32_t reduce_mul(const vec8ia& lhs) noexcept
    {
        const vec4ia low4 = _mm256_castsi256_si128(lhs);
        const vec4ia high4 = _mm256_extracti128_si256(lhs, 1);
        const vec4ia sum0 = low4 * high4;
        const vec4ia sum1 = sum0 * vec4ia(_mm_movehl_ps(static_cast<__m128>(sum0), static_cast<__m128>(sum0)));
        const vec4ia sum2 = sum1 * vec4ia(_mm_shuffle_ps(static_cast<__m128>(sum1), static_cast<__m128>(sum1), 0x1));
        return _mm_cvtsi128_si32(sum2);
    }

    [[nodiscard]] inline int32_t reduce_min(const vec8ia& lhs) noexcept
    {
        const vec4ia low4 = _mm256_castsi256_si128(lhs);
        const vec4ia high4 = _mm256_extracti128_si256(lhs, 1);
        const vec4ia sum0 = min(low4, high4);
        const vec4ia sum1 = min(sum0, vec4ia(_mm_movehl_ps(static_cast<__m128>(sum0), static_cast<__m128>(sum0))));
        const vec4ia sum2 = min(sum1, vec4ia(_mm_shuffle_ps(static_cast<__m128>(sum1), static_cast<__m128>(sum1), 0x1)));
        return _mm_cvtsi128_si32(sum2);
    }

    [[nodiscard]] inline int32_t reduce_max(const vec8ia& lhs) noexcept
    {
        const vec4ia low4 = _mm256_castsi256_si128(lhs);
        const vec4ia high4 = _mm256_extracti128_si256(lhs, 1);
        const vec4ia sum0 = max(low4, high4);
        const vec4ia sum1 = max(sum0, vec4ia(_mm_movehl_ps(static_cast<__m128>(sum0), static_cast<__m128>(sum0))));
        const vec4ia sum2 = max(sum1, vec4ia(_mm_shuffle_ps(static_cast<__m128>(sum1), static_cast<__m128>(sum1), 0x1)));
        return _mm_cvtsi128_si32(sum2);
    }
#endif

    ////////////////////////////////////////////////////////////////
    // Dot product etc.
    ////////////////////////////////////////////////////////////////

#if 0
    inline int32_t dot(const vec8ia& lhs, const vec8ia& rhs) { return reduce_add(lhs * rhs); }

    inline float length(const vec8ia& lhs) { return sqrt(static_cast<float>(dot(lhs, lhs))); }

    inline int32_t sqr_length(const vec8ia& lhs) { return dot(lhs, lhs); }

    inline float rcp_length(const vec8ia& lhs) { return rsqrt(static_cast<float>(dot(lhs, lhs))); }

    inline vec8ia normalize(const vec8ia& lhs) { return _mm256_cvtps_epi32(_mm256_cvtepi32_ps(lhs) * rcp_length(lhs)); }

    inline vec8ia normalize(const vec8ia& lhs, int32_t& length) { length = math::length(lhs); return lhs / length; }

    inline int32_t distance(const vec8ia& lhs, const vec8ia& rhs) { return length(lhs - rhs); }
#endif

    ////////////////////////////////////////////////////////////////
    // Exponential / Logarithmic.
    ////////////////////////////////////////////////////////////////

#if 0
    inline vec8ia exp(const vec8ia& lhs) { return _mm256_cvtps_epi32(exp(_mm256_cvtepi32_ps(lhs))); }

    inline vec8ia exp2(const vec8ia& lhs) { return _mm256_cvtps_epi32(exp2(_mm256_cvtepi32_ps(lhs))); }

    inline vec8ia log(const vec8ia& lhs) { return _mm256_cvtps_epi32(log(_mm256_cvtepi32_ps(lhs))); }

    inline vec8ia log2(const vec8ia& lhs) { return _mm256_cvtps_epi32(log2(_mm256_cvtepi32_ps(lhs))); }

    inline vec8ia log10(const vec8ia& lhs) { return _mm256_cvtps_epi32(log10(_mm256_cvtepi32_ps(lhs))); }
#endif

    ////////////////////////////////////////////////////////////////
    // Power.
    ////////////////////////////////////////////////////////////////

#if 0
    inline vec8ia pow(const vec8ia& lhs, const vec8ia& rhs) { return _mm256_cvtps_epi32(pow(_mm256_cvtepi32_ps(lhs), _mm256_cvtepi32_ps(rhs))); }

    inline vec8ia sqr(const vec8ia& lhs) { return lhs * lhs; }

    inline vec8ia sqrt(const vec8ia& lhs) { return _mm256_cvtps_epi32(sqrt(_mm256_cvtepi32_ps(lhs))); }

    inline vec8ia rsqrt(const vec8ia& lhs) { return _mm256_cvtps_epi32(rsqrt(_mm256_cvtepi32_ps(lhs))); }
#endif

    ////////////////////////////////////////////////////////////////
    // Rounding, abs, etc.
    ////////////////////////////////////////////////////////////////

#ifdef __AVX2__
    [[nodiscard]] inline vec8ia abs(const vec8ia& lhs) noexcept
    {
        const __m256i mask = _mm256_set1_epi32(0x7fffffff);
        return _mm256_and_si256(lhs, mask);
    }
#endif

    ////////////////////////////////////////////////////////////////
    // Select.
    ////////////////////////////////////////////////////////////////

    [[nodiscard]] inline vec8ia select(const vec8ia& t, const vec8ia& f, const vec8ba& b) noexcept
    {
        return vec8ia(_mm256_blendv_ps(_mm256_castsi256_ps(f), _mm256_castsi256_ps(t), _mm256_castsi256_ps(b)));
    }

    ////////////////////////////////////////////////////////////////
    // Multiply and add.
    ////////////////////////////////////////////////////////////////

#ifdef __AVX2__
    [[nodiscard]] inline vec8ia madd(const vec8ia& a, const vec8ia& b, const vec8ia& c) noexcept { return a * b + c; }

    [[nodiscard]] inline vec8ia nmadd(const vec8ia& a, const vec8ia& b, const vec8ia& c) noexcept { return -a * b + c; }

    [[nodiscard]] inline vec8ia msub(const vec8ia& a, const vec8ia& b, const vec8ia& c) noexcept { return a * b - c; }

    [[nodiscard]] inline vec8ia nmsub(const vec8ia& a, const vec8ia& b, const vec8ia& c) noexcept { return -a * b - c; }
#endif

    ////////////////////////////////////////////////////////////////
    // Shift operators.
    ////////////////////////////////////////////////////////////////

#ifdef __AVX2__
    [[nodiscard]] inline vec8ia operator<<(const vec8ia& lhs, const vec8ia& rhs) noexcept { return _mm256_sllv_epi32(lhs, rhs); }

    [[nodiscard]] inline vec8ia operator<<(const vec8ia& lhs, const int32_t rhs) noexcept { return _mm256_slli_epi32(lhs, rhs); }

    [[nodiscard]] inline vec8ia operator<<(const int32_t lhs, const vec8ia& rhs) noexcept { return _mm256_sllv_epi32(_mm256_set1_epi32(lhs), rhs); }

    [[nodiscard]] inline vec8ia operator>>(const vec8ia& lhs, const vec8ia& rhs) noexcept { return _mm256_srlv_epi32(lhs, rhs); }

    [[nodiscard]] inline vec8ia operator>>(const vec8ia& lhs, const int32_t rhs) noexcept { return _mm256_srli_epi32(lhs, rhs); }

    [[nodiscard]] inline vec8ia operator>>(const int32_t lhs, const vec8ia& rhs) noexcept { return _mm256_srlv_epi32(_mm256_set1_epi32(lhs), rhs); }

    inline vec8ia& operator<<=(vec8ia& lhs, const vec8ia& rhs) noexcept { return lhs = lhs << rhs; }

    inline vec8ia& operator<<=(vec8ia& lhs, const int32_t rhs) noexcept { return lhs = lhs << rhs; }

    inline vec8ia& operator>>=(vec8ia& lhs, const vec8ia& rhs) noexcept { return lhs = lhs >> rhs; }

    inline vec8ia& operator>>=(vec8ia& lhs, const int32_t rhs) noexcept { return lhs = lhs >> rhs; }
#endif

    ////////////////////////////////////////////////////////////////
    // Bitwise operators.
    ////////////////////////////////////////////////////////////////

#ifdef __AVX2__
    [[nodiscard]] inline vec8ia operator|(const vec8ia& lhs, const vec8ia& rhs) noexcept { return _mm256_or_si256(lhs, rhs); }

    [[nodiscard]] inline vec8ia operator|(const vec8ia& lhs, const int32_t rhs) noexcept { return _mm256_or_si256(lhs, vec8ia(rhs)); }

    [[nodiscard]] inline vec8ia operator|(const int32_t lhs, const vec8ia& rhs) noexcept { return _mm256_or_si256(vec8ia(lhs), rhs); }

    [[nodiscard]] inline vec8ia operator&(const vec8ia& lhs, const vec8ia& rhs) noexcept { return _mm256_and_si256(lhs, rhs); }

    [[nodiscard]] inline vec8ia operator&(const vec8ia& lhs, const int32_t rhs) noexcept { return _mm256_and_si256(lhs, vec8ia(rhs)); }

    [[nodiscard]] inline vec8ia operator&(const int32_t lhs, const vec8ia& rhs) noexcept { return _mm256_and_si256(vec8ia(lhs), rhs); }

    [[nodiscard]] inline vec8ia operator^(const vec8ia& lhs, const vec8ia& rhs) noexcept { return _mm256_xor_si256(lhs, rhs); }

    [[nodiscard]] inline vec8ia operator^(const vec8ia& lhs, const int32_t rhs) noexcept { return _mm256_xor_si256(lhs, vec8ia(rhs)); }

    [[nodiscard]] inline vec8ia operator^(const int32_t lhs, const vec8ia& rhs) noexcept { return _mm256_xor_si256(vec8ia(lhs), rhs); }

    [[nodiscard]] inline vec8ia operator~(const vec8ia& lhs) noexcept { return _mm256_sub_epi32(_mm256_set1_epi32(0), lhs); }

    inline vec8ia& operator|=(vec8ia& lhs, const vec8ia& rhs) noexcept { return lhs = lhs | rhs; }

    inline vec8ia& operator|=(vec8ia& lhs, const int32_t rhs) noexcept { return lhs = lhs | rhs; }

    inline vec8ia& operator&=(vec8ia& lhs, const vec8ia& rhs) noexcept { return lhs = lhs & rhs; }

    inline vec8ia& operator&=(vec8ia& lhs, const int32_t rhs) noexcept { return lhs = lhs & rhs; }

    inline vec8ia& operator^=(vec8ia& lhs, const vec8ia& rhs) noexcept { return lhs = lhs ^ rhs; }

    inline vec8ia& operator^=(vec8ia& lhs, const int32_t rhs) noexcept { return lhs = lhs ^ rhs; }
#endif

    ////////////////////////////////////////////////////////////////
    // Output.
    ////////////////////////////////////////////////////////////////

    inline std::ostream& operator<<(std::ostream& out, const vec8ia& v) { return out << "(" << v[0] << ", " << v[1] << ", " << v[2] << ", " << v[3] << ", " << v[4] << ", " << v[5] << ", " << v[6] << ", " << v[7] << ")"; }
#endif
}
