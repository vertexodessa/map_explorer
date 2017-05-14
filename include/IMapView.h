#ifndef IMAPVIEW_H
#define IMAPVIEW_H

#include <memory>

namespace map_solver {

class Map;

class IMapView {
public:
    virtual ~IMapView() {}
    virtual void Draw() const =0;
protected:
    explicit IMapView(std::shared_ptr<Map> map) : m_map(map) {};
    std::shared_ptr<Map> m_map;
private:
};

}

#endif
