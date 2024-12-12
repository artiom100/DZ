#include <chrono>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
#include <iostream>

using namespace std;

int goldberg(std::vector<std::vector<int>> graph, int source, int sink) {
    int n = graph.size();
    std::vector<int> height(n, 0), excess(n, 0);
    std::vector<std::vector<int>> flow(n, std::vector<int>(n, 0));
    height[source] = n;
    for (int v = 0; v < n; ++v) {
        flow[source][v] = graph[source][v];
        flow[v][source] = -flow[source][v];
        excess[v] = flow[source][v];
        graph[source][v] -= flow[source][v];
        graph[v][source] += flow[source][v];
    }
    bool active = true;
    while (active) {
        active = false;
        for (int u = 0; u < n; ++u) {
            if (excess[u] > 0 && u != source && u != sink) {
                active = true;
                for (int v = 0; v < n; ++v) {
                    if (graph[u][v] > 0 && height[u] == height[v] + 1) {
                        int pushed = std::min(excess[u], graph[u][v]);
                        flow[u][v] += pushed;
                        flow[v][u] -= pushed;
                        graph[u][v] -= pushed;
                        graph[v][u] += pushed;
                        excess[u] -= pushed;
                        excess[v] += pushed;
                    }
                }
                if (excess[u] > 0) {
                    int min_height = INT_MAX;
                    for (int v = 0; v < n; ++v) {
                        if (graph[u][v] > 0) {
                            min_height = std::min(min_height, height[v]);
                        }
                    }
                    height[u] = min_height + 1;
                }
            }
        }
    }
    int max_flow = 0;
    for (int v = 0; v < n; ++v) {
        max_flow += flow[source][v];
    }
    return max_flow;
}

int VyunovGoldberg(std::vector<std::vector<int>>& graph, int source, int sink) {
    int n = graph.size();
    std::vector<int> height(n, 0), excess(n, 0);
    std::vector<std::vector<int>> flow(n, std::vector<int>(n, 0));
    height[source] = n;
    for (int v = 0; v < n; ++v) {
        flow[source][v] = graph[source][v];
        flow[v][source] = -flow[source][v];
        excess[v] = flow[source][v];
        graph[source][v] -= flow[source][v];
        graph[v][source] += flow[source][v];
    }
    bool active = true;
    while (active) {
        active = false;
        for (int u = 0; u < n; ++u) {
            if (excess[u] > 0 && u != source && u != sink) {
                active = true;
                for (int v = 0; v < n; ++v) {
                    if (graph[u][v] > 0 && height[u] == height[v] + 1) {
                        int pushed = std::min(excess[u], graph[u][v]);
                        flow[u][v] += pushed;
                        flow[v][u] -= pushed;
                        graph[u][v] -= pushed;
                        graph[v][u] += pushed;
                        excess[u] -= pushed;
                        excess[v] += pushed;
                    }
                }
                if (excess[u] > 0) {
                    int min_height = INT_MAX;
                    for (int v = 0; v < n; ++v) {
                        if (graph[u][v] > 0) {
                            min_height = std::min(min_height, height[v]);
                        }
                    }
                    height[u] = min_height + 1;
                }
            }
        }
    }
    int max_flow = 0;
    for (int v = 0; v < n; ++v) {
        max_flow += flow[source][v];
    }
    return max_flow;
}

