//
// Created by will on 10/23/25.
//

#include <gtest/gtest.h>
#include "../src/WaffineForm.hpp"

TEST(waffine_equals, equality) {
    auto first = WaffineForm(Winterval(-2, 3));
    ASSERT_TRUE(first == first);

    auto third = first + WaffineForm(Winterval(1, 1));
    ASSERT_FALSE(first == third);
}