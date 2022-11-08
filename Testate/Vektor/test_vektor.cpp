#include "Vektor.h"
#include "alltest.h"
#include "gtest/gtest.h"
#include <iomanip>
#include <iostream>
using namespace std;

// EXPECT_EQ(a, b): a und b müssen gleich sein, sonst Fehler
// ASSERT_EQ(a, b): a und b müssen gleich sein, sonst Fehler und Abbruch

TEST_F(AllTest, construct1) { // ohne Speicherleackcheck
  SuspendMemCheck smc;
  Vektor v;
  ASSERT_EQ(v._len, 3);
  for (int i = 0; i < 3; ++i) { // musn't use SuspendMemCheck
    ASSERT_EQ(v._vek[i], 0);
  }
}

TEST_F(AllTest, construct2) { // ab hier alle mit Speicherleakcheck
  Vektor v;
  {
    SuspendMemCheck smc;
    ASSERT_EQ(v._len, 3);
    for (int i = 0; i < 3; ++i) {
      ASSERT_EQ(v._vek[i], 0);
    }
  }
}

TEST_F(AllTest, copy) {
  Vektor v(5);
  for (unsigned i = 0; i < 5; i++) {
    v._vek[i] = i;
  }
  Vektor w(v);
  {
    SuspendMemCheck smc;
    ASSERT_EQ(5, w._len);
    for (unsigned i = 0; i < 5; i++) {
      EXPECT_EQ(i, w._vek[i]);
    }
  }
}

TEST_F(AllTest, assign1) {
  Vektor v(5);
  for (unsigned i = 0; i < 5; i++) {
    v._vek[i] = i;
  }
  Vektor w(7);
  for (unsigned i = 0; i < 7; i++) {
    w._vek[i] = 10 - i;
  }
  {
    SuspendMemCheck smc;
    ASSERT_EQ(7, w._len);
    for (unsigned i = 0; i < 7; i++) {
      EXPECT_EQ(10 - i, w._vek[i]);
    }
  }
  w = v;

  {
    SuspendMemCheck smc;
    ASSERT_EQ(5, w._len);
    for (unsigned i = 0; i < 5; i++) {
      EXPECT_EQ(i, w._vek[i]);
    }
  }
}

TEST_F(AllTest, assign2) {
  Vektor v(5);
  for (unsigned i = 0; i < 5; i++) {
    v._vek[i] = 8;
  }
  Vektor w(8);
  for (unsigned i = 0; i < 8; i++) {
    w._vek[i] = 10 - i;
  }
  {
    SuspendMemCheck smc;
    ASSERT_EQ(8, w._len);
    for (unsigned i = 0; i < 8; i++) {
      EXPECT_EQ(10 - i, w._vek[i]);
    }
  }
  v = v; // @suppress("Assignment to itself")
  {
    SuspendMemCheck smc;

    for (unsigned i = 0; i < 5; i++) {
      EXPECT_EQ(8, v._vek[i]);
    }
  }
  w = v;

  {
    SuspendMemCheck smc;
    ASSERT_EQ(5, w._len);
    for (unsigned i = 0; i < 5; i++) {
      EXPECT_EQ(8, w._vek[i]);
    }
  }
}

TEST_F(AllTest, plus1) {
  SuspendMemCheck smc;
  Vektor v(5);
  for (unsigned i = 0; i < 5; i++) {
    v._vek[i] = 5;
  }
  Vektor w(5);
  for (unsigned i = 0; i < 5; i++) {
    w._vek[i] = 100 + i;
  }
  Vektor z = v + w;
  {
    ASSERT_EQ(5, z._len);
    for (unsigned i = 0; i < 5; i++) {
      EXPECT_EQ(105 + i, z._vek[i]);
    }
  }
}

TEST_F(AllTest, plus2) {
  SuspendMemCheck smc;
  Vektor v(5);
  for (unsigned i = 0; i < 5; i++) {
    v._vek[i] = 5;
  }
  Vektor w(5);
  for (unsigned i = 0; i < 5; i++) {
    w._vek[i] = 100 + i;
  }
  Vektor z = v + w;
  {
    ASSERT_EQ(5, z._len);
    for (unsigned i = 0; i < 5; i++) {
      EXPECT_EQ(105 + i, z._vek[i]);
    }
  }
  Vektor a(10);
  EXPECT_THROW(a + v, std::runtime_error);
  EXPECT_THROW(v + a, std::runtime_error);
}

TEST_F(AllTest, plus3) {
  Vektor v(5);
  for (unsigned i = 0; i < 5; i++) {
    v._vek[i] = 5;
  }
  Vektor w(5);
  for (unsigned i = 0; i < 5; i++) {
    w._vek[i] = 100 + i;
  }
  Vektor z = v + w;
  {
    SuspendMemCheck smc;
    ASSERT_EQ(5, z._len);
    for (unsigned i = 0; i < 5; i++) {
      EXPECT_EQ(105 + i, z._vek[i]);
    }
  }
  Vektor a(10);
  {
    SuspendMemCheck smc;
    EXPECT_THROW(a + v, std::runtime_error);
    EXPECT_THROW(v + a, std::runtime_error);
  }
}

TEST_F(AllTest, resize1) {
  Vektor v(6);
  for (unsigned i = 0; i < 6; i++) {
    v._vek[i] = 77 + i;
  }
  Vektor w(8);
  for (unsigned i = 0; i < 8; i++) {
    w._vek[i] = 130 + i;
  }

  {
    SuspendMemCheck smc;
    ASSERT_EQ(6, v._len);
    for (unsigned i = 0; i < 6; i++) {
      EXPECT_EQ(v._vek[i], 77 + i);
    }
    ASSERT_EQ(8, w._len);
    for (unsigned i = 0; i < 6; i++) {
      EXPECT_EQ(w._vek[i], 130 + i);
    }
  }
  v.resize(10);
  {
    SuspendMemCheck smc;
    ASSERT_EQ(10, v._len);
    for (unsigned i = 0; i < 6; i++) {
      EXPECT_EQ(v._vek[i], 77 + i);
    }
    for (unsigned i = 7; i < 10; i++) {
      EXPECT_EQ(v._vek[i], 0);
    }
  }
  w.resize(4);
  {
    SuspendMemCheck smc;
    ASSERT_EQ(4, w._len);
    for (unsigned i = 0; i < 4; i++) {
      EXPECT_EQ(w._vek[i], 130 + i);
    }
  }
}

TEST_F(AllTest, resize2) {
  Vektor v(6);
  for (unsigned i = 0; i < 6; i++) {
    v._vek[i] = 77 + i;
  }
  Vektor w(8);
  for (unsigned i = 0; i < 8; i++) {
    w._vek[i] = 130 + i;
  }

  {
    SuspendMemCheck smc;
    ASSERT_EQ(6, v._len);
    for (unsigned i = 0; i < 6; i++) {
      EXPECT_EQ(v._vek[i], 77 + i);
    }
    ASSERT_EQ(8, w._len);
    for (unsigned i = 0; i < 6; i++) {
      EXPECT_EQ(w._vek[i], 130 + i);
    }
  }
  v.resize(10);
  {
    SuspendMemCheck smc;
    ASSERT_EQ(10, v._len);
    for (unsigned i = 0; i < 6; i++) {
      EXPECT_EQ(v._vek[i], 77 + i);
    }
    for (unsigned i = 7; i < 10; i++) {
      EXPECT_EQ(v._vek[i], 0);
    }
  }
  w.resize(8);
  {
    SuspendMemCheck smc;
    ASSERT_EQ(8, w._len);
    for (unsigned i = 0; i < 8; i++) {
      EXPECT_EQ(w._vek[i], 130 + i);
    }
  }
}
