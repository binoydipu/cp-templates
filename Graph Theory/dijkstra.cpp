template<class T> using minheap = priority_queue<T, vector<T>, greater<T>>;
const int inf = 2e9;

struct Dijkstra {
    vector<vector<pair<int, int>>> g;
    vector<bool> vis;
    vector<int> dis;

    Dijkstra(int n) : vis(n + 1), dis(n + 1, inf), g(n + 1) {}

    void add_edge(int u, int v, int w) {
        g[u].push_back({v, w}); // <node, weight>
        g[v].push_back({u, w});
    }
    void dijkstra(int root) {
        minheap<pair<int, int>> pq;
        dis[root] = 0;
        pq.push({0, root}); // <distance, node>
        while(!pq.empty()) {
            int u = pq.top().second; pq.pop();
            if(vis[u]) continue; 
            vis[u] = true;
            for(auto adj : g[u]) {
                int v = adj.first; 
                int cost = adj.second; 
                if(dis[u] + cost < dis[v]) {
                    dis[v] = dis[u] + cost;
                    pq.push({dis[v], v});
                }
            }
        }
    }
};