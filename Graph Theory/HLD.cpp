const int N = 2e5 + 5;

int a[N], value[N], tree[2 * N];
int n;

inline int unite(int p, int q) {
    return max(p, q);
}
void seg_build() {
    for(int i = 1; i <= n; i++) tree[i + n] = a[i];
    for(int i = n; i > 1; --i) tree[i] = unite(tree[i << 1], tree[i << 1 | 1]);
}
void seg_upd(int p, int v) {
    for (tree[p += n] = v; p >>= 1; ) tree[p] = unite(tree[p << 1], tree[p << 1 | 1]);
}
int seg_query(int l, int r) {
    int resl = 0, resr = 0;
    for(l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
        if(l & 1) resl = unite(resl, tree[l++]);
        if(r & 1) resr = unite(tree[--r], resr);
    }
    return unite(resl, resr);
}

template <typename T> 
class hld_graph : public graph<T> {
  public:
    using graph<T>::edges;
    using graph<T>::g;
    using graph<T>::n;

    int max_depth;
    vector<int> depth;
    vector<int> sz;
    vector<vector<int>> par;
    vector<int> heavy;
    vector<int> head;
    vector<int> start;
    vector<int> end;
    vector<int> linear;
    int timer;
    
    hld_graph(int _n) : graph<T>(_n) {
        max_depth = 31 - __builtin_clz(_n);
    }

    void build_hld(int from) {
        depth = vector<int>(n + 1, 0);
        sz = vector<int>(n + 1, 0);
        heavy = vector<int>(n + 1, 0);
        head = vector<int>(n + 1, 0);
        start = vector<int>(n + 1, -1);
        end = vector<int>(n + 1, -1);
        par = vector<vector<int>>(n + 1, vector<int>(max_depth + 1));
        linear = vector<int>(n + 1, 0);
        timer = 1;
        dfs(from);
        dfs_hld(from, 0, from);
    }

    void dfs(int v, int p = 0) {
        par[v][0] = p;
        sz[v] = 1;
        for (int i = 1; i <= max_depth; i++) par[v][i] = par[par[v][i - 1]][i - 1];
        for (int j = 0; j < (int) g[v].size(); j++) {
            int id = g[v][j];
            auto &e = edges[id];
            int to = e.from ^ e.to ^ v;
            if(to == p) {
                continue;
            }
            depth[to] = depth[v] + 1;
            dfs(to, v);
            sz[v] += sz[to];
            if(sz[to] > sz[heavy[v]]) {
                heavy[v] = to;
            }
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

    inline int dist(int u, int v) {
        int l = lca(u, v);
        return depth[u] + depth[v] - (depth[l] << 1);
    }
    
    inline bool is_ancestor(int u, int v) {
        return depth[u] <= depth[v] && kth(v, depth[v] - depth[u]) == u;
    } 

    void dfs_hld(int v, int p, int chain) {
        head[v] = chain;
        linear[timer] = v;
        start[v] = timer++;
        a[start[v]] = value[v]; // change this
        if(heavy[v] != 0) {
            dfs_hld(heavy[v], v, chain);
        }
        for (auto id : g[v]) {
            auto &e = edges[id];
            int to = e.from ^ e.to ^ v;
            if(to == p || to == heavy[v]) {
                continue;
            }
            dfs_hld(to, v, to);
        }
        end[v] = timer;
    }

    int query(int u, int v) { // change this
        int ans = LLONG_MIN;
        while(head[u] != head[v]) {
            if(depth[head[u]] < depth[head[v]]) swap(u, v);
            ans = max(ans, seg_query(start[head[u]], start[u]));
            u = par[head[u]][0];
        }
        if(depth[u] < depth[v]) swap(u, v);
        ans = max(ans, seg_query(start[v], start[u]));
        return ans;
    }
};
// g.build_hld(1); seg_build();