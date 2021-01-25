#pragma once

////////////////////////////////////////////////////////////////
// Module includes.
////////////////////////////////////////////////////////////////

#include "bettertest/mixins/compare_mixin.h"
#include "bettertest/tests/unit_test.h"

class VectorAdd : public bt::UnitTest<VectorAdd, bt::CompareMixin>
{
public:
    void operator()() override;
};
