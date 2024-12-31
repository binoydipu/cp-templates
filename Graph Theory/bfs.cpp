const int N = 2e5 + 9;

int a[N];
struct Bfs {
    vector<vector<int>> g;
    vector<int> lvl;
    vector<bool> vis;

    Bfs(int n) : lvl(n + 1), vis(n + 1), g(n + 1) {}

    void add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u); 
    }
    void bfs(int root) {
        vis[root] = true;
        queue<int> q;
        q.push(root);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (auto u : g[v]) if (!vis[u]) {
                vis[u] = true;
                lvl[u] = lvl[v] + 1;
                q.push(u);
            }
        }
    }
};