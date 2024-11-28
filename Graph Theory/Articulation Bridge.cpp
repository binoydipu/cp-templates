struct Bridge {
    int n, timer;
    vector<int> dis, low;
    vector<vector<int>> g;
    vector<pair<int, int>> bridges;
    Bridge(int _n) : n (_n), timer (0) {
        dis.assign(n + 1, 0);
        low.assign(n + 1, 0);
        g.assign(n + 1, vector<int>());
    }
    void addEdge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u); 
    }
    void _inBridge(int u, int v) {
        bridges.push_back({u, v});
    }
    void _dfs(int u, int p = -1) {
        dis[u] = low[u] = ++timer;
        bool parent_skipped = false;
        for(auto v : g[u]) {
            if(v == p && !parent_skipped) {
                parent_skipped = true;
                continue; // in case of multi edge to parent - skip once
            }
            if(dis[v] == 0) { // not yet visited
                _dfs(v, u);
                low[u] = min(low[u], low[v]); // using child nodes
                if(low[v] > dis[u]) _inBridge(u, v);
            }
            else {
                low[u] = min(low[u], dis[v]); // using back edge
            }
        }
    }
    vector<pair<int, int>> getBridges() {
        _dfs(1);
        return bridges;
    }
};