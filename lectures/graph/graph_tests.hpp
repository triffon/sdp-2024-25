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
    for(Graph<int>::VS const& vs : g) {
        int const& u = vs.key;
        su += u;
        Graph<int>::SuccessorSet const& succs = vs.value;
        int s = 0;
        for(int v : succs)
            s += v;
        CHECK_EQ(s, 45);
    }
    CHECK_EQ(su, 45);
}