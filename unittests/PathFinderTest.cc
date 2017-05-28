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

class PFTest : public ::testing::TestWithParam<PathFinderFactory::PathFinderType> {
protected:
    virtual void SetUp() override { }
    virtual void TearDown() override { }
};

INSTANTIATE_TEST_CASE_P(PathFinderType,
                        PFTest,
                        ::testing::Values(PathFinderFactory::AStar, PathFinderFactory::Dijkstra));

namespace {
shared_ptr<Map> MapFromString(index_t width, index_t height, const string& s) {
    stringstream ss;

    ss.write((const char*)&width, sizeof(width));
    ss.write((const char*)&height, sizeof(height));
    ss.write(s.data(), s.length());

    shared_ptr<Map> map = make_shared<Map>();
    index_t cell_count = map->readFromStream(ss);
    EXPECT_NE(kInvalidIndex, cell_count);

    return map;
}
}

TEST_P(PFTest, SolvedMapWeight) {

    PathFinderFactory f;
    f.setType(GetParam());

    shared_ptr<Map> map = MapFromString(10, 10, kTestField);
    unique_ptr<IPathFinder> pf = f.create(map);
    unique_ptr<Path> path { pf->solve() };

    EXPECT_EQ(path->weight(), 18);
}

TEST_P(PFTest, UnreachableDestination) {
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

    shared_ptr<Map> map = MapFromString(10, 10, kLocalTestField);

    PathFinderFactory f;
    f.setType(GetParam());

    unique_ptr<IPathFinder> pf = f.create(map);
    ASSERT_THROW(pf->solve(), DestinationUnreachableException);
}

TEST_P(PFTest, DoubleWallsAreStillUnreachable) {
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

    shared_ptr<Map> map = MapFromString(10, 10, kLocalTestField);

    PathFinderFactory f;
    f.setType(GetParam());

    unique_ptr<IPathFinder> pf = f.create(map);
    ASSERT_THROW(pf->solve(), DestinationUnreachableException);
}

