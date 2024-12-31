const int N = 3e5 + 9, LOG = 19;

struct LCA {
    vector<vector<pair<int, int>>> g;
    vector<vector<int>> par, mx;
    vector<int> dep, sz;
    LCA(int n) : g(n + 1), dep(n + 1), sz(n + 1) {
        par.assign(n + 1, vector<int>(LOG + 1));
        mx.assign(n + 1, vector<int>(LOG + 1));
    }
    void add_edge(int u, int v, int w = 1) {
        g[u].push_back({v, w});
        g[v].push_back({u, w}); 
    }
    void dfs(int u, int p = 0) {
        par[u][0] = p;
        sz[u] = 1;
        for (int i = 1; i <= LOG; i++) par[u][i] = par[par[u][i - 1]][i - 1];
        for (int i = 1; i <= LOG; i++) mx[u][i] = max(mx[u][i - 1], mx[par[u][i - 1]][i - 1]);
        for (auto v : g[u]) if(v.first != p) {
            dep[v.first] = dep[u] + 1;
            mx[v.first][0] = v.second;
            dfs(v.first, u);
            sz[u] += sz[v.first];
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
    int get_max_edge(int u, int v) {
        int l = lca(u, v);
        int ans = 0, k = dep[u] - dep[l];
        for (int i = 0; i <= LOG; i++) {
            if(k & (1 << i)) ans = max(ans, mx[u][i]), u = par[u][i];
        }
        k = dep[v] - dep[l];
        for (int i = 0; i <= LOG; i++) {
            if(k & (1 << i)) ans = max(ans, mx[v][i]), v = par[v][i];
        }
        return ans;
    }
};