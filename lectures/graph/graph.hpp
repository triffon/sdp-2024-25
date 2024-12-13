#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <stdexcept>
#include "hash_table.hpp"
#include "set.hpp"

template <typename V>
class Graph : HashTable<V, Set<V, HashTable>> {
public:
    using SuccessorSet = Set<V, HashTable>;
    using VS = KeyValuePair<V, SuccessorSet>;
private:
    using D = HashTable<V, SuccessorSet>;

    SuccessorSet& successors(V const& v) {
        return D::lookup(v);
    }
public:
    using Iterator = typename D::Iterator;
    using D::empty;
    using D::begin;
    using D::end;

    SuccessorSet const& successors(V const& v) const {
        return D::lookup(v);
    }

    bool isEdge(V const& u, V const& v) const {
        return successors(u).contains(v);
    }

    bool addVertex(V const& v) {
        return D::add(v, SuccessorSet());
    }

    bool removeVertex(V const& v) {
        throw std::runtime_error("За домашно");
    }

    bool addEdge(V const& u, V const& v) {
        return successors(u).insert(v);
    }

    bool removeEdge(V const& u, V const& v) {
        return successors(u).remove(v);
    }
};

#endif // GRAPH_HPP