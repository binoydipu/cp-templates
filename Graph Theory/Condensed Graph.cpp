// eleminates loops (into a single node)
struct SCC {
    int n, scc;
    vector<int> vis;
    vector<vector<int>> g, gT, com;
    stack<int> st;
    bool sccDone;
    SCC(int _n) : n (_n), scc (0), sccDone (false) { // 1-indexed
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
        getScc();
        return com;
    }
    int getScc() {
        if(sccDone) return scc;
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
        sccDone = true;
        return scc; 
    }
    vector<vector<int>> getCondensedGraph() {
        getScc();
        vector<vector<int>> gC(n + 1, vector<int>());
        vector<int> par(n + 1, 0);
        for(auto component : com) { // all component nodes -> 1 node (par)
            if(component.empty()) continue;
            int root = *min_element(component.begin(), component.end());
            for(auto v : component) par[v] = root; 
        }
        for (int v = 1; v <= n; v++) {
            for(auto u : g[v]) {
                if(par[v] != par[u]) gC[par[v]].push_back(par[u]);
            }
        }
        return gC;
    }
};