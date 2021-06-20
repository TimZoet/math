#include "math_test/vector_div.h"

#include "math/include_all.h"

void VectorDiv::operator()()
{
    // Test vectors with different element types and lengths.

    compareEQ(math::int2(300, 10000) / math::int2(30, -20), math::int2(300 / 30, 10000 / -20));

    compareEQ(math::int3(50000, -3010, 40) / math::int3(4564, -2345, 7564534),
              math::int3(50000 / 4564, -3010 / -2345, 40 / 7564534));

    compareEQ(math::ushort4(40, 80, 160, 320) / math::ushort4(16, 32, 64, 128),
              math::ushort4(40 / 16, 80 / 32, 160 / 64, 320 / 128));

    compareEQ(math::float4(40, 80, 160, 320) / math::float4(16, 32, 64, 128),
              math::float4(40.0f / 16.0f, 80.0f / 32.0f, 160.0f / 64.0f, 320.0f / 128.0f));

    compareEQ(math::vec<float, 5>(40, 80, 160, 320, 640) / math::vec<float, 5>(16, 32, 64, 128, 256),
              math::vec<float, 5>(40.0f / 16.0f, 80.0f / 32.0f, 160.0f / 64.0f, 320.0f / 128.0f, 640.0f / 256.0f));

    // Test compound assignment.
    math::vec<float, 5> a(40, 80, 160, 320, 640);
    a /= math::vec<float, 5>(16, 32, 64, 128, 256);
    compareEQ(a, math::vec<float, 5>(40.0f / 16.0f, 80.0f / 32.0f, 160.0f / 64.0f, 320.0f / 128.0f, 640.0f / 256.0f));
}
