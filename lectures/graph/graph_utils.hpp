#ifndef GRAPH_UTILS_HPP
#define GRAPH_UTILS_HPP

#include "linked_list.hpp"
#include "linked_queue.hpp"

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

    // O(|V| + |E|)
    static bool findSource(G const& g, V& source) {
        VS children;
        VS vertices;
        for(VSS const& vss : g) {
            vertices.insert(vss.key);
            for(V const& v : vss.value)
                children.insert(v);
        }
        for (V const& v : vertices)
            if (!children.contains(v)) {
                source = v;
                return true;
            }
        return false;
    }

    // O(|V| + |E|)
    static LinkedList<V> findSources(G const& g) {
        VS children;
        VS vertices;
        LinkedList<V> result;
        for(VSS const& vss : g) {
            vertices.insert(vss.key);
            for(V const& v : vss.value)
                children.insert(v);
        }
        for (V const& v : vertices)
            if (!children.contains(v))
                result.insertLast(v);

        return result;
    }

    // O(|V| + |E|)
    static HashTable<V, int> findIncomingDegrees(G const& g) {
        HashTable<V, int> result;
        // инициализираме степените с 0
        for(VSS& vss : g)
            result.add(vss.key, 0);

        for(VSS const& vss : g)
            for(V const& v : vss.value)
                result.lookup(v)++;

        return result;
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

    static void findPathsFrom(G const& g, V const& u, VS& visited, P& path, LinkedList<P>& paths) {
        // лошо дъно
        if (visited.contains(u))
            // зациклихме
            return;

        path.insertLast(u);
        visited.insert(u);

        // намерихме нов път
        paths.insertLast(path);

        for(V const& w : g.successors(u))
            // стъпка напред
            findPathsFrom(g, w, visited, path, paths);

        // стъпка назад: махаме върха от пътя
        V tmp;
        path.deleteLast(tmp);
        visited.remove(u);
    }

    static void spanningTree(G const& g, V const& u, VS& visited, G& st) {
        visited.insert(u);

        for(V const& w : g.successors(u))
            // стъпка напред
            // посетили ли сме този връх?
            if (!visited.contains(w)) {
                // добавяме го в дървото, както и реброто, по което идваме в него
                st.addVertex(w);
                st.addEdge(u, w);
                // продължаваме обхождането в дълбочина
                spanningTree(g, w, visited, st);
            }
    }


public:
    static P findPath(G const& g, V const& u, V const& v) {
        VS visited;
        P path;
        findPath(g, u, v, visited, path);
        return path;
    }

    static LinkedList<P> findPathsFrom(G const& g, V const& u) {
        VS visited;
        P path;
        LinkedList<P> paths;
        findPathsFrom(g, u, visited, path, paths);
        return paths;
    }

    // допускаме, че графът е силно свързан
    static G spanningTree(G const& g) {
        // започваме от първия (произволен) връх
        V u = (*g.begin()).key;
        VS visited;
        G st;
        st.addVertex(u);
        spanningTree(g, u, visited, st);
        return st;
    }
};


template <typename V>
class BFS {
private:
    using G = Graph<V>;
    using VS = typename G::VertexSet;
    using P = Path<V>;
public:
    static P findPath(G const& g, V const& u, V const& v) {
        using Q = LinkedQueue<V>;
        using ParentDictionary = HashTable<V, V>;

        ParentDictionary pd;
        Q queue;
        VS visited;
        P path;

        queue.enqueue(u);
        V current = u;

        while (!queue.empty() && current != v) {
            current = queue.dequeue();
            // маркираме текущия връх като посетен
            visited.insert(current);

            if (current != v)
                for(V const& w : g.successors(current))
                    if (!visited.contains(w)) {
                        // добавяме го в опашката за посещение
                        queue.enqueue(w);
                        // записваме си реброто current -> w
                        if (!pd.contains(w))
                            // за първи път обхождаме w
                            pd.add(w, current);
                    }
        }
        // q.empty() || current == v
        if (current == v) {
            // намерили сме път, сега трябва да го възстановим
            path.insertFirst(current);
            while (current != u)
                path.insertFirst(current = pd.lookup(current));
        }
        
        return path;
    }

    static LinkedList<P> findPathsFrom(G const& g, V const& u) {
        LinkedList<P> paths;
        VS visited;
        P path;

        path.insertLast(u);
        paths.insertLast(path);

        for(P const& currentPath : paths) {
            V const& current = *currentPath.last();

            for(V const& w : g.successors(current)) {
                // проверяваме дали w го няма вече в currentPath
                typename P::Iterator pathIt = currentPath.begin();
                while (pathIt && *pathIt != w)
                    ++pathIt;
                if (!pathIt) {
                    // w го няма в currentPath!
                    // слагаме го накрая на пътя
                    P newPath = currentPath;
                    newPath.insertLast(w);
                    // добавяме новия път за обхождане
                    paths.insertLast(newPath);
                }
            }
        }
        return paths;
    }

    static G spanningTree(G const& g) {
        using Q = LinkedQueue<V>;

        Q queue;
        VS visited;
        G st;

        V u = (*g.begin()).key;

        queue.enqueue(u);
        visited.insert(u);
        V current = u;
        st.addVertex(u);

        while (!queue.empty()) {
            current = queue.dequeue();

            for(V const& w : g.successors(current))
                if (!visited.contains(w)) {
                    // добавяме го в опашката за посещение
                    queue.enqueue(w);
                    // маркираме го като посетен
                    visited.insert(w);
                    // записваме си реброто current -> w
                    st.addVertex(w);
                    st.addEdge(current, w);
                }
        }
        return st;
    }

    static LinkedList<V> topologicalSort(G const& g) {
        HashTable<V, int> inDegrees = GraphUtils<int>::findIncomingDegrees(g);
        LinkedList<V> result;
        for(KeyValuePair<V, int> const& kvp : inDegrees)
            if (kvp.value == 0)
                result.insertLast(kvp.key);
        for(V const& u : result)
            for(V const& v : g.successors(u))
                if (--inDegrees.lookup(v) == 0)
                    result.insertLast(v);
        return result;
    }
};

#endif // GRAPH_UTILS_HPP