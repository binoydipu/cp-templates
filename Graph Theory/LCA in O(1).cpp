template <class T>
struct RMQ { // 0-based
    vector<vector<T>> rmq;
    T kInf = numeric_limits<T>::max();
    void build(const vector<T>& V) {
        int n = V.size(), on = 1, dep = 1;
        while (on < n) on *= 2, ++dep;
        rmq.assign(dep, V);
    
        for (int i = 0; i < dep - 1; i++) {
            for (int j = 0; j < n; j++) {
                rmq[i + 1][j] = min(rmq[i][j], rmq[i][min(n - 1, j + (1 << i))]);
            }
        }
    }
    T query(int a, int b) { // [a, b)
        if (b <= a) return kInf;
        int dep = 31 - __builtin_clz(b - a); // log(b - a)
        return min(rmq[dep][a], rmq[dep][b - (1 << dep)]);
    }
};

struct LCA { // 0-based
    vector<int> tin, depth, tout;
    vector<vector<int>> G;
    vector<pair<int, int>> linear;
    RMQ<pair<int, int>> rmq;
    int timer = 0;
    
    LCA() {} 
    LCA(int n) : tin(n, -1), tout(n, -1), depth(n), G(n), linear(2 * n) {}

    void dfs(int v, int dep) {
        linear[timer] = {dep, v};
        tin[v] = timer++;
        depth[v] = dep;
        for (auto u : G[v]){
            if (tin[u] == -1) {
                dfs(u, dep + 1);
                linear[timer++] = {dep, v};
            }
        }
        tout[v] = timer;
    }
    void add_edge(int a, int b) {
        G[a].push_back(b);
        G[b].push_back(a);
    }
    void build(int root) {
        dfs(root, 0);
        rmq.build(linear);
    }
    int _query(int a, int b) {
        a = tin[a], b = tin[b];
        return rmq.query(min(a, b), max(a, b) + 1).second;
    }
    int dist(int a, int b) {
        return depth[a] + depth[b] - 2 * depth[_query(a, b)];
    }
};
