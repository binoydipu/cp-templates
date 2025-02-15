const int N = 3e5 + 9;
long long a[N];

class LazySegmentTree {
  private:
    #define lc (n << 1)
    #define rc ((n << 1) | 1)
    struct Node {
        int val, lazy;
        Node() : val(0), lazy(0) {}
        Node(int _val) : val(_val), lazy(0) {}
    };
    
    inline void push(int n, int b, int e) {
        if (t[n].lazy == 0) return;
        t[n].val = t[n].val + t[n].lazy * (e - b + 1);
        if (b != e) {
            t[lc].lazy = t[lc].lazy + t[n].lazy;
            t[rc].lazy = t[rc].lazy + t[n].lazy;
        }
        t[n].lazy = 0;
    }
    inline Node combine(const Node& a, const Node& b) {
        return Node(a.val + b.val);
    }
    inline void pull(int n) {
        t[n].val = t[lc].val + t[rc].val;
    }
    void build(int n, int b, int e) {
        t[n].lazy = 0;
        if (b == e) {
            t[n].val = a[b];
            return;
        }
        int mid = (b + e) >> 1;
        build(lc, b, mid);
        build(rc, mid + 1, e);
        pull(n);
    }
    void upd(int n, int b, int e, int i, int j, int v) {
        push(n, b, e);
        if (b > e || j < b || e < i) return;
        if (i <= b && e <= j) {
            t[n].lazy = v; // set lazy
            push(n, b, e);
            return;
        }
        int mid = (b + e) >> 1;
        upd(lc, b, mid, i, j, v);
        upd(rc, mid + 1, e, i, j, v);
        pull(n);
    }
    Node query(int n, int b, int e, int i, int j) {
        push(n, b, e);
        if (b > e || i > e || b > j) return Node(); // return null
        if (i <= b && e <= j) return t[n];
        int mid = (b + e) >> 1;
        return combine(query(lc, b, mid, i, j), query(rc, mid + 1, e, i, j));
    }

    const int root, tL, tR;
    vector<Node> t;

  public:
    LazySegmentTree(int b, int e) : root(1), tL(b), tR(e) {
        t.resize(4 * tR);
        build(root, tL, tR); 
    }
    void range_upd(int i, int j, int v) {
        upd(root, tL, tR, i, j, v);
    }
    int range_query(int i, int j) {
        return query(root, tL, tR, i, j).val;
    }
};