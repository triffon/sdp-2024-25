#ifndef GRAPH_UTILS_HPP
#define GRAPH_UTILS_HPP

#include "linked_list.hpp"

template <typename V>
using Path = LinkedList<V>;

template <typename V>
class GraphUtils {
    using G = Graph<V>;
    using VS = typename G::VertexSet;
    using VSS = typename G::VertexSuccessors;
public:
    // O(|V|)
    static VS childless(G const& g) {
        VS result;
        for(VSS const& vs : g)
            if (vs.value.empty())
                result.insert(vs.key);
        return result;
    }

    // O(|V|)
    static VS parents(G const& g, V const& v) {
        VS result;
        for(VSS const& vs : g)
            if (vs.value.contains(v))
                result.insert(vs.key);
        return result;
    }

    // O(|V| + |E|)
    static bool isSymmetric(G const& g) {
        for(VSS const& vs : g) {
            int u = vs.key;
            for(int v : vs.value)
                if (!g.isEdge(v, u))
                    return false;
        }
        return true;
    }

};

template <typename V>
class DFS {
private:
    using G = Graph<V>;
    using VS = typename G::VertexSet;
    using P = Path<V>;

    static bool findPath(G const& g, V const& u, V const& v, VS& visited, P& path) {
        // лошо дъно
        if (visited.contains(u))
            // зациклихме
            return false;

        path.insertLast(u);
        visited.insert(u);

        // хубаво дъно
        if (u == v)
            // намерихме път
            return true;

        for(V const& w : g.successors(u))
            // успешна ли е стъпката напред?
            if (findPath(g, w, v, visited, path))
                return true;

        // стъпка назад: махаме върха от пътя
        V tmp;
        path.deleteLast(tmp);

        return false;
    }

public:
    static P findPath(G const& g, V const& u, V const& v) {
        VS visited;
        P path;
        findPath(g, u, v, visited, path);
        return path;
    }

};



#endif // GRAPH_UTILS_HPP