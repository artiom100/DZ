#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

bool dfs(const vector<vector<int>>& residualGraph, int source, int sink, vector<int>& parent) {
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

// Алгоритм Форда-Фалкерсона для поиска максимального потока
int SerkovaFordFulkerson(const vector<vector<int>>& graph, int source, int sink) {
    int n = graph.size();
    vector<vector<int>> residualGraph = graph; // Остаточная сеть
    vector<int> parent(n);                      // Массив для хранения пути
    int maxFlow = 0;

    // Пока есть путь из источника в сток
    while (dfs(residualGraph, source, sink, parent)) {
        // Находим минимальную пропускную способность на пути
        int pathFlow = INT_MAX;
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            pathFlow = min(pathFlow, residualGraph[u][v]);
        }
        // Обновляем остаточную сеть
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            residualGraph[u][v] -= pathFlow;
            residualGraph[v][u] += pathFlow;
        }
        // Добавляем поток пути к общему максимальному потоку
        maxFlow += pathFlow;
    }
    return maxFlow;
};