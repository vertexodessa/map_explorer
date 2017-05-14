
#include "Cell.h"
#include "Logging.h"
#include "Map.h"
#include "Utils.h"


#include <boost/filesystem.hpp>

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

inline Rect GetMapSize(string filename) {
    LOG_TRACE << __PRETTY_FUNCTION__ << " entered";

    int x,y;
    ifstream f;
    f.open(filename);

    f.read((char*)&x, 4);
    f.read((char*)&y, 4);
    return Rect(x,y);
}

inline vector<Cell> ReadCellsFromFile(string filename) {
    LOG_TRACE << __PRETTY_FUNCTION__ << " entered";
    vector<Cell> ret;

    int x,y;
    ifstream f;
    f.open(filename);

    f.read((char*)&x, 4);
    f.read((char*)&y, 4);

    char c;
    ret.reserve(x*y);

    while (true) {
        f.read(&c, 1);
        if (f.eof())
            break;
        LOG_TRACE << "read " << (int)c << " as cell number";
        ret.emplace_back(c);
    }

    return ret;
}
}

Map::Map() {
}

int Map::ReadFromFile(std::string filename) {
    LOG_TRACE << __PRETTY_FUNCTION__ << " entered";

    path p(filename);
    if (!exists(p)
         || (file_size(p) < kHeaderSize) ) {
        LOG_ERROR << "File " << filename << " does not exist";
        return -1;
    }

    int cell_count=0;
    Rect mapSize = GetMapSize(filename);

    uint32_t width, height;
    tie(width, height) = mapSize;
    cell_count = width * height;

    uintmax_t estimatedFileSize = width * height + kHeaderSize;
    LOG_TRACE << "File size of " << filename <<  " " << file_size(p) << ", estimated file size " << estimatedFileSize;
    if (file_size(p) != estimatedFileSize) {
        LOG_ERROR << "File size of " << filename <<  " (" << file_size(p) << ") does not equal to the estimated file size " << estimatedFileSize;
        return -1;
    }

    // read cells
    m_cells = ReadCellsFromFile(filename);

    if (m_cells.size() != (width * height)) {
        LOG_ERROR << "Read " << m_cells.size() << " cells, expected " << width * height << " cells";
        return -1;
    }

    return cell_count;
}

}

