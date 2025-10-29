//
// Created by will on 10/23/25.
//

#include <gtest/gtest.h>
#include "../src/AffineForm.hpp"

TEST(affine_equals, equality) {
    auto first = AffineForm(Winterval(-2, 3));
    ASSERT_TRUE(first == first);

    auto third = first + AffineForm(Winterval(1, 1));
    ASSERT_FALSE(first == third);
}