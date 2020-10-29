#include "gtest/gtest.h"

extern "C" {
#include "testy/customer.h"
}

TEST(skyscraper, purpose_output) {
    struct skyscraper skyscrapers[3] = {
            { 81, 300,  30,  "office",  "euro"},
            { 90, 320,  35,  "home", "asian"},
            { 75, 280,  25,  "office",  "asian"}
    };
    qsort(skyscrapers, 3, sizeof(struct skyscraper*), comp_purpose);
    EXPECT_EQ(skyscrapers[0].purpose, "home");
    EXPECT_EQ(skyscrapers[1].purpose, "home");
    EXPECT_EQ(skyscrapers[2].purpose, "office");
}

TEST(skyscraper, location_region_output) {
    struct skyscraper skyscrapers[3] = {
            { 81, 300,  30,  "office",  "euro"},
            { 90, 320,  35,  "home", "asian"},
            { 75, 280,  25,  "office",  "asian"}
    };
    qsort(skyscrapers, 3, sizeof(struct skyscraper*), comp_location_region);
    EXPECT_EQ(skyscrapers[0].purpose, "euro");
    EXPECT_EQ(skyscrapers[1].purpose, "asian");
    EXPECT_EQ(skyscrapers[2].purpose, "asian");
}
