//
// Created by Nicholas Patrick on 8/8/23.
//

#include "matcher.h"

matcher::matcher(int l, int r) : l(l), r(r), e_r(r) {}

void matcher::addEdge(int u, int v) {
    e_r[v].push_back(u);
    long long random_ish = std::chrono::steady_clock::now().time_since_epoch().count() ^ 0x123456789;
    std::swap(e_r[v].back(), e_r[v][random_ish % e_r[v].size()]);
}

romanian::romanian(int l, int r) : matcher(l, r) {}

std::vector<int> romanian::findMatch() const {
    std::vector<int> match_l(l, -1);
    std::vector<bool> visited;
    auto dfs = [&](auto self, int u) {
        visited[u] = true;
        for (int v : e_r[u]) {
            if (match_l[v] == -1) {
                match_l[v] = u;
                return true;
            }
        }
        for (int v : e_r[u]) {
            if (!visited[match_l[v]] && self(self, match_l[v])) {
                match_l[v] = u;
                return true;
            }
        }
        return false;
    };
    for (int u = 0; u < r; ++u) {
        visited.assign(r, false);
        dfs(dfs, u);
    }
    return match_l;
}

hop_karp::hop_karp(int l, int r) : matcher(l, r) {}

std::vector<int> hop_karp::findMatch() const {
    int vertex_count = l + r + 2;
    int source = vertex_count - 2, sink = vertex_count - 1;
    std::vector<std::vector<int>> adjacency_list(vertex_count);
    for (int u = 0; u < l; ++u)
        adjacency_list[source].push_back(u);
    for (int v = 0; v < r; ++v) {
        for (int u : e_r[v])
            adjacency_list[u].push_back(v + l);
        adjacency_list[v + l].push_back(sink);
    }
    struct edge_t {
        int from, to, inv_index, residual, flow;
    };
    std::vector<std::pair<int, int>> simple_edge_list;
    for (int i = 0; i < vertex_count; ++i) {
        for (int j : adjacency_list[i]) {
            simple_edge_list.emplace_back(i, j);
            simple_edge_list.emplace_back(j, i);
        }
    }
    sort(simple_edge_list.begin(), simple_edge_list.end());
    simple_edge_list.resize(unique(simple_edge_list.begin(), simple_edge_list.end()) - simple_edge_list.begin());
    std::vector<int> edge_partitions(vertex_count + 1);
    edge_partitions[0] = 0;
    edge_partitions.back() = int(simple_edge_list.size());
    std::vector<edge_t> edge_list(edge_partitions.back(), {-1, -1, -1, 0, 0});
    for (int i = 0; i < vertex_count; ++i) {
        for (int j : adjacency_list[i]) {
            int index = int(lower_bound(simple_edge_list.begin(), simple_edge_list.end(),
                                                  std::pair(i, j)) - simple_edge_list.begin());
            int inv_index = int(lower_bound(simple_edge_list.begin(), simple_edge_list.end(),
                                                  std::pair(j, i)) - simple_edge_list.begin());
            edge_list[index].from = i;
            edge_list[index].to = j;
            edge_list[index].inv_index = inv_index;
            ++edge_list[index].residual;
            edge_list[inv_index].from = j;
            edge_list[inv_index].to = i;
            edge_list[inv_index].inv_index = index;
        }
    }
    for (int i = 0, partition = 0; i < vertex_count; ++i) {
        edge_partitions[i] = partition;
        while (partition < edge_list.size() && edge_list[partition].from == i)
            ++partition;
    }
    for (;;) {
        // BFS
        std::vector<int> distances(vertex_count, vertex_count);
        std::queue<int> bfs_queue;
        distances[source] = 0;
        bfs_queue.push(source);
        while (!bfs_queue.empty()) {
            int u = bfs_queue.front();
            bfs_queue.pop();
            int d = distances[u];
            for (int i = edge_partitions[u]; i < edge_partitions[u + 1]; ++i) {
                int v = edge_list[i].to;
                if (edge_list[i].residual && distances[v] > d + 1) {
                    distances[v] = d + 1;
                    if (v == sink) {
                        bfs_queue = std::queue<int>();
                        break;
                    }
                    bfs_queue.push(v);
                }
            }
        }
        // check
        if (distances[sink] == vertex_count) {
            std::vector<int> ret(l);
            for (auto i : edge_list) {
                if (i.from < l && l <= i.to && i.to < l + r && i.flow)
                    ret[i.from] = i.to - l;
            }
            return ret;
        }
        // DFS
        std::vector<int> shared_iterators = edge_partitions;
        auto dfs = [&](auto self, int u) -> bool {
            if (u == source)
                return true;
            for (int &i = shared_iterators[u]; i < edge_partitions[u + 1]; ++i) {
                int v = edge_list[i].to;
                int j = edge_list[i].inv_index;
                if (distances[v] + 1 != distances[u] || !edge_list[j].residual) continue;
                if (self(self, v)) {
                    --edge_list[j].residual;
                    ++edge_list[i].residual;
                    if (edge_list[i].flow) {
                        --edge_list[i].flow;
                    } else {
                        ++edge_list[j].flow;
                    }
                    return true;
                }
            }
            return false;
        };
        while (dfs(dfs, sink));
    }
}
