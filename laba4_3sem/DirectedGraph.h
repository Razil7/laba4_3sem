#pragma once
#include "darr.h"
#include <iostream>
#include <stdexcept>
#include <stack>
#include <queue>


template <typename T> 
class DirectedGraph {
private:
    T numVertices;
    Dynamic_Array<Dynamic_Array<T>> adj;

    void fillOrder(T v, Dynamic_Array<bool>& visited, std::stack<T>& Stack) const {
        visited[v] = true;
        for (T i = 0; i < adj[v].get_colElm(); ++i) {
            T neighbor = adj[v][i];
            if (!visited[neighbor]) {
                fillOrder(neighbor, visited, Stack);
            }
        }
        Stack.push(v);
    }

    DirectedGraph<T> getTranspose() const {
        DirectedGraph<T> gTranspose(numVertices);
        for (T v = 0; v < numVertices; ++v) {
            for (T i = 0; i < adj[v].get_colElm(); ++i) {
                T neighbor = adj[v][i];
                gTranspose.addEdge(neighbor, v);
            }
        }
        return gTranspose;
    }

    void dfsUtil(T v, Dynamic_Array<bool>& visited, Dynamic_Array<T>& component) const {
        visited[v] = true;
        component.push_back(v);
        for (T i = 0; i < adj[v].get_colElm(); ++i) {
            T neighbor = adj[v][i];
            if (!visited[neighbor]) {
                dfsUtil(neighbor, visited, component);
            }
        }
    }

public:

    DirectedGraph(T vertices) : numVertices(vertices), adj()
    {
        for (T i = 0; i < numVertices; ++i) {
            Dynamic_Array<T> temp;
            adj.push_back(temp);
        }
    }

    Dynamic_Array<Dynamic_Array<T>> get_adj() {
        return adj;
    }

    void addEdge(T from, T to) {
        if (from >= numVertices || to >= numVertices || from < 0 || to < 0) {
            std::cerr << "Invalid vertex indices.\n";
            return;
        }
        adj[from].push_back(to);
    }

    void printGraph() const {
        for (T v = 0; v < numVertices; ++v) {
            std::cout << "Vertex " << v << ":";
            for (T i = 0; i < adj[v].get_colElm(); ++i) {
                std::cout << " -> " << adj[v].get(i);
            }
            std::cout << "\n";
        }
    }



    Dynamic_Array<T> shortestPath(T start, T end) const {
        if (start < 0 || start >= numVertices || end < 0 || end >= numVertices) {
            throw std::invalid_argument("Invalid vertex indices for pathfinding.");
        }

        Dynamic_Array<bool> visited;

        for (T i = 0; i < numVertices; ++i) {
            visited.push_back(false);
        }

        Dynamic_Array<T> distance(numVertices);
        for (T i = 0; i < numVertices; i++) {
            distance.push_back(-1);
        }
        std::queue<T> q;
        distance[start] = 0;
        visited.set(start, true);
        q.push(start);

        while (!q.empty()) {
            T u = q.front();
            q.pop();

            for (T i = 0; i < adj[u].get_colElm(); ++i) {
                T neighbor = adj[u].get(i);
                if (!visited.get(neighbor)) {
                    visited.set(neighbor, true);
                    distance[neighbor] = distance[u] + 1;
                    q.push(neighbor);
                    if (neighbor == end)
                        return distance;
                }
            }
        }
        return distance;
    }

    Dynamic_Array<Dynamic_Array<T>> stronglyConnectedComponents() const {
        std::stack<T> Stack;
        Dynamic_Array<bool> visited;

        for (T i = 0; i < numVertices; ++i) {
            visited.push_back(false);
        }


        for (T i = 0; i < numVertices; ++i)
            if (!visited.get(i))
                fillOrder(i, visited, Stack);


        DirectedGraph<T> gr = getTranspose();

        for (T i = 0; i < numVertices; ++i)
            visited.set(i, false);

        Dynamic_Array<Dynamic_Array<T>> scc;

        while (!Stack.empty()) {
            T v = Stack.top();
            Stack.pop();

            if (!visited.get(v)) {
                Dynamic_Array<T> component;
                gr.dfsUtil(v, visited, component);
                scc.push_back(component);
            }
        }
        return scc;
    }
        T getNumVertices() const {
        return numVertices;
    }
};


