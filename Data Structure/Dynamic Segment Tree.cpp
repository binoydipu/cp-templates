class DynamicSegTree {
  private:
    struct Node {
        long long sum, lazy;
        Node *lc, *rc;
        Node() : sum(0), lazy(0) { lc = rc = NULL; }
    };
    struct Node *root; // root contains [1, n]
    const int n; // size of array

    inline void expand(Node *n) {
        if(!n->lc) n->lc = new Node();
        if(!n->rc) n->rc = new Node();
    }
    inline void push_lazy(Node *n, int b, int e) {
        if(n->lazy) {
            n->sum += (e - b + 1) * (n->lazy);
            if(n->lc) n->lc->lazy += n->lazy;
            if(n->rc) n->rc->lazy += n->lazy;
        }
        n->lazy = 0;
    }
    inline long long combine(long long a, long long b) {
        return a + b;
    }
    inline void pull(Node *n) {
        n->sum = n->lc->sum + n->rc->sum;
    }
    void update(Node *n, int b, int e, int i, int j, long long val) {
        expand(n);
        push_lazy(n, b, e);
        if (j < b || e < i) return;
        if (i <= b && e <= j) {
            n->lazy += val;
            push_lazy(n, b, e);
            return;
        }
        int mid = (b + e) >> 1;
        update(n->lc, b, mid, i, j, val);
        update(n->rc, mid + 1, e, i, j, val);
        pull(n);
    }
    long long query(Node *n, int b, int e, int i, int j) {
        if(!n) return 0;
        expand(n);
        push_lazy(n, b, e);
        if((!n) || i > e || b > j) return 0; //return null
        if (i <= b && e <= j) return n->sum;
        int mid = (b + e) >> 1;
        return combine(query(n->lc, b, mid, i, j), query(n->rc, mid + 1, e, i, j));
    }

  public:
    DynamicSegTree(int _n) : n(_n) { root = new Node(); }
    void range_upd(int L, int R, long long v) { 
        return update(root, 1, n, L, R, v); 
    }
    long long range_sum(int L, int R) { 
        return query(root, 1, n, L, R); 
    }
};