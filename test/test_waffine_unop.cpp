//
// Created by will on 9/30/25.
//

// NOTE: gtest keeps static state in a given test suite (i.e. waffine).
// Therefore, we switch noise symbols.

#include <gtest/gtest.h>

#include "../src/WaffineForm.hpp"

TEST(waffine_unop, negation) {
    auto value = -WaffineForm(Winterval(-2, 3));
    ASSERT_NEAR(value.center(), -0.5, 0.001);
    ASSERT_NEAR(value.radius(), 2.5, 0.001);
}