class SparseTable {
  public:
    int n, max_log;
    vector<vector<int>> mat; // 1-indexed

    inline int func(int l, int r) {
        return max(l, r);
    }

    SparseTable(const vector<int>& a) : n((int) a.size()) {
        max_log = 32 - __builtin_clz(n);
        mat.resize(n + 1, vector<int>(max_log));
        for (int i = 1; i <= n; i++) mat[i][0] = a[i - 1];
        for (int k = 1; k < max_log; k++) {
            for (int i = 1; i + (1 << k) - 1 <= n; i++) {
                mat[i][k] = func(mat[i][k - 1], mat[i + (1 << (k - 1))][k - 1]);
            }
        }
    }

    // idempotent - to get max, min, gcd, and, or; -> O(1)
    int query(int from, int to) {
        int k = 31 - __builtin_clz(to - from + 1);
        return func(mat[from][k], mat[to - (1 << k) + 1][k]);
    }

    // non-idempotent - to get sum, count, lcm, xor -> O(logn)
    int query2(int from, int to) {
        int res = -1; // neutral value
        for (int k = max_log - 1; k >= 0; k--) {
            if((1 << k) <= to - from + 1) {
                res = func(res, mat[from][k]);
                from += (1 << k);
            }
        }
        return res;
    }
};