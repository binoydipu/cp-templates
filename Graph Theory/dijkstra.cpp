vector<int> par;

template <typename T>
vector<T> dijkstra(const graph<T> &g, int start) {
    vector<T> dist(g.n + 1, numeric_limits<T>::max());
    par = vector<int>(g.n + 1, -1);
    vector<bool> vis(g.n + 1, false);
    priority_queue<pair<T, int>, vector<pair<T, int>>, greater<pair<T, int>>> q;
    dist[start] = 0;
    q.emplace(dist[start], start);

    while(!q.empty()) {
        int v = q.top().second;
        q.pop();
        if(vis[v]) continue; 
        vis[v] = true;
        for(auto id : g.g[v]) {
            auto &e = g.edges[id];
            int to = e.from ^ e.to ^ v; 
            if(dist[v] + e.cost < dist[to]) {
                dist[to] = dist[v] + e.cost;
                par[to] = v;
                q.emplace(dist[to], to);
            }
        }
    }
    return dist;
}

vector<int> find_shortest_path(int root, int to) { // dist[to] != inf
    assert(par.size() != 0);
    vector<int> path;
    for (int v = to; v != root; v = par[v]) path.push_back(v);
    path.push_back(root);
    reverse(path.begin(), path.end());
    return path;
}