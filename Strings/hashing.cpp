long long power(long long a, long long b, int mod) { // (a ^ b) % mod
    long long res = 1;
    while (b) {
        if (b & 1) res = (res * a) % mod;
        a = (a * a) % mod;
        b >>= 1;
    }
    return res;
}

const int P1 = 137, P2 = 277, N = 1e6 + 9;
const int MOD1 = 127657753, MOD2 = 987654319;
// const int P1 = 6529, P2 = 7057, N = 1e6 + 9;
// const int MOD1 = 2091573227LL, MOD2 = 2117566807LL;

int invP1, invP2;
pair<int, int> pw[N], ipw[N];

void prec() {
    pw[0] = {1, 1};
    for (int i = 1; i < N; i++) { 
        pw[i].first = 1LL * pw[i - 1].first * P1 % MOD1;
        pw[i].second = 1LL * pw[i - 1].second * P2 % MOD2;
    }

    invP1 = power(P1, MOD1 - 2, MOD1);
    invP2 = power(P2, MOD2 - 2, MOD2); 

    ipw[0] = {1, 1};
    for (int i = 1; i < N; i++) {  
        ipw[i].first = 1LL * ipw[i - 1].first * invP1 % MOD1;
        ipw[i].second = 1LL * ipw[i - 1].second * invP2 % MOD2;
    }
}
struct Hashing {
    int n;
    string s; // 0 - indexed.
    vector<pair<int, int>> hs; // 1 - indexed.
    Hashing() {}
    Hashing(string _s) {
        n = _s.size();
        s = _s;
        hs.assign(n + 1, make_pair(0, 0));
        for (int i = 0; i < n; i++) { // Generating prefix hash.
            hs[i + 1].first = (hs[i].first + 1LL * s[i] * pw[i].first % MOD1) % MOD1;
            hs[i + 1].second = (hs[i].second + 1LL * s[i] * pw[i].second % MOD2) % MOD2;
        }
    }
    pair<int, int> getHash(int l, int r) { // 1 - indexed.
        assert(1 <= l && l <= r && r <= n);
        pair<int, int> ans;
        ans.first = (hs[r].first - hs[l - 1].first + MOD1) * 1LL * ipw[l - 1].first % MOD1;
        ans.second = (hs[r].second - hs[l - 1].second + MOD2) * 1LL * ipw[l - 1].second % MOD2;
        return ans;
    }
    pair<int, int> getHash() {
        return getHash(1, n);
    }
};