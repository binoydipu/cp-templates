struct AP {
    int n, timer;
    vector<int> dis, low;
    vector<bool> art;
    vector<vector<int>> g;
    vector<int> articulationPoints;
    AP(int _n) : n (_n), timer (0) {
        dis.assign(n + 1, 0);
        low.assign(n + 1, 0);
        art.assign(n + 1, false);
        g.assign(n + 1, vector<int>());
    }
    void addEdge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u); 
    }
    void _dfs(int u, int p = -1) {
        dis[u] = low[u] = ++timer;
        int child = 0;
        for(auto v : g[u]) {
            if(v == p) continue; 
            if(dis[v] == 0) { // not yet visited
                _dfs(v, u);
                low[u] = min(low[u], low[v]); // using child nodes
                if(low[v] >= dis[u] && p != -1) art[u] = true;
                child++;
            }
            else {
                low[u] = min(low[u], dis[v]); // using back edge
            }
        }
        if(child > 1 && p == -1) art[u] = true;
    }
    vector<int> getPoints() {
        _dfs(1);
        for (int i = 0; i <= n; i++) {
            if(art[i]) articulationPoints.push_back(i);
        }
        return articulationPoints;
    }
};