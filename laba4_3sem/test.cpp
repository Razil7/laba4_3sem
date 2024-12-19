#include "test.h"
#include <iostream>
#include <cassert>
#include "DirectedGraph.h"

void testAddEdge() {
    DirectedGraph<int> graph(3);
    graph.addEdge(0, 1);
    graph.addEdge(1, 2);
    assert(graph.get_adj()[0].get_colElm() == 1);
    assert(graph.get_adj()[0].get(0) == 1);
    assert(graph.get_adj()[1].get_colElm() == 1);
    assert(graph.get_adj()[1].get(0) == 2);

    std::cout << "testAddEdge passed!" << std::endl;
}

void testShortestPath() {
    DirectedGraph<int> graph(5);
    graph.addEdge(0, 1);
    graph.addEdge(1, 2);
    graph.addEdge(0, 3);
    graph.addEdge(3, 4);
    graph.addEdge(4, 2);

    Dynamic_Array<int> distances = graph.shortestPath(0, 2);
    assert(distances[2] == 2); 

    distances = graph.shortestPath(0, 4);
    assert(distances[4] == 2); 

    std::cout << "testShortestPath passed!" << std::endl;
}

void testStronglyConnectedComponents() {
    DirectedGraph<int> graph(5);
    graph.addEdge(0, 1);
    graph.addEdge(1, 2);
    graph.addEdge(2, 0);
    graph.addEdge(3, 4);

    Dynamic_Array<Dynamic_Array<int>> scc = graph.stronglyConnectedComponents();

    assert(scc.get_colElm() == 3);
    assert(scc[0].get_colElm() == 1); 
    assert(scc[1].get_colElm() == 1); 
    assert(scc[2].get_colElm() == 3);
    assert(scc[0][0] == 3);
    assert(scc[1][0] == 4);
    assert(scc[2][0] == 0);
    assert(scc[2][1] == 2);
    assert(scc[2][2] == 1);

    std::cout << "testStronglyConnectedComponents passed!" << std::endl;
}

