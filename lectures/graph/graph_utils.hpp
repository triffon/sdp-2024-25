#ifndef GRAPH_UTILS_HPP
#define GRAPH_UTILS_HPP

template <typename V>
class GraphUtils {
    using G = Graph<V>;
    using VS = typename G::VertexSet;
public:
    static VS childless(G const& g) {
        VS result;
        for(typename G::VertexSuccessors const& vs : g)
            if (vs.value.empty())
                result.insert(vs.key);
        return result;
    }
};

#endif // GRAPH_UTILS_HPP