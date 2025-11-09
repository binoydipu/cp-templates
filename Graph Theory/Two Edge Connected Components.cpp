/**
 *    author:   Binoy Barman
 *    created:  2025-11-09 14:48:58
**/

#include<bits/stdc++.h>
#ifdef LOCAL
#include "algo/debug.h"
#else
#define dbg(...) 42
#endif
using namespace std;
using ll = long long;
const int mod = 1e9 + 7;
const int inf = 2e9;

#define int long long
#define nl '\n'
#define all(v) v.begin(), v.end()
#define clg(x) (32 - __builtin_clz(x))
#define Testcase_Handler int tts, tc = 0; cin >> tts; hell: while(tc++ < tts)
#define uniq(v) sort(all(v)), v.resize(distance(v.begin(), unique(v.begin(), v.end())))
template<class T> using minheap = priority_queue<T, vector<T>, greater<T>>;
template<typename T> istream& operator>>(istream& in, vector<T>& a) {for(auto &x : a) in >> x; return in;};
template<typename T> ostream& operator<<(ostream& out, vector<T>& a) {bool first = true;for(auto &x : a) {if(!first) out << ' ';first = false;out << x;}return out;};

namespace Dark_Lord_Binoy {
inline void init() {
    ios::sync_with_stdio(false); 
    cin.tie(nullptr);

    #ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
}
}

template <typename T>
class graph {
  public:
    struct edge {
        int from;
        int to;
        T cost;
    };

    vector<edge> edges;
    vector<vector<int>> g;
    int n;

    graph() = default;
    graph(int _n) : n(_n) {
        g.resize(n + 1);
    }

    int add_edge(int from, int to, T cost = 1) {
        int id = (int) edges.size();
        g[from].push_back(id);
        g[to].push_back(id);
        edges.push_back({from, to, cost});
        return id;
    }

    void print_graph() {
      #ifdef LOCAL
        for (int v = 1; v <= n; v++) {
            cerr << "node " << v << " to=> ";
            for(auto id : g[v]) {
                auto &e = edges[id];
                int to = e.from ^ e.to ^ v;
                cerr << '(' << to << ", " << e.cost << ") ";
            }
            cerr << "\n";
        }
      #endif
    }

    graph<T> reverse() const {
        graph<T> rev(n);
        for(auto &e : edges) {
            rev.add_edge(e.to, e.from, e.cost);
        }
        return rev;
    }

    virtual ~graph() = default;
};

template <typename T>
class tecc_graph : public graph<T> {
  public:
    using graph<T>::edges;
    using graph<T>::g;
    using graph<T>::n;
    using edge = typename graph<T>::edge;

    vector<int> par;
    vector<int> lvl;
    vector<int> sz;
    vector<int> vis;
    vector<int> order;
    vector<int> comp; // component id for each node
    vector<int> dis; // discovery time
    vector<int> low; // lowest discovery time
    vector<edge> bridges; // edges, if removed -> disconnects the graph
    int timer = 0;
    int comps = 0;
    graph<T> tree; // tree of 2-edge-connected components
    // graph() = default; // add this line to graph template

    tecc_graph(int _n) : graph<T>(_n) {
        init();
    }

    void init() {
        par = vector<int>(n + 1, -1);
        lvl = vector<int>(n + 1, 0);
        sz = vector<int>(n + 1, 0);
        vis = vector<int>(n + 1, 0);
        comp = vector<int>(n + 1, -1);
        dis = vector<int>(n + 1, 0);
        low = vector<int>(n + 1, 0);
    }

    void dfs(int v) {
        dis[v] = low[v] = ++timer;
        vis[v] = 1;
        sz[v] = 1;
        order.push_back(v);
        bool parent_skipped = false;
        for(auto id : g[v]) {
            auto &e = edges[id];
            int to = e.from ^ e.to ^ v;
            if(to == par[v] && !parent_skipped) {
                parent_skipped = true;
                continue; // in case of multi edge to parent - skip once
            }
            if(vis[to] != 0) {
                low[v] = min(low[v], dis[to]); // using back edge
            } else {
                lvl[to] = 1 + lvl[v];
                par[to] = v;
                dfs(to);
                sz[v] += sz[to];
                low[v] = min(low[v], low[to]); // using child nodes
                if(low[to] > dis[v]) { // edge (v, to) is a bridge
                    bridges.push_back(e);
                }
            }
        }
    }

    void dfs2(int v, int num) {
        comp[v] = num;
        for(auto id : g[v]) {
            auto &e = edges[id];
            int to = e.from ^ e.to ^ v;
            if(comp[to] != -1) continue;
            if(low[to] > dis[v]) { // bridge found, new component
                comps++;
                dfs2(to, comps);
            } else { // same component
                dfs2(to, num);
            }
        }
    }

    void dfs_all() {
        for (int v = 1; v <= n; v++) {
            if (vis[v] == 0) {
                dfs(v);
                comps++;
                dfs2(v, comps);
            }
        }
    }

    void build_tree() {
        tree = graph<T>(comps);
        for(auto &e : bridges) {
            int u = comp[e.from], v = comp[e.to];
            tree.add_edge(u, v, e.cost);
        }
    }
};

int32_t main() {
    Dark_Lord_Binoy::init();
    int n, m;
    cin >> n >> m;
    tecc_graph<int> g(n);
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        u++, v++;
        g.add_edge(min(u, v), max(u, v));
    }
    g.dfs_all();
    g.build_tree();
    vector<vector<int>> ans(g.comps + 1);
    for (int i = 1; i <= n; i++) {
        ans[g.comp[i]].push_back(i);
    }
    cout << g.comps << nl;
    for (int i = 1; i <= g.comps; i++) {
        cout << ans[i].size();
        for(auto x : ans[i]) cout << ' ' << x - 1;
        cout << nl;
    }

    dbg(_Time_);
    return 0;
}

// https://judge.yosupo.jp/problem/two_edge_connected_components