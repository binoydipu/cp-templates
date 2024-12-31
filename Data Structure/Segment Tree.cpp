const int N = 1e6 + 9;

class SegmentTree {
  private:
    #define lc (n << 1)
    #define rc ((n << 1) | 1)
    struct Node { // change this
        int val;
        Node() : val(0) {}
        Node(int _val) : val(_val) {}
    };
    
    inline void pull(int n) { // change this
        t[n].val = (t[lc].val + t[rc].val);
    }
    inline Node combine(const Node& a, const Node& b) { // change this
        return Node(a.val + b.val);
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
        if (b > e || b > i || e < i) return;
        if (b == e && b == i) {
            t[n].val += x; // update
            return;
        }
        int mid = (b + e) >> 1;
        upd(lc, b, mid, i, x);
        upd(rc, mid + 1, e, i, x);
        pull(n);
    }
    Node query(int n, int b, int e, int i, int j) {
        if (b > e || b > j || e < i) return Node(); // return null
        if (b >= i && e <= j) return t[n];
        int mid = (b + e) >> 1;
        return combine(query(lc, b, mid, i, j), query(rc, mid + 1, e, i, j));
    }

    const int root, tL, tR;
    vector<Node> t;

  public:
    SegmentTree(int b, int e) : root(1), tL(b), tR(e) {
        t.resize(4 * tR);
        build(root, tL, tR);
    }
    void point_upd(int i, int x) {
        upd(root, tL, tR, i, x);
    }
    int range_query(int i, int j) {
        return query(root, tL, tR, i, j).val;
    }
};