//
// Created by will on 9/30/25.
//
#include <gtest/gtest.h>

#include "../src/WaffineForm.hpp"

TEST(waffine_binop, add) {
    auto base = WaffineForm(Winterval(-2, 3));
    auto next = base + WaffineForm(Winterval(4, 5));
    ASSERT_NEAR(next.center(), 5, 0.001);
    ASSERT_NEAR(next.radius(), 3, 0.001);
}

TEST(waffine_binop, sub) {
    auto base = WaffineForm(Winterval(-2, 3));
    auto next = base - WaffineForm(Winterval(4, 5));
    ASSERT_NEAR(next.center(), -4, 0.001);
    ASSERT_NEAR(next.radius(), 3, 0.001);

    // test correspondence of variables.
    next = next - base;
    ASSERT_NEAR(next.coeff_of(2), 0, 0.001);
    ASSERT_NEAR(next.coeff_of(3), 0.5, 0.001);
}

TEST(waffine_binop, mult) {
    auto base = WaffineForm(Winterval(-2, 3));
    auto next = base * WaffineForm(Winterval(4, 5));
    ASSERT_NEAR(next.center(), 2.25, 0.001);
    ASSERT_NEAR(next.radius(), 12.75, 0.001);
    ASSERT_NEAR(next.coeff_of(4), -11.25, 0.001);
    ASSERT_NEAR(next.coeff_of(5), -0.25, 0.001);
    ASSERT_NEAR(next.coeff_of(6), 1.25, 0.001);
}

TEST(waffine_binop, div) {
    auto base = WaffineForm(Winterval(-2, 3));
    auto next = base / WaffineForm(Winterval(4, 5));
    ASSERT_NEAR(next.center(), 0.112500, 0.001);
    ASSERT_NEAR(next.radius(), 0.637500, 0.001);
    ASSERT_NEAR(next.coeff_of(7), -0.562500, 0.001);
    ASSERT_NEAR(next.coeff_of(8), 0.010000, 0.001);
    ASSERT_NEAR(next.coeff_of(9), -0.002500, 0.001);
    ASSERT_NEAR(next.coeff_of(10), 0.062500, 0.001);
}