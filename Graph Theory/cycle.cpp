const int N = 5e5 + 9;

vector<pair<int, int>> g[N];
int vis[N], par[N], e_id[N];
vector<int> cycle; // simple cycle, contains edge ids

bool dfs(int u) {
    if (!cycle.empty()) return 1;
    vis[u] = 1;
    for (auto it : g[u]) {
        int v = it.first, id = it.second;
        if (vis[v] == 0) {
            par[v] = u;
            e_id[v] = id;
            if (dfs(v)) return 1;
        }
        else if (vis[v] == 1) {
            // cycle here
            cycle.push_back(id);
            for (int x = u; x != v; x = par[x]) {
                cycle.push_back(e_id[x]);
            }
            return 1;
        }
    }
    vis[u] = 2;
    return 0;
}