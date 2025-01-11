#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <stdexcept>
#include "hash_table.hpp"
#include "set.hpp"

template <typename V>
class Graph : HashTable<V, Set<V, HashTable>> {
public:
    using VertexSet = Set<V, HashTable>;
    using VertexSuccessors = KeyValuePair<V, VertexSet>;
private:
    using D = HashTable<V, VertexSet>;

    VertexSet& successors(V const& v) {
        return D::lookup(v);
    }
public:
    using Iterator = typename D::Iterator;
    using D::empty;
    using D::begin;
    using D::end;

    VertexSet const& successors(V const& v) const {
        return D::lookup(v);
    }

    bool isEdge(V const& u, V const& v) const {
        return D::contains(u) && D::contains(v) && successors(u).contains(v);
    }

    bool addVertex(V const& v) {
        return D::add(v, VertexSet());
    }

    bool removeVertex(V const& v) {
        if (!this->remove(v)) return false;

        for (HashTableIterator it = begin(); it != end(); ++it) {
            (*it).value.remove(v);
        }
        return true;
    }

    bool addEdge(V const& u, V const& v) {
        return D::contains(u) && D::contains(v) && successors(u).insert(v);
    }

    bool removeEdge(V const& u, V const& v) {
        return D::contains(u) && D::contains(v) && successors(u).remove(v);
    }

    void printDOT(std::ostream& os = std::cout) const {
        os << "digraph Graph {" << std::endl;
        for(VertexSuccessors const& vss : *this) {
            V const& u = vss.key;
            for(V const& v : vss.value)
                os << '"' << u << "\" -> \"" << v << '"' << std::endl;
        }
        os << "}" << std::endl;
    }

};

#endif // GRAPH_HPP