#include <chrono>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
#include <iostream>
#include "Goldberg.h"

using namespace std;

bool dfs1(const vector<vector<int>>& residualGraph, int source, int sink, vector<int>& parent) {
    int n = residualGraph.size();
    vector<bool> visited(n, false);
    vector<int> stack;
    stack.push_back(source);
    visited[source] = true;
    parent[source] = -1;

    while (!stack.empty()) {
        int u = stack.back();
        stack.pop_back();

        for (int v = 0; v < n; ++v) {
            // Если есть остаточная пропускная способность и вершина не посещена
            if (!visited[v] && residualGraph[u][v] > 0) {
                stack.push_back(v);
                parent[v] = u;
                visited[v] = true;
                // Если достигли стока, путь найден
                if (v == sink) return true;
            }
        }
    }
    return false;
}

// Алгоритм Гольдберга для поиска максимального потока
int VyunovGoldberg(vector<vector<int>>& graph, int source, int sink) {
    // Инициализация
    int flow = 0;
    vector<bool> visited(graph.size(), false);
    while (true) {
        // Поиск пути от источника к стоку
        vector<int> path;
        if (!dfs1(graph, source, sink, path)) break;

        // Нахождение максимального потока вдоль пути
        int curr = sink;
        int max_flow = INT_MAX;
        while (curr != source) {
            int prev = path[path.size() - 1];
            max_flow = min(max_flow, graph[prev][curr]);
            curr = prev;
        }

        // Релаксация вершин вдоль пути
        curr = sink;
        for (int i = 0; i < path.size(); ++i) {
            if (graph[path[i]][curr] > 0) {
                graph[path[i]][curr] -= max_flow;
                graph[curr][path[i]] += max_flow;
            }
            curr = path[i];
        }
        flow += max_flow;
    }
    return flow;
}

