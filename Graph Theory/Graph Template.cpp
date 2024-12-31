template<class T> using minheap = priority_queue<T, vector<T>, greater<T>>;

const int N = 2e5 + 9;
int a[N];

class Graph {
  private:
    struct Edge {
        int to, w;
        Edge() : to(0), w(1) {}
        Edge(int _to) : to(_to), w(1) {}
        Edge(int _to, int _w) : to(_to), w(_w) {}
    };
    vector<vector<Edge>> g;
    vector<int> lvl, dis;
    vector<bool> vis;
    const int V;

  public: 
    Graph(int n) : lvl(n + 1, 0), vis(n + 1, 0), V(n) {
        g.assign(V + 1, vector<Edge>());
    }

    void add_edge(int u, int v, int w = 1) {
        g[u].push_back(Edge(v, w));
        g[v].push_back(Edge(u, w)); 
    }
    void dfs(int v, int p = -1) {
        vis[v] = true;
        for(auto adj : g[v]) if(!vis[adj.to]) {
            int to = adj.to, w = adj.w;
            lvl[to] = 1 + lvl[v];
            dfs(to, v);
        }
    }
    int bfs(int st) {
        vis.assign(V + 1, false);
        vis[st] = true;
        queue<int> q;
        q.push(st);
        int cnt = 0;

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            cnt++;
            for (auto adj : g[v]) if (!vis[adj.to]) {
                int to = adj.to, w = adj.w;
                vis[to] = true;
                lvl[to] = lvl[v] + 1;
                q.push(to);
            }
        }
        return cnt;
    }
    vector<int> dijkstra(int st) {
        dis.assign(V + 1, inf);
        vis.assign(V + 1, false);
        minheap<pair<int, int>> pq;

        dis[st] = 0;
        pq.push({0, st}); // <distance, node>

        while(!pq.empty()) {
            int v = pq.top().second;
            pq.pop();
            if(vis[v]) continue; 
            vis[v] = true;
            for (auto adj : g[v]) {
                int to = adj.to; 
                int cost = adj.w; 
                if (dis[v] + cost < dis[to]) {
                    dis[to] = dis[v] + cost;
                    pq.push({dis[to], to});
                }
            }
        }
        return dis;
    }
};