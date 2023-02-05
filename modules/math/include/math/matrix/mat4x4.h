#pragma once

////////////////////////////////////////////////////////////////
// Current target includes.
////////////////////////////////////////////////////////////////

#include "math/vector/vec3.h"
#include "math/vector/vec4.h"
#include "math/matrix/matrix.h"

namespace math
{
    template<typename T>
    struct matrix<T, 4, 4>
    {
        using element_type = T;
        using row_type = vec<T, 4>;
        using column_type = vec<T, 4>;
        static constexpr size_t size = 16;

        row_type r0, r1, r2, r3;

        ////////////////////////////////////////////////////////////////
        // Constructors.
        ////////////////////////////////////////////////////////////////

        [[nodiscard]] matrix() noexcept : r0(0), r1(0), r2(0), r3(0) {}

        [[nodiscard]] explicit matrix(const T v) noexcept : r0(v), r1(v), r2(v), r3(v) {}

        [[nodiscard]] explicit matrix(const row_type& r) noexcept : r0(r), r1(r), r2(r), r3(r) {}

        [[nodiscard]] matrix(const row_type& r0, const row_type& r1, const row_type& r2, const row_type& r3) noexcept : r0(r0), r1(r1), r2(r2), r3(r3) {}

        [[nodiscard]] explicit matrix(const matrix<T, 3, 3>& rhs) noexcept : r0(rhs[0], 0), r1(rhs[1], 0), r2(rhs[2], 0), r3(0, 0, 0, 1) {}

        [[nodiscard]] matrix(const matrix<T, 3, 3>& rhs, const row_type& r3) noexcept : r0(rhs[0], 0), r1(rhs[1], 0), r2(rhs[2], 0), r3(r3) {}

        [[nodiscard]] matrix(
            const T a, const T b, const T c, const T d,
            const T e, const T f, const T g, const T h,
            const T i, const T j, const T k, const T l,
            const T m, const T n, const T o, const T p) noexcept :
            r0(a, b, c, d),
            r1(e, f, g, h),
            r2(i, j, k, l),
            r3(m, n, o, p)
        {
        }

        [[nodiscard]] matrix(const matrix<T, 4, 4>& rhs) noexcept : r0(rhs.r0), r1(rhs.r1), r2(rhs.r2), r3(rhs.r3) {}

        template<typename U>
        [[nodiscard]] explicit matrix(const matrix<T, 4, 4>& rhs) : r0(static_cast<row_type>(rhs.r0)), r1(static_cast<row_type>(rhs.r1)), r2(static_cast<row_type>(rhs.r2)), r3(static_cast<row_type>(rhs.r3)) {}

        ////////////////////////////////////////////////////////////////
        // Assignment operators.
        ////////////////////////////////////////////////////////////////

        matrix<T, 4, 4>& operator=(const T rhs) noexcept { r0 = rhs; r1 = rhs; r2 = rhs; r3 = rhs; return *this; }

        matrix<T, 4, 4>& operator=(const matrix<T, 4, 4>& rhs) noexcept { r0 = rhs.r0; r1 = rhs.r1; r2 = rhs.r2; r3 = rhs.r3; return *this; }

        template<typename U>
        matrix<T, 4, 4>& operator=(const matrix<T, 4, 4>& rhs) { r0 = static_cast<row_type>(rhs.r0); r1 = static_cast<row_type>(rhs.r1); r2 = static_cast<row_type>(rhs.r2); r3 = static_cast<row_type>(rhs.r3); return *this; }

        ////////////////////////////////////////////////////////////////
        // Defaulted constructors and operators.
        ////////////////////////////////////////////////////////////////

        ~matrix() = default;

        matrix(matrix<T, 4, 4>&& rhs) noexcept = default;

        matrix<T, 4, 4>& operator=(matrix<T, 4, 4>&& rhs) noexcept = default;

        ////////////////////////////////////////////////////////////////
        // Element access.
        ////////////////////////////////////////////////////////////////

        [[nodiscard]] const row_type& operator[](const size_t i) const { assert(i < 4); return (&r0)[i]; }

        [[nodiscard]] row_type& operator[](const size_t i) { assert(i < 4); return (&r0)[i]; }

        [[nodiscard]] column_type column(const size_t j) const
        {
            assert(j < 4);
            return column_type(r0[j], r1[j], r2[j], r3[j]);
        }
    };

    ////////////////////////////////////////////////////////////////
    // Matrix-Matrix multiplication.
    ////////////////////////////////////////////////////////////////

    template<typename T>
    [[nodiscard]] matrix<T, 4, 4> operator*(const matrix<T, 4, 4>& lhs, const matrix<T, 4, 4>& rhs) noexcept
    {
        const auto c0 = rhs.column(0);
        const auto c1 = rhs.column(1);
        const auto c2 = rhs.column(2);
        const auto c3 = rhs.column(3);

        return matrix<T, 4, 4>(
            dot(lhs.r0, c0), dot(lhs.r0, c1), dot(lhs.r0, c2), dot(lhs.r0, c3),
            dot(lhs.r1, c0), dot(lhs.r1, c1), dot(lhs.r1, c2), dot(lhs.r1, c3),
            dot(lhs.r2, c0), dot(lhs.r2, c1), dot(lhs.r2, c2), dot(lhs.r2, c3),
            dot(lhs.r3, c0), dot(lhs.r3, c1), dot(lhs.r3, c2), dot(lhs.r3, c3)
            );
    }

    template<typename T>
    matrix<T, 4, 4>& operator*=(matrix<T, 4, 4>& lhs, const matrix<T, 4, 4>& rhs) noexcept
    {
        return lhs = lhs * rhs;
    }

    ////////////////////////////////////////////////////////////////
    // Matrix-Vector multiplication.
    ////////////////////////////////////////////////////////////////

    template<typename T>
    [[nodiscard]] vec<T, 4> operator*(const matrix<T, 4, 4>& lhs, const vec<T, 4>& rhs) noexcept { return vec<T, 4>(dot(lhs.r0, rhs), dot(lhs.r1, rhs), dot(lhs.r2, rhs), dot(lhs.r3, rhs)); }

    template<typename T>
    [[nodiscard]] vec<T, 3> operator*(const matrix<T, 4, 4>& lhs, const vec<T, 3>& rhs) noexcept
    {
        const vec<T, 4> rhs2(rhs.x, rhs.y, rhs.z, T(1));
        return vec<T, 3>(dot(lhs.r0, rhs2), dot(lhs.r1, rhs2), dot(lhs.r2, rhs2));
    }

    ////////////////////////////////////////////////////////////////
    // Matrix-Scalar multiplication.
    ////////////////////////////////////////////////////////////////

    template<typename T>
    [[nodiscard]] matrix<T, 4, 4> operator*(const matrix<T, 4, 4>& lhs, const T rhs) noexcept { return matrix<T, 4, 4>(lhs.r0 * rhs, lhs.r1 * rhs, lhs.r2 * rhs, lhs.r3 * rhs); }

    template<typename T>
    matrix<T, 4, 4>& operator*=(matrix<T, 4, 4>& lhs, const T rhs) noexcept
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

    template<typename T>
    [[nodiscard]] matrix<T, 4, 4> transpose(const matrix <T, 4, 4>& lhs) noexcept { return matrix<T, 4, 4>(lhs.column(0), lhs.column(1), lhs.column(2), lhs.column(3)); }

    [[nodiscard]] inline matrix<float, 4, 4> invert(const matrix <float, 4, 4>& lhs) noexcept
    {
        // Source: MESA, code taken from http://stackoverflow.com/questions/1148309/inverting-a-4x4-matrix.
        matrix<float, 4, 4> M(
          lhs[1][1] * lhs[2][2] * lhs[3][3] - lhs[1][1] * lhs[2][3] * lhs[3][2] - lhs[2][1] * lhs[1][2] * lhs[3][3] +
            lhs[2][1] * lhs[1][3] * lhs[3][2] + lhs[3][1] * lhs[1][2] * lhs[2][3] - lhs[3][1] * lhs[1][3] * lhs[2][2],
          -lhs[0][1] * lhs[2][2] * lhs[3][3] + lhs[0][1] * lhs[2][3] * lhs[3][2] + lhs[2][1] * lhs[0][2] * lhs[3][3] -
            lhs[2][1] * lhs[0][3] * lhs[3][2] - lhs[3][1] * lhs[0][2] * lhs[2][3] + lhs[3][1] * lhs[0][3] * lhs[2][2],
          lhs[0][1] * lhs[1][2] * lhs[3][3] - lhs[0][1] * lhs[1][3] * lhs[3][2] - lhs[1][1] * lhs[0][2] * lhs[3][3] +
            lhs[1][1] * lhs[0][3] * lhs[3][2] + lhs[3][1] * lhs[0][2] * lhs[1][3] - lhs[3][1] * lhs[0][3] * lhs[1][2],
          -lhs[0][1] * lhs[1][2] * lhs[2][3] + lhs[0][1] * lhs[1][3] * lhs[2][2] + lhs[1][1] * lhs[0][2] * lhs[2][3] -
            lhs[1][1] * lhs[0][3] * lhs[2][2] - lhs[2][1] * lhs[0][2] * lhs[1][3] + lhs[2][1] * lhs[0][3] * lhs[1][2],
          -lhs[1][0] * lhs[2][2] * lhs[3][3] + lhs[1][0] * lhs[2][3] * lhs[3][2] + lhs[2][0] * lhs[1][2] * lhs[3][3] -
            lhs[2][0] * lhs[1][3] * lhs[3][2] - lhs[3][0] * lhs[1][2] * lhs[2][3] + lhs[3][0] * lhs[1][3] * lhs[2][2],
          lhs[0][0] * lhs[2][2] * lhs[3][3] - lhs[0][0] * lhs[2][3] * lhs[3][2] - lhs[2][0] * lhs[0][2] * lhs[3][3] +
            lhs[2][0] * lhs[0][3] * lhs[3][2] + lhs[3][0] * lhs[0][2] * lhs[2][3] - lhs[3][0] * lhs[0][3] * lhs[2][2],
          -lhs[0][0] * lhs[1][2] * lhs[3][3] + lhs[0][0] * lhs[1][3] * lhs[3][2] + lhs[1][0] * lhs[0][2] * lhs[3][3] -
            lhs[1][0] * lhs[0][3] * lhs[3][2] - lhs[3][0] * lhs[0][2] * lhs[1][3] + lhs[3][0] * lhs[0][3] * lhs[1][2],
          lhs[0][0] * lhs[1][2] * lhs[2][3] - lhs[0][0] * lhs[1][3] * lhs[2][2] - lhs[1][0] * lhs[0][2] * lhs[2][3] +
            lhs[1][0] * lhs[0][3] * lhs[2][2] + lhs[2][0] * lhs[0][2] * lhs[1][3] - lhs[2][0] * lhs[0][3] * lhs[1][2],
          lhs[1][0] * lhs[2][1] * lhs[3][3] - lhs[1][0] * lhs[2][3] * lhs[3][1] - lhs[2][0] * lhs[1][1] * lhs[3][3] +
            lhs[2][0] * lhs[1][3] * lhs[3][1] + lhs[3][0] * lhs[1][1] * lhs[2][3] - lhs[3][0] * lhs[1][3] * lhs[2][1],
          -lhs[0][0] * lhs[2][1] * lhs[3][3] + lhs[0][0] * lhs[2][3] * lhs[3][1] + lhs[2][0] * lhs[0][1] * lhs[3][3] -
            lhs[2][0] * lhs[0][3] * lhs[3][1] - lhs[3][0] * lhs[0][1] * lhs[2][3] + lhs[3][0] * lhs[0][3] * lhs[2][1],
          lhs[0][0] * lhs[1][1] * lhs[3][3] - lhs[0][0] * lhs[1][3] * lhs[3][1] - lhs[1][0] * lhs[0][1] * lhs[3][3] +
            lhs[1][0] * lhs[0][3] * lhs[3][1] + lhs[3][0] * lhs[0][1] * lhs[1][3] - lhs[3][0] * lhs[0][3] * lhs[1][1],
          -lhs[0][0] * lhs[1][1] * lhs[2][3] + lhs[0][0] * lhs[1][3] * lhs[2][1] + lhs[1][0] * lhs[0][1] * lhs[2][3] -
            lhs[1][0] * lhs[0][3] * lhs[2][1] - lhs[2][0] * lhs[0][1] * lhs[1][3] + lhs[2][0] * lhs[0][3] * lhs[1][1],
          -lhs[1][0] * lhs[2][1] * lhs[3][2] + lhs[1][0] * lhs[2][2] * lhs[3][1] + lhs[2][0] * lhs[1][1] * lhs[3][2] -
            lhs[2][0] * lhs[1][2] * lhs[3][1] - lhs[3][0] * lhs[1][1] * lhs[2][2] + lhs[3][0] * lhs[1][2] * lhs[2][1],
          lhs[0][0] * lhs[2][1] * lhs[3][2] - lhs[0][0] * lhs[2][2] * lhs[3][1] - lhs[2][0] * lhs[0][1] * lhs[3][2] +
            lhs[2][0] * lhs[0][2] * lhs[3][1] + lhs[3][0] * lhs[0][1] * lhs[2][2] - lhs[3][0] * lhs[0][2] * lhs[2][1],
          -lhs[0][0] * lhs[1][1] * lhs[3][2] + lhs[0][0] * lhs[1][2] * lhs[3][1] + lhs[1][0] * lhs[0][1] * lhs[3][2] -
            lhs[1][0] * lhs[0][2] * lhs[3][1] - lhs[3][0] * lhs[0][1] * lhs[1][2] + lhs[3][0] * lhs[0][2] * lhs[1][1],
          lhs[0][0] * lhs[1][1] * lhs[2][2] - lhs[0][0] * lhs[1][2] * lhs[2][1] - lhs[1][0] * lhs[0][1] * lhs[2][2] +
            lhs[1][0] * lhs[0][2] * lhs[2][1] + lhs[2][0] * lhs[0][1] * lhs[1][2] - lhs[2][0] * lhs[0][2] * lhs[1][1]
        );
        const float det = lhs[0][0] * M[0][0] + lhs[0][1] * M[1][0] + lhs[0][2] * M[2][0] + lhs[0][3] * M[3][0];
        if (det != 0)
        {
            const float invdet = 1.0f / det;
            for (int32_t i = 0; i < 4; i++)
                for (int32_t j = 0; j < 4; j++)
                    M[i][j] = M[i][j] * invdet;
        }
        return M;
    }

    ////////////////////////////////////////////////////////////////
    // Rotation, scale, translation.
    ////////////////////////////////////////////////////////////////

    inline void decompose(const matrix<float, 4, 4>& transform, matrix<float, 4, 4>& translation, matrix<float, 4, 4>& rotation, matrix<float, 4, 4>& scale) noexcept
    {
        // Extract translation.
        translation[0][3] = transform[0][3];
        translation[1][3] = transform[1][3];
        translation[2][3] = transform[2][3];

        // Extract scale.
        scale[0][0] = length(transform.column(0).xyz());
        scale[1][1] = length(transform.column(1).xyz());
        scale[2][2] = length(transform.column(2).xyz());

        // Extract rotation.
        rotation[0][0] = transform[0][0] / scale[0][0];
        rotation[0][1] = transform[0][1] / scale[1][1];
        rotation[0][2] = transform[0][2] / scale[2][2];
        rotation[1][0] = transform[1][0] / scale[0][0];
        rotation[1][1] = transform[1][1] / scale[1][1];
        rotation[1][2] = transform[1][2] / scale[2][2];
        rotation[2][0] = transform[2][0] / scale[0][0];
        rotation[2][1] = transform[2][1] / scale[1][1];
        rotation[2][2] = transform[2][2] / scale[2][2];
    }


    template<typename T>
    [[nodiscard]] matrix<T, 4, 4> translation(const vec<T, 3>& translation) noexcept
    {
        return matrix<T, 4, 4>(
            T(1), T(0), T(0), translation.x,
            T(0), T(1), T(0), translation.y,
            T(0), T(0), T(1), translation.z,
            T(0), T(0), T(0), T(1)
            );
    }

    template<typename T>
    [[nodiscard]] matrix<T, 4, 4> translation(const vec<T, 4>& translation) noexcept
    {
        return matrix<T, 4, 4>(
            T(1), T(0), T(0), translation.x,
            T(0), T(1), T(0), translation.y,
            T(0), T(0), T(1), translation.z,
            T(0), T(0), T(0), T(1)
            );
    }

    template<typename T>
    [[nodiscard]] matrix<T, 4, 4> rotation_from_quat(const vec<T, 4>& q) noexcept
    {
        const vec<T, 4> q2 = q * q;
        const T xy = q.x * q.y;
        const T xz = q.x * q.z;
        const T xw = q.x * q.w;
        const T yz = q.y * q.z;
        const T yw = q.y * q.w;
        const T zw = q.z * q.w;
        return matrix<T, 4, 4>(
            T(1) - T(2) * (q2.y + q2.z), T(2) * (xy - zw), T(2) * (xz + yw), T(0),
            T(2) * (xy + zw), T(1) - T(2) * (q2.x + q2.z), T(2) * (yz - xw), T(0),
            T(2) * (xz - yw), T(2) * (yz + xw), T(1) - T(2) * (q2.x + q2.y), T(0),
            T(0), T(0), T(0), T(1)
            );
    }

    template<typename T>
    [[nodiscard]] matrix<T, 4, 4> rotation_x(const T angle) noexcept
    {
        const T c = cos(angle);
        const T s = sin(angle);
        return matrix<T, 4, 4>(
            T(1), T(0), T(0), T(0),
            T(0), c,    -s,   T(0),
            T(0), s,    c,    T(0),
            T(0), T(0), T(0), T(1)
            );
    }

    template<typename T>
    [[nodiscard]] matrix<T, 4, 4> rotation_y(const T angle) noexcept
    {
        const T c = cos(angle);
        const T s = sin(angle);
        return matrix<T, 4, 4>(
            c,    T(0), s,    T(0),
            T(0), T(1), T(0), T(0),
            -s,   T(0), c,    T(0),
            T(0), T(0), T(0), T(1)
            );
    }

    template<typename T>
    [[nodiscard]] matrix<T, 4, 4> rotation_z(const T angle) noexcept
    {
        const T c = cos(angle);
        const T s = sin(angle);
        return matrix<T, 4, 4>(
            c,    -s,   T(0), T(0),
            s,    c,    T(0), T(0),
            T(0), T(0), T(1), T(0),
            T(0), T(0), T(0), T(1)
            );
    }

    template<typename T>
    [[nodiscard]] matrix<T, 4, 4> scale(const vec<T, 3>& scale) noexcept
    {
        return matrix<T, 4, 4>(
            scale.x, T(0), T(0), T(0),
            T(0), scale.y, T(0), T(0),
            T(0), T(0), scale.z, T(0),
            T(0), T(0), T(0), T(1)
            );
    }

    [[nodiscard]] inline matrix<float, 4, 4> look_at(const vec<float, 3>& from, const vec<float, 3>& to) noexcept
    {
        matrix<float, 4, 4> M;

        const vec<float, 3> forward = normalize(from - to);
        const vec<float, 3> right = cross(vec<float, 3>(0, 1, 0), forward);
        const vec<float, 3> up = cross(forward, right);

        M[0] = vec<float, 4>(right.x, up.x, forward.x, from.x);
        M[1] = vec<float, 4>(right.y, up.y, forward.y, from.y);
        M[2] = vec<float, 4>(right.z, up.z, forward.z, from.z);
        M[3] = vec<float, 4>(0, 0, 0, 1);

        return M;
    }

    ////////////////////////////////////////////////////////////////
    // Output.
    ////////////////////////////////////////////////////////////////

    template<typename T>
    std::ostream& operator<<(std::ostream& out, const matrix<T, 4, 4>& m) { return out << "[" << m.r0 << "\n " << m.r1 << "\n " << m.r2 << "\n " << m.r3 << "]"; }
}
