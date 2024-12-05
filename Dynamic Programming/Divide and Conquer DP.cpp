const int N = 1e5 + 5;

int m, n; // 20, 1e5
vector<long long> dp_before, dp_cur;

long long costOf(int l, int r) {} // edit this
// compute dp_cur[l], ... dp_cur[r] (inclusive)
void compute(int l, int r, int optl, int optr) {
    if (l > r) return;
    int mid = (l + r) >> 1;
    pair<long long, int> best = {LLONG_MAX, -1};

    for (int k = optl; k <= min(mid, optr); k++) {
        best = min(best, {(k ? dp_before[k - 1] : 0) + costOf(k, mid), k});
    }
    dp_cur[mid] = best.first;
    int opt = best.second;

    compute(l, mid - 1, optl, opt);
    compute(mid + 1, r, opt, optr);
}

long long solve() { // 1-indexed
    dp_before.assign(n + 1, 0); 
    dp_cur.assign(n + 1, 0);
    for (int i = 1; i <= n; i++) dp_before[i] = costOf(1, i);
    for (int i = 2; i <= m; i++) {
        compute(1, n, 1, n);
        dp_before = dp_cur;
    }
    return dp_before[n];
}