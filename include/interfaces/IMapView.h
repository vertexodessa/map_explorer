#ifndef IMAPVIEW_H
#define IMAPVIEW_H

#include <memory>

namespace map_solver {

class Map;

class IMapView {
public:
    virtual ~IMapView() = default;
    virtual void draw() const =0;
protected:
    explicit IMapView(std::shared_ptr<Map> map) : m_map(std::move(map)) { }
    std::shared_ptr<const Map> map() const {return m_map;}
private:
    std::shared_ptr<Map> m_map;
};

}

#endif
