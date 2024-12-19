#ifndef GRAPH_UTILS_HPP
#define GRAPH_UTILS_HPP

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

#endif // GRAPH_UTILS_HPP