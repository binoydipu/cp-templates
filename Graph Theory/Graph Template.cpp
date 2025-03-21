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

    graph(int _n) : n(_n) {
        g.resize(n + 1);
    }

    int add_edge(int from, int to, T cost = 1) {
        int id = (int) edges.size();
        g[from].push_back(to);
        g[to].push_back(from);
        edges.push_back({from, to, cost});
        return id;
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

template <typename T>
class Dfs : public graph<T> {
  public:
    using graph<T>::edges;
    using graph<T>::g;
    using graph<T>::n;

    vector<int> lvl;
    vector<bool> vis;

    Dfs(int _n) : graph<T>(_n), lvl(_n + 1, 0), vis(_n + 1, false) {}

    void reset() {
        fill(lvl.begin(), lvl.end(), 0);
        fill(vis.begin(), vis.end(), false);
    }

    void dfs(int u, int p = -1) {
        vis[u] = true;
        for(auto v : g[u]) {
            if(vis[v]) continue;
            dfs(v, u);
        }
    }

    void dfs_all() {
        fill(vis.begin(), vis.end(), false);
        for (int v = 1; v <= n; v++) {
            if (!vis[v]) {
                dfs(v);
            }
        }
    }
};