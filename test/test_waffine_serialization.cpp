//
// Created by will on 10/21/25.
//

#include <gtest/gtest.h>

#include "cereal/archives/json.hpp"
#include "../src/WaffineForm.hpp"

TEST(waffine_serialization, serialize_deserialize) {
    auto original = WaffineForm(Winterval(-2, 3));

    std::stringstream ss;
    {
        cereal::JSONOutputArchive oarchive(ss);
        oarchive(original);
    }

    WaffineForm deserialized(Winterval(0,0));
    {
        cereal::JSONInputArchive iarchive(ss);
        iarchive(deserialized);
    }

    auto original_interval = original.to_interval();
    auto deserialized_interval = deserialized.to_interval();

    ASSERT_NEAR(original_interval.min(), deserialized_interval.min(), 0.001);
    ASSERT_NEAR(original_interval.max(), deserialized_interval.max(), 0.001);
}