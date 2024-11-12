const int N = 2e5 + 9;

int a[N];
struct Dfs {
    int n;
    vector<int> lvl;
    vector<vector<int>> g;
    Dfs(int _n) : n (_n) {
        lvl.assign(n + 1, 0);
        g.assign(n + 1, vector<int>());
    }
    void addEdge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u); 
    }
    void dfs(int v, int p = -1) {
        for(auto u : g[v]) {
            if(u == p) continue;
            lvl[u] = 1 + lvl[v];
            dfs(u, v);
        }
    }
};