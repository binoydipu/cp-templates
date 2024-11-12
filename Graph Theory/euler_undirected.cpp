/*
  all the edges should be in the same connected component
  #undirected graph: euler path: all degrees are even or exactly two of them are odd.
  #undirected graph: euler circuit: all degrees are even
*/

// euler path in an undirected graph: start from odd deg -> finish in odd deg; 
// it also finds circuit if it exists
struct Euler {
    int n, edges;
    vector<bool> vis;
    vector<int> done, path, deg;
    vector<vector<pair<int, int>>> g;
    Euler(int _n, int _edges) : n (_n), edges (_edges) {
        vis.assign(edges + 1, false);
        done.assign(n + 1, 0);
        deg.assign(n + 1, 0);
        g.assign(n + 1, vector<pair<int, int>>());
    }
    void addEdge(int u, int v, int idx) {
        g[u].push_back({v, idx});
        g[v].push_back({u, idx});
        deg[u]++, deg[v]++;
    }
    void dfs(int u) {
        while(done[u] < g[u].size()) {
            auto v = g[u][done[u]++];
            if(vis[v.second]) continue;
            vis[v.second] = true;
            dfs(v.first);
        }
        path.push_back(u);
    }
    bool hasEulerPath() {
        path.clear();
        int odd = 0, root = -1;
        for (int i = 1; i <= n; i++) {
            if(deg[i] & 1) odd++, root = i;
        }
        if(odd > 2) return false;
        if(root == -1) { // odd == 0
            for (int i = 1; i <= n; i++) if (deg[i]) { root = i; break; }
        }
        if(root == -1) return true; // empty graph
        dfs(root);
        if(path.size() != edges + 1) return false;
        reverse(path.begin(), path.end());
        return true;
    }
    vector<int> getEulerPath() {
        if(hasEulerPath()) return path;
        return {};
    }
};