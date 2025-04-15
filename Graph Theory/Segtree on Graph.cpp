// use to add edges from a node to multiple nodes at once, and v.v.
template <typename T>
class segtree_graph {
  public:
    #define lc (n << 1)
    #define rc ((n << 1) | 1)
    struct edge {
        int from;
        int to;
        T cost;
    };

    vector<edge> edges;
    vector<vector<int>> g;
    int N, N2;

    segtree_graph(int _n) : N(_n) {
        N2 = N * 5;
        g.resize(N * 9 + 1);
        build_forw(1, 1, _n);
        build_revs(1, 1, _n);
    }

    int add_edge(int from, int to, T cost = 1) {
        int id = (int) edges.size();
        g[from].push_back(id);
        edges.push_back({from, to, cost});
        return id;
    }

    void print_graph() {
        for (int v = 1; v <= N * 9; v++) {
            cerr << "node " << v << " to=> ";
            for(auto id : g[v]) {
                auto &e = edges[id];
                int to = e.from ^ e.to ^ v;
                cerr << '(' << to << ", " << e.cost << ") ";
            }
            cerr << "\n";
        }
    }

    void build_forw(int n, int b, int e) {
        if(b == e) {
            add_edge(n + N, b, 0);
            return;
        }
        int mid = (b + e) >> 1;
        add_edge(n + N, lc + N, 0);
        add_edge(n + N, rc + N, 0);
        build_forw(lc, b, mid);
        build_forw(rc, mid + 1, e);
    }

    void build_revs(int n, int b, int e) {
        if(b == e) {
            add_edge(b, n + N2, 0);
            return;
        }
        int mid = (b + e) >> 1;
        add_edge(lc + N2, n + N2, 0);
        add_edge(rc + N2, n + N2, 0);
        build_revs(lc, b, mid);
        build_revs(rc, mid + 1, e);
    }

    void upd_forw(int n, int b, int e, int v, int i, int j, int w) {
        if (b > e || j < b || e < i) return;
        if (i <= b && e <= j) {
            add_edge(v, n + N, w); // v to [i, j]
            return;
        }
        int mid = (b + e) >> 1;
        upd_forw(lc, b, mid, v, i, j, w);
        upd_forw(rc, mid + 1, e, v, i, j, w);
    }

    void upd_revs(int n, int b, int e, int i, int j, int v, int w) {
        if (b > e || j < b || e < i) return;
        if (i <= b && e <= j) {
            add_edge(n + N2, v, w); // [i, j] to v
            return;
        }
        int mid = (b + e) >> 1;
        upd_revs(lc, b, mid, i, j, v, w);
        upd_revs(rc, mid + 1, e, i, j, v, w);
    }
};