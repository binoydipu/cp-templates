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
    vector<pair<int, int>> pre_hash, suf_hash; // 1 - indexed.
    int n;

    Hashing() {}
    Hashing(const char* _s) : Hashing(vector<char>(_s, _s + strlen(_s))) {}
    Hashing(const string& _s) : Hashing(vector<char>(_s.begin(), _s.end())) {}

    template<typename T>
    Hashing(const vector<T>& s) : n (s.size()) {
        if(!pw[0].first) prec();
        pre_hash.emplace_back(0, 0);
        for (int i = 0; i < n; i++) { // Generating prefix hash.
            pair<int, int> p;
            p.first = (pre_hash[i].first + 1LL * s[i] * pw[i].first % MOD1) % MOD1;
            p.second = (pre_hash[i].second + 1LL * s[i] * pw[i].second % MOD2) % MOD2;
            pre_hash.push_back(p);
        }
        suf_hash.assign(n + 2, {0, 0});
        for (int i = n - 1; i >= 0; i--) { // Generating suffix hash.
            suf_hash[i + 1].first = (suf_hash[i + 2].first + 1LL * s[i] * pw[n - i - 1].first % MOD1) % MOD1;
            suf_hash[i + 1].second = (suf_hash[i + 2].second + 1LL * s[i] * pw[n - i - 1].second % MOD2) % MOD2;
        }
    }
    pair<int, int> get_hash(int l, int r) { // 1 - indexed.
        assert(1 <= l && l <= r && r <= n);
        pair<int, int> ans;
        ans.first = (pre_hash[r].first - pre_hash[l - 1].first + MOD1) * 1LL * ipw[l - 1].first % MOD1;
        ans.second = (pre_hash[r].second - pre_hash[l - 1].second + MOD2) * 1LL * ipw[l - 1].second % MOD2;
        return ans;
    }
    pair<int, int> rev_hash(int l, int r) { // 1 - indexed.
        assert(1 <= l && l <= r && r <= n);
        pair<int, int> ans;
        ans.first = (suf_hash[l].first - suf_hash[r + 1].first + MOD1) * 1LL * ipw[n - r].first % MOD1;
        ans.second = (suf_hash[l].second - suf_hash[r + 1].second + MOD2) * 1LL * ipw[n - r].second % MOD2;
        return ans;
    }
    pair<int, int> get_hash() { return get_hash(1, n); }
    pair<int, int> rev_hash() { return rev_hash(1, n); }
};