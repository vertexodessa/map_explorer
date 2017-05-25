#include "Logging.h"
#include "Map.h"

#include "gtest/gtest.h"

#include <utility>

using namespace std;
using namespace map_solver;

class MapTest : public ::testing::Test {
protected:
    virtual void SetUp() override {
        Logging::initLogging();
        m_map = make_unique<Map>();
    }
    virtual void TearDown() override {  }
    std::unique_ptr<Map> m_map;
};

TEST_F(MapTest, InitialWidthHeight)
{
    ASSERT_EQ(m_map->width(), -1);
    ASSERT_EQ(m_map->height(), -1);
}

TEST_F(MapTest, ExpectedWidthHeight)
{
    // setup Map from filename
    m_map->readFromFile(GTEST_MAP_FILE);

    // test width and height
    ASSERT_EQ(m_map->width(), 10);
    ASSERT_EQ(m_map->height(), 10);
}




