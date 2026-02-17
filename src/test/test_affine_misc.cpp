//
// Created by will on 2/17/26.
//

#include "gtest/gtest.h"
#include "../AffineForm.hpp"

TEST(affine_misc, min_max) {
    // Just a sanity test to make sure the test suite is working.
    auto a = AffineForm(Winterval(-2, 3));
    ASSERT_NEAR(a.min(), -2, 0.001);
    ASSERT_NEAR(a.max(), 3, 0.001);

    a = a - AffineForm(Winterval(4, 5));
    ASSERT_NEAR(a.min(), -7, 0.001);
    ASSERT_NEAR(a.max(), -1, 0.001);
}
