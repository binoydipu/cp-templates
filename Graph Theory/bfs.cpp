template <typename T>
class bfs_graph : public graph<T> {
  public:
    using graph<T>::edges;
    using graph<T>::g;
    using graph<T>::n;

    vector<int> par;
    vector<int> lvl;
    vector<int> sz;
    vector<int> vis;
    vector<int> order;

    bfs_graph(int _n) : graph<T>(_n) {
        init();
    }

    void init() {
        par = vector<int>(n + 1, -1);
        lvl = vector<int>(n + 1, 0);
        sz = vector<int>(n + 1, 0);
        vis = vector<int>(n + 1, 0);
    }

    void bfs(int root) {
        vis[root] = 1;
        queue<int> q;
        q.push(root);

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            sz[v] = 1;
            order.push_back(v);
            for (auto id : g[v]) {
                auto &e = edges[id];
                int to = e.from ^ e.to ^ v;
                if(vis[to] != 0) {
                    continue;
                }
                vis[to] = 1;
                par[to] = v;
                lvl[to] = lvl[v] + 1;
                q.push(to);
            }
        }

        // calculate subtree size
        for (int i = order.size() - 1; i >= 0; i--) {
            int v = order[i];
            if (par[v] != -1) {
                sz[par[v]] += sz[v];
            }
        }
    }

    void bfs_all() {
        for (int v = 1; v <= n; v++) {
            if (vis[v] == 0) {
                bfs(v);
            }
        }
    }
};