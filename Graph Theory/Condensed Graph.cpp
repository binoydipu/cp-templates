template <typename T>
graph<T> find_condensed_graph(const graph<T>& g, const vector<int> &com) {
    vector<int> par(g.n + 1, -1), root(g.n + 1, -1);
    for (int v = 1; v <= g.n; v++) {
        int id = com[v];
        if(root[id] == -1) {
            root[id] = v;
        }
        par[v] = root[id];
    }
    graph<T> gc(g.n);
    for (int v = 1; v <= g.n; v++) {
        for(auto id : g.g[v]) {
            auto &e = g.edges[id];
            int to = e.from ^ e.to ^ v;
            if(par[v] != par[to]) gc.add_edge(par[v], par[to]);
        }
    }
    return gc;
    // all scc's compressed to 1 node(minimum one)
}