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

class MapTest : public ::testing::Test {
protected:
    virtual void SetUp() override {
        Logging::initLogging();
        m_map = make_unique<Map>();
    }
    virtual void TearDown() override {  }
    std::unique_ptr<Map> m_map;
};

TEST_F(MapTest, InitialWidthHeight) {
    ASSERT_EQ(m_map->width(), -1);
    ASSERT_EQ(m_map->height(), -1);
}

TEST_F(MapTest, ExpectedWidthHeight) {
    m_map->readFromFile(GTEST_MAP_FILE);

    ASSERT_EQ(m_map->width(), kMapWidth);
    ASSERT_EQ(m_map->height(), kMapHeight);
}

TEST_F(MapTest, ExpectedCellCount) {
    ASSERT_EQ(m_map->readFromFile(GTEST_MAP_FILE), kMapWidth * kMapHeight);
}

TEST_F(MapTest, ReadFromStream) {
    vector<char> v;
    stringstream stream;

    const char field[] =
        "s         "
        "          "
        "          "
        "          "
        "          "
        "          "
        "          "
        "          "
        "          "
        "         e"
    ;
    uint32_t ten = 10;
    stream.write((const char*)&ten, sizeof(uint32_t));
    stream.write((const char*)&ten, sizeof(uint32_t));
    stream.write(field, sizeof(field) - 1);

    ASSERT_EQ(sizeof(field), 101);
    ASSERT_EQ(m_map->readFromStream(stream), 100);
}

