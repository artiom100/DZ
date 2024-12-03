#include "ReadMatrix.h"
#include <chrono>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
#include <iostream>
#define RUN(x, y, z, data) {\
    Run(#x, x, y, z, data);\
}

using namespace std;

// Алгоритм Гольдберга для поиска максимального потока
int Goldberg(const std::vector<std::vector<int>>& graph, int source, int sink) {
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

// Шаблонная функция для запуска алгоритмов и измерения времени
template<typename Method>
void Run(const std::string& method_name, Method method, int source, int sink, std::vector<std::vector<int>>& data) {
    std::cout << "Запуск алгоритма: " << method_name << std::endl;

    auto start = std::chrono::system_clock::now();
    int result = method(data, source, sink);
    auto stop = std::chrono::system_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();

    std::cout << "Время: " << time << " мкс" << std::endl;
    std::cout << "Максимальный поток: " << result << std::endl << std::endl;
}

int main() {
    setlocale(LC_ALL, "RU");

    // Тестирование на графе-дереве с различным количеством вершин
    std::vector<int> test_sizes = { 20, 98, 150, 250 };
    for (auto size : test_sizes) {
        std::cout << "-------Тестирование на графе-дереве (" << size << " вершин)-------" << std::endl;
        GenerateAdjacencyMatrix("data1.txt", size);
        std::vector<std::vector<int>> matrix = ReadData("data1.txt");
        int source = 0;
        int sink = size - 1;
        int res;
        // Запуск алгоритма Гольдберга
        RUN(Goldberg, matrix, source, sink);

        std::cout << std::endl;
    }

    return 0;
}
