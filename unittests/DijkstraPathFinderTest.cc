#include "DijkstraPathFinder.h"
#include "Map.h"
#include "Path.h"
#include "factories/PathFinderFactory.h"

#include <gtest/gtest.h>

#include <sstream>
#include <memory>
#include <utility>

using namespace std;
using namespace map_solver;

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

class DijkstraPFTest : public ::testing::Test {
protected:
    virtual void SetUp() override { }
    virtual void TearDown() override { }
};

TEST_F(DijkstraPFTest, SolvedMapWeight) {
    stringstream ss;
    uint32_t ten = 10;
    ss.write((const char*)&ten, sizeof(ten));
    ss.write((const char*)&ten, sizeof(ten));
    ss.write(kTestField, sizeof(kTestField) - 1);

    shared_ptr<Map> map = make_shared<Map>();
    ASSERT_NE(kInvalidIndex, map->readFromStream(ss));

    PathFinderFactory f;
    f.setType(PathFinderFactory::Dijkstra);

    unique_ptr<IPathFinder> pf = f.create(map);
    unique_ptr<Path> path { pf->solve() };

    EXPECT_EQ(path->weight(), 18);
}

TEST_F(DijkstraPFTest, UnreachableDestination) {
    const char kLocalTestField[] =
        "s*        "
        "**        "
        "          "
        "          "
        "          "
        "          "
        "          "
        "          "
        "          "
        "        *e";

    stringstream ss;
    uint32_t ten = 10;
    ss.write((const char*)&ten, sizeof(ten));
    ss.write((const char*)&ten, sizeof(ten));
    ss.write(kLocalTestField, sizeof(kLocalTestField) - 1);

    shared_ptr<Map> map = make_shared<Map>();
    ASSERT_NE(kInvalidIndex, map->readFromStream(ss));

    PathFinderFactory f;
    f.setType(PathFinderFactory::Dijkstra);

    unique_ptr<IPathFinder> pf = f.create(map);
    ASSERT_THROW(pf->solve(), DestinationUnreachableException);
}

TEST_F(DijkstraPFTest, DoubleWallsAreStillUnreachable) {
    const char kLocalTestField[] =
        "s*        "
        "**        "
        "**********"
        "          "
        "          "
        "          "
        "          "
        "          "
        "          "
        "        *e";

    stringstream ss;
    uint32_t ten = 10;
    ss.write((const char*)&ten, sizeof(ten));
    ss.write((const char*)&ten, sizeof(ten));
    ss.write(kLocalTestField, sizeof(kLocalTestField) - 1);

    shared_ptr<Map> map = make_shared<Map>();
    ASSERT_NE(kInvalidIndex, map->readFromStream(ss));

    PathFinderFactory f;
    f.setType(PathFinderFactory::Dijkstra);

    unique_ptr<IPathFinder> pf = f.create(map);
    ASSERT_THROW(pf->solve(), DestinationUnreachableException);
}

