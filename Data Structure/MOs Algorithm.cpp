const int N = 1e6 + 9, B = 440;

struct query {
    int l, r, id;
    bool operator < (const query &x) const {
        if(l / B == x.l / B) return ((l / B) & 1) ? r > x.r : r < x.r;
        return l / B < x.l / B;
    }
} Q[N];
int cnt[N], a[N];
long long odds; // no of odd elements [l, r]
inline void add_left(int i) {
    int x = a[i];
    odds = odds + (cnt[x] % 2 == 0 ? 1 : -1); // edit this
    ++cnt[x];
}
inline void add_right(int i) {
    int x = a[i];
    odds = odds + (cnt[x] % 2 == 0 ? 1 : -1);
    ++cnt[x];
}
inline void rem_left(int i) {
    int x = a[i];
    odds = odds + (cnt[x] % 2 == 0 ? 1 : -1);
    --cnt[x];
}
inline void rem_right(int i) {
    int x = a[i];
    odds = odds + (cnt[x] % 2 == 0 ? 1 : -1);
    --cnt[x];
}
long long ans[N];

void processQuery(int q) {
    for(int i = 1; i <= q; i++) {
        cin >> Q[i].l >> Q[i].r;
        Q[i].id = i;
    }
    sort(Q + 1, Q + q + 1); // sorting query optimally
    int l = 1, r = 0;
    for(int i = 1; i <= q; i++) {
        int L = Q[i].l, R = Q[i].r; 
        if(R < l) {
            while (l > L) add_left(--l);
            while (l < L) rem_left(l++);
            while (r < R) add_right(++r);
            while (r > R) rem_right(r--);
        } else {
            while (r < R) add_right(++r);
            while (r > R) rem_right(r--);
            while (l > L) add_left(--l);
            while (l < L) rem_left(l++);
        }
        ans[Q[i].id] = ((r - l + 1) - odds) / 2;
    }
}
int32_t main() {
    int n; cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    int q; cin >> q;
    processQuery(q); 
    for(int i = 1; i <= q; i++) cout << ans[i] << nl;
    return 0;
}