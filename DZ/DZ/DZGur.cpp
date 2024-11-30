#include <iostream>
#include <vector>
#include <queue>
#include <climits>

// Вспомогательная функция для выполнения BFS
bool findAugmentingPath(const std::vector<std::vector<int>>& residualGraph, int source, int sink, std::vector<int>& parent) {
    int n = residualGraph.size();
    parent.assign(n, -1); // Сбрасываем родительский массив
    std::queue<int> queue;
    queue.push(source);

    while (!queue.empty()) {
        int current = queue.front();
        queue.pop();

        for (int next = 0; next < n; ++next) {
            // Если есть пропускная способность и вершина не посещена
            if (residualGraph[current][next] > 0 && parent[next] == -1 && next != source) {
                parent[next] = current; // Сохраняем текущую вершину как родительскую
                if (next == sink) return true; // Если дошли до стока
                queue.push(next); // Продолжаем исследование
            }
        }
    }
    return false; // Пути нет
}

// Реализация алгоритма Эдмондса-Карпа
int GuryevEdmondsKarp(const std::vector<std::vector<int>>& graph, int source, int sink) {
    int n = graph.size();
    std::vector<std::vector<int>> residualGraph(graph); // Создаем остаточную сеть
    std::vector<int> parent(n); // Для хранения пути
    int maxFlow = 0;

    // Повторяем поиск увеличивающих путей
    while (findAugmentingPath(residualGraph, source, sink, parent)) {
        // Вычисляем минимальную пропускную способность на найденном пути
        int flow = INT_MAX;
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            flow = std::min(flow, residualGraph[u][v]);
        }

        // Обновляем остаточную сеть
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            residualGraph[u][v] -= flow;
            residualGraph[v][u] += flow;
        }

        // Увеличиваем общий поток
        maxFlow += flow;
    }

    return maxFlow;
}
