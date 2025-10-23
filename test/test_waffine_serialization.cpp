//
// Created by will on 10/21/25.
//

#include <gtest/gtest.h>

#include "cereal/archives/json.hpp"
#include "cereal/types/vector.hpp"
#include "../src/WaffineForm.hpp"

TEST(waffine_serialization, serialize_deserialize) {
    auto original = WaffineForm(Winterval(-2, 3));

    std::stringstream ss;
    {
        cereal::JSONOutputArchive oarchive(ss);
        oarchive(original);
    }

    auto deserialized = WaffineForm();
    {
        cereal::JSONInputArchive iarchive(ss);
        iarchive(deserialized);
    }

    ASSERT_TRUE(original == deserialized);
}

TEST(waffine_serialization, serialize_vector) {
    auto original = std::vector<WaffineForm>();

    for (auto i = 0; i < 2000; i++) {
        original.emplace_back(WaffineForm(Winterval(i, i + 1)));
    }
    std::stringstream ss;
    {
        cereal::JSONOutputArchive oarchive(ss);
        oarchive(original);
    }

    auto new_vec = std::vector<WaffineForm>();
    {
        cereal::JSONInputArchive iarchive(ss);
        iarchive(new_vec);
    }

    assert(original[0] == new_vec[0]);
    assert(original[1] == new_vec[1]);
    assert(original[1999] == new_vec[1999]);
}