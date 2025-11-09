const int MAXN = 1e5 + 5;
int gn[MAXN]; // Grundy num

// Generate all possible next splits of n
vector<vector<int>> get_splits(int n) {
    vector<vector<int>> splits;
    for (int d = 2; d <= n; d++) {
        int h = n / d;
        int mn = h - ((d - 1) / 2);
        if(mn < 1) break;
        int mx = mn + d - 1;
        int sum = (mx * (mx + 1)) / 2 - (mn * (mn - 1)) / 2;
        if(sum != n) continue;

        vector<int> sp;
        for (int i = mn; i <= mx; i++) sp.push_back(i);
        splits.push_back(sp);
    }
    return splits;
}

// Use if upper limit is known
// int mex(const vector<int>& v) {
//     static bool vis[128];
//     for (int x : v) if (x < 128) vis[x] = true;
//     int m = 0; while (m < 128 && vis[m]) m++;
//     for (int x : v) if (x < 128) vis[x] = false;
//     return m;
// }

int mex(vector<int> v) {
    sort(v.begin(), v.end());
    int m = 0;
    for (int x : v) {
        if (x == m) m++;
        else if (x > m) break;
    }
    return m;
}

// Grundy for splitting game
int grundy(int n) {
    if (~gn[n]) return gn[n];

    vector<int> reachable;
    for (const auto& nxt : get_splits(n)) {
        int xorsum = 0;
        for(int x : nxt) xorsum ^= grundy(x);
        reachable.push_back(xorsum);
    }
    return gn[n] = mex(reachable);
}

// XOR all piles (multi-pile Grundy)
int compute_nim_sum(const vector<int>& piles) {
    int xorsum = 0;
    for (int pile : piles) xorsum ^= grundy(pile);
    return xorsum;
}

// memset(gn, -1, sizeof gn);
// if from n, can reach these 2 states: -> (2, 3, 4) and (4, 5)
// gn[n] = MEX({ (gn[2] ^ gn[3] ^ gn[4]), (gn[4] ^ gn[5]) })
// gn[n] = 0: losing state, gn[n] = +ve: winning state
