

#include <iostream>
#include <cassert>
#include <vector>
#include <memory>

using namespace std;

#include "gtest/gtest.h"

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
