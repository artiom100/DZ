#include "ReadMatrix.h"
#include <chrono>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
#include "Goldberg.h"
#define RUN(x, y, z, data) {\
    Run(#x, x, y, z, data);\
}



bool bfs(const std::vector<std::vector<int>>& residualGraph, int source, int sink, std::vector<int>& parent) {
    int n = residualGraph.size();
    std::vector<bool> visited(n, false);
    std::queue<int> q;

    q.push(source);
    visited[source] = true;
    parent[source] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < n; ++v) {
            // Если есть остаточная пропускная способность и вершина не посещена
            if (!visited[v] && residualGraph[u][v] > 0) {
                q.push(v);
                parent[v] = u;
                visited[v] = true;

                // Если достигли стока, путь найден
                if (v == sink) return true;
            }
        }
    }
    return false;
}

// Алгоритм Эдмондса-Карпа для поиска максимального потока
int edmondsKarp(const std::vector<std::vector<int>>& graph, int source, int sink) {
    int n = graph.size();
    std::vector<std::vector<int>> residualGraph = graph; // Остаточная сеть
    std::vector<int> parent(n);                         // Массив для хранения пути
    int maxFlow = 0;

    // Пока есть путь из источника в сток
    while (bfs(residualGraph, source, sink, parent)) {
        // Находим минимальную пропускную способность на пути
        int pathFlow = INT_MAX;
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            pathFlow = std::min(pathFlow, residualGraph[u][v]);
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
}


template<typename Method>
void Run(const std::string& method_name, Method method, int sourse, int sink, std::vector<std::vector<int>>& data) {
    std::cout << "Запуск алгоритма: " << method_name << std::endl;

    auto start = std::chrono::system_clock::now();
    int result = method(data, sourse, sink);
    auto stop = std::chrono::system_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();

    std::cout << "Время: " << time << " mcs" << std::endl;
    std::cout << "Максимальный поток  " << result << std::endl << std::endl;
}

int main(){
    setlocale(LC_ALL, "RU");
    GenerateAdjacencyMatrix("data1.txt", 20);
	std::vector<std::vector<int>> matrix = ReadData("data1.txt");
    std::cout << "-------Тестирование на графе-дереве (20 вершины)-------";
    std::cout << "" << std::endl;
    int source = 0;
    int sink = 19;
    int res;
    /*RUN(SerkovaFordFulkerson, matrix, source, sink);*/
    /*RUN(GuryevEdmondsKarp, matrix, source, sink);*/
    /*RUN(VyunovGoldberg, matrix, source, sink);*/
    res = edmondsKarp(matrix, source, sink);
    std::cout << res << std::endl;
    std::cout << "" << std::endl;
    


    std::cout << "-------Тестирование на графе-дереве (98 вершины)-------";
    std::cout << "" << std::endl;
    GenerateAdjacencyMatrix("data1.txt", 98);
    matrix = ReadData("data1.txt");
    source = 0;
    sink = 97;
    res = edmondsKarp(matrix, source, sink);
    std::cout << res << std::endl;
    std::cout << "" << std::endl;

    std::cout << "-------Тестирование на графе-дереве (150 вершины)-------";
    std::cout << "" << std::endl;
    GenerateAdjacencyMatrix("data1.txt", 150);
    matrix = ReadData("data1.txt");
    source = 0;
    sink = 149;
    res = edmondsKarp(matrix, source, sink);
    std::cout << res << std::endl;
    std::cout << "" << std::endl;




    std::cout << "-------Тестирование на графе-дереве (250 вершины)-------";
    std::cout << "" << std::endl;
    GenerateAdjacencyMatrix("data1.txt", 250);
    matrix = ReadData("data1.txt");
    source = 0;
    sink = 249;
    res = edmondsKarp(matrix, source, sink);
    std::cout << res << std::endl;
    std::cout << "" << std::endl;


    return 0;

}



