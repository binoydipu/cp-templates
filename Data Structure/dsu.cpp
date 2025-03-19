class DSU {
  public:
    vector<int> par, rank, sz;
    int c, n;

    DSU(int _n) : n(_n), par(_n + 1), rank(_n + 1), c(_n) {
        iota(par.begin(), par.end(), 0);
        sz.resize(n + 1, 1);
    }

    inline int find(int v) { // finding root of v
        return par[v] == v ? v : par[v] = find(par[v]);
    }
    inline bool same(int a, int b) {
        return find(a) == find(b);
    }
    inline int get_size(int v) {
        return sz[find(v)];
    }
    inline int count() {
        return c; // connected components
    }
    inline bool unite(int a, int b) {
        a = find(a), b = find(b);
        if(a == b) return false; // already in same component
        else c--;
        if(rank[a] > rank[b]) swap(a, b);
        par[a] = b;
        sz[b] += sz[a];
        if(rank[a] == rank[b]) rank[b]++;
        return true;
    }
};