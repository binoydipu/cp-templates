vector<bool> alive;
vector<int> sz, cen_par;
// return's centroid of the connected component of node
template <typename T>
int find_centroid(const graph<T>& g, int node) {
    function<void(int, int)> dfs = [&](int v, int p) {
        sz[v] = 1;
        for(auto id : g.g[v]) {
            auto &e = g.edges[id];
            int to = e.from ^ e.to ^ v;
            if(to == p || !alive[to]) {
                continue;
            }
            dfs(to, v);
            sz[v] += sz[to];
        }
    };
 
    dfs(node, -1);
    int cen = node;
    int par = -1;
    while(true) {
        int nxt = -1;
        for(auto id : g.g[cen]) {
            auto &e = g.edges[id];
            int to = e.from ^ e.to ^ cen;
            if(to != par && alive[to] && 2 * sz[to] > sz[node]) {
                nxt = to; // centroid is in this subtree
                break;
            }
        }
        if(nxt == -1) {
            break;
        }
        par = cen;
        cen = nxt;
    }
    alive[cen] = false;
    return cen;
}

// builds centroid tree, par -> prev centroid
void decompose(const graph<int>& g, int v, int p) {
    int cen = find_centroid(g, v);
    cen_par[cen] = p;
    alive[cen] = false;
    for(auto id : g.g[cen]) {
        auto &e = g.edges[id];
        int to = e.from ^ e.to ^ cen;
        if(alive[to]) {
            decompose(g, to, cen);
        }
    }
}