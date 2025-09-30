//
// Created by will on 9/30/25.
//
#include <gtest/gtest.h>

#include "../src/WaffineForm.hpp"


TEST(waffine, negation) {
    auto value = -WaffineForm(Winterval(-2, 3));
    ASSERT_NEAR(value.center(), -0.5, 0.001);
    ASSERT_NEAR(value.radius(), 2.5, 0.001);
    ASSERT_EQ(value.coeff_of(0), 2.5);
}

TEST(waffine, add) {
    auto base = WaffineForm(Winterval(-2, 3));
    auto next = base + WaffineForm(Winterval(4, 5));
    ASSERT_NEAR(next.center(), 5, 0.001);
    ASSERT_NEAR(next.radius(), 3, 0.001);
}