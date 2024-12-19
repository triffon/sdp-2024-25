#include "doctest.h"

#include "graph.hpp"

TEST_CASE("Създаване на празен граф") {
    Graph<int> g;
    CHECK(g.empty());
}

TEST_CASE("Създаване на празен граф с 10 върха") {
    Graph<int> g;
    for(int i = 0; i < 10; i++)
        g.addVertex(i);
    CHECK(!g.empty());
    for(int i = 0; i < 10; i++)
        for(int j = 0; j < 10; j++)
            CHECK(!g.isEdge(i, j));
}

TEST_CASE("Опит за повторно добавяне на връх се проваля") {
    Graph<int> g;
    CHECK(g.addVertex(1));
    CHECK(!g.addVertex(1));
}

TEST_CASE("Опит за повторно добавяне на ребро се проваля") {
    Graph<int> g;
    g.addVertex(1);
    g.addVertex(2);
    CHECK(g.addEdge(1, 2));
    CHECK(!g.addEdge(1, 2));
}

TEST_CASE("Опит за добавяне на ребро към несъществуващ връх се проваля") {
    Graph<int> g;
    g.addVertex(1);
    CHECK(!g.addEdge(1, 2));
}

TEST_CASE("Създаване на пълен граф с 10 върха") {
    Graph<int> g;
    for(int i = 0; i < 10; i++)
        g.addVertex(i);
    for(int i = 0; i < 10; i++)
        for(int j = 0; j < 10; j++)
            g.addEdge(i, j);
    CHECK(!g.empty());
    for(int i = 0; i < 10; i++)
        for(int j = 0; j < 10; j++)
            CHECK(g.isEdge(i, j));
    int su = 0;
    for(Graph<int>::VertexSuccessors const& vs : g) {
        int const& u = vs.key;
        su += u;
        Graph<int>::VertexSet const& succs = vs.value;
        int s = 0;
        for(int v : succs)
            s += v;
        CHECK_EQ(s, 45);
    }
    CHECK_EQ(su, 45);
}