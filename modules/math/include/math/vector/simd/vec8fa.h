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

#include "math/vector/simd/vec4fa.h"
#include "math/vector/simd/vec8ba.h"

namespace math
{
#ifdef __AVX__
    struct alignas(32) vec8fa
    {
        static constexpr size_t size = 8;
        using element_type = float;

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4201)
#endif
        union
        {
            __m256 m256;
            float data[8];
        };
#ifdef _MSC_VER
#pragma warning(pop)
#endif

        ////////////////////////////////////////////////////////////////
        // Constructors.
        ////////////////////////////////////////////////////////////////

        [[nodiscard]] vec8fa() noexcept : m256(_mm256_set1_ps(0)) {}

        [[nodiscard]] explicit vec8fa(const float v) noexcept : m256(_mm256_set1_ps(v)) {}

        [[nodiscard]] vec8fa(const float a, const float b, const float c, const float d, const float e, const float f, const float g, const float h) noexcept : m256(_mm256_setr_ps(a, b, c, d, e, f, g, h)) {}

        [[nodiscard]] vec8fa(const __m256 m256) noexcept : m256(m256) {}

        [[nodiscard]] explicit vec8fa(const __m256i m256)  noexcept : m256(_mm256_castsi256_ps(m256)) {}

        [[nodiscard]] vec8fa(const vec8fa& rhs) noexcept : m256(rhs.m256) {}

        [[nodiscard]] vec8fa(const __m128 low, const __m128 high) noexcept : m256(_mm256_set_m128(high, low)) {}

        [[nodiscard]] vec8fa(const vec4fa& low, const vec4fa& high) noexcept : m256(_mm256_set_m128(high, low)) {}

        [[nodiscard]] explicit vec8fa(const vec<float, 8>& rhs) noexcept : m256(_mm256_setr_ps(rhs[0], rhs[1], rhs[2], rhs[3], rhs[4], rhs[5], rhs[6], rhs[7])) {}

        ////////////////////////////////////////////////////////////////
        // Assignment operators.
        ////////////////////////////////////////////////////////////////

        vec8fa& operator=(const vec8fa& rhs) noexcept { m256 = rhs.m256; return *this; }

        vec8fa& operator=(const float rhs) noexcept { m256 = _mm256_set1_ps(rhs); return *this; }

        ////////////////////////////////////////////////////////////////
        // Load/store.
        ////////////////////////////////////////////////////////////////

        [[nodiscard]] static vec8fa load(const void* const ptr) { return _mm256_load_ps(static_cast<const float*>(ptr)); }

        [[nodiscard]] static vec8fa loadu(const void* const ptr) { return _mm256_loadu_ps(static_cast<const float*>(ptr)); }

        static void store(void* ptr, const vec8fa& v) { _mm256_store_ps(static_cast<float*>(ptr), v.m256); }

        static void storeu(void* ptr, const vec8fa& v) { _mm256_storeu_ps(static_cast<float*>(ptr), v.m256); }

        ////////////////////////////////////////////////////////////////
        // Defaulted constructors and operators.
        ////////////////////////////////////////////////////////////////

        ~vec8fa() noexcept = default;

        vec8fa(vec8fa&& rhs) noexcept = default;

        vec8fa& operator=(vec8fa&& rhs) noexcept = default;

        ////////////////////////////////////////////////////////////////
        // Casting operators.
        ////////////////////////////////////////////////////////////////

        [[nodiscard]] operator const __m256& () const noexcept { return m256; }

        [[nodiscard]] operator __m256& () noexcept { return m256; }

        [[nodiscard]] explicit operator __m256i () const noexcept { return _mm256_castps_si256(m256); }

        [[nodiscard]] explicit operator vec<float, 8>() const noexcept { return vec<float, 8>(data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7]); }

        ////////////////////////////////////////////////////////////////
        // Element access.
        ////////////////////////////////////////////////////////////////

        [[nodiscard]] const float& operator[](const size_t i) const { assert(i < 8); return data[i]; }

        [[nodiscard]] float& operator[](const size_t i) { assert(i < 8); return data[i]; }
    };

    ////////////////////////////////////////////////////////////////
    // Shuffle.
    ////////////////////////////////////////////////////////////////

    /*template<int32_t i0, int32_t i1, int32_t i2, int32_t i3, int32_t i4, int32_t i5, int32_t i6, int32_t i7>
    vec8fa shuffle(const vec8fa& v) { return _mm256_permute_ps(v, _MM_SHUFFLE(i7, i6, i5, i4, i3, i2, i1, i0)); }*/

    ////////////////////////////////////////////////////////////////
    // Arithmetic operators.
    ////////////////////////////////////////////////////////////////

    [[nodiscard]] inline vec8fa operator+(const vec8fa& lhs, const vec8fa& rhs) noexcept { return _mm256_add_ps(lhs, rhs); }

    [[nodiscard]] inline vec8fa operator+(const vec8fa& lhs, const float rhs) noexcept { return lhs + vec8fa(rhs); }

    [[nodiscard]] inline vec8fa operator+(const float lhs, const vec8fa& rhs) noexcept { return vec8fa(lhs) + rhs; }

    [[nodiscard]] inline vec8fa operator-(const vec8fa& lhs, const vec8fa& rhs) noexcept { return _mm256_sub_ps(lhs, rhs); }

    [[nodiscard]] inline vec8fa operator-(const vec8fa& lhs, const float rhs) noexcept { return lhs - vec8fa(rhs); }

    [[nodiscard]] inline vec8fa operator-(const float lhs, const vec8fa& rhs) noexcept { return vec8fa(lhs) - rhs; }

    [[nodiscard]] inline vec8fa operator-(const vec8fa& lhs) noexcept { const __m256 mask = _mm256_castsi256_ps(_mm256_set1_epi32(0x80000000)); return _mm256_xor_ps(lhs, mask); }

    [[nodiscard]] inline vec8fa operator*(const vec8fa& lhs, const vec8fa& rhs) noexcept { return _mm256_mul_ps(lhs, rhs); }

    [[nodiscard]] inline vec8fa operator*(const vec8fa& lhs, const float rhs) noexcept { return lhs * vec8fa(rhs); }

    [[nodiscard]] inline vec8fa operator*(const float lhs, const vec8fa& rhs) noexcept { return vec8fa(lhs) * rhs; }

    [[nodiscard]] inline vec8fa operator/(const vec8fa& lhs, const vec8fa& rhs) noexcept { return _mm256_div_ps(lhs, rhs); }

    [[nodiscard]] inline vec8fa operator/(const vec8fa& lhs, const float rhs) noexcept { return lhs / vec8fa(rhs); }

    [[nodiscard]] inline vec8fa operator/(const float lhs, const vec8fa& rhs) noexcept { return vec8fa(lhs) / rhs; }

    inline vec8fa& operator+=(vec8fa& lhs, const vec8fa& rhs) noexcept { return lhs = lhs + rhs; }

    inline vec8fa& operator+=(vec8fa& lhs, const float rhs) noexcept { return lhs = lhs + rhs; }

    inline vec8fa& operator-=(vec8fa& lhs, const vec8fa& rhs) noexcept { return lhs = lhs - rhs; }

    inline vec8fa& operator-=(vec8fa& lhs, const float rhs) noexcept { return lhs = lhs - rhs; }

    inline vec8fa& operator*=(vec8fa& lhs, const vec8fa& rhs) noexcept { return lhs = lhs * rhs; }

    inline vec8fa& operator*=(vec8fa& lhs, const float rhs) noexcept { return lhs = lhs * rhs; }

    inline vec8fa& operator/=(vec8fa& lhs, const vec8fa& rhs) noexcept { return lhs = lhs / rhs; }

    inline vec8fa& operator/=(vec8fa& lhs, const float rhs) noexcept { return lhs = lhs / rhs; }

    ////////////////////////////////////////////////////////////////
    // Comparison operators.
    ////////////////////////////////////////////////////////////////

    [[nodiscard]] inline bool operator==(const vec8fa& lhs, const vec8fa& rhs) noexcept { return (_mm256_movemask_ps(_mm256_cmp_ps(lhs, rhs, _CMP_EQ_UQ)) & 0x31) == 0x31; }

    [[nodiscard]] inline bool operator!=(const vec8fa& lhs, const vec8fa& rhs) noexcept { return (_mm256_movemask_ps(_mm256_cmp_ps(lhs, rhs, _CMP_EQ_UQ)) & 0x31) != 0x31; }

    ////////////////////////////////////////////////////////////////
    // Per-element comparisons.
    ////////////////////////////////////////////////////////////////

    [[nodiscard]] inline vec8ba cmpeq(const vec8fa& lhs, const vec8fa& rhs) noexcept { return vec8ba(_mm256_cmp_ps(lhs, rhs, _CMP_EQ_UQ)); }

    [[nodiscard]] inline vec8ba cmpeq(const vec8fa& lhs, const float rhs) noexcept { return cmpeq(lhs, vec8fa(rhs)); }

    [[nodiscard]] inline vec8ba cmpeq(const float lhs, const vec8fa& rhs) noexcept { return cmpeq(vec8fa(lhs), rhs); }

    [[nodiscard]] inline vec8ba cmpneq(const vec8fa& lhs, const vec8fa& rhs) noexcept { return vec8ba(_mm256_cmp_ps(lhs, rhs, _CMP_NEQ_UQ)); }

    [[nodiscard]] inline vec8ba cmpneq(const vec8fa& lhs, const float rhs) noexcept { return cmpneq(lhs, vec8fa(rhs)); }

    [[nodiscard]] inline vec8ba cmpneq(const float lhs, const vec8fa& rhs) noexcept { return cmpneq(vec8fa(lhs), rhs); }

    [[nodiscard]] inline vec8ba cmplt(const vec8fa& lhs, const vec8fa& rhs) noexcept { return vec8ba(_mm256_cmp_ps(lhs, rhs, _CMP_LT_OQ)); }

    [[nodiscard]] inline vec8ba cmplt(const vec8fa& lhs, const float rhs) noexcept { return cmplt(lhs, vec8fa(rhs)); }

    [[nodiscard]] inline vec8ba cmplt(const float lhs, const vec8fa& rhs) noexcept { return cmplt(vec8fa(lhs), rhs); }

    [[nodiscard]] inline vec8ba cmpgt(const vec8fa& lhs, const vec8fa& rhs) noexcept { return vec8ba(_mm256_cmp_ps(lhs, rhs, _CMP_GT_OQ)); }

    [[nodiscard]] inline vec8ba cmpgt(const vec8fa& lhs, const float rhs) noexcept { return cmpgt(lhs, vec8fa(rhs)); }

    [[nodiscard]] inline vec8ba cmpgt(const float lhs, const vec8fa& rhs) noexcept { return cmpgt(vec8fa(lhs), rhs); }

    [[nodiscard]] inline vec8ba cmple(const vec8fa& lhs, const vec8fa& rhs) noexcept { return vec8ba(_mm256_cmp_ps(lhs, rhs, _CMP_LE_OQ)); }

    [[nodiscard]] inline vec8ba cmple(const vec8fa& lhs, const float rhs) noexcept { return cmple(lhs, vec8fa(rhs)); }

    [[nodiscard]] inline vec8ba cmple(const float lhs, const vec8fa& rhs) noexcept { return cmple(vec8fa(lhs), rhs); }

    [[nodiscard]] inline vec8ba cmpge(const vec8fa& lhs, const vec8fa& rhs) noexcept { return vec8ba(_mm256_cmp_ps(lhs, rhs, _CMP_GE_OQ)); }

    [[nodiscard]] inline vec8ba cmpge(const vec8fa& lhs, const float rhs) noexcept { return cmpge(lhs, vec8fa(rhs)); }

    [[nodiscard]] inline vec8ba cmpge(const float lhs, const vec8fa& rhs) noexcept { return cmpge(vec8fa(lhs), rhs); }

    ////////////////////////////////////////////////////////////////
    // Min/max, abs and clamp.
    ////////////////////////////////////////////////////////////////

    [[nodiscard]] inline vec8fa min(const vec8fa& lhs, const vec8fa& rhs) noexcept { return _mm256_min_ps(lhs, rhs); }

    [[nodiscard]] inline vec8fa min(const vec8fa& lhs, const float rhs) noexcept { return min(lhs, vec8fa(rhs)); }

    [[nodiscard]] inline vec8fa min(const float lhs, const vec8fa& rhs) noexcept { return min(vec8fa(lhs), rhs); }

    [[nodiscard]] inline vec8fa max(const vec8fa& lhs, const vec8fa& rhs) noexcept { return _mm256_max_ps(lhs, rhs); }

    [[nodiscard]] inline vec8fa max(const vec8fa& lhs, const float rhs) noexcept { return max(lhs, vec8fa(rhs)); }

    [[nodiscard]] inline vec8fa max(const float lhs, const vec8fa& rhs) noexcept { return max(vec8fa(lhs), rhs); }

    [[nodiscard]] inline vec8fa clamp(const vec8fa& a, const vec8fa& min, const vec8fa& max) noexcept { return math::max(min, math::min(a, max)); }

    [[nodiscard]] inline vec8fa clamp(const vec8fa& a, const vec8fa& min, const float max) noexcept { return clamp(a, min, vec8fa(max)); }

    [[nodiscard]] inline vec8fa clamp(const vec8fa& a, const float min, const vec8fa& max) noexcept { return clamp(a, vec8fa(min), max); }

    [[nodiscard]] inline vec8fa clamp(const vec8fa& a, const float min, const float max) noexcept { return clamp(a, vec8fa(min), vec8fa(max)); }

    ////////////////////////////////////////////////////////////////
    // Reduction.
    ////////////////////////////////////////////////////////////////

    [[nodiscard]] inline float reduce_add(const vec8fa& lhs) noexcept
    {
        const vec4fa low4 = _mm256_castps256_ps128(lhs);
        const vec4fa high4 = _mm256_extractf128_ps(lhs, 1);
        const vec4fa sum0 = low4 + high4;
        const vec4fa sum1 = sum0 + _mm_movehl_ps(sum0, sum0);
        const vec4fa sum2 = sum1 + _mm_shuffle_ps(sum1, sum1, 0x1);
        return _mm_cvtss_f32(sum2);
    }

    [[nodiscard]] inline float reduce_mul(const vec8fa& lhs) noexcept
    {
        const vec4fa low4 = _mm256_castps256_ps128(lhs);
        const vec4fa high4 = _mm256_extractf128_ps(lhs, 1);
        const vec4fa sum0 = low4 * high4;
        const vec4fa sum1 = sum0 * _mm_movehl_ps(sum0, sum0);
        const vec4fa sum2 = sum1 * _mm_shuffle_ps(sum1, sum1, 0x1);
        return _mm_cvtss_f32(sum2);
    }

    [[nodiscard]] inline float reduce_min(const vec8fa& lhs) noexcept
    {
        const vec4fa low4 = _mm256_castps256_ps128(lhs);
        const vec4fa high4 = _mm256_extractf128_ps(lhs, 1);
        const vec4fa sum0 = min(low4, high4);
        const vec4fa sum1 = min(sum0, _mm_movehl_ps(sum0, sum0));
        const vec4fa sum2 = min(sum1, _mm_shuffle_ps(sum1, sum1, 0x1));
        return _mm_cvtss_f32(sum2);
    }

    [[nodiscard]] inline float reduce_max(const vec8fa& lhs) noexcept
    {
        const vec4fa low4 = _mm256_castps256_ps128(lhs);
        const vec4fa high4 = _mm256_extractf128_ps(lhs, 1);
        const vec4fa sum0 = max(low4, high4);
        const vec4fa sum1 = max(sum0, _mm_movehl_ps(sum0, sum0));
        const vec4fa sum2 = max(sum1, _mm_shuffle_ps(sum1, sum1, 0x1));
        return _mm_cvtss_f32(sum2);
    }

    ////////////////////////////////////////////////////////////////
    // Multiply and add.
    ////////////////////////////////////////////////////////////////

    [[nodiscard]] inline vec8fa madd(const vec8fa& a, const vec8fa& b, const vec8fa& c) noexcept
    {
#ifdef __FMA__
        return _mm256_fmadd_ps(a, b, c);
#else
        return a * b + c;
#endif
    }

    [[nodiscard]] inline vec8fa nmadd(const vec8fa& a, const vec8fa& b, const vec8fa& c) noexcept
    {
#ifdef __FMA__
        return _mm256_fnmadd_ps(a, b, c);
#else
        return -a * b + c;
#endif
    }

    [[nodiscard]] inline vec8fa msub(const vec8fa& a, const vec8fa& b, const vec8fa& c) noexcept
    {
#ifdef __FMA__
        return _mm256_fmsub_ps(a, b, c);
#else
        return a * b - c;
#endif
    }

    [[nodiscard]] inline vec8fa nmsub(const vec8fa& a, const vec8fa& b, const vec8fa& c) noexcept
    {
#ifdef __FMA__
        return _mm256_fnmsub_ps(a, b, c);
#else
        return -a * b - c;
#endif
    }

    ////////////////////////////////////////////////////////////////
    // Dot product etc.
    ////////////////////////////////////////////////////////////////

    [[nodiscard]] inline float dot(const vec8fa& lhs, const vec8fa& rhs) noexcept
    {
        const __m256 dot = _mm256_dp_ps(lhs, rhs, 0xFF);
        const __m128 dotlow = _mm256_castps256_ps128(dot);
        const __m128 dothigh = _mm256_extractf128_ps(dot, 1);
        return _mm_cvtss_f32(_mm_add_ss(dotlow, dothigh));

    }

    [[nodiscard]] inline float length(const vec8fa& lhs) noexcept { return sqrt(dot(lhs, lhs)); }

    [[nodiscard]] inline float sqr_length(const vec8fa& lhs) noexcept { return dot(lhs, lhs); }

    [[nodiscard]] inline float rcp_length(const vec8fa& lhs) noexcept { return rsqrt(dot(lhs, lhs)); }

    [[nodiscard]] inline vec8fa normalize(const vec8fa& lhs) noexcept { return lhs * rcp_length(lhs); }

    [[nodiscard]] inline vec8fa normalize(const vec8fa& lhs, float& length) noexcept { length = math::length(lhs); return lhs / length; }

    [[nodiscard]] inline float distance(const vec8fa& lhs, const vec8fa& rhs) noexcept { return length(lhs - rhs); }

    [[nodiscard]] inline vec8fa lerp(const vec8fa& a, const vec8fa& b, const vec8fa& t) noexcept { return madd(t, b - a, a); }

    [[nodiscard]] inline vec8fa lerp(const vec8fa& a, const vec8fa& b, const float t) noexcept { return madd(vec8fa(t), b - a, a); }

    ////////////////////////////////////////////////////////////////
    // Trigonometry.
    ////////////////////////////////////////////////////////////////

    [[nodiscard]] inline vec8fa acos(const vec8fa& lhs) noexcept { return vec8fa(acos(lhs[0]), acos(lhs[1]), acos(lhs[2]), acos(lhs[3]), acos(lhs[4]), acos(lhs[5]), acos(lhs[6]), acos(lhs[7])); }

    [[nodiscard]] inline vec8fa asin(const vec8fa& lhs) noexcept { return vec8fa(asin(lhs[0]), asin(lhs[1]), asin(lhs[2]), asin(lhs[3]), asin(lhs[4]), asin(lhs[5]), asin(lhs[6]), asin(lhs[7])); }

    [[nodiscard]] inline vec8fa atan(const vec8fa& lhs) noexcept { return vec8fa(atan(lhs[0]), atan(lhs[1]), atan(lhs[2]), atan(lhs[3]), atan(lhs[4]), atan(lhs[5]), atan(lhs[6]), atan(lhs[7])); }

    [[nodiscard]] inline vec8fa atan2(const vec8fa& lhs, const vec8fa& rhs) noexcept { return vec8fa(atan2(lhs[0], rhs[0]), atan2(lhs[1], rhs[1]), atan2(lhs[2], rhs[2]), atan2(lhs[3], rhs[3]), atan2(lhs[4], rhs[4]), atan2(lhs[5], rhs[5]), atan2(lhs[6], rhs[6]), atan2(lhs[7], rhs[7])); }

    [[nodiscard]] inline vec8fa cos(const vec8fa& lhs) noexcept { return vec8fa(cos(lhs[0]), cos(lhs[1]), cos(lhs[2]), cos(lhs[3]), cos(lhs[4]), cos(lhs[5]), cos(lhs[6]), cos(lhs[7])); }

    [[nodiscard]] inline vec8fa cosh(const vec8fa& lhs) noexcept { return vec8fa(cosh(lhs[0]), cosh(lhs[1]), cosh(lhs[2]), cosh(lhs[3]), cosh(lhs[4]), cosh(lhs[5]), cosh(lhs[6]), cosh(lhs[7])); }

    [[nodiscard]] inline vec8fa sin(const vec8fa& lhs) noexcept { return vec8fa(sin(lhs[0]), sin(lhs[1]), sin(lhs[2]), sin(lhs[3]), sin(lhs[4]), sin(lhs[5]), sin(lhs[6]), sin(lhs[7])); }

    [[nodiscard]] inline vec8fa sinh(const vec8fa& lhs) noexcept { return vec8fa(sinh(lhs[0]), sinh(lhs[1]), sinh(lhs[2]), sinh(lhs[3]), sinh(lhs[4]), sinh(lhs[5]), sinh(lhs[6]), sinh(lhs[7])); }

    [[nodiscard]] inline vec8fa tan(const vec8fa& lhs) noexcept { return vec8fa(tan(lhs[0]), tan(lhs[1]), tan(lhs[2]), tan(lhs[3]), tan(lhs[4]), tan(lhs[5]), tan(lhs[6]), tan(lhs[7])); }

    [[nodiscard]] inline vec8fa tanh(const vec8fa& lhs) noexcept { return vec8fa(tanh(lhs[0]), tanh(lhs[1]), tanh(lhs[2]), tanh(lhs[3]), tanh(lhs[4]), tanh(lhs[5]), tanh(lhs[6]), tanh(lhs[7])); }

    ////////////////////////////////////////////////////////////////
    // Exponential / Logarithmic.
    ////////////////////////////////////////////////////////////////

#ifdef __AVX2__
    template<size_t Precision = 5>
    [[nodiscard]] vec8fa exp2(const vec8fa& lhs) noexcept
    {
        static_assert(Precision >= 2 && Precision <= 5, "Provided precision is outside of supported range.");

        const vec8fa x = clamp(lhs, -126.99999f, 129.00000f);
        const __m256i ipart = _mm256_cvtps_epi32(x - 0.5f);
        const vec8fa fpart = x - _mm256_cvtepi32_ps(ipart);
        const vec8fa expipart = _mm256_castsi256_ps(_mm256_slli_epi32(_mm256_add_epi32(ipart, _mm256_set1_epi32(127)), 23));

        vec8fa expfpart;
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
    [[nodiscard]] vec8fa log2(const vec8fa& lhs) noexcept
    {
        static_assert(Precision >= 2 && Precision <= 5, "Provided precision is outside of supported range.");

        const __m256i expmask = _mm256_set1_epi32(0x7F800000);
        const __m256i mantmask = _mm256_set1_epi32(0x007FFFFF);
        const vec8fa one = math::one<vec8fa>();

        const __m256i i = _mm256_castps_si256(lhs);
        const vec8fa exp = _mm256_cvtepi32_ps(_mm256_sub_epi32(_mm256_srli_epi32(_mm256_and_si256(i, expmask), 23), _mm256_set1_epi32(127)));

        const vec8fa mant = _mm256_or_ps(_mm256_castsi256_ps(_mm256_and_si256(i, mantmask)), one);

        vec8fa p;
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
    [[nodiscard]] vec8fa exp(const vec8fa& lhs) noexcept { return exp2<Precision>(lhs * log2<Precision>(vec8fa(m_e))); }

    template<size_t Precision = 5>
    [[nodiscard]] vec8fa log(const vec8fa& lhs) noexcept { return log2<Precision>(lhs) / log2<Precision>(vec8fa(m_e)); }

    template<size_t Precision = 5>
    [[nodiscard]] vec8fa log10(const vec8fa& lhs) noexcept { return log2<Precision>(lhs) / log2<Precision>(vec8fa(10.0f)); }
#endif

    ////////////////////////////////////////////////////////////////
    // Power.
    ////////////////////////////////////////////////////////////////

#ifdef __AVX2__
    template<size_t Precision = 5>
    [[nodiscard]] vec8fa pow(const vec8fa& lhs, const vec8fa& rhs) noexcept { return exp2<Precision>(rhs * log2<Precision>(lhs)); }

    template<size_t Precision = 5>
    [[nodiscard]] vec8fa pow(const vec8fa& lhs, const float rhs) noexcept { return exp2<Precision>(vec8fa(rhs) * log2<Precision>(lhs)); }

    template<size_t Precision = 5>
    [[nodiscard]] vec8fa pow(const float lhs, const vec8fa& rhs) noexcept { return exp2<Precision>(rhs * log2<Precision>(vec8fa(lhs))); }
#endif
    [[nodiscard]] inline vec8fa sqr(const vec8fa& lhs) noexcept { return lhs * lhs; }

    [[nodiscard]] inline vec8fa sqrt(const vec8fa& lhs) noexcept { return _mm256_sqrt_ps(lhs); }

    [[nodiscard]] inline vec8fa rsqrt(const vec8fa& lhs) noexcept { return _mm256_rsqrt_ps(lhs); }

    ////////////////////////////////////////////////////////////////
    // Rounding, abs, etc.
    ////////////////////////////////////////////////////////////////

    [[nodiscard]] inline vec8fa abs(const vec8fa& lhs) noexcept
    {
        const __m256 mask = _mm256_castsi256_ps(_mm256_set1_epi32(0x7fffffff));
        return _mm256_and_ps(lhs, mask);
    }

    [[nodiscard]] inline vec8fa round(const vec8fa& lhs) noexcept { return _mm256_round_ps(lhs, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC); }

    [[nodiscard]] inline vec8fa ceil(const vec8fa& lhs) noexcept { return _mm256_round_ps(lhs, _MM_FROUND_CEIL); }

    [[nodiscard]] inline vec8fa floor(const vec8fa& lhs) noexcept { return _mm256_round_ps(lhs, _MM_FROUND_FLOOR); }

    [[nodiscard]] inline vec8fa frac(const vec8fa& lhs) noexcept { return _mm256_sub_ps(lhs, _mm256_round_ps(lhs, _MM_FROUND_TRUNC)); }

    [[nodiscard]] inline vec8fa trunc(const vec8fa& lhs) noexcept { return _mm256_round_ps(lhs, _MM_FROUND_TRUNC); }

    ////////////////////////////////////////////////////////////////
    // Select.
    ////////////////////////////////////////////////////////////////

    [[nodiscard]] inline vec8fa select(const vec8fa& t, const vec8fa& f, const vec8ba& b) noexcept { return _mm256_blendv_ps(f, t, _mm256_castsi256_ps(b)); }

    ////////////////////////////////////////////////////////////////
    // Output.
    ////////////////////////////////////////////////////////////////

    inline std::ostream& operator<<(std::ostream& out, const vec8fa& v) { return out << "(" << v[0] << ", " << v[1] << ", " << v[2] << ", " << v[3] << ", " << v[4] << ", " << v[5] << ", " << v[6] << ", " << v[7] << ")"; }
#endif
}
