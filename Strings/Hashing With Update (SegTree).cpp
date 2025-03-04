const int N = 2e5 + 9;

long long power(long long a, long long b, int mod) {
    long long res = 1 % mod;
    a = (a + mod) % mod;
    while (b) {
        if (b & 1) res = (res * a) % mod;
        a = (a * a) % mod;
        b >>= 1;
    }
    return res;
}

using T = pair<int, int>;
const T MOD = {127657753, 987654319};
const T P = {137, 277};

T operator+(T a, int x) { return {(a.first + x) % MOD.first, (a.second + x) % MOD.second}; }
T operator+(T a, T x) { return {(a.first + x.first) % MOD.first, (a.second + x.second) % MOD.second}; }
T operator-(T a, int x) { return {(a.first - x + MOD.first) % MOD.first, (a.second - x + MOD.second) % MOD.second}; }
T operator-(T a, T x) { return {(a.first - x.first + MOD.first) % MOD.first, (a.second - x.second + MOD.second) % MOD.second}; }
T operator*(T a, int x) { return {(1LL * a.first * x) % MOD.first, (1LL * a.second * x) % MOD.second}; }
T operator*(T a, T x) { return {(1LL * a.first * x.first) % MOD.first, (1LL * a.second * x.second) % MOD.second}; }
ostream &operator<<(ostream &os, T hash) { return os << "(" << hash.first << ", " << hash.second << ")"; }

T pw[N], ipw[N];
T invP;

void prec() {
    pw[0] = {1, 1};
    for (int i = 1; i < N; i++) {
        pw[i] = pw[i - 1] * P;
    }
    invP = {power(P.first, MOD.first - 2, MOD.first), power(P.second, MOD.second - 2, MOD.second)};
    ipw[0] = {1, 1};
    for (int i = 1; i < N; i++) {
        ipw[i] = ipw[i - 1] * invP;
    }
}

// String Hashing with Segment tree, allows point update
class Hashing {
  private:
    #define lc (n << 1)
    #define rc ((n << 1) | 1)
    struct Node {
          T forw, rev;
          Node() : forw(0, 0), rev(0, 0) {}
          Node(T _forw, T _rev) : forw(_forw), rev(_rev) {}
    };
    
    inline Node merge(const Node& L, const Node& R) {
        return Node(L.forw + R.forw, L.rev + R.rev);
    }
    void build(int n, int b, int e) {
        if (b == e) {
            t[n].forw = pw[b] * s[b];
            t[n].rev = pw[tR - b + 1] * s[b];
            return;
        }
        int mid = (b + e) >> 1;
        build(lc, b, mid);
        build(rc, mid + 1, e);
        t[n] = merge(t[lc], t[rc]);
    }
    void upd(int n, int b, int e, int i, char ch) {
        if (b > e || b > i || e < i) return;
        if (b == e && b == i) {
            t[n].forw = pw[b] * ch;
            t[n].rev = pw[tR - b + 1] * ch;
            return;
        }
        int mid = (b + e) >> 1;
        upd(lc, b, mid, i, ch);
        upd(rc, mid + 1, e, i, ch);
        t[n] = merge(t[lc], t[rc]);
    }
    Node query(int n, int b, int e, int i, int j) {
        if (b > e || b > j || e < i) return Node(); // return null
        if (b >= i && e <= j) return t[n];
        int mid = (b + e) >> 1;
        return merge(query(lc, b, mid, i, j), query(rc, mid + 1, e, i, j));
    }

    int root, tL, tR;
    vector<Node> t;
    string s; // 1 - indexed

  public:
    Hashing() {}
    Hashing(string _s) : root(1), tL(1) {
        tR = _s.size();
        s = "#" + _s;
        t.resize(4 * tR);
        if(!pw[0].first) prec();
        build(root, tL, tR);
    }
    void point_upd(int i, char ch) {
        upd(root, tL, tR, i, ch);
        s[i] = ch;
    }
    T get_hash(int l, int r) { // 1 - indexed
        return query(root, tL, tR, l, r).forw * ipw[l - 1];
    }
    T rev_hash(int l, int r) { // 1 - indexed
        return query(root, tL, tR, l, r).rev * ipw[tR - r];
    }
    T get_hash() { 
        return get_hash(tL, tR); 
    }
    T rev_hash() { 
        return rev_hash(tL, tR); 
    }
    bool is_palindrome(int l, int r) {
        return get_hash(l, r) == rev_hash(l, r);
    }
};