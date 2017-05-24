#ifndef ADJACENT_CELL_ITERATOR_H
#define ADJACENT_CELL_ITERATOR_H

#include "Logging.h"

#include <vector>

#include <boost/iterator/iterator_facade.hpp>

template <typename size_type>
class AdjacentCells {
public:
    class iterator :
        public boost::iterator_facade < iterator,
                                        size_type,
                                        boost::single_pass_traversal_tag> {
    public:
        iterator() : m_start_iter(-1), m_current_iter(-1) { }

        iterator(size_type w, size_type h, size_type idx) :
            m_start_iter(idx),
            m_current_iter(0) {

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
    private:
        friend boost::iterator_core_access;
        bool equal(const AdjacentCells<size_type>::iterator& other) const {
            return this->m_current_iter == other.m_current_iter && this->m_start_iter == other.m_start_iter;
        }

        void increment() {
            ++m_current_iter;
            if (m_current_iter == ((size_type)m_ids.size())) {
                *this = end();
            }
        }

        size_type& dereference() const {
            return const_cast<size_type&>(m_ids[m_current_iter]);
        }

        std::vector<size_type> m_ids;
        size_type m_start_iter;
        size_type m_current_iter;
    };

    AdjacentCells(size_type w, size_type h, size_type i) : m_width(w), m_height(h), m_index(i){};
    iterator begin() {return iterator(m_width, m_height, m_index);}
    static iterator& end() {
        static iterator s_end;
        return s_end;
    }

private:
    size_type m_width, m_height, m_index;
};


#endif
