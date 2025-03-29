template <typename T>
vector<vector<int>> find_cycles(const graph<T> &g) {
    vector<int> vis(g.n + 1, -1);
    vector<int> st; // cur dfs path
    vector<vector<int>> cycles;

    function<void(int, int)> dfs = [&](int v, int p) {
        vis[v] = (int) st.size();
        for(auto id : g.g[v]) {
            if(id == p) {
                continue;
            }
            auto &e = g.edges[id];
            int to = e.from ^ e.to ^ v;
            if(vis[to] >= 0) { // cycle here
                vector<int> cycle(1, id);
                for (int j = vis[to]; j < (int)st.size(); j++) {
                    cycle.push_back(st[j]);
                }
                cycles.push_back(cycle);
                continue;
            }
            if(vis[to] == -1) { // not yet visited
                st.push_back(id);
                dfs(to, id);
                st.pop_back();
            }
        }
        vis[v] = -2;
    };

    for (int v = 1; v <= g.n; v++) {
        if(vis[v] == -1) {
            dfs(v, -1);
        }
    }
    return cycles; // contain edge ids, finds all cycles
}

template <typename T>
vector<int> edges_to_vertices(const graph<T> &g, const vector<int> &edge_cycle) {
    int sz = (int) edge_cycle.size();
    vector<int> vertex_cycle;
    if (sz <= 2) {
        vertex_cycle.push_back(g.edges[edge_cycle[0]].from);
        if (sz == 2) {
            vertex_cycle.push_back(g.edges[edge_cycle[0]].to);
        }
    } else {
        for (int i = 0; i < sz; i++) {
            int j = (i + 1) % sz;
            auto &e = g.edges[edge_cycle[i]];
            auto &other = g.edges[edge_cycle[j]];
            if (other.from == e.from || other.to == e.from) {
                vertex_cycle.push_back(e.to);
            } else {
                vertex_cycle.push_back(e.from);
            }
        }
    }
    return vertex_cycle;
}