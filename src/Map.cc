#include "Cell.h"
#include "Logging.h"
#include "Map.h"
#include "utils/Constants.h"
#include "utils/Types.h"


#include <boost/filesystem.hpp>

#include <map>
#include <fstream>

using namespace boost::filesystem;
using namespace std;

/*
 * Map file format (stored in native byte order: not portable)
 * 4 bytes: map width
 * 4 bytes: map height
 * <cell_size>*<cell_count>: cells
 */

namespace map_solver {

namespace {
constexpr int kHeaderSize = 8;

inline Rect GetMapSize(istream& f) {
    LOG_TRACE << __PRETTY_FUNCTION__ << " entered";

    int x,y;
    f.clear();
    f.seekg(0);

    f.read((char*)&x, 4);
    f.read((char*)&y, 4);

    return Rect(x,y);
}

inline vector<Cell> ReadCellsFromFile(istream& f) {
    LOG_TRACE << __PRETTY_FUNCTION__ << " entered";
    vector<Cell> ret;

    int x, y;
    tie(x, y) = GetMapSize(f);

    char c;
    ret.reserve(x*y);

    int i=0;
    while (true) {
        f.read(&c, 1);
        if (f.eof())
            break;
        LOG_TRACE << "read " << (int)c << " as cell number";
        LOG_TRACE << "emplacing cell " << (int)c << " to map position x: " << i%x << ", y: " << i/y ;
        ret.emplace_back(c, i);
        ++i;
    }

    return ret;
}

int GetWeightFor(char type) {
    static map<char, weight_t> s_map = {
        {'s', 1},
        {'e', 1},
        {' ', 1},
        {'*', kWallWeight}
    };
    if (s_map.find(type) == s_map.end()) {
        LOG_ERROR << (int) type << " not found in the weight map!";
        return 1;
    }
    return s_map[type];
}

}

void Map::checkInBounds(index_t idx) const {
    if (idx > m_cells.size())
        throw OutOfBoundsException("index is larger than the current cell size");
    if (idx/m_width > m_height)
        throw OutOfBoundsException("y is larger than the current height");
    if (m_width == kNonExistentIndex)
        throw OutOfBoundsException("m_width == -1");
}

Map::Map() {
}

index_t Map::cartesianToIndex(index_t x, index_t y) const {
    // TODO: make a test
    index_t idx = x + y * m_width;
    checkInBounds(idx);

    return idx;
}

CartesianPoint Map::indexToCartesian(index_t i) const {
    checkInBounds(i);

    index_t x = i%m_width;
    index_t y = i/m_width;

    return CartesianPoint{ x, y };
}

Cell& Map::operator[](index_t idx){
    checkInBounds(idx);
    return m_cells[idx];
};

index_t Map::start() const {
    auto i = std::find_if(m_cells.cbegin(), m_cells.cend(),
                          [](const auto& c) {
                              return c.getType() == kStartCellType;
                          });
    index_t idx = i->index();
    checkInBounds(idx);
    return idx;
}

index_t Map::finish() const {
    auto i = std::find_if(m_cells.cbegin(), m_cells.cend(),
                          [](const auto& c) {
                              return c.getType() == kFinishCellType;
                          });
    index_t idx = i->index();
    checkInBounds(idx);
    return idx;
}

weight_t Map::weight(index_t idx) const {
    checkInBounds(idx);
    return GetWeightFor(m_cells[idx].getType());
}

index_t Map::readFromStream(istream& stream) {
    LOG_TRACE << __PRETTY_FUNCTION__ << " entered";

    if (stream.bad()) {
        LOG_ERROR << "istream is in incorrect state.";
        return -1;
    }

    index_t width, height;
    tie(width, height) = GetMapSize(stream);

    streampos estimatedDataSize = width * height;

    streampos fsize = stream.tellg();
    stream.seekg( 0, std::ios::end );
    fsize = stream.tellg() - fsize;

    if (fsize != estimatedDataSize) {
        LOG_ERROR << "Stream size (" << fsize << ") does not equal to the estimated file size " << estimatedDataSize;
        return -1;
    }

    // read cells
    m_cells = ReadCellsFromFile(stream);

    if (m_cells.size() != (width * height)) {
        LOG_ERROR << "Read " << m_cells.size() << " cells, expected " << width * height << " cells";
        return -1;
    }

    m_width = width;
    m_height = height;

    return m_cells.size();
}

index_t Map::readFromFile(string filename) {
    LOG_TRACE << __PRETTY_FUNCTION__ << " entered";

    path p(filename);
    if (!exists(p)
         || (file_size(p) < kHeaderSize) ) {
        LOG_ERROR << "File " << filename << " does not exist";
        return -1;
    }

    ifstream file;
    file.open(filename);

    index_t cell_count = readFromStream(file);

    return cell_count;
}

}

