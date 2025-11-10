/**
 * Green Hackenbush (General Graph Version)
 *
 * Game rule summary:
 * - Two players alternately remove one edge.
 * - Any subgraph disconnected from the ground (root) disappears.
 * - The player unable to move (graph reduced to the root) loses.
 *
 * Goal:
 * - Compute the Grundy number of the graph (nim-equivalent value).
 *
 * Approach:
 * - Fuse all ground-connected vertices into one (Fusion Principle).
 * - Perform DFS (Tarjan’s algorithm) to find bridges.
 * - Bridges contribute "height + 1" to Grundy value (Colon Principle).
 * - Non-bridge edges (in cycles) XOR directly with their subgames.
 */

template <typename T>
class green_hackenbush {
  public:
    struct edge {
        int from;
        int to;
        T cost;
    };
    vector<edge> edges;
    vector<vector<int>> g;
    int n;

    vector<int> gr;  // gr[v] = 1 if vertex is ground-connected
    vector<int> dis; // discovery time
    vector<int> low; // lowest discovery time
    int timer = 0;
    int root = -1;   // representative of fused ground
    int base_xor = 0; // handles self-loops directly attached to ground

    green_hackenbush(int _n) : n(_n) {
        g.resize(n + 1);
        init();
    }

    void init() {
        gr = vector<int>(n + 1, 0);
        dis = vector<int>(n + 1, 0);
        low = vector<int>(n + 1, 0);
    }

    // Mark a vertex as ground and set it as root (fusion of all grounds)
    void ground(int v) {
        gr[v] = 1;
        if(root == -1) root = v;
    }

    void add_edge(int from, int to, T cost = 1) {
        int id = (int) edges.size();
        if(gr[from]) from = root;
        if(gr[to]) to = root;
        if(from == to) { base_xor ^= 1; return; }

        g[from].push_back(id);
        g[to].push_back(id);
        edges.push_back({from, to, cost});
    }

    int dfs(int v, int p = -1) {
        dis[v] = low[v] = ++timer;
        bool parent_skipped = false;
        int gnum = 0; // accumulated Grundy value for this subtree

        for(auto id : g[v]) {
            auto &e = edges[id];
            int to = e.from ^ e.to ^ v;
            if(to == p && !parent_skipped) {
                parent_skipped = true;
                continue; // in case of multi edge to parent - skip once
            }
            if(dis[to] != 0) {
                low[v] = min(low[v], dis[to]); // using back edge
            } else {
                int child_grundy = dfs(to, v);
                low[v] = min(low[v], low[to]); // using child nodes

                if(low[to] > dis[v]) {
                    // Bridge -> adds height + 1
                    gnum ^= (1 + child_grundy) ^ 1;
                } else {
                    // Cycle -> merge by XOR (Fusion inside component)
                    gnum ^= child_grundy;
                }
            }
        }
        // Count extra edges (cycles or parallels) that stay connected.
        // Each such edge adds one extra move -> XOR with 1.
        for(auto id : g[v]) {
            auto &e = edges[id];
            int to = e.from ^ e.to ^ v;
            if(to != p && dis[v] <= dis[to]) gnum ^= 1;
        }
        return gnum;
    }

    // Returns overall Grundy number of the graph
    int grundy() {
        return (root == -1) ? 0 : base_xor ^ dfs(root);
    }
};
