vector<vector<int>> Mat;

template <typename T>
void build_max_edges(const lca_graph<T> &g, int from) {
    Mat.resize(g.n + 1, vector<int>(g.max_depth + 1));
    vector<bool> vis(g.n + 1, false);

    function<void(int)> dfs = [&](int v) {
        vis[v] = true;
        for (int i = 1; i <= g.max_depth; i++) Mat[v][i] = max(Mat[v][i - 1], Mat[g.par[v][i - 1]][i - 1]);
        for(auto id : g.g[v]) {
            auto &e = g.edges[id];
            int to = e.from ^ e.to ^ v;
            if(vis[to]) {
                continue;
            }
            Mat[to][0] = e.cost;
            dfs(to);
        }
    };
    dfs(from);
}

template <typename T>
T find_max_edge(int u, int v, lca_graph<T> &g) {
    assert(!Mat.empty());
    int l = g.lca(u, v);
    int k = g.depth[u] - g.depth[l];
    T ans = 0;
    for (int i = 0; i <= g.max_depth; i++) {
        if(k & (1 << i)) ans = max(ans, Mat[u][i]), u = g.par[u][i];
    }
    k = g.depth[v] - g.depth[l];
    for (int i = 0; i <= g.max_depth; i++) {
        if(k & (1 << i)) ans = max(ans, Mat[v][i]), v = g.par[v][i];
    }
    return ans;
}