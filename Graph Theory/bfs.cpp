const int N = 2e5 + 9;

int a[N];
struct Bfs {
    int n;
    vector<int> lvl;
    vector<bool> vis;
    vector<vector<int>> g;
    Bfs(int _n) : n (_n) {
        lvl.assign(n + 1, 0);
        vis.assign(n + 1, false);
        g.assign(n + 1, vector<int>());
    }
    void addEdge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u); 
    }
    void bfs(int st) {
        vis[st] = true;
        queue<int> q;
        q.push(st);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            dbg(v, lvl[v], a[v]);
            for (auto u : g[v]) if (!vis[u]) {
                vis[u] = true;
                lvl[u] = lvl[v] + 1;
                q.push(u);
            }
        }
    }
};