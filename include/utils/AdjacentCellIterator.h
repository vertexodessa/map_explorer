#ifndef ADJACENT_CELL_ITERATOR_H
#define ADJACENT_CELL_ITERATOR_H

#include "Logging.h"

#include <vector>
#include <boost/operators.hpp>


template <typename size_type>
class AdjacentCells {
public:
    class iterator : private boost::equality_comparable<iterator> {
    public:
        static iterator& end() {
            static iterator end_(0, 0, -1);
            return end_;
        }

        iterator(size_type w, size_type h, size_type idx) :
            m_start_iter(idx),
            m_current_iter(0) {

            if (idx == -1)
                return;

            size_type x = idx % w;
            size_type y = idx / w;

            if (x > 0)
                m_ids.push_back(idx - 1);
            if (x < w-1)
                m_ids.push_back(idx + 1);
            if (y > 0)
                m_ids.push_back(idx - w);
            if (y < h-1)
                m_ids.push_back(idx + w);

            for (auto& a : m_ids) {
                LOG_TRACE << "Adjacent cells for " << idx << " (" << x << ", " << y << ")" << " is: " << a;
            }
        }

        iterator& operator ++() {
            if (m_current_iter == ((size_type)m_ids.size() - 1) || *this == end()) {
                *this = end();
                return end();
            }
            ++m_current_iter;
            return *this;
        };

        friend bool operator==(const AdjacentCells<size_type>::iterator& one, const AdjacentCells<size_type>::iterator& two) {
            return one.m_current_iter == two.m_current_iter && one.m_start_iter == two.m_start_iter;
        };

        size_type operator *() { return m_current_iter != -1 ? m_ids[m_current_iter] : -1; }
    private:
        std::vector<size_type> m_ids;
        size_type m_start_iter;
        size_type m_current_iter;
    };
    AdjacentCells(size_type w, size_type h, size_type i) : m_width(w), m_height(h), m_index(i){};
    iterator begin() {return iterator(m_width, m_height, m_index);}
    iterator end() {return iterator::end(); }
private:
    size_type m_width, m_height, m_index;
};


#endif
