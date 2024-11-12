/*
  all the edges should be in the same connected component
  #directed graph: euler path: for all -> indeg = outdeg or nodes having indeg > outdeg = outdeg > indeg = 1 and for others in = out
  #directed graph: euler circuit: for all -> indeg = outdeg
*/

// euler path in a directed graph
// it also finds circuit if it exists
struct Euler {
    int n, edges;
    vector<int> done, path, in, out;
    vector<vector<int>> g;
    Euler(int _n, int _edges) : n (_n), edges (_edges) {
        done.assign(n + 1, 0);
        in.assign(n + 1, 0);
        out.assign(n + 1, 0);
        g.assign(n + 1, vector<int>());
    }
    void addEdge(int u, int v) {
        g[u].push_back(v);
        out[u]++, in[v]++;
    }
    void dfs(int u) {
        while(done[u] < g[u].size()) {
            int v = g[u][done[u]++];
            dfs(v);
        }
        path.push_back(u);
    }
    bool hasEulerPath() {
        path.clear();
        int cnt1 = 0, cnt2 = 0, root = -1;
        for (int i = 1; i <= n; i++) {
            if(in[i] - out[i] == 1) cnt1++;
            if(out[i] - in[i] == 1) cnt2++, root = i;
            if(abs(in[i] - out[i] > 1)) return false;
        }
        if(cnt1 > 1 || cnt2 > 1) return false;
        if(root == -1) { // all in == out degree's
            for (int i = 1; i <= n; i++) if(out[i]) { root = i; break; }
        }
        if(root == -1) return true; // empty graph
        dfs(root);
        if(path.size() != edges + 1) return false; // connectivity issue
        reverse(path.begin(), path.end());
        return true;
    }
    vector<int> getEulerPath() {
        if(hasEulerPath()) return path;
        return {};
    }
};
