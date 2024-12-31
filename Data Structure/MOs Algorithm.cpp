const int N = 1e6 + 9, B = 440;

struct Query {
    int l, r, id;
    Query() {}
    Query(int _id, int _l, int _r) : id(_id), l(_l), r(_r) {}
    bool operator<(const Query& other) const {
        if(l / B == other.l / B) return ((l / B) & 1) ? r > other.r : r < other.r;
        return l / B < other.l / B;
    }
} Q[N];

int cnt[N], a[N];
long long uniq; // no of distinct elements [l, r]

inline void add_left(int i) {
    int x = a[i];
    ++cnt[x];
    uniq += (cnt[x] == 1);
}
inline void add_right(int i) {
    int x = a[i];
    ++cnt[x];
    uniq += (cnt[x] == 1);
}
inline void rem_left(int i) {
    int x = a[i];
    uniq -= (cnt[x] == 1);
    --cnt[x];
}
inline void rem_right(int i) {
    int x = a[i];
    uniq -= (cnt[x] == 1);
    --cnt[x];
}
int get_ans(int l, int r) { // edit this
    return uniq;
}

long long ans[N];

void processQ(int q) {
    sort(Q + 1, Q + q + 1);
    int curL = 1, curR = 0;
    for(int i = 1; i <= q; i++) {
        int ql = Q[i].l, qr = Q[i].r; 
        if(qr < curL) {
            while (curL > ql) add_left(--curL);
            while (curL < ql) rem_left(curL++);
            while (curR < qr) add_right(++curR);
            while (curR > qr) rem_right(curR--);
        } else {
            while (curR < qr) add_right(++curR);
            while (curR > qr) rem_right(curR--);
            while (curL > ql) add_left(--curL);
            while (curL < ql) rem_left(curL++);
        }
        ans[Q[i].id] = get_ans(curL, curR);
    }
}