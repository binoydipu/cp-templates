#include<bits/stdc++.h>
using namespace std;

template <typename T>
int farthest(const graph<T> &g, int start, vector<int> &dist) {
    dist.assign(g.n + 1, inf); // dist w.r.t start node
    vector<bool> vis(g.n + 1, false);
    vis[start] = true; 
    dist[start] = 0;
    queue<int> q; 
    q.push(start);
    int last = start;

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (auto id : g.g[v]) {
            auto &e = g.edges[id];
            int to = e.from ^ e.to ^ v;
            if(vis[to]) {
                continue;
            }
            vis[to] = true;
            dist[to] = dist[v] + 1;
            q.push(to);
        }
        last = v;
    }
    return last; // fartest node from start
}

int32_t main() {
    int n;
    cin >> n;
    graph<int> g(n);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g.add_edge(u, v);
    }
    vector<int> dist;
    int x = farthest(g, 1, dist); // 1 to max dist node = x
    int y = farthest(g, x, dist); // x to max dist node = y
    cout << dist[y] << nl; // x to y path is the tree diameter

    return 0;
}
