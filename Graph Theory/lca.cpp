const int N = 3e5 + 9, LOG = 19;

struct LCA {
    vector<vector<int>> g, par;
    vector<int> dep, sz;

    LCA(int n) : dep(n + 1), sz(n + 1), g(n + 1) {
        par.assign(n + 1, vector<int>(LOG + 1));
    }
    void add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u); 
    }
    void dfs(int u, int p = 0) {
        par[u][0] = p;
        sz[u] = 1;
        for (int i = 1; i <= LOG; i++) par[u][i] = par[par[u][i - 1]][i - 1];
        for (auto v : g[u]) if(v != p) {
            dep[v] = dep[u] + 1;
            dfs(v, u);
            sz[u] += sz[v];
        }
    }
    int lca(int u, int v) {
        if(dep[u] < dep[v]) swap(u, v);
        u = kth(u, dep[u] - dep[v]); // move u to same depth as v
        if(u == v) return u;
        for (int i = LOG; i >= 0; i--) {
            if(par[u][i] != par[v][i]) u = par[u][i], v = par[v][i];
        }
        return par[u][0];
    }
    int kth(int u, int k) {
        assert(k >= 0);
        for (int i = 0; i <= LOG; i++) {
            if(k & (1 << i)) u = par[u][i];
        }
        return u;
    }
    int dist(int u, int v) {
        int l = lca(u, v);
        return dep[u] + dep[v] - (dep[l] << 1);
    }
    // kth node from u to v, 0th node is u
    int go(int u, int v, int k) {
        int l = lca(u, v);
        int d = dep[u] + dep[v] - (dep[l] << 1); 
        assert(k <= d); 
        if(dep[u] >= dep[l] + k) return kth(u, k);
        k -= dep[u] - dep[l];
        return kth(v, dep[v] - (dep[l] + k));
    }
    // checks if x is in between u->v path
    bool isInPath(int u, int v, int x) {
        int l = lca(u, v), l1 = lca(u, x), l2 = lca(v, x);
        return (l == x || (l1 == l && l2 == x) || (l2 == l && l1 == x));
    }
    // returns v's child in who's subtree u exists
    int inBranch(int u, int v) {
        if(dep[u] < dep[v]) swap(u, v);
        u = kth(u, dep[u] - dep[v] - 1); // move u to 1 depth from v
        return u;
    }
};