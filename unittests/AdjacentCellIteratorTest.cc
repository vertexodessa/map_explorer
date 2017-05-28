#include "utils/AdjacentCellIterator.h"

#include "gtest/gtest.h"

#include <cstdlib>

template <typename T>
class IteratorTest : public ::testing::Test {
protected:
    void SetUp() override {
        std::srand(std::time(nullptr));
    }
    void TearDown() override {  }
};

typedef ::testing::Types<char, int, unsigned int> MyTypes;
TYPED_TEST_CASE(IteratorTest, MyTypes);

TYPED_TEST(IteratorTest, IteratingFromZeroIndex10x10) {
    AdjacentCells<TypeParam> cells(10, 10, 0);
    typename AdjacentCells<TypeParam>::iterator i = cells.begin();

    EXPECT_EQ(*i, 1);
    EXPECT_EQ(*++i, 10);
    EXPECT_EQ(++i, cells.end());
}

TYPED_TEST(IteratorTest, IteratingFromZeroIndex9x10) {
    AdjacentCells<TypeParam> cells(9, 10, 0);
    typename AdjacentCells<TypeParam>::iterator i = cells.begin();

    EXPECT_EQ(*i, 1);
    EXPECT_EQ(*++i, 9);
    EXPECT_EQ(++i, cells.end());
}

TYPED_TEST(IteratorTest, TwoRandomlyInitializedIteratorsShouldBehaveEqual5x5) {
    TypeParam r = rand() % 25;
    AdjacentCells<TypeParam> cells(5, 5, r);
    typename AdjacentCells<TypeParam>::iterator i = cells.begin();
    typename AdjacentCells<TypeParam>::iterator i2 = cells.begin();

    while (i != cells.end()) {
        EXPECT_EQ(*i, *i2);
        ++i;
        ++i2;
    }

    EXPECT_EQ(i, cells.end());
    EXPECT_EQ(i2, cells.end());
}

TYPED_TEST(IteratorTest, IteratingFromMiddleIndex10x10) {
    AdjacentCells<TypeParam> cells(10, 10, 23);
    typename AdjacentCells<TypeParam>::iterator i = cells.begin();

    EXPECT_EQ(*i, 22);
    EXPECT_EQ(*++i, 24);
    EXPECT_EQ(*++i, 13);
    EXPECT_EQ(*++i, 33);

    EXPECT_EQ(++i, cells.end());
}

TYPED_TEST(IteratorTest, IteratingFromLastIndex5x5) {
    AdjacentCells<TypeParam> cells(5, 5, 24);
    typename AdjacentCells<TypeParam>::iterator i = cells.begin();

    EXPECT_EQ(*i, 23);
    EXPECT_EQ(*++i, 24-5);
    EXPECT_EQ(++i, cells.end());
}
