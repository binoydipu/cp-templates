template <typename T>
vector<int> find_topsort(const graph<T> &g) { // g must be DAG
    vector<int> deg(g.n + 1, 0);
    for (int id = 0; id < (int) g.edges.size(); id++) {
        deg[g.edges[id].to]++;
    }
    queue<int> q;
    for (int i = 1; i <= g.n; i++) {
        if(deg[i] == 0) q.push(i);
    }
    vector<int> ts;
    while(!q.empty()) {
        int v = q.front();
        q.pop();
        ts.push_back(v);
        for(auto id : g.g[v]) {
            auto &e = g.edges[id];
            int to = e.from ^ e.to ^ v;
            deg[to]--;
            if(deg[to] == 0) q.push(to);
        }
    }
    if(ts.size() != g.n) {
        return vector<int>();
    }
    return ts;
}