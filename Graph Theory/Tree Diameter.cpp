template <typename T>
int find_diameter(const graph<T> &g) {
    int d = 0;
    function<int(int, int)> dfs = [&](int v, int p) {
        int mx1 = 0, mx2 = 0; // two longest heights
        for(auto id : g.g[v]) {
            auto &e = g.edges[id];
            int to = e.from ^ e.to ^ v;
            if(to == p) {
                continue;
            }
            int h = dfs(to, v);
            if(h > mx1) mx2 = mx1, mx1 = h;
            else if(h > mx2) mx2 = h;
        }
        d = max(d, mx1 + mx2); // diameter passing through this node
        return mx1 + 1; // longest path downward
    };
    dfs(1, 0);
    return d;
}