// graph must be DAG - Directed Acyclic Graph
int n;
const int N = 2e5 + 5;
vector<int> g[N]; vector<bool> vis; vector<int> ts;

void dfs(int u) {
    vis[u] = true;
    for(auto v : g[u]) {
        if(!vis[v]) {
            dfs(v);
        }
    }
    ts.push_back(u);
}
void topSort() {
    vis.assign(n + 1, false);
    ts.clear();
    for (int i = 1; i <= n; i++) {
        if(!vis[i]) {
            dfs(i);
        }
    }
    reverse(ts.begin(), ts.end());
}