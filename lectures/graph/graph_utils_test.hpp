#include "doctest.h"

#include "graph.hpp"
#include "graph_utils.hpp"

Graph<int> testGraph() {
    Graph<int> g;
    for(int i = 1; i <= 6; i++)
        g.addVertex(i);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(1, 3);
    g.addEdge(3, 4);
    g.addEdge(3, 5);
    g.addEdge(5, 4);
    g.addEdge(5, 6);
    g.addEdge(5, 2);
    g.addEdge(6, 2);
    return g;
}

TEST_CASE("В празен граф от 10 върха всички върхове са без деца") {
    Graph<int> g;
    for(int i = 0; i < 10; i++)
        g.addVertex(i);
    Graph<int>::VertexSet result = GraphUtils<int>::childless(g);
    for(int i = 0; i < 10; i++)
        CHECK(result.contains(i));
}

TEST_CASE("В пълен граф от 10 върха няма върхове без деца") {
    Graph<int> g;
    for(int i = 0; i < 10; i++)
        g.addVertex(i);
    for(int i = 0; i < 10; i++)
        for(int j = 0; j < 10; j++)
            g.addEdge(i, j);
    Graph<int>::VertexSet result = GraphUtils<int>::childless(g);
    CHECK(result.empty());
}

TEST_CASE("В тестовия граф единственият връх без деца е 4") {
    Graph<int> g = testGraph();
    Graph<int>::VertexSet result = GraphUtils<int>::childless(g);
    for(int v : result)
        CHECK_EQ(v, 4);
    CHECK(result.contains(4));
}