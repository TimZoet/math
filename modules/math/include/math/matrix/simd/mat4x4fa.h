#pragma once

////////////////////////////////////////////////////////////////
// Current target includes.
////////////////////////////////////////////////////////////////

#include "math/vector/simd/vec4fa.h"
#include "math/matrix/matrix.h"

#if 0
namespace math
{
    struct mat4x4fa
    {
        using RowType = vec4fa;
        using ColumnType = vec4fa;

        RowType r0, r1, r2, r3;

        ////////////////////////////////////////////////////////////////
        // Constructors and assignment operators.
        ////////////////////////////////////////////////////////////////

        inline mat4x4fa() {}

        inline explicit mat4x4fa(const float v)
        {
            r0 = RowType(v);
            r1 = RowType(v);
            r2 = RowType(v);
            r3 = RowType(v);
        }

        inline mat4x4fa(const RowType& r0, const RowType& r1, const RowType& r2, const RowType& r3) : r0(r0), r1(r1), r2(r2), r3(r3) {}

        inline mat4x4fa(const mat4x4fa& rhs)
        {
            r0 = rhs.r0;
            r1 = rhs.r1;
            r2 = rhs.r2;
            r3 = rhs.r3;
        }

        inline mat4x4fa& operator=(const mat4x4fa& rhs)
        {
            r0 = rhs.r0;
            r1 = rhs.r1;
            r2 = rhs.r2;
            r3 = rhs.r3;
            return *this;
        }

        template<typename U>
        inline explicit mat4x4fa(const matrix<U, 4, 4>& rhs)
        {
            r0 = static_cast<RowType>(rhs[0]);
            r1 = static_cast<RowType>(rhs[1]);
            r2 = static_cast<RowType>(rhs[2]);
            r3 = static_cast<RowType>(rhs[3]);
        }

        template<typename U>
        inline mat4x4fa& operator=(const matrix<U, 4, 4>& rhs)
        {
            r0 = static_cast<RowType>(rhs[0]);
            r1 = static_cast<RowType>(rhs[1]);
            r2 = static_cast<RowType>(rhs[2]);
            r3 = static_cast<RowType>(rhs[3]);
            return *this;
        }

        ////////////////////////////////////////////////////////////////
        // Element access.
        ////////////////////////////////////////////////////////////////

        inline const RowType& operator[](const size_t i) const { assert(i < 4); return (&r0)[i]; }

        inline RowType& operator[](const size_t i) { assert(i < 4); return (&r0)[i]; }

        inline ColumnType column(const size_t j) const { assert(j < 4); return ColumnType(r0[j], r1[j], r2[j], r3[j]); }

        ////////////////////////////////////////////////////////////////
        // Construct special values.
        ////////////////////////////////////////////////////////////////

        inline static mat4x4fa identity() { return mat4x4fa(RowType(1, 0, 0, 0), RowType(0, 1, 0, 0), RowType(0, 0, 1, 0), RowType(0, 0, 0, 1)); }

        inline static mat4x4fa zeroes() { return mat4x4fa(0.0f); }

        inline static mat4x4fa ones() { return mat4x4fa(1.0f); }

        inline static mat4x4fa highest() { return mat4x4fa(std::numeric_limits<float>::max()); }

        inline static mat4x4fa lowest() { return mat4x4fa(std::numeric_limits<float>::lowest()); }

        inline static mat4x4fa pos_infinity() { static_assert(std::numeric_limits<float>::has_infinity); return mat4x4fa(std::numeric_limits<float>::infinity()); }

        inline static mat4x4fa neg_infinity() { static_assert(std::numeric_limits<float>::has_infinity); return mat4x4fa(-std::numeric_limits<float>::infinity()); }

        inline static mat4x4fa NaN() { static_assert(std::numeric_limits<float>::has_quiet_NaN); return mat4x4fa(std::numeric_limits<float>::quiet_NaN()); }

    };

    ////////////////////////////////////////////////////////////////
    // Matrix-Matrix multiplication.
    ////////////////////////////////////////////////////////////////

    inline mat4x4fa operator*(const mat4x4fa& lhs, const mat4x4fa& rhs)
    {
        mat4x4fa mat;

        for (size_t j = 0; j < 4; j++)
        {
            const vec4fa col = rhs.column(j);
            for (size_t i = 0; i < 4; i++)
            {
                mat[i][j] = dot(lhs[i], col);
            }
        }

        return mat;
    }

    ////////////////////////////////////////////////////////////////
    // Matrix-Vector multiplication.
    ////////////////////////////////////////////////////////////////

    inline vec4fa operator*(const mat4x4fa& lhs, const vec4fa& rhs)
    {
        return vec4fa(dot(lhs.r0, rhs), dot(lhs.r1, rhs), dot(lhs.r2, rhs), dot(lhs.r3, rhs));
    }

    inline vec4fa operator*(const vec4fa& lhs, const mat4x4fa& rhs) { return rhs * lhs; }

    ////////////////////////////////////////////////////////////////
    // Matrix-Scalar multiplication.
    ////////////////////////////////////////////////////////////////

    inline mat4x4fa operator*(const mat4x4fa& lhs, const float rhs)
    {
        mat4x4fa mat;
        mat.r0 = lhs.r0 * rhs;
        mat.r1 = lhs.r1 * rhs;
        mat.r2 = lhs.r2 * rhs;
        mat.r3 = lhs.r3 * rhs;
        return mat;
    }

    inline mat4x4fa operator*(const float lhs, const mat4x4fa& rhs) { return rhs * lhs; }

    inline mat4x4fa& operator*=(mat4x4fa& lhs, const float rhs)
    {
        lhs.r0 *= rhs;
        lhs.r1 *= rhs;
        lhs.r2 *= rhs;
        lhs.r3 *= rhs;
        return lhs;
    }

    ////////////////////////////////////////////////////////////////
    // Transpose, invert.
    ////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////
    // Output.
    ////////////////////////////////////////////////////////////////

    inline std::ostream& operator<<(std::ostream& out, const mat4x4fa& m)
    {
        return out << "[" << m.r0 << "\n " << m.r1 << "\n " << m.r2 << "\n " << m.r3 << "]";
    }

}
#endif