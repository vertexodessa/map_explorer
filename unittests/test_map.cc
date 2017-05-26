#include "Logging.h"
#include "Map.h"

#include "gtest/gtest.h"

#include <utility>
#include <vector>
#include <sstream>

using namespace std;
using namespace map_solver;

const int kMapWidth = 10;
const int kMapHeight = 10;

const char kTestField[] =
    "s         "
    "          "
    "          "
    " ******   "
    "          "
    "          "
    "          "
    "          "
    "          "
    "        *e";

class MapTest : public ::testing::Test {
protected:
    virtual void SetUp() override {
        Logging::initLogging();
    }
    virtual void TearDown() override {  }
    Map m_map;
};

TEST_F(MapTest, InitialWidthHeight) {
    EXPECT_EQ(m_map.width(), -1);
    EXPECT_EQ(m_map.height(), -1);
}

TEST_F(MapTest, ExpectedWidthHeight) {
    m_map.readFromFile(GTEST_MAP_FILE);

    ASSERT_EQ(m_map.width(), kMapWidth);
    ASSERT_EQ(m_map.height(), kMapHeight);
}

TEST_F(MapTest, ExpectedCellCount) {
    ASSERT_EQ(m_map.readFromFile(GTEST_MAP_FILE), kMapWidth * kMapHeight);
}

TEST_F(MapTest, ReadFromStream) {
    stringstream stream;

    index_t ten = 10;
    stream.write((const char*)&ten, sizeof(index_t));
    stream.write((const char*)&ten, sizeof(index_t));
    stream.write(kTestField, sizeof(kTestField) - 1);

    ASSERT_EQ(sizeof(kTestField), 101);
    ASSERT_EQ(m_map.readFromStream(stream), 100);
}

TEST_F(MapTest, StartFinish) {
    stringstream stream;
    index_t ten = 10;
    stream.write((const char*)&ten, sizeof(index_t));
    stream.write((const char*)&ten, sizeof(index_t));
    stream.write(kTestField, sizeof(kTestField) - 1);

    ASSERT_EQ(m_map.readFromStream(stream), 100);
    ASSERT_EQ(m_map.start(), 0);
    ASSERT_EQ(m_map.finish(), 99);
}

TEST_F(MapTest, Weight) {
    stringstream stream;
    index_t ten = 10;
    stream.write((const char*)&ten, sizeof(index_t));
    stream.write((const char*)&ten, sizeof(index_t));
    stream.write(kTestField, sizeof(kTestField) - 1);

    ASSERT_EQ(m_map.readFromStream(stream), 100);

    ASSERT_EQ(m_map.weight(m_map.start()), 1);
    ASSERT_EQ(m_map.weight(m_map.finish()), 1);

    index_t cellWithWall = m_map.finish() - 1;
    EXPECT_GT(m_map.weight(cellWithWall), 50000);
}
