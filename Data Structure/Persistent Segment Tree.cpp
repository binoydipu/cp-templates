const int N = 1e5 + 9;

long long a[N];
class PersistentSegTree {
  private:
    struct Node {
        int val;
        Node *lc, *rc;
        Node() : val(0) { lc = rc = NULL; }
        Node(int _val) : val(_val) { lc = rc = NULL; }
    } *ver[N];

    inline int combine(int a, int b) {
        return a + b;
    }
    inline void pull(Node *n) {
        n->val = n->lc->val + n->rc->val;
    }
    Node* build(int b, int e) {
        if(b == e) {
            Node *n = new Node(); // in leaf
            return n;
        }
        Node *n = new Node();
        int mid = (b + e) >> 1;

        n->lc = build(b, mid);
        n->rc = build(mid + 1, e);
        pull(n);
        return n;
    }
    Node* update(Node *n, int b, int e, int i, int v) {
        if(b == e) {
            Node *cn = new Node(n->val + v); // new leaf
            return cn;
        }
        Node *cn = new Node();
        int mid = (b + e) >> 1;

        if(i <= mid) {
            cn->lc = update(n->lc, b, mid, i, v);
            cn->rc = n->rc;
        } else {
            cn->lc = n->lc;
            cn->rc = update(n->rc, mid + 1, e, i, v);
        }
        pull(cn);
        return cn;
    }
    int query1(Node *R, Node *L, int b, int e, int k) {
        if(b == e) return b;
        int mid = (b + e) >> 1;
        int leftval = R->lc->val - L->lc->val;
        if(k <= leftval) {
            return query1(R->lc, L->lc, b, mid, k);
        } else {
            return query1(R->rc, L->rc, mid + 1, e, k - leftval);
        }
    }
    int query2(Node *R, Node *L, int b, int e, int i, int j) {
        if(i > e || b > j) return 0; //return null
        if (i <= b && e <= j) return R->val - L->val;
        int mid = (b + e) >> 1;
        return combine(query2(R->lc, L->lc, b, mid, i, j), query2(R->rc, L->rc, mid + 1, e, i, j));
    }

    const int tL, tR; // total [1, n]
    vector<Node *> nodes; // store all created nodes, to delete

  public:
    PersistentSegTree(int b, int e) : tL(b), tR(e) { ver[0] = build(b, e); }

    ~PersistentSegTree() {}

    // takes current version, generates new version from prev for current prefix, pos: freq+=v
    void point_upd(int cur_ver, int pos, int v) {
        ver[cur_ver] = update(ver[cur_ver - 1], tL, tR, pos, v); 
    }
    // takes r and (l-1)th version nodes, finds k-th minimum in range [l, r]
    int find_kth(int r_ver, int l_ver, int k) {
        return query1(ver[r_ver], ver[l_ver], tL, tR, k);
    }
    // takes r and (l-1)th version nodes, finds number of elements in range [i, j]
    int find_elements(int r_ver, int l_ver, int i, int j) {
        return query2(ver[r_ver], ver[l_ver], tL, tR, i, j);
    }
};