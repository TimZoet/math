#pragma once

////////////////////////////////////////////////////////////////
// Module includes.
////////////////////////////////////////////////////////////////

#include "bettertest/mixins/compare_mixin.h"
#include "bettertest/tests/unit_test.h"

class VectorMul : public bt::UnitTest<VectorMul, bt::CompareMixin>
{
public:
    void operator()() override;
};
