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
            // ���� ���� ���������� ���������� ����������� � ������� �� ��������
            if (!visited[v] && residualGraph[u][v] > 0) {
                stack.push_back(v);
                parent[v] = u;
                visited[v] = true;
                // ���� �������� �����, ���� ������
                if (v == sink) return true;
            }
        }
    }
    return false;
}

// �������� �����-���������� ��� ������ ������������� ������
int SerkovaFordFulkerson(const vector<vector<int>>& graph, int source, int sink) {
    int n = graph.size();
    vector<vector<int>> residualGraph = graph; // ���������� ����
    vector<int> parent(n);                      // ������ ��� �������� ����
    int maxFlow = 0;

    // ���� ���� ���� �� ��������� � ����
    while (dfs(residualGraph, source, sink, parent)) {
        // ������� ����������� ���������� ����������� �� ����
        int pathFlow = INT_MAX;
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            pathFlow = min(pathFlow, residualGraph[u][v]);
        }
        // ��������� ���������� ����
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            residualGraph[u][v] -= pathFlow;
            residualGraph[v][u] += pathFlow;
        }
        // ��������� ����� ���� � ������ ������������� ������
        maxFlow += pathFlow;
    }
    return maxFlow;
};