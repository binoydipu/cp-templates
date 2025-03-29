template <typename T>
vector<int> find_cycle(const graph<T> &g) {
    vector<int> vis(g.n + 1, 0);
    vector<int> par(g.n + 1, -1);
    vector<int> eg_id(g.n + 1, -1);

    vector<int> cycle;

    function<bool(int)> dfs = [&](int v) {
        if(!cycle.empty()) return true;
        vis[v] = 1;
        for(auto id : g.g[v]) {
            auto &e = g.edges[id];
            int to = e.from ^ e.to ^ v;
            if(to != par[v]) {
                if(vis[to] == 0) {
                    par[to] = v;
                    eg_id[to] = id;
                    if(dfs(to)) return true;
                } else if(vis[to] == 1) { // cycle here
                    cycle.push_back(id);
                    for (int x = v; x != to; x = par[x]) {
                        cycle.push_back(eg_id[x]);
                    }
                    return true;
                }
            }
        }
        vis[v] = 2;
        return false;
    };

    for (int v = 1; v <= g.n; v++) {
        if(vis[v] == 0 && dfs(v)) {
            break;
        }
    }
    return cycle; // contain edge ids, finds one cycle if exists
}