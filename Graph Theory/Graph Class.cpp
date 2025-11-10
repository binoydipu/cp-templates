template <typename T>
class graph {
  public:
    struct edge {
        int from;
        int to;
        T cost;
    };

    vector<edge> edges;
    vector<vector<int>> g;
    int n;

    graph() = default;
    graph(int _n) : n(_n) {
        g.resize(n + 1);
    }

    int add_edge(int from, int to, T cost = 1) {
        int id = (int) edges.size();
        g[from].push_back(id);
        g[to].push_back(id);
        edges.push_back({from, to, cost});
        return id;
    }

    void print_graph() {
        for (int v = 1; v <= n; v++) {
            cerr << "node " << v << " to=> ";
            for(auto id : g[v]) {
                auto &e = edges[id];
                int to = e.from ^ e.to ^ v;
                cerr << '(' << to << ", " << e.cost << ") ";
            }
            cerr << "\n";
        }
    }

    graph<T> reverse() const {
        graph<T> rev(n);
        for(auto &e : edges) {
            rev.add_edge(e.to, e.from, e.cost);
        }
        return rev;
    }

    virtual ~graph() = default;
};