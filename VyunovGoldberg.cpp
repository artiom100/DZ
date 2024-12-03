#include <chrono>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
#include <iostream>

// �������� ���������� ��� ������ ������������� ������
int VyunovGoldberg(const std::vector<std::vector<int>>& graph, int source, int sink) {
    int n = graph.size();
    // ������������� ���������� ����
    std::vector<std::vector<int>> residualGraph(n, std::vector<int>(n, 0));
    for (int u = 0; u < n; ++u) {
        for (int v = 0; v < n; ++v) {
            residualGraph[u][v] = graph[u][v];
        }
    }

    std::vector<int> height(n, 0);    // ������ ������ �������
    std::vector<int> excess(n, 0);    // ������� ������ � ������ �������
    std::queue<int> q;                 // ������� �������� ������

    height[source] = n;                // ������ ��������� ��������������� ������ ���������� ������
    // ������������� ����������: ������������ ����������� ��������� ����� �� ���������
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
            // ������� ����������� ����� ����� ��� ������� �������
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
                // ���� �� ������� ����������� �����, ������������� ������
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
                    // ��� ��������� ������ ��� �������������, �������
                    break;
                }
            }
        }
    }

    // ��������� �����, ��������� � ����
    int maxFlow = 0;
    for (int u = 0; u < n; ++u) {
        maxFlow += residualGraph[u][sink];
    }

    return maxFlow;
}