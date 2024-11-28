struct SCC {
    int n, scc;
    vector<int> vis;
    vector<vector<int>> g, gT, com;
    stack<int> st;
    SCC(int _n) : n (_n), scc (0) { // 1-indexed
        vis.assign(n + 1, 0);
        g.assign(n + 1, vector<int>());
        gT.assign(n + 1, vector<int>());
        com.assign(n + 1, vector<int>());
    }
    void addEdge(int u, int v) {
        g[u].push_back(v);
        gT[v].push_back(u); // reversed edges graph
    }
    void _dfs(int v) {
        vis[v] = 1;
        for(auto u : g[v]) {
            if(!vis[u]) {
                _dfs(u);
            }
        }
        st.push(v);
    }
    void _dfs2(int v) {
        vis[v] = 1;
        com[scc].push_back(v); // node v is in scc'th component
        for(auto u : gT[v]) {
            if(!vis[u]) {
                _dfs2(u);
            }
        }
    }
    vector<vector<int>> getComponents() {
        return com;
    }
    int getScc() {
        for (int i = 1; i <= n; i++) {
            if(!vis[i]) {
                _dfs(i);
            }
        }
        vis.assign(n + 1, 0);
        while(!st.empty()) {
            int u = st.top();
            st.pop();
            if(!vis[u]) {
                scc++;
                _dfs2(u);
            }
        }
        return scc; 
    }
};