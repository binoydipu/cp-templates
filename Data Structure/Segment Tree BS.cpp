class SegmentTree {
  private:
    #define lc (n << 1)
    #define rc ((n << 1) | 1)
    struct node {
        int val, add;
        bool neg = false;
        node() : val(0), add(0) {}
        node(int _val, int _add = 0) : val(_val), add(_add) {}
        
        void apply(int b, int e, int v) { // change this
            val = (e - b + 1) * v;
            neg = (val < 0);
            if(b != e) add += v; // add lazy
        }
    };
    
    node unite(const node& a, const node& b) { // change this
        node res;
        res.val = a.val + b.val;
        res.neg = (a.neg | (res.val < 0));
        return res;
    }

    inline void push(int n, int b, int e) {
        if(tree[n].add != 0) {
            int mid = (b + e) >> 1;
            tree[lc].apply(b, mid, tree[n].add);
            tree[rc].apply(mid + 1, e, tree[n].add);
            tree[n].add = 0;
        }
    }

    inline void pull(int n) {
        tree[n] = unite(tree[lc], tree[rc]);
    }

    void build(int n, int b, int e) {
        if (b == e) {
            return;
        }
        int mid = (b + e) >> 1;
        build(lc, b, mid);
        build(rc, mid + 1, e);
        pull(n);
    }

    template <typename M>
    void build(int n, int b, int e, const vector<M> &v) {
        if (b == e) {
            tree[n].apply(b, e, v[b - 1]);
            return;
        }
        int mid = (b + e) >> 1;
        build(lc, b, mid, v);
        build(rc, mid + 1, e, v);
        pull(n);
    }

    node query(int n, int b, int e, int i, int j) {
        if (b >= i && e <= j) {
            return tree[n];
        }
        int mid = (b + e) >> 1;
        push(n, b, e);
        node res;
        if(j <= mid) {
            res = query(lc, b, mid, i, j);
        } else {
            if(i > mid) {
                res = query(rc, mid + 1, e, i, j);
            } else {
                res = unite(query(lc, b, mid, i, j), query(rc, mid + 1, e, i, j));
            }
        }
        pull(n);
        return res;
    }

    template <typename M>
    void modify(int n, int b, int e, int i, int j, const M& v) {
        if (i <= b && e <= j) {
            tree[n].apply(b, e, v);
            return;
        }
        int mid = (b + e) >> 1;
        push(n, b, e);
        if(i <= mid) {
            modify(lc, b, mid, i, j, v);
        }
        if(j > mid) {
            modify(rc, mid + 1, e, i, j, v);
        }
        pull(n);
    }

    int find_first_knowingly(int n, int b, int e, const function<bool(const node&)> &func) {
        if(b == e) {
            return b;
        }
        push(n, b, e);
        int mid = (b + e) >> 1;
        int res;
        if(func(tree[lc])) {
            res = find_first_knowingly(lc, b, mid, func);
        } else {
            res = find_first_knowingly(rc, mid + 1, e, func);
        }
        pull(n);
        return res;
    }

    int find_first(int n, int b, int e, int i, int j, const function<bool(const node&)> &func) {
        if(i <= b && e <= j) {
            if(!func(tree[n])) {
                return -1;
            }
            return find_first_knowingly(n, b, e, func);
        }
        push(n, b, e);
        int mid = (b + e) >> 1;
        int res = -1;
        if(i <= mid) {
            res = find_first(lc, b, mid, i, j, func);
        }
        if(j > mid && res == -1) {
            res = find_first(rc, mid + 1, e, i, j, func);
        }
        pull(n);
        return res;
    }

    int find_last_knowingly(int n, int b, int e, const function<bool(const node&)> &func) {
        if(b == e) {
            return b;
        }
        push(n, b, e);
        int mid = (b + e) >> 1;
        int res;
        if(func(tree[rc])) {
            res = find_last_knowingly(rc, mid + 1, e, func);
        } else {
            res = find_last_knowingly(lc, b, mid, func);
        }
        pull(n);
        return res;
    }

    int find_last(int n, int b, int e, int i, int j, const function<bool(const node&)> &func) {
        if(i <= b && e <= j) {
            if(!func(tree[n])) {
                return -1;
            }
            return find_last_knowingly(n, b, e, func);
        }
        push(n, b, e);
        int mid = (b + e) >> 1;
        int res = -1;
        if(j > mid) {
            res = find_last(rc, mid + 1, e, i, j, func);
        }
        if(i <= mid && res == -1) {
            res = find_last(lc, b, mid, i, j, func);
        }
        pull(n);
        return res;
    }

    int N;
    vector<node> tree;

  public:
    SegmentTree(int _n) : N(_n) {
        tree.resize(4 * N);
        build(1, 1, N);
    }
    
    template <typename M>
    SegmentTree(const vector<M> &v) {
        N = v.size();
        tree.resize(4 * N);
        build(1, 1, N, v);
    }

    node query(int l, int r) {
        assert(1 <= l && l <= r && r <= N);
        return query(1, 1, N, l, r);
    }

    node query(int id) {
        assert(1 <= id && id <= N);
        return query(1, 1, N, id, id);
    }

    template <typename M>
    void modify(int l, int r, const M& v) {
        assert(1 <= l && l <= r && r <= N);
        modify(1, 1, N, l, r, v);
    }

    // returns first index where func returns true
    int find_first(int l, int r) {
        assert(1 <= l && l <= r && r <= N);
        auto func = [](const node &a) {
            return a.neg;
        };
        return find_first(1, 1, N, l, r, func);
    }
    // returns last index where func returns true
    int find_last(int l, int r) {
        assert(1 <= l && l <= r && r <= N);
        auto func = [](const node &a) {
            return a.neg;
        };
        return find_last(1, 1, N, l, r, func);
    }
};