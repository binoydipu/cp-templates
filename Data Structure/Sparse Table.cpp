const int N = 1e5 + 9;

int a[N];
struct SparseTable {
    int t[N][18][2], logs[N];
    SparseTable() {
        memset(t, 0, sizeof t);
        memset(logs, 0, sizeof logs);
        for (int i = 2; i < N; i++) logs[i] = logs[i >> 1] + 1;
    }
    void build(int n) { // O(nlogn)
        for(int i = 1; i <= n; i++) t[i][0][0] = t[i][0][1] = a[i];
        for(int k = 1; k < 18; k++) {
            for(int i = 1; i + (1 << k) - 1 <= n; i++) {
                t[i][k][0] = min(t[i][k - 1][0], t[i + (1 << (k - 1))][k - 1][0]);
                t[i][k][1] = max(t[i][k - 1][1], t[i + (1 << (k - 1))][k - 1][1]);
            }
        }
    }
    int minQuery(int l, int r) { // O(1)
        // int k = 31 - __builtin_clz(r - l + 1);
        int k = logs[r - l + 1];
        return min(t[l][k][0], t[r - (1 << k) + 1][k][0]);
    }
    int maxQuery(int l, int r) { // O(1)
        int k = logs[r - l + 1];
        return max(t[l][k][1], t[r - (1 << k) + 1][k][1]);
    }
}st;