const int N = 2e5 + 9;

int a[N];
struct Dfs {
    vector<vector<int>> g;
    vector<int> lvl;
    vector<bool> vis;

    Dfs(int n) : lvl(n + 1), vis(n + 1), g(n + 1) {}

    void add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u); 
    }
    void dfs(int v, int p = -1) {
        vis[v] = true;
        for(auto u : g[v]) if(!vis[u]) {
            lvl[u] = 1 + lvl[v];
            dfs(u, v);
        }
    }
};


auto dfs = [&](auto self, int u, int p) -> void {
    dbg(u);
    for (int v : g[u]) {
        if (v == p) continue;
        self(self, v, u);
    }
};
// dfs(dfs, 1, 0);