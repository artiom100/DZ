#include <chrono>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
#include <iostream>

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
            if (!visited[v] && residualGraph[u][v] > 0) {
                stack.push_back(v);
                parent[v] = u;
                visited[v] = true;
                if (v == sink) return true;
            }
        }
    }
    return false;
}

// Алгоритм Гольдберга для поиска максимального потока
int VyunovGoldberg(const std::vector<std::vector<int>>& graph, int source, int sink) {
    int n = graph.size();
    // Инициализация остаточной сети
    std::vector<std::vector<int>> residualGraph(n, std::vector<int>(n, 0));
    for (int u = 0; u < n; ++u) {
        for (int v = 0; v < n; ++v) {
            residualGraph[u][v] = graph[u][v];
        }
    }

    std::vector<int> height(n, 0);    // Высота каждой вершины
    std::vector<int> excess(n, 0);    // Избыток потока в каждой вершине
    std::queue<int> q;                 // Очередь активных вершин

    height[source] = n;                // Высота источника устанавливается равной количеству вершин
    // Инициализация предпотока: проталкиваем максимально возможный поток из источника
    for (int v = 0; v < n; ++v) {
        if (residualGraph[source][v] > 0) {
            excess[source] -= residualGraph[source][v];
            excess[v] += residualGraph[source][v];
            residualGraph[v][source] += residualGraph[source][v];
            residualGraph[source][v] = 0;
            if (v != sink && v != source && excess[v] > 0) {
                q.push(v);
            }
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();


        while (excess[u] > 0) {
            bool pushed = false;
            // Попытка протолкнуть поток через все смежные вершины
            for (int v = 0; v < n; ++v) {
                if (residualGraph[u][v] > 0 && height[u] > height[v]) {
                    int delta = std::min(excess[u], residualGraph[u][v]);
                    residualGraph[u][v] -= delta;
                    residualGraph[v][u] += delta;
                    excess[u] -= delta;
                    excess[v] += delta;
                    if (v != sink && v != source && excess[v] == delta) {
                        q.push(v);
                    }
                    pushed = true;
                    if (excess[u] == 0) {
                        break;
                    }
                }
            }
            if (!pushed) {
                // Если не удалось протолкнуть поток, переоцениваем высоту
                int minHeight = INT32_MAX;
                for (int v = 0; v < n; ++v) {
                    if (residualGraph[u][v] > 0) {
                        minHeight = std::min(minHeight, height[v]);
                    }
                }
                if (minHeight < INT32_MAX) {
                    height[u] = minHeight + 1;
                }
                else {
                    // Нет доступных вершин для проталкивания, выходим
                    break;
                }
            }
        }
    }

    // Суммируем поток, пришедший в сток
    int maxFlow = 0;
    for (int u = 0; u < n; ++u) {
        maxFlow += residualGraph[u][sink];
    }

    return maxFlow;
}