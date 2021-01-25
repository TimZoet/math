#pragma once

////////////////////////////////////////////////////////////////
// Module includes.
////////////////////////////////////////////////////////////////

#include "bettertest/mixins/compare_mixin.h"
#include "bettertest/tests/unit_test.h"

class VectorDiv : public bt::UnitTest<VectorDiv, bt::CompareMixin>
{
public:
    void operator()() override;
};
