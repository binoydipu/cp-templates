const int N = 3e5 + 9;

struct DSU {
    vector<int> par, rank, sz;
    int c;
    DSU(int n) : par(n + 1), rank(n + 1, 0), sz(n + 1, 1), c(n) {
        for (int i = 1; i <= n; i++) par[i] = i;
    }
    int find(int v) { // finding root of v
        if(par[v] == v) return v;
        else return par[v] = find(par[v]);
    }
    bool same(int a, int b) {
        return find(a) == find(b);
    }
    int get_size(int v) {
        return sz[find(v)];
    }
    int count() {
        return c; // connected components
    }
    void merge(int a, int b) {
        a = find(a), b = find(b);
        if(a == b) return; // already in same component
        else c--;
        if(rank[a] > rank[b]) swap(a, b);
        par[a] = b;
        sz[b] += sz[a];
        if(rank[a] == rank[b]) rank[b]++;
    }
};
