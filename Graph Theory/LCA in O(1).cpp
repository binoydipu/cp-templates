template <typename T> 
class lca_graph : public graph<T> {
  public:
    using graph<T>::edges;
    using graph<T>::g;
    using graph<T>::n;

    int max_depth;
    vector<int> start; // enter time
    vector<int> end; // exit time
    vector<int> depth;
    vector<int> sz;
    vector<vector<int>> par;
    vector<vector<int>> rmq;
    vector<int> linear;

    lca_graph(int _n) : graph<T>(_n) {
        max_depth = 31 - __builtin_clz(_n);
    }

  private:
    void build_rmq() {
        int len = linear.size() - 1, dep = 0;
        while((1 << dep) <= len) dep++; // log2(len)
        rmq.resize(len + 1, vector<int>(dep));

        for (int i = 1; i <= len; i++) rmq[i][0] = linear[i];
        for (int k = 1; k < dep; k++) {
            for (int i = 1; i + (1 << k) - 1 <= len; i++) {
                int u = rmq[i][k - 1], v = rmq[i + (1 << (k - 1))][k - 1];
                rmq[i][k] = depth[u] < depth[v] ? u : v;
            }
        }
    }

    int query(int from, int to) {
        int k = 31 - __builtin_clz(to - from + 1);
        int u = rmq[from][k], v = rmq[to - (1 << k) + 1][k];
        return depth[u] < depth[v] ? u : v;
    }

    void dfs(int v) {
        start[v] = (int)linear.size();
        linear.push_back(v);
        sz[v] = 1;
        for(int id : g[v]) {
            auto &e = edges[id];
            int to = e.from ^ e.to ^ v;
            if(start[to] != -1) { // visited
                continue;
            }
            depth[to] = 1 + depth[v];
            dfs(to);
            sz[v] += sz[to];
            linear.push_back(v);
        }
        end[v] = (int)linear.size() - 1;
    }

  public:
    void build_lca(int from) {
        start = vector<int>(n + 1, -1);
        end = vector<int>(n + 1, -1);
        depth = vector<int>(n + 1, 0);
        sz = vector<int>(n + 1, 0);
        linear = vector<int>(1, -1);
        par = vector<vector<int>>(n + 1, vector<int>(max_depth + 1));
        dfs(from);
        build_rmq();
    }

    inline int lca(int u, int v) { // O(1)
        u = start[u], v = start[v];
        return query(min(u, v), max(u, v));
    }

    inline int dist(int u, int v) {
        int l = lca(u, v);
        return depth[u] + depth[v] - (depth[l] << 1);
    }

    inline bool is_ancestor(int u, int v) { // v... -> u
        assert(u != v);
        return start[v] < start[u] && end[v] > end[u];
    }
};