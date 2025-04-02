template <typename T>
vector<int> find_scc(const graph<T> &g, int &cnt) {
    graph<T> g_rev = g.reverse();
    vector<int> order;
    vector<bool> vis(g.n + 1, false);

    function<void(int)> dfs1 = [&](int v) {
        vis[v] = true;
        for(auto id : g.g[v]) {
            auto &e = g.edges[id];
            int to = e.from ^ e.to ^ v;
            if(vis[to]) {
                continue;
            }
            dfs1(to);
        }
        order.push_back(v);
    };
    for (int v = 1; v <= g.n; v++) {
        if(!vis[v]) {
            dfs1(v);
        }
    }
    vector<int> com(g.n + 1, -1);

    function<void(int)> dfs2 = [&](int v) {
        vis[v] = 1;
        for(auto id : g_rev.g[v]) {
            auto &e = g_rev.edges[id];
            int to = e.from ^ e.to ^ v;
            if(com[to] != -1) {
                continue;
            }
            com[to] = com[v];
            dfs2(to);
        }
    };
    cnt = 0;
    for (int i = g.n - 1; i >= 0; i--) {
        int v = order[i];
        if(com[v] != -1) {
            continue;
        }
        com[v] = cnt++;
        dfs2(v);
    }
    return com;
    // component id of scc(0 to cnt-1); all same id's are strongly connected
}
