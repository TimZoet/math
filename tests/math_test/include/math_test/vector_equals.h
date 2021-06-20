#pragma once

////////////////////////////////////////////////////////////////
// Module includes.
////////////////////////////////////////////////////////////////

#include "bettertest/mixins/compare_mixin.h"
#include "bettertest/tests/unit_test.h"

class VectorEquals : public bt::UnitTest<VectorEquals, bt::CompareMixin>
{
public:
    void operator()() override;
};
