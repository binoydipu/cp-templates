template <typename T>
class dfs_graph : public graph<T> {
  public:
    using graph<T>::edges;
    using graph<T>::g;
    using graph<T>::n;

    vector<int> par;
    vector<int> lvl;
    vector<int> sz;
    vector<int> vis;
    vector<int> order;

    dfs_graph(int _n) : graph<T>(_n) {
        init();
    }

    void init() {
        par = vector<int>(n + 1, -1);
        lvl = vector<int>(n + 1, 0);
        sz = vector<int>(n + 1, 0);
        vis = vector<int>(n + 1, 0);
    }

    void dfs(int v) {
        vis[v] = 1; 
        sz[v] = 1;
        order.push_back(v);
        for(auto id : g[v]) {
            auto &e = edges[id];
            int to = e.from ^ e.to ^ v;
            if(vis[to] != 0) {
                continue;
            }
            lvl[to] = 1 + lvl[v];
            par[to] = v;
            dfs(to);
            sz[v] += sz[to];
        }
    }

    void dfs_all() {
        for (int v = 1; v <= n; v++) {
            if (vis[v] == 0) {
                dfs(v);
            }
        }
    }
};