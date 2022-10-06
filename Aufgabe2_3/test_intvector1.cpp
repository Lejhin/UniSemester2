#include <gtest/gtest.h>
#include "alltest.h"

#include "IntVector.h"

// mit AllTest bei TEST_F wird Speicher überprüft

void fill(IntVector& vec, int val = 0) {
    for (size_t i = 0; i < vec.size(); ++i) {
        vec.at(i) = val * val;
        val += 1;
    }
}

TEST_F(AllTest, einfach_size) {
    size_t size = 10;
    IntVector v(size); // Groesse in () wie bei vector
    {
        SuspendMemCheck smc;
        EXPECT_EQ(size, v.size());
    }
}

TEST_F(AllTest, at) {
    size_t size = 42;
    IntVector v(size);
    fill(v, 17);
    for (size_t idx = 0; idx < v.size(); idx += 1) {
        {
            SuspendMemCheck smc;
            EXPECT_EQ((17 + idx) * (17 + idx), v.at(idx));
        }
    }
}

void check_fail(IntVector& v, size_t idx) {
    try {
        v.at(10); // out of range
        {
            SuspendMemCheck smc;
            FAIL() << "Zugriff v.at(" << idx << ") sollte Fehler werfen";
        }
    } catch (std::runtime_error& e) {
        // erwarteter Fehler
        {
            SuspendMemCheck smc;
            EXPECT_STREQ(e.what(), "index out of range");
        }
    } catch (...) {
        {
            SuspendMemCheck smc;
            FAIL() << "Zugriff v.at(" << idx
                   << ") sollte std::runtime_error werfen";
        }
    }
}

TEST_F(AllTest, at_fail) {
    size_t size = 10;
    IntVector v(size);
    fill(v);
    check_fail(v, size);
    check_fail(v, -1);
    check_fail(v, size + 1000000);
}

TEST_F(AllTest, Kopierkonstruktor) {
    size_t size = 20;
    IntVector v1(size);
    fill(v1, 0);
    IntVector v2(v1);
    {
        SuspendMemCheck smc;
        EXPECT_EQ(v1.size(), v2.size());
    }
    for (size_t i = 0; i < v1.size(); ++i) {
        {
            SuspendMemCheck smc;
            EXPECT_EQ(v1.at(i), v2.at(i));
        }
    }
}

TEST_F(AllTest, Zuweisungsoperator) {
    IntVector v1(20);
    fill(v1, 2);
    IntVector v2(10);
    v2 = v1;
    {
        SuspendMemCheck smc;
        EXPECT_EQ(v1.size(), v2.size());
    }
    for (size_t i = 0; i < v1.size(); ++i) {
        {
            SuspendMemCheck smc;
            EXPECT_EQ(v1.at(i), v2.at(i));
        }
    }
    IntVector v3(30);
    IntVector v4(20);
    fill(v4, 3);
    v3 = v4;
    {
        SuspendMemCheck smc;
        EXPECT_EQ(v3.size(), v4.size());
        EXPECT_EQ(20, v3.size());
    }
    for (size_t i = 0; i < v3.size(); ++i) {
        {
            SuspendMemCheck smc;
            EXPECT_EQ(v3.at(i), v4.at(i));
        }
    }
    v1 = v2 = v3 = v4;
}
