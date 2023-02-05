#pragma once

////////////////////////////////////////////////////////////////
// Current target includes.
////////////////////////////////////////////////////////////////

#include "math/vector/vector.h"
#include "math/math_type_traits.h"

namespace math
{
    template<typename T, size_t N, size_t M>
    struct matrix
    {
        using element_type = T;
        using row_type = vec<T, M>;
        using column_type = vec<T, N>;
        static constexpr size_t size = N * M;

        row_type data[N];

        ////////////////////////////////////////////////////////////////
        // Constructors.
        ////////////////////////////////////////////////////////////////
        
        [[nodiscard]] matrix() noexcept : data() {}

        [[nodiscard]] explicit matrix(const T v) noexcept
        {
            for (size_t i = 0; i < N; i++)
                data[i] = v;
        }

        [[nodiscard]] matrix(const matrix<T, N, M>& rhs) noexcept
        {
            for (size_t i = 0; i < N; i++)
                data[i] = rhs.data[i];
        }

        template<std::convertible_to<T> ... Ts>
        [[nodiscard]] explicit matrix(const Ts ... v)
        {
            size_t i = 0;
            ((data[i / M][i++ % M] = v), ...);
        }

        [[nodiscard]] explicit matrix(const T* ptr)
        {
            std::copy(ptr, ptr + size, data);
        }

        template<typename U>
        [[nodiscard]] explicit matrix(const matrix<U, N, M>& rhs)
        {
            for (size_t i = 0; i < N; i++)
                data[i] = static_cast<row_type>(rhs.data[i]);
        }

        ////////////////////////////////////////////////////////////////
        // Assignment operators.
        ////////////////////////////////////////////////////////////////

        matrix<T, N, M>& operator=(const T rhs) noexcept
        {
            for (size_t i = 0; i < N; i++)
                data[i] = rhs;
            return *this;
        }

        matrix<T, N, M>& operator=(const matrix<T, N, M>& rhs) noexcept
        {
            for (size_t i = 0; i < N; i++)
                data[i] = rhs.data[i];
            return *this;
        }

        template<typename U>
        matrix<T, N, M>& operator=(const matrix<U, N, M>& rhs)
        {
            for (size_t i = 0; i < N; i++)
                data[i] = static_cast<row_type>(rhs.data[i]);
            return *this;
        }

        ////////////////////////////////////////////////////////////////
        // Defaulted constructors and operators.
        ////////////////////////////////////////////////////////////////

        ~matrix() = default;

        matrix(matrix<T, N, M>&& rhs) noexcept = default;

        matrix<T, N, M>& operator=(matrix<T, N, M>&& rhs) noexcept = default;

        ////////////////////////////////////////////////////////////////
        // Element access.
        ////////////////////////////////////////////////////////////////
        
        [[nodiscard]] const row_type& operator[](const size_t i) const { assert(i < N); return data[i]; }

        [[nodiscard]] row_type& operator[](const size_t i) { assert(i < N); return data[i]; }

        [[nodiscard]] column_type column(const size_t j) const
        {
            assert(j < M);
            column_type col;
            for (size_t i = 0; i < N; i++)
                col[i] = data[i][j];
            return col;
        }
    };

    ////////////////////////////////////////////////////////////////
    // Construct special values.
    ////////////////////////////////////////////////////////////////

    template<is_square_matrix T>
    [[nodiscard]] T identity() noexcept
    {
        T mat = zero<T>();
        for (size_t i = 0; i < T::row_type::size; i++)
            mat[i][i] = T::element_type(1);
        return mat;
    }

    ////////////////////////////////////////////////////////////////
    // Matrix-Matrix multiplication.
    ////////////////////////////////////////////////////////////////

    template<typename T, size_t N, size_t K, size_t M>
    [[nodiscard]] matrix<T, N, M> operator*(const matrix<T, N, K>& lhs, const matrix<T, K, M>& rhs) noexcept
    {
        matrix<T, N, M> mat;
        // Find out which is more optimal.
#if 1
        for (size_t j = 0; j < K; j++)
        {
            const auto col = rhs.column(j);
            for (size_t i = 0; i < N; i++)
                mat[i][j] = dot(lhs[i], col);
        }
#else
        
        for (size_t i = 0; i < N; i++)
        {
            for (size_t j = 0; j < K; j++)
                mat[i][j] = dot(lhs[i], rhs.column(j));
        }
#endif

        return mat;
    }

    ////////////////////////////////////////////////////////////////
    // Matrix-Vector multiplication.
    ////////////////////////////////////////////////////////////////

    template<typename T, size_t N, size_t M>
    [[nodiscard]] vec<T, M> operator*(const matrix<T, N, M>& lhs, const vec<T, M>& rhs) noexcept
    {
        vec<T, M> v;
        for (size_t i = 0; i < N; i++)
            v[i] = dot(lhs[i], rhs);
        return v;
    }

    template<typename T, size_t N, size_t M>
    [[nodiscard]] vec<T, M> operator*(const vec<T, M>& lhs, const matrix<T, N, M>& rhs) noexcept { return rhs * lhs; }

    ////////////////////////////////////////////////////////////////
    // Matrix-Scalar multiplication.
    ////////////////////////////////////////////////////////////////

    template<typename T, size_t N, size_t M>
    [[nodiscard]] matrix<T, N, M> operator*(const matrix<T, N, M>& lhs, const T rhs) noexcept
    {
        matrix<T, N, M> mat;
        for (size_t i = 0; i < N; i++)
            mat[i] = lhs[i] * rhs;
        return mat;
    }

    template<typename T, size_t N, size_t M>
    [[nodiscard]] matrix<T, N, M> operator*(const T lhs, const matrix<T, N, M>& rhs) noexcept { return rhs * lhs; }

    template<typename T, size_t N, size_t M>
    matrix<T, N, M>& operator*=(matrix<T, N, M>& lhs, const T rhs) noexcept
    {
        for (size_t i = 0; i < N; i++)
            lhs[i] *= rhs;
        return lhs;
    }

    ////////////////////////////////////////////////////////////////
    // Transpose, invert. Also make transpose and transposed: one returns a new matrix, the other modifies the existing matrix (if it is square). (Do this for mat4x4 etc also).
    ////////////////////////////////////////////////////////////////
    
    template<typename T, size_t N, size_t M>
    [[nodiscard]] matrix<T, M, N> transpose(const matrix <T, N, M>& lhs) noexcept
    {
        matrix<T, M, N> mat;
        for (size_t i = 0; i < N; i++)
            for (size_t j = 0; j < M; j++)
                mat[j][i] = lhs[i][j];
        return mat;
    }

    ////////////////////////////////////////////////////////////////
    // Output.
    ////////////////////////////////////////////////////////////////

    template<typename T, size_t N, size_t M>
    std::ostream& operator<<(std::ostream& out, const matrix<T, N, M>& m)
    {
        out << "[" << m[0];
        for (size_t i = 1; i < N; i++)
            out << "\n " << m[i];
        return out << "]";
    }
}
