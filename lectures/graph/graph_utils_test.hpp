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

TEST_CASE("В тестовия граф родителите на 3 са 1 и 2") {
    Graph<int> g = testGraph();
    Graph<int>::VertexSet result = GraphUtils<int>::parents(g, 3);
    CHECK(result.contains(1));
    CHECK(result.contains(2));
    for(int v : result)
        CHECK((v == 1 || v == 2));
}

TEST_CASE("В пълен граф родителите на всеки връх са всички останали върхове") {
    Graph<int> g;
    for(int i = 0; i < 10; i++)
        g.addVertex(i);
    for(int i = 0; i < 10; i++)
        for(int j = 0; j < 10; j++)
            if (i != j)
                g.addEdge(i, j);
    for(int i = 0; i < 10; i++) {
        Graph<int>::VertexSet result = GraphUtils<int>::parents(g, i);
        for(int j = 0; j < 10; j++)
            if (i != j)
                CHECK(result.contains(j));
    }
}

TEST_CASE("Пълният и празният граф са симетрични") {
    Graph<int> g;
    CHECK(GraphUtils<int>::isSymmetric(g));
    for(int i = 0; i < 10; i++)
        g.addVertex(i);
    CHECK(GraphUtils<int>::isSymmetric(g));
    for(int i = 0; i < 10; i++)
        for(int j = 0; j < 10; j++)
            g.addEdge(i, j);
    CHECK(GraphUtils<int>::isSymmetric(g));
}

TEST_CASE("Тестовият граф не е симетричен, но след добавяне на обратните ребра става симетричен") {
    Graph<int> g = testGraph();
    CHECK(!GraphUtils<int>::isSymmetric(g));
    g.addEdge(2, 1);
    g.addEdge(3, 2);
    g.addEdge(3, 1);
    g.addEdge(4, 3);
    g.addEdge(5, 3);
    g.addEdge(4, 5);
    g.addEdge(6, 5);
    g.addEdge(2, 5);
    g.addEdge(2, 6);
    CHECK(GraphUtils<int>::isSymmetric(g));
}