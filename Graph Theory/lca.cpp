template <typename T> 
class lca_graph : public graph<T> {
  public:
    using graph<T>::edges;
    using graph<T>::g;
    using graph<T>::n;

    int max_depth;
    vector<int> depth;
    vector<int> sz;
    vector<vector<int>> par;

    lca_graph(int _n) : graph<T>(_n) {
        max_depth = 31 - __builtin_clz(_n);
    }

    void build_lca(int from) {
        depth = vector<int>(n + 1, 0);
        sz = vector<int>(n + 1, 0);
        par = vector<vector<int>>(n + 1, vector<int>(max_depth + 1));
        dfs(from);
    }

    void dfs(int v, int p = 0) {
        par[v][0] = p;
        sz[v] = 1;
        for (int i = 1; i <= max_depth; i++) par[v][i] = par[par[v][i - 1]][i - 1];
        for (auto id : g[v]) {
            auto &e = edges[id];
            int to = e.from ^ e.to ^ v;
            if(to == p) {
                continue;
            }
            depth[to] = depth[v] + 1;
            dfs(to, v);
            sz[v] += sz[to];
        }
    }

    int kth(int u, int k) {
        assert(k >= 0);
        for (int i = 0; i <= max_depth; i++) {
            if(k & (1 << i)) u = par[u][i];
        }
        return u;
    }

    int lca(int u, int v) {
        if(depth[u] < depth[v]) swap(u, v);
        u = kth(u, depth[u] - depth[v]);
        if(u == v) return u;
        for (int k = max_depth; k >= 0; k--) {
            if(par[u][k] != par[v][k]) u = par[u][k], v = par[v][k];
        }
        return par[u][0];
    }

    int dist(int u, int v) {
        int l = lca(u, v);
        return depth[u] + depth[v] - (depth[l] << 1);
    }

    // k-th node from u to v, 0th node is u
    int go(int u, int v, int k) {
        int l = lca(u, v);
        int d = depth[u] + depth[v] - (depth[l] << 1);
        assert(k <= d);
        if (depth[l] + k <= depth[u]) return kth(u, k);
        k -= depth[u] - depth[l];
        return kth(v, depth[v] - depth[l] - k);
    }

    bool is_ancestor(int u, int v) {
        return depth[u] <= depth[v] && kth(v, depth[v] - depth[u]) == u;
    }    

    // checks if node x is in between u->v path
    bool is_in_path(int u, int v, int x) {
        int l = lca(u, v), l1 = lca(u, x), l2 = lca(v, x);
        return (l == x || (l1 == l && l2 == x) || (l2 == l && l1 == x));
    }

    // returns v's child in which subtree has node x (opposite if dep x<v)
    int in_branch(int v, int x) {
        if(depth[x] < depth[v]) swap(x, v);
        x = kth(x, depth[x] - depth[v] - 1); // move x to 1 depth from v
        return x;
    }
};