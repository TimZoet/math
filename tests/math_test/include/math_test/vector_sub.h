#pragma once

////////////////////////////////////////////////////////////////
// Module includes.
////////////////////////////////////////////////////////////////

#include "bettertest/mixins/compare_mixin.h"
#include "bettertest/tests/unit_test.h"

class VectorSub : public bt::UnitTest<VectorSub, bt::CompareMixin>
{
public:
    void operator()() override;
};
