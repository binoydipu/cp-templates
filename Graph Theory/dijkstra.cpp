const int N = 2e5 + 9, inf = 2e9;

int a[N];
struct Dijkstra {
    int n;
    vector<bool> vis;
    vector<int> dis;
    vector<vector<pair<int, int>>> g;
    Dijkstra(int _n) : n (_n) {
        vis.assign(n + 1, false);
        dis.assign(n + 1, inf);
        g.assign(n + 1, vector<pair<int, int>>());
    }
    void addEdge(int u, int v, int w) {
        g[u].push_back({v, w}); // <node, weight>
        g[v].push_back({u, w});
    }
    void dijkstra(int st) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // minheap
        dis[st] = 0;
        pq.push({0, st}); // <distance, node>
        while(!pq.empty()) {
            int u = pq.top().second;
            pq.pop();
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