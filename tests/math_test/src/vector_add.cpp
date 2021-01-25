#include "math_test/vector_add.h"

#include "math/include_all.h"

void VectorAdd::operator()()
{
    compareEQ(math::int2(0, 10) + math::int2(30, -20), math::int2(0 + 30, 10 - 20));

    compareEQ(math::int3(50000, -3010, 40) + math::int3(45634, -2345, 7564534),
              math::int3(50000 + 45634, -3010 - 2345, 40 + 7564534));

    compareEQ(math::ushort4(40, 80, 160, 320) + math::ushort4(16, 32, 64, 128),
              math::ushort4(40 + 16, 80 + 32, 160 + 64, 320 + 128));

    compareEQ(math::float4(40, 80, 160, 320) + math::float4(16, 32, 64, 128),
              math::float4(40 + 16, 80 + 32, 160 + 64, 320 + 128));

    compareEQ(math::vec<float, 5>(40, 80, 160, 320, 640) + math::vec<float, 5>(16, 32, 64, 128, 256),
              math::vec<float, 5>(40 + 16, 80 + 32, 160 + 64, 320 + 128, 640 + 256));
}
