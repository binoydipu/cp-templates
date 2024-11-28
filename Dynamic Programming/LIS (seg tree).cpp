const int N = 2e5 + 9;

int c[N];
struct Node { // change this
    int val;
    Node(): val (0) {}
    Node(int _val): val (_val) {}
};
struct SegmentTree {
    #define lc (n << 1)
    #define rc ((n << 1) | 1)
    #define out 0 // change this
    vector<Node> t;
    SegmentTree() {
        t.resize(4 * N);
    }
    inline void pull(int n) { // change this
        t[n].val = max(t[lc].val, t[rc].val);
    }
    inline Node combine(Node a, Node b) { // change this
        if(a.val == out) return b;
        if(b.val == out) return a;
        Node n;
        n.val = max(a.val, b.val);
        return n;
    }
    void build(int n, int b, int e) {
        if (b == e) {
            t[n].val = 0;  // change this
            return;
        }
        int mid = (b + e) >> 1;
        build(lc, b, mid);
        build(rc, mid + 1, e);
        pull(n);
    }
    void upd(int n, int b, int e, int i, int x) {
        if (b > i || e < i) return;
        if (b == e && b == i) {
            t[n].val = x; // update
            return;
        }
        int mid = (b + e) >> 1;
        upd(lc, b, mid, i, x);
        upd(rc, mid + 1, e, i, x);
        pull(n);
    }
    Node query(int n, int b, int e, int i, int j) {
        if (b > j || e < i) { 
            Node x(out);
            return x; // return approriate value
        }
        if (b >= i && e <= j) return t[n];
        int mid = (b + e) >> 1;
        return combine(query(lc, b, mid, i, j), query(rc, mid + 1, e, i, j));
    }
}t;

int LIS(int n) { // O(nlonn)
    t.build(1, 1, n);
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        auto cur = t.query(1, 1, n, 1, c[i] - 1);
        t.upd(1, 1, n, c[i], cur.val + 1);
        ans = max(ans, cur.val + 1);
    }
    return ans;
}