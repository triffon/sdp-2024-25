#ifndef GRAPH_UTILS_HPP
#define GRAPH_UTILS_HPP

template <typename V>
class GraphUtils {
    using G = Graph<V>;
    using VS = typename G::VertexSet;
    using VSS = typename G::VertexSuccessors;
public:
    static VS childless(G const& g) {
        VS result;
        for(VSS const& vs : g)
            if (vs.value.empty())
                result.insert(vs.key);
        return result;
    }

    static VS parents(G const& g, V const& v) {
        VS result;
        for(VSS const& vs : g)
            if (vs.value.contains(v))
                result.insert(vs.key);
        return result;
    }
};

#endif // GRAPH_UTILS_HPP