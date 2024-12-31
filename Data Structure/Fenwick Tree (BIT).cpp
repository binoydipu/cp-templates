template <class T>
struct FenwickTree {
    int n; vector<T> bit;
    FenwickTree() {}
    FenwickTree(int _n) : n(_n) {
        bit.assign(n + 1, 0);
    }
    FenwickTree(const vector<T> &a) : FenwickTree(a.size()) {
        for (int i = 1; i <= n; i++) upd(i, a[i]);
    }
    T query(int i) {
        T ans = 0;
        for (; i >= 1; i -= (i & -i)) ans += bit[i];
        return ans;
    }
    void upd(int i, T val) {
        if (i <= 0) return;
        for (; i <= n; i += (i & -i)) bit[i] += val;
    }
    void upd(int l, int r, T val) {
        upd(l, val);
        upd(r + 1, -val);
    }
    T query(int l, int r) {
        return query(r) - query(l - 1);
    }
};