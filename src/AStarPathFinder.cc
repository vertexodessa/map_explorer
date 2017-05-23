#include "AStarPathFinder.h"
#include "Logging.h"
#include "Map.h"
#include "Path.h"
#include "utils/Types.h"
#include "utils/AdjacentCellIterator.h"

#include <boost/graph/astar_search.hpp>
#include <boost/graph/adjacency_list.hpp>

using namespace boost;
using namespace std;

typedef int32_t cost;

template <class Graph, class CostType, class LocMap>
class distance_heuristic : public astar_heuristic<Graph, CostType>
{
public:
    typedef typename graph_traits<Graph>::vertex_descriptor Vertex;
    distance_heuristic(LocMap l, Vertex goal)
        : m_location(l), m_goal(goal) {}
    CostType operator()(Vertex u)
    {
        CostType dx = m_location[m_goal].x() - m_location[u].x();
        CostType dy = m_location[m_goal].y() - m_location[u].y();
        return dx + dy;
    }
private:
    LocMap& m_location;
    Vertex m_goal;
};


struct found_goal {}; // exception for termination

// visitor that terminates when we find the goal
template <class Vertex>
class throwing_astar_visitor : public boost::default_astar_visitor
{
public:
    throwing_astar_visitor(Vertex goal) : m_goal(goal) {}
    template <class Graph>
    void examine_vertex(Vertex u, Graph& g) throw(found_goal) {
        LOG_TRACE << "Examining vertex: " << u;
        if(u == m_goal)
            throw found_goal();
    }
private:
    Vertex m_goal;
};


namespace map_solver {

AStarPathFinder::AStarPathFinder(std::shared_ptr<Map> mmap)
    : IPathFinder(mmap) {

}

unique_ptr<Path> AStarPathFinder::solve() {
    // specify some types
    typedef adjacency_list<vecS, vecS, directedS, no_property,
                           property<edge_weight_t, cost> > mygraph_t;
    typedef property_map<mygraph_t, edge_weight_t>::type WeightMap;
    typedef mygraph_t::vertex_descriptor vertex;
    typedef mygraph_t::edge_descriptor edge_descriptor;
    // typedef mygraph_t::vertex_iterator vertex_iterator;
    // typedef std::pair<int, int> edge;

    int32_t start_idx, finish_idx;
    start_idx = m_map->start();
    finish_idx = m_map->finish();

    if (-1 == start_idx || -1 == finish_idx) {
        LOG_FATAL << "The map is not correct. Cannot find a start or finish cell.";
        return nullptr;
    }

    // graph: directed, vector for storing vecs and edges
    // create graph
    const int num_nodes = m_map->width() * m_map->height();
    mygraph_t g(num_nodes);
    // fill edges' weights
    WeightMap weightmap = get(edge_weight, g);
    LOG_TRACE << "num_nodes: " << num_nodes;
    for (int i=0; i < num_nodes; ++i) {
        auto& current_cell = i;
        auto cell_weight = m_map->weight(current_cell);
        LOG_TRACE << "node " << current_cell << " weight: " << cell_weight;

        AdjacentCells<int32_t> adjacent_indexes(m_map->width(), m_map->height(), i);

        for_each(adjacent_indexes.begin(), adjacent_indexes.end(), [&](int adjacent_index) {
                edge_descriptor e; bool inserted;
                tie(e, inserted) = add_edge(current_cell, adjacent_index, g);
                LOG_TRACE << "e, inserted: " << e << ", " << inserted;
                weightmap[e] = cell_weight;
            });
    }

    // pick start/finish
    vertex start = start_idx;
    vertex finish = finish_idx;

    // run astar
    vector<mygraph_t::vertex_descriptor> p(num_vertices(g));
    vector<cost> d(num_vertices(g));
    list<vertex> shortest_path;
    try {
        // call astar named parameter interface
        astar_search
            (g, start,
             distance_heuristic<mygraph_t, cost, Map>
             (*m_map, finish),
             predecessor_map(&p[0]).distance_map(&d[0]).
             visitor(throwing_astar_visitor<vertex>(finish)));

    } catch(found_goal fg) { // found a path to the goal
        for(vertex v = finish;; v = p[v]) {
            shortest_path.push_front(v);
            if(p[v] == v)
                break;
        }
        LOG_TRACE << "Shortest path from " << start << " to "
             << finish << ": ";
        list<vertex>::iterator spi = shortest_path.begin();
        LOG_TRACE << start;
        for(++spi; spi != shortest_path.end(); ++spi)
            LOG_TRACE  << *std::prev(spi) << " -> " << *spi;
        LOG_TRACE << '\n' << "Total travel time: " << d[finish] << '\n';

        auto ret = make_unique<Path>(m_map->width(), m_map->height());
        for (auto&& i : shortest_path)
            ret->markCell(i);
        return ret;
    }

    LOG_WARN << "Didn't find a path from " << start << " to "
             << finish << "!" << '\n';

    return nullptr;
}

} //namespace map_solver
