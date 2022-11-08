#include <cstddef>
#include <stdexcept>
#ifndef VEKTOR_H_
#define VEKTOR_H_
#include <gtest/gtest.h>

class Vektor {
public:
	Vektor();
	Vektor(unsigned len);
	Vektor(const Vektor &other);
	~Vektor();
	Vektor &operator=(const Vektor &other);
	double &operator[](unsigned i) {return _vek[i];}
	void resize(unsigned l);
    unsigned get_len(){return _len;}


private:
	double *_vek;
	unsigned _len;
	FRIEND_TEST(AllTest, construct1);
	FRIEND_TEST(AllTest, construct2);
	FRIEND_TEST(AllTest, copy);
	FRIEND_TEST(AllTest, assign1);
	FRIEND_TEST(AllTest, assign2);
	FRIEND_TEST(AllTest, plus1);
	FRIEND_TEST(AllTest, plus2);
	FRIEND_TEST(AllTest, plus3);
	FRIEND_TEST(AllTest, resize1);
	FRIEND_TEST(AllTest, resize2);
};

Vektor operator+(Vektor left, Vektor right);

#endif /* INTVECTOR_H_ */
