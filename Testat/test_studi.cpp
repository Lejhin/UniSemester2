#include <iostream>
#include "gtest/gtest.h"
#include "alltest.h"
#include "Studi.h"
using namespace std;

static void fillimage(char *a, int size);

TEST_F(AllTest, constructTest1) {
    Studi ghost;
}

TEST_F(AllTest, constructTest2) {
    long matnr = 1234567L;
    string vorname = "Rudi";
    string nachname = "Ratlos";

    Studi rudi(matnr, vorname, nachname);
    EXPECT_EQ(rudi.matnr(), matnr);
    EXPECT_EQ(rudi.vorname(), vorname);
    EXPECT_EQ(rudi.nachname(), "Ratlos");
}

TEST_F(AllTest, constructArrayTest) {
    Studi empty_studis[2]; // leer

    long matnr1 = 1234567L;
    string vorname1 = "Rudi";
    string nachname1 = "Ratlos";
    long matnr2 = 7654321L;
    string vorname2 = "Susi";
    string nachname2 = "Sinnlos";
    Studi studis[2] = { {matnr1, vorname1, nachname1},
                        {matnr2, vorname2, nachname2} };
    Studi &rudi = studis[0];
    EXPECT_EQ(rudi.matnr(), matnr1);
    EXPECT_EQ(rudi.vorname(), vorname1);
    EXPECT_EQ(rudi.nachname(), nachname1);
    Studi &susi = studis[1];
    EXPECT_EQ(susi.matnr(), matnr2);
    EXPECT_EQ(susi.vorname(), vorname2);
    EXPECT_EQ(susi.nachname(), nachname2);
}


TEST_F(AllTest, setmatnrTest) {
    long matnr = 1234567;
    long neu_matnr = 7654321;
    Studi willi = { matnr, "Willi", "Wahnsinn" };
    EXPECT_FALSE(willi.set_matnr(666));
    EXPECT_FALSE(willi.set_matnr(13));
    EXPECT_FALSE(willi.set_matnr(0));
    EXPECT_FALSE(willi.set_matnr(123456));
    EXPECT_FALSE(willi.set_matnr(123456789));
    EXPECT_EQ(willi.matnr(), matnr);
    EXPECT_TRUE(willi.set_matnr(neu_matnr));
    EXPECT_EQ(willi.matnr(), neu_matnr);
}

TEST_F(AllTest, clearMatnrOnCopy) {
    long matnr = 1234567;
    Studi willi = { matnr, "Willi", "Wahnsinn" };
    EXPECT_EQ(willi.matnr(), matnr);
    Studi notwilli(willi);
    EXPECT_EQ(willi.matnr(), matnr);
    EXPECT_NE(notwilli.matnr(), matnr);
    EXPECT_EQ(notwilli.matnr(), 0);
}

TEST_F(AllTest, copyImageMemory) {
    long matnr = 1234567;
    Studi willi = { matnr, "Willi", "Wahnsinn" };
    int len = 128;
    char image[len];
    fillimage(image, len);
    willi.set_image(image, len);
}

TEST_F(AllTest, copyImageFill) {
    long matnr = 1234567;
    Studi willi = { matnr, "Willi", "Wahnsinn" };
    int len = 128;
    char image[len];
    fillimage(image, len);
    willi.set_image(image, len);
    char *img = willi.get_image();
    for (int i=0; i < len; i++) {
        ASSERT_EQ(image[i], img[i]);
    }
}

TEST_F(AllTest, copyStudiImage) {
    long matnr = 1234567;
    Studi willi = { matnr, "Willi", "Wahnsinn" };
    ASSERT_EQ(willi.get_image(), nullptr);
    int len = 128;
    char image[len];
    fillimage(image, len);
    willi.set_image(image, len);
    Studi notwilli(willi);
    char *img1 = willi.get_image();
    char *img2 = notwilli.get_image();
    ASSERT_NE(img1, img2);
    ASSERT_NE(img1, nullptr);
    ASSERT_NE(img2, nullptr);
    for (int i=0; i < len; i++) {
        ASSERT_EQ(img1[i], img2[i]);
    }
}

static void fillimage(char *a, int size) {
    // not 0 terminated, no 0s, just small chars
    char small_chars[] = "abcdefghijklmnopqrstuvwxyz";
    int anz_small_chars = sizeof(small_chars) / sizeof(char);
    for (int i=0; i < size; i+=1) {
        a[i] = small_chars[i%anz_small_chars];
    }
}
