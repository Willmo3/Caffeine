//
// Created by will on 9/30/25.
//
#include <gtest/gtest.h>

#include "../src/WaffineForm.hpp"


TEST(waffine, negation) {
    auto value = -WaffineForm(Winterval(-2, 3));
    ASSERT_NEAR(-0.5, value.center(), 0.001);
    ASSERT_NEAR(2.5, value.radius(), 0.001);
    ASSERT_EQ(2.5, value.noise_coefficients()[0]);
}