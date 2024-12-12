#include <iostream>
#include <vector>
#include <queue>
#include <climits>

// ��������������� ������� ��� ���������� BFS
bool findAugmentingPath(const std::vector<std::vector<int>>& residualGraph, int source, int sink, std::vector<int>& parent) {
    int n = residualGraph.size();
    parent.assign(n, -1); // ���������� ������������ ������
    std::queue<int> queue;
    queue.push(source);

    while (!queue.empty()) {
        int current = queue.front();
        queue.pop();

        for (int next = 0; next < n; ++next) {
            // ���� ���� ���������� ����������� � ������� �� ��������
            if (residualGraph[current][next] > 0 && parent[next] == -1 && next != source) {
                parent[next] = current; // ��������� ������� ������� ��� ������������
                if (next == sink) return true; // ���� ����� �� �����
                queue.push(next); // ���������� ������������
            }
        }
    }
    return false; // ���� ���
}

// ���������� ��������� ��������-�����
int GuryevEdmondsKarp(std::vector<std::vector<int>> graph, int source, int sink) {
    int n = graph.size();
    std::vector<std::vector<int>> residualGraph(graph); // ������� ���������� ����
    std::vector<int> parent(n); // ��� �������� ����
    int maxFlow = 0;

    // ��������� ����� ������������� �����
    while (findAugmentingPath(residualGraph, source, sink, parent)) {
        // ��������� ����������� ���������� ����������� �� ��������� ����
        int flow = INT_MAX;
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            flow = std::min(flow, residualGraph[u][v]);
        }

        // ��������� ���������� ����
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            residualGraph[u][v] -= flow;
            residualGraph[v][u] += flow;
        }

        // ����������� ����� �����
        maxFlow += flow;
    }

    return maxFlow;
}
