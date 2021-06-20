#include "math_test/vector_equals.h"

#include "math/include_all.h"

void VectorEquals::operator()()
{
    // Test vectors with different element types and lengths.

    compareEQ(math::int2(0, 10), math::int2(0, 10));
    compareEQ(math::int3(50000, -3010, 40), math::int3(50000, -3010, 40));
    compareEQ(math::ushort4(40, 80, 160, 320), math::ushort4(40, 80, 160, 320));
    compareEQ(math::float4(40, 80, 160, 320), math::float4(40, 80, 160, 320));
    compareEQ(math::vec<float, 5>(40, 80, 160, 320, 640), math::vec<float, 5>(40, 80, 160, 320, 640));

    compareNE(math::int2(10, 20), math::int2(20, 20));
    compareNE(math::int2(20, 10), math::int2(20, 20));
    compareEQ(math::vec<float, 5>(400, 80, 160, 320, 640), math::vec<float, 5>(40, 80, 160, 320, 640));
    compareEQ(math::vec<float, 5>(40, 800, 160, 320, 640), math::vec<float, 5>(40, 80, 160, 320, 640));
    compareEQ(math::vec<float, 5>(40, 80, 1600, 320, 640), math::vec<float, 5>(40, 80, 160, 320, 640));
    compareEQ(math::vec<float, 5>(40, 80, 160, 3200, 640), math::vec<float, 5>(40, 80, 160, 320, 640));
    compareEQ(math::vec<float, 5>(40, 80, 160, 320, 6400), math::vec<float, 5>(40, 80, 160, 320, 640));
}
