#include "gtest/gtest.h"
#include "simplemath.h"

TEST(testMath, einfach) {
    // mit EXPECT_EQ werden zwei Werte verglichen
    // wenn diese nicht gleich sind, dann schlägt
    // der Test fehl und der Grund (die beiden
    // unterschiedlichen Werte) werden angezeigt.
    EXPECT_EQ(quadrat(10), 100); 
    EXPECT_EQ(kubik(10), 1000);
    EXPECT_EQ(hoch4(10), 10000);
}

TEST(testMath, mehr) {
    for (int i=-100; i < 100; i+=1) {
        // ASSERT_EQ ist wie EXPECT_EQ, nur wird der Test
        // beim ersten Fehlschlag abgebrochen
        ASSERT_EQ(quadrat(i), i*i);
        ASSERT_EQ(kubik(i), i*i*i);
        ASSERT_EQ( hoch4(i), i*i*i*i);
    }
}
