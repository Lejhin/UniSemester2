#include "gtest/gtest.h"
#include "at.h"

TEST(at, OutOfBound) {
    int v1[10];
    int v2[20];
    EXPECT_ANY_THROW(at(v1, 10, 10));
    EXPECT_ANY_THROW(at(v2, 20, 20));
    EXPECT_ANY_THROW(at(v1, 10, 1234567));
}

TEST(at, AccessElements) {
    int v1[10];
    for(int i = 0; i < 10; ++i) {
        v1[i] = i;
        EXPECT_EQ(at(v1,10,i), i);
    }
}

TEST(at, ModifyElement) {
    int v1[10];
    at(v1,10,5) = 999;
    EXPECT_EQ(v1[5], 999);
    at(v1,10,5) = 333;
    EXPECT_EQ(v1[5], 333);
}
