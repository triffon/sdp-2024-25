#include "doctest.h"

#include <fstream>
#include "graph.hpp"
#include "graph_utils.hpp"

#define STRATEGIES DFS<int>, BFS<int>

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
    std::ofstream dotFile("testGraph.dot");
    g.printDOT(dotFile);
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

bool isPath(Graph<int> const& g, Path<int> const& path) {
    if (path.empty())
        return false;
    Path<int>::Iterator it = path.begin();
    while(it.next() && g.isEdge(*it, *it.next()))
        ++it;
    return !it.next();
}

TEST_CASE_TEMPLATE("Има път от 1 до всеки друг връх в тестовия граф", Strategy, STRATEGIES) {
    Graph<int> g = testGraph();
    for(int i = 2; i <= 6; i++)
        CHECK(isPath(g, Strategy::findPath(g, 1, i)));
}

TEST_CASE_TEMPLATE("Има път от 1 до всеки друг връх в тестовия граф", Strategy, STRATEGIES) {
    Graph<int> g = testGraph();
    for(int i = 2; i <= 6; i++)
        CHECK(isPath(g, Strategy::findPath(g, 1, i)));
}

TEST_CASE_TEMPLATE("Няма път до 1 от всеки друг връх в тестовия граф", Strategy, STRATEGIES) {
    Graph<int> g = testGraph();
    for(int i = 2; i <= 6; i++)
        CHECK(!isPath(g, Strategy::findPath(g, i, 1)));
}

TEST_CASE_TEMPLATE("Няма път от 4 до всеки друг връх в тестовия граф", Strategy, STRATEGIES) {
    Graph<int> g = testGraph();
    for(int i = 1; i <= 6; i++)
        if (i != 4)
            CHECK(!isPath(g, Strategy::findPath(g, 4, i)));
}

TEST_CASE_TEMPLATE("Намираме всички ациклични пътища, започващи от 1 в тестовия граф", Strategy, STRATEGIES) {
    Graph<int> g = testGraph();
    LinkedList<Path<int>> paths = Strategy::findPathsFrom(g, 1);
    int count = 0;
    for(Path<int> const& path : paths) {
        CHECK(isPath(g, path));
        count++;
    }
    CHECK_EQ(count, 14);
}

TEST_CASE_TEMPLATE("Коректно намираме покриващо дърво на тестовия граф", Strategy, STRATEGIES) {
    Graph<int> g = testGraph();
    // правим графа силно свързан
    g.addEdge(4, 1);
    Graph<int> spanningTree = Strategy::spanningTree(g);
    int root = -1;
    CHECK(GraphUtils<int>::findSource(spanningTree, root));
    int countVertices = 0;
    int countEdges = 0;
    for(Graph<int>::VertexSuccessors const& vss : spanningTree) {
        countVertices++;
        for(int v : vss.value)
            countEdges++;
    }
    CHECK_EQ(countVertices, 6);
    CHECK_EQ(countEdges, 5);
    std::ofstream dotFile("spanningTree.dot");
    spanningTree.printDOT(dotFile);
    for(int i = 1; i <= 6; i++)
        CHECK(isPath(spanningTree, Strategy::findPath(spanningTree, root, i)));
}

TEST_CASE("Пресмятаме правилно входящите степени на тестовия граф") {
    Graph<int> g = testGraph();
    HashTable<int, int> inDegrees = GraphUtils<int>::findIncomingDegrees(g);
    CHECK_EQ(inDegrees.lookup(1), 0);
    CHECK_EQ(inDegrees.lookup(2), 3);
    CHECK_EQ(inDegrees.lookup(3), 2);
    CHECK_EQ(inDegrees.lookup(4), 2);
    CHECK_EQ(inDegrees.lookup(5), 1);
    CHECK_EQ(inDegrees.lookup(6), 1);
}

TEST_CASE_TEMPLATE("Проверяваме, че topologicalSort подрежда всеки ръб u->v с u преди v в testGraph", Strategy, BFS<int>) {
    Graph<int> g = testGraph();
    // правим графа ацикличен
    g.removeEdge(2, 3);
    LinkedList<int> sorted = Strategy::topologicalSort(g);

    // Създаваме речник, пазещ индексите на всеки връх в сортирането
    HashTable<int, int> indices;
    int pos = 0;
    for(int v : sorted)
        indices.add(v, pos++);
    
    CHECK_EQ(pos, 6);

    // За всяко ребро проверяваме дали индекс(u) < индекс(v)
    for(auto const& vs : g) {
        for(int succ : vs.value) {
            CHECK(indices.lookup(vs.key) < indices.lookup(succ));
        }
    }
}

TEST_CASE_TEMPLATE("Проверяваме topologicalSort върху малък ацикличен граф", Strategy, BFS<int>) {
    Graph<int> g;
    for(int i = 1; i <= 4; i++)
        g.addVertex(i);
    // Правим граф 1 -> 2 -> 3 -> 4
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(3, 4);

    LinkedList<int> sorted = Strategy::topologicalSort(g);

    HashTable<int, int> indices;
    int pos = 0;
    for(int v : sorted)
        indices.add(v, pos++);
    
    CHECK_EQ(pos, 4);

    // Проверяваме реда
    CHECK(indices.lookup(1) < indices.lookup(2));
    CHECK(indices.lookup(2) < indices.lookup(3));
    CHECK(indices.lookup(3) < indices.lookup(4));
}
