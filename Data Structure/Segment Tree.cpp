const int N = 3e5 + 9;

int a[N];
struct Node { // change this
    int val;
    Node() {
        val = 0;
    }
};
struct SegmentTree {
    #define lc (n << 1)
    #define rc ((n << 1) | 1)
    #define out INT_MIN // change this
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
            t[n].val = a[b];  // change this
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
            a[b] = x;
            return;
        }
        int mid = (b + e) >> 1;
        upd(lc, b, mid, i, x);
        upd(rc, mid + 1, e, i, x);
        pull(n);
    }
    Node query(int n, int b, int e, int i, int j) {
        if (b > j || e < i) { 
            Node x;
            x.val = out; 
            return x; // return approriate value
        }
        if (b >= i && e <= j) return t[n];
        int mid = (b + e) >> 1;
        return combine(query(lc, b, mid, i, j), query(rc, mid + 1, e, i, j));
    }
}t;