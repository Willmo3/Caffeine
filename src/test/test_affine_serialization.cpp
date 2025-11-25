//
// Created by will on 10/21/25.
//

#include <gtest/gtest.h>

#include "cereal/archives/json.hpp"
#include "cereal/types/vector.hpp"
#include "../src/AffineForm.hpp"

TEST(affine_serialization, serialize_deserialize) {
    auto original = AffineForm(Winterval(-2, 3));

    std::stringstream ss;
    {
        cereal::JSONOutputArchive oarchive(ss);
        oarchive(original);
    }

    auto deserialized = AffineForm();
    {
        cereal::JSONInputArchive iarchive(ss);
        iarchive(deserialized);
    }

    ASSERT_TRUE(original == deserialized);
}

TEST(affine_serialization, serialize_vector) {
    auto original = std::vector<AffineForm>();

    for (auto i = 0; i < 2000; i++) {
        original.emplace_back(AffineForm(Winterval(i, i + 1)));
    }
    std::stringstream ss;
    {
        cereal::JSONOutputArchive oarchive(ss);
        oarchive(original);
    }

    auto new_vec = std::vector<AffineForm>();
    {
        cereal::JSONInputArchive iarchive(ss);
        iarchive(new_vec);
    }

    assert(original[0] == new_vec[0]);
    assert(original[1] == new_vec[1]);
    assert(original[1999] == new_vec[1999]);
}